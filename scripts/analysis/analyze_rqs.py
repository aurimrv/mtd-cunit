#!/usr/bin/env python3
"""
Statistical analysis for RQ1–RQ4 (operator and category levels).

Produces a JSON results file consumed by generate_latex_report.py.
"""

from __future__ import annotations

import argparse
import json
import math
import sys
from collections import defaultdict
from pathlib import Path
from typing import Any

import numpy as np
import pandas as pd

try:
    from scipy import stats
except ImportError as e:  # pragma: no cover
    raise SystemExit("scipy is required: pip install scipy pandas numpy") from e


def _safe_float(x: Any) -> float | None:
    if x is None or (isinstance(x, float) and math.isnan(x)):
        return None
    try:
        return float(x)
    except (TypeError, ValueError):
        return None


def summarise_binary(df: pd.DataFrame, group_col: str, success_col: str) -> list[dict]:
    rows = []
    for g, sub in df.groupby(group_col, dropna=False):
        n = len(sub)
        k = int(sub[success_col].sum())
        rows.append(
            {
                "group": str(g),
                "n": n,
                "successes": k,
                "rate": (k / n) if n else None,
                "failures": n - k,
            }
        )
    return sorted(rows, key=lambda r: (-(r["rate"] or -1), r["group"]))


def summarise_duration(df: pd.DataFrame, group_col: str, value_col: str) -> list[dict]:
    rows = []
    for g, sub in df.groupby(group_col, dropna=False):
        vals = [_safe_float(v) for v in sub[value_col].tolist()]
        vals = [v for v in vals if v is not None]
        if not vals:
            rows.append(
                {
                    "group": str(g),
                    "n": 0,
                    "mean_s": None,
                    "median_s": None,
                    "sd_s": None,
                    "min_s": None,
                    "max_s": None,
                }
            )
            continue
        arr = np.asarray(vals, dtype=float)
        rows.append(
            {
                "group": str(g),
                "n": int(arr.size),
                "mean_s": float(arr.mean()),
                "median_s": float(np.median(arr)),
                "sd_s": float(arr.std(ddof=1)) if arr.size > 1 else 0.0,
                "min_s": float(arr.min()),
                "max_s": float(arr.max()),
            }
        )
    return sorted(rows, key=lambda r: (r["mean_s"] is None, r["mean_s"] or 0, r["group"]))


def chi_square_independence(df: pd.DataFrame, group_col: str, outcome_col: str) -> dict:
    table = pd.crosstab(df[group_col], df[outcome_col])
    if table.shape[0] < 2 or table.shape[1] < 2:
        return {
            "test": "chi_square",
            "applicable": False,
            "reason": "need ≥2 groups and ≥2 outcomes",
            "table": table.to_dict(),
        }
    chi2, p, dof, expected = stats.chi2_contingency(table)
    n = table.to_numpy().sum()
    r, k = table.shape
    cramers_v = math.sqrt(chi2 / (n * (min(r - 1, k - 1)))) if n and min(r, k) > 1 else None
    return {
        "test": "chi_square",
        "applicable": True,
        "chi2": float(chi2),
        "df": int(dof),
        "p_value": float(p),
        "cramers_v": float(cramers_v) if cramers_v is not None else None,
        "n": int(n),
        "table": {str(i): {str(c): int(table.loc[i, c]) for c in table.columns} for i in table.index},
        "min_expected": float(np.min(expected)),
        "note": (
            "If min expected count < 5, interpret cautiously "
            "(consider Fisher's exact / Monte Carlo)."
        ),
    }


def kruskal_wallis(df: pd.DataFrame, group_col: str, value_col: str) -> dict:
    groups = []
    labels = []
    for g, sub in df.groupby(group_col):
        vals = [_safe_float(v) for v in sub[value_col].tolist()]
        vals = [v for v in vals if v is not None]
        if len(vals) >= 1:
            groups.append(vals)
            labels.append(str(g))
    if len(groups) < 2:
        return {
            "test": "kruskal_wallis",
            "applicable": False,
            "reason": "need ≥2 non-empty groups",
        }
    # Require at least one group with n>=2 for variance; Kruskal still runs with n=1 groups
    H, p = stats.kruskal(*groups)
    n = sum(len(g) for g in groups)
    k = len(groups)
    # epsilon-squared effect size
    eps2 = (H - k + 1) / (n - k) if n > k else None
    return {
        "test": "kruskal_wallis",
        "applicable": True,
        "H": float(H),
        "df": k - 1,
        "p_value": float(p),
        "epsilon_squared": float(eps2) if eps2 is not None else None,
        "n": int(n),
        "groups": labels,
        "group_ns": {lab: len(g) for lab, g in zip(labels, groups)},
    }


def analyze_scope(df: pd.DataFrame, scope_name: str) -> dict:
    """One program or 'ALL' pooled."""
    out: dict[str, Any] = {"scope": scope_name, "n_mutants": int(len(df))}
    if df.empty:
        out["empty"] = True
        return out

    # RQ1 / RQ1.1 — kill capability (outcome KILLED vs EQUIVALENT)
    out["RQ1"] = {
        "question": (
            "Which mutation operators are more easily killed "
            "(higher kill rate / fewer failures as EQUIVALENT)?"
        ),
        "by_operator": summarise_binary(df, "operator", "killed"),
        "chi_square_status_by_operator": chi_square_independence(
            df.assign(outcome=df["status"]), "operator", "outcome"
        ),
        "iterations_when_killed": summarise_duration(
            df[df["killed"] == 1], "operator", "number_of_iterations"
        ),
        "kruskal_iterations_killed_by_operator": kruskal_wallis(
            df[df["killed"] == 1], "operator", "number_of_iterations"
        ),
    }
    out["RQ1_1"] = {
        "question": "Is kill capability different across mutation categories?",
        "by_category": summarise_binary(df, "category", "killed"),
        "chi_square_status_by_category": chi_square_independence(
            df.assign(outcome=df["status"]), "category", "outcome"
        ),
        "kruskal_iterations_killed_by_category": kruskal_wallis(
            df[df["killed"] == 1], "category", "number_of_iterations"
        ),
    }

    # RQ2 / RQ2.1 — equivalents concentration
    out["RQ2"] = {
        "question": "Which operators generate more possible-equivalent mutants?",
        "by_operator": summarise_binary(df, "operator", "equivalent"),
        "chi_square_equivalent_by_operator": chi_square_independence(
            df.assign(outcome=df["status"]), "operator", "outcome"
        ),
    }
    out["RQ2_1"] = {
        "question": "Which categories concentrate more possible equivalents?",
        "by_category": summarise_binary(df, "category", "equivalent"),
        "chi_square_equivalent_by_category": chi_square_independence(
            df.assign(outcome=df["status"]), "category", "outcome"
        ),
    }

    killed = df[df["killed"] == 1].copy()
    equiv = df[df["equivalent"] == 1].copy()

    # RQ3 / RQ3.1 — time to kill
    out["RQ3"] = {
        "question": "How long does it take to kill mutants of each operator?",
        "metric": "duration_s (mutant end_time − initial_time)",
        "by_operator": summarise_duration(killed, "operator", "duration_s"),
        "kruskal_duration_by_operator": kruskal_wallis(killed, "operator", "duration_s"),
    }
    out["RQ3_1"] = {
        "question": "How long does it take to kill mutants of each category?",
        "by_category": summarise_duration(killed, "category", "duration_s"),
        "kruskal_duration_by_category": kruskal_wallis(killed, "category", "duration_s"),
    }

    # RQ4 / RQ4.1 — time to declare possible equivalence
    out["RQ4"] = {
        "question": (
            "How long does it take to detect possible equivalence "
            "(until EQUIVALENT after LLM_GEN_MODELS is exhausted)?"
        ),
        "metric": "duration_s (mutant end_time − initial_time)",
        "by_operator": summarise_duration(equiv, "operator", "duration_s"),
        "kruskal_duration_by_operator": kruskal_wallis(equiv, "operator", "duration_s"),
    }
    out["RQ4_1"] = {
        "question": "Equivalence-detection time by mutation category?",
        "by_category": summarise_duration(equiv, "category", "duration_s"),
        "kruskal_duration_by_category": kruskal_wallis(equiv, "category", "duration_s"),
    }

    # RQ5 / RQ5.1 — equality of kill times across operators / categories
    kw_kill_op = out["RQ3"]["kruskal_duration_by_operator"]
    kw_kill_cat = out["RQ3_1"]["kruskal_duration_by_category"]
    out["RQ5"] = {
        "question": (
            "Are the times to kill mutants equal across all mutation operators?"
        ),
        "null_hypothesis": (
            "H0: the distributions of kill duration_s are the same for every operator."
        ),
        "alternative": "H1: at least one operator differs in kill-time distribution.",
        "test": kw_kill_op,
        "descriptive_by_operator": out["RQ3"]["by_operator"],
    }
    out["RQ5_1"] = {
        "question": (
            "Are the times to kill mutants equal across all mutation categories?"
        ),
        "null_hypothesis": (
            "H0: the distributions of kill duration_s are the same for every category."
        ),
        "alternative": "H1: at least one category differs in kill-time distribution.",
        "test": kw_kill_cat,
        "descriptive_by_category": out["RQ3_1"]["by_category"],
    }

    # RQ6 / RQ6.1 — equality of equivalence-detection times
    kw_eq_op = out["RQ4"]["kruskal_duration_by_operator"]
    kw_eq_cat = out["RQ4_1"]["kruskal_duration_by_category"]
    out["RQ6"] = {
        "question": (
            "Are the times to detect possible-equivalent mutants equal "
            "across all mutation operators?"
        ),
        "null_hypothesis": (
            "H0: the distributions of equivalence-detection duration_s "
            "are the same for every operator."
        ),
        "alternative": (
            "H1: at least one operator differs in equivalence-detection time."
        ),
        "test": kw_eq_op,
        "descriptive_by_operator": out["RQ4"]["by_operator"],
    }
    out["RQ6_1"] = {
        "question": (
            "Are the times to detect possible-equivalent mutants equal "
            "across all mutation categories?"
        ),
        "null_hypothesis": (
            "H0: the distributions of equivalence-detection duration_s "
            "are the same for every category."
        ),
        "alternative": (
            "H1: at least one category differs in equivalence-detection time."
        ),
        "test": kw_eq_cat,
        "descriptive_by_category": out["RQ4_1"]["by_category"],
    }

    out["descriptive"] = {
        "n_killed": int(df["killed"].sum()),
        "n_equivalent": int(df["equivalent"].sum()),
        "overall_kill_rate": float(df["killed"].mean()) if len(df) else None,
        "n_collateral_kills": int(df["collateral"].sum()),
        "operators": sorted(df["operator"].unique().tolist()),
        "categories": sorted(df["category"].unique().tolist()),
    }
    return out


def interpret_p(p: float | None, alpha: float = 0.05) -> str:
    if p is None:
        return "not applicable"
    if p < alpha:
        return f"statistically significant at alpha={alpha:g} (p={p:.4g})"
    return f"not statistically significant at alpha={alpha:g} (p={p:.4g})"


def interpret_equality(st: dict | None, alpha: float = 0.05) -> str:
    """Plain answer for H0: times equal across groups."""
    if not st or not st.get("applicable"):
        return "equality test not applicable"
    p = st.get("p_value")
    if p is None:
        return "equality test not applicable"
    if p < alpha:
        return (
            f"reject equality at alpha={alpha:g} (p={p:.4g}): "
            "times are not the same across groups"
        )
    return (
        f"cannot reject equality at alpha={alpha:g} (p={p:.4g}): "
        "no significant evidence that times differ across groups"
    )


def add_plain_language(results: dict) -> None:
    """Attach short human-readable verdicts for the LaTeX report."""
    alpha = float(results.get("alpha") or 0.05)
    for scope, block in results.get("scopes", {}).items():
        if block.get("empty"):
            continue
        notes = {}
        for rq in ("RQ1", "RQ1_1", "RQ2", "RQ2_1"):
            key = {
                "RQ1": "chi_square_status_by_operator",
                "RQ1_1": "chi_square_status_by_category",
                "RQ2": "chi_square_equivalent_by_operator",
                "RQ2_1": "chi_square_equivalent_by_category",
            }[rq]
            st = block[rq].get(key) or {}
            notes[rq] = interpret_p(
                st.get("p_value") if st.get("applicable") else None, alpha
            )
        for rq, k in (
            ("RQ3", "kruskal_duration_by_operator"),
            ("RQ3_1", "kruskal_duration_by_category"),
            ("RQ4", "kruskal_duration_by_operator"),
            ("RQ4_1", "kruskal_duration_by_category"),
        ):
            st = block[rq].get(k) or {}
            notes[rq] = interpret_p(
                st.get("p_value") if st.get("applicable") else None, alpha
            )
        notes["RQ5"] = interpret_equality(block.get("RQ5", {}).get("test"), alpha)
        notes["RQ5_1"] = interpret_equality(block.get("RQ5_1", {}).get("test"), alpha)
        notes["RQ6"] = interpret_equality(block.get("RQ6", {}).get("test"), alpha)
        notes["RQ6_1"] = interpret_equality(block.get("RQ6_1", {}).get("test"), alpha)
        block["plain_language"] = notes


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--records-csv", required=True)
    p.add_argument("--out-json", required=True)
    p.add_argument("--alpha", type=float, default=0.05)
    args = p.parse_args()

    df = pd.read_csv(args.records_csv)
    if "duration_s" not in df.columns and "duration_ms" in df.columns:
        df["duration_s"] = df["duration_ms"] / 1000.0

    scopes: dict[str, Any] = {}
    for prog, sub in df.groupby("program"):
        scopes[str(prog)] = analyze_scope(sub, str(prog))
    scopes["ALL"] = analyze_scope(df, "ALL")

    results = {
        "alpha": args.alpha,
        "n_total": int(len(df)),
        "programs": sorted(df["program"].unique().tolist()),
        "caveat": (
            "Existing collected runs may include automated reuse of ts_data rows "
            "(llm_name composer-automated-proposer). Future runs should use "
            "LLM-invented mutation-specific tests only; re-run this analysis then."
        ),
        "methods": {
            "RQ1_RQ2": (
                "Chi-square test of independence on contingency tables "
                "status × operator (or category). Effect size: Cramér's V."
            ),
            "RQ3_RQ4": (
                "Kruskal–Wallis rank test on duration_s across operators/categories "
                "(non-parametric; durations are skewed). Effect size: ε². "
                "RQ3/RQ4 report descriptive timings; RQ5/RQ6 state the equality hypotheses."
            ),
            "RQ5_RQ6": (
                "RQ5/RQ5.1: H0 = kill times equal across operators/categories. "
                "RQ6/RQ6.1: H0 = equivalence-detection times equal across operators/categories. "
                "Both use the same Kruskal–Wallis tests as RQ3/RQ4; reject H0 if p < alpha."
            ),
            "aggregation": (
                "Per-program analyses use that program's mutants only. "
                "ALL pools all programs (mutant-level rows), then reports "
                "group means/rates; overall kill rate is the unweighted mean "
                "across mutant rows (not an average of program rates)."
            ),
            "categories": (
                "Constants (u-C*), Operators (u-O*), Statements (u-S*), "
                "Variables (u-V*) from Proteum unit-operator families."
            ),
        },
        "scopes": scopes,
    }
    add_plain_language(results)

    out = Path(args.out_json)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"out_json": str(out), "n_total": results["n_total"], "programs": results["programs"]}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
