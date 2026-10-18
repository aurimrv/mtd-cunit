#!/usr/bin/env python3
"""Generate a clear LaTeX report answering RQ1–RQ4 from analyze_rqs.py JSON."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path


def esc(s: object) -> str:
    t = str(s)
    placeholders = {
        "ε²": "<<<EPS2>>>",
        "ε": "<<<EPS>>>",
        "α": "<<<ALPHA>>>",
        "×": "<<<TIMES>>>",
        "Cramér": "<<<CRAMER>>>",
    }
    for u, ph in placeholders.items():
        t = t.replace(u, ph)
    t = (
        t.replace("–", "--")
        .replace("—", "---")
        .replace("’", "'")
        .replace("‘", "'")
        .replace("“", "``")
        .replace("”", "''")
        .replace("\\", "\\textbackslash{}")
        .replace("_", "\\_")
        .replace("%", "\\%")
        .replace("&", "\\&")
        .replace("#", "\\#")
    )
    return (
        t.replace("<<<EPS2>>>", "$\\varepsilon^2$")
        .replace("<<<EPS>>>", "$\\varepsilon$")
        .replace("<<<ALPHA>>>", "$\\alpha$")
        .replace("<<<TIMES>>>", "$\\times$")
        .replace("<<<CRAMER>>>", "Cram\\'er")
    )


def fmt_rate(r: float | None) -> str:
    if r is None:
        return "---"
    return f"{100.0 * r:.1f}\\%"


def fmt_num(x: float | None, nd: int = 3) -> str:
    if x is None:
        return "---"
    return f"{x:.{nd}f}"


def fmt_p(p: float | None) -> str:
    if p is None:
        return "---"
    if p < 1e-4:
        return f"{p:.2e}"
    return f"{p:.4f}"


def table_binary(rows: list[dict], success_label: str) -> str:
    lines = [
        "\\begin{tabular}{lrrr}",
        "\\toprule",
        f"Group & $n$ & {esc(success_label)} & Rate \\\\",
        "\\midrule",
    ]
    for r in rows:
        lines.append(
            f"{esc(r['group'])} & {r['n']} & {r['successes']} & {fmt_rate(r['rate'])} \\\\"
        )
    lines += ["\\bottomrule", "\\end{tabular}"]
    return "\n".join(lines)


def table_duration(rows: list[dict]) -> str:
    lines = [
        "\\begin{tabular}{lrrrrr}",
        "\\toprule",
        "Group & $n$ & Mean (s) & Median (s) & SD (s) & Max (s) \\\\",
        "\\midrule",
    ]
    for r in rows:
        if r["n"] == 0:
            continue
        lines.append(
            f"{esc(r['group'])} & {r['n']} & {fmt_num(r['mean_s'])} & "
            f"{fmt_num(r['median_s'])} & {fmt_num(r['sd_s'])} & {fmt_num(r['max_s'])} \\\\"
        )
    lines += ["\\bottomrule", "\\end{tabular}"]
    return "\n".join(lines)


def stats_box(title: str, st: dict, plain: str) -> str:
    if not st or not st.get("applicable"):
        reason = esc((st or {}).get("reason", "n/a"))
        return (
            f"\\paragraph{{{esc(title)}.}}\n"
            f"Test not applicable ({reason}).\n"
        )
    plain_tex = esc(plain).replace("alpha=", "$\\alpha$=")
    if st.get("test") == "chi_square":
        body = (
            f"Chi-square test of independence: "
            f"$\\chi^2={fmt_num(st['chi2'])}$, df$={st['df']}$, "
            f"$p={fmt_p(st['p_value'])}$, Cram\\'er's $V={fmt_num(st.get('cramers_v'))}$. "
            f"Minimum expected cell count $={fmt_num(st.get('min_expected'))}$. "
            f"\\emph{{{plain_tex}.}}\n"
        )
    else:
        body = (
            f"Kruskal--Wallis test: "
            f"$H={fmt_num(st['H'])}$, df$={st['df']}$, "
            f"$p={fmt_p(st['p_value'])}$, $\\varepsilon^2={fmt_num(st.get('epsilon_squared'))}$. "
            f"\\emph{{{plain_tex}.}}\n"
        )
    return f"\\paragraph{{{esc(title)}.}}\n{body}"


def top_groups(rows: list[dict], key: str = "rate", k: int = 5, reverse: bool = True) -> str:
    usable = [r for r in rows if r.get(key) is not None and r.get("n", 0) > 0]
    usable = sorted(usable, key=lambda r: r[key], reverse=reverse)[:k]
    parts = []
    for r in usable:
        if key == "rate":
            parts.append(f"{esc(r['group'])} ({fmt_rate(r['rate'])}, $n={r['n']}$)")
        else:
            parts.append(f"{esc(r['group'])} (mean {fmt_num(r.get('mean_s'))}s, $n={r['n']}$)")
    return "; ".join(parts) if parts else "none"


def emit_scope(scope: str, block: dict) -> str:
    if block.get("empty"):
        return f"\\subsection{{Scope: {esc(scope)}}}\nNo mutants recorded.\n"
    plain = block.get("plain_language") or {}
    d = block.get("descriptive") or {}
    bits = [
        f"\\subsection{{Scope: {esc(scope)}}}",
        f"Mutants analysed: ${d.get('n_killed', 0) + d.get('n_equivalent', 0)}$ "
        f"(killed ${d.get('n_killed', 0)}$, possible-equivalent ${d.get('n_equivalent', 0)}$). "
        f"Overall kill rate: {fmt_rate(d.get('overall_kill_rate'))}. "
        f"Collateral kills (killed while targeting another mutant): ${d.get('n_collateral_kills', 0)}$.",
        "",
        "\\subsubsection{RQ1 --- Kill capability by mutation operator}",
        esc(block["RQ1"]["question"]),
        "",
        "Highest kill rates: " + top_groups(block["RQ1"]["by_operator"], "rate", 8, True) + ".",
        "",
        "Lowest kill rates: " + top_groups(block["RQ1"]["by_operator"], "rate", 8, False) + ".",
        "",
        "\\begin{center}",
        table_binary(block["RQ1"]["by_operator"], "Killed"),
        "\\end{center}",
        stats_box(
            "Statistical test (status × operator)",
            block["RQ1"]["chi_square_status_by_operator"],
            plain.get("RQ1", ""),
        ),
        "",
        "\\subsubsection{RQ1.1 --- Kill capability by mutation category}",
        esc(block["RQ1_1"]["question"]),
        "",
        "\\begin{center}",
        table_binary(block["RQ1_1"]["by_category"], "Killed"),
        "\\end{center}",
        stats_box(
            "Statistical test (status × category)",
            block["RQ1_1"]["chi_square_status_by_category"],
            plain.get("RQ1_1", ""),
        ),
        "",
        "\\subsubsection{RQ2 --- Possible equivalents by operator}",
        esc(block["RQ2"]["question"]),
        "",
        "Highest equivalence rates: "
        + top_groups(block["RQ2"]["by_operator"], "rate", 8, True)
        + ".",
        "",
        "\\begin{center}",
        table_binary(block["RQ2"]["by_operator"], "Equivalent"),
        "\\end{center}",
        stats_box(
            "Statistical test (same contingency as RQ1; focus on EQUIVALENT share)",
            block["RQ2"]["chi_square_equivalent_by_operator"],
            plain.get("RQ2", ""),
        ),
        "",
        "\\subsubsection{RQ2.1 --- Possible equivalents by category}",
        esc(block["RQ2_1"]["question"]),
        "",
        "\\begin{center}",
        table_binary(block["RQ2_1"]["by_category"], "Equivalent"),
        "\\end{center}",
        stats_box(
            "Statistical test (status × category)",
            block["RQ2_1"]["chi_square_equivalent_by_category"],
            plain.get("RQ2_1", ""),
        ),
        "",
        "\\subsubsection{RQ3 --- Time to kill by operator}",
        esc(block["RQ3"]["question"]),
        "Metric: wall-clock seconds from mutant \\texttt{initial\\_time} to \\texttt{end\\_time}.",
        "",
        "Slowest mean kill times: "
        + top_groups(block["RQ3"]["by_operator"], "mean_s", 8, True)
        + ".",
        "",
        "\\begin{center}",
        table_duration(block["RQ3"]["by_operator"]),
        "\\end{center}",
        stats_box(
            "Statistical test (Kruskal--Wallis on kill duration by operator)",
            block["RQ3"]["kruskal_duration_by_operator"],
            plain.get("RQ3", ""),
        ),
        "",
        "\\subsubsection{RQ3.1 --- Time to kill by category}",
        "",
        "\\begin{center}",
        table_duration(block["RQ3_1"]["by_category"]),
        "\\end{center}",
        stats_box(
            "Statistical test (Kruskal--Wallis on kill duration by category)",
            block["RQ3_1"]["kruskal_duration_by_category"],
            plain.get("RQ3_1", ""),
        ),
        "",
        "\\subsubsection{RQ4 --- Time to possible equivalence by operator}",
        esc(block["RQ4"]["question"]),
        "",
        "\\begin{center}",
        table_duration(block["RQ4"]["by_operator"]),
        "\\end{center}",
        stats_box(
            "Statistical test (Kruskal--Wallis on equivalence duration by operator)",
            block["RQ4"]["kruskal_duration_by_operator"],
            plain.get("RQ4", ""),
        ),
        "",
        "\\subsubsection{RQ4.1 --- Time to possible equivalence by category}",
        "",
        "\\begin{center}",
        table_duration(block["RQ4_1"]["by_category"]),
        "\\end{center}",
        stats_box(
            "Statistical test (Kruskal--Wallis on equivalence duration by category)",
            block["RQ4_1"]["kruskal_duration_by_category"],
            plain.get("RQ4_1", ""),
        ),
        "",
        "\\subsubsection{RQ5 --- Are kill times equal across operators?}",
        esc(block["RQ5"]["question"]),
        "",
        "Null hypothesis: " + esc(block["RQ5"]["null_hypothesis"]),
        "",
        "Alternative: " + esc(block["RQ5"]["alternative"]),
        "",
        "\\textbf{Answer:} " + esc(plain.get("RQ5", "")),
        "",
        stats_box(
            "Kruskal--Wallis test of equal kill-time distributions across operators",
            block["RQ5"]["test"],
            plain.get("RQ5", ""),
        ),
        "",
        "\\subsubsection{RQ5.1 --- Are kill times equal across categories?}",
        esc(block["RQ5_1"]["question"]),
        "",
        "\\textbf{Answer:} " + esc(plain.get("RQ5_1", "")),
        "",
        stats_box(
            "Kruskal--Wallis test of equal kill-time distributions across categories",
            block["RQ5_1"]["test"],
            plain.get("RQ5_1", ""),
        ),
        "",
        "\\subsubsection{RQ6 --- Are equivalence-detection times equal across operators?}",
        esc(block["RQ6"]["question"]),
        "",
        "Null hypothesis: " + esc(block["RQ6"]["null_hypothesis"]),
        "",
        "Alternative: " + esc(block["RQ6"]["alternative"]),
        "",
        "\\textbf{Answer:} " + esc(plain.get("RQ6", "")),
        "",
        stats_box(
            "Kruskal--Wallis test of equal equivalence-detection times across operators",
            block["RQ6"]["test"],
            plain.get("RQ6", ""),
        ),
        "",
        "\\subsubsection{RQ6.1 --- Are equivalence-detection times equal across categories?}",
        esc(block["RQ6_1"]["question"]),
        "",
        "\\textbf{Answer:} " + esc(plain.get("RQ6_1", "")),
        "",
        stats_box(
            "Kruskal--Wallis test of equal equivalence-detection times across categories",
            block["RQ6_1"]["test"],
            plain.get("RQ6_1", ""),
        ),
    ]
    return "\n".join(bits)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--results-json", required=True)
    p.add_argument("--out-tex", required=True)
    args = p.parse_args()

    data = json.loads(Path(args.results_json).read_text(encoding="utf-8"))
    scopes = data.get("scopes") or {}
    # Prefer ALL first, then each program
    order = ["ALL"] + [s for s in sorted(scopes) if s != "ALL"]

    body = []
    for s in order:
        if s in scopes:
            body.append(emit_scope(s, scopes[s]))

    tex = rf"""\documentclass[11pt,a4paper]{{article}}
\usepackage[margin=2.2cm]{{geometry}}
\usepackage{{booktabs}}
\usepackage{{longtable}}
\usepackage{{hyperref}}
\usepackage{{xcolor}}
\usepackage{{microtype}}
\usepackage{{amsmath}}

\title{{Mutation-operator adequate suites:\\ statistical answers to RQ1--RQ6}}
\author{{Generated analysis pipeline}}
\date{{\today}}

\begin{{document}}
\maketitle

\begin{{abstract}}
This report summarises kill versus possible-equivalence outcomes and timings
from Proteum/IM unit-mutation experiments with CUnit data-driven tests.
Analyses are reported per program and for all programs pooled (mutant-level).
Statistical tests use $\\alpha={data.get('alpha', 0.05)}$.
RQ5--RQ6 test whether kill and equivalence-detection times are equal across
operators (and categories).
\end{{abstract}}

\section{{Research questions}}
\begin{{itemize}}
  \item \textbf{{RQ1}} Which mutation operators are more easily killed by the generated tests?
  \item \textbf{{RQ1.1}} Do mutation categories differ in kill capability?
  \item \textbf{{RQ2}} Which operators yield more possible-equivalent mutants?
  \item \textbf{{RQ2.1}} Which categories concentrate more possible equivalents?
  \item \textbf{{RQ3}} How long does it take to kill mutants of each operator?
  \item \textbf{{RQ3.1}} \ldots by mutation category?
  \item \textbf{{RQ4}} How long does it take to declare possible equivalence per operator?
  \item \textbf{{RQ4.1}} \ldots by mutation category?
  \item \textbf{{RQ5}} Are the times to kill mutants equal across all mutation operators?
  \item \textbf{{RQ5.1}} Are kill times equal across mutation categories?
  \item \textbf{{RQ6}} Are the times to detect possible-equivalent mutants equal across all operators?
  \item \textbf{{RQ6.1}} Are equivalence-detection times equal across mutation categories?
\end{{itemize}}

\section{{Methods (brief)}}
{esc(data.get('methods', {}).get('RQ1_RQ2', ''))}

{esc(data.get('methods', {}).get('RQ3_RQ4', ''))}

{esc(data.get('methods', {}).get('RQ5_RQ6', ''))}

{esc(data.get('methods', {}).get('aggregation', ''))}

{esc(data.get('methods', {}).get('categories', ''))}

\subsection{{Caveat on the current dataset}}
{esc(data.get('caveat', ''))}

Programs included: {', '.join(esc(p) for p in data.get('programs', []))}.
Total mutant records: ${data.get('n_total', 0)}$.

\section{{Results}}
{chr(10).join(body)}

\section{{How to read the verdicts}}
A result marked \emph{{statistically significant}} means the observed differences
across operators or categories are unlikely under the null of no association /
no location shift, at the chosen $\alpha$. It does not by itself prove a
causal advantage of the LLM; interpret together with rates, sample sizes, and
effect sizes (Cramér's $V$, $\varepsilon^2$).

\end{{document}}
"""
    out = Path(args.out_tex)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(tex, encoding="utf-8")
    print(json.dumps({"out_tex": str(out)}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
