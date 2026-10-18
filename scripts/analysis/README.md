# RQ analysis (RQ1–RQ4)

## What it answers

| RQ | Focus | Main statistic |
|----|--------|----------------|
| RQ1 / RQ1.1 | Kill capability by operator / category | Kill rate; χ² on status × group |
| RQ2 / RQ2.1 | Possible equivalents by operator / category | Equivalence rate; χ² |
| RQ3 / RQ3.1 | Time to kill by operator / category | Mean/median `duration_s`; Kruskal–Wallis |
| RQ4 / RQ4.1 | Time to declare EQUIVALENT | Same on equivalent mutants |
| RQ5 / RQ5.1 | Are kill times **equal** across operators / categories? | Kruskal–Wallis H0: equal distributions |
| RQ6 / RQ6.1 | Are equivalence-detection times **equal** across operators / categories? | Same H0 on EQUIVALENT mutants |

**Categories:** Constants (`u-C*`), Operators (`u-O*`), Statements (`u-S*`), Variables (`u-V*`).

**Scopes:** each program separately, plus `ALL` (all mutant rows pooled).

## Run

```bash
# from repo root
scripts/analysis/run_rq_analysis.sh programs-v1 programs-v1/_analysis
pdflatex -output-directory programs-v1/_analysis programs-v1/_analysis/rq_report.tex
```

Requires: `python3`, `pandas`, `numpy`, `scipy`.

## Caveat

Older batch runs used automated `ts_data` reuse (`composer-automated-proposer`).
The report states this. Future LLM-invented suites should be re-analysed the same way.
