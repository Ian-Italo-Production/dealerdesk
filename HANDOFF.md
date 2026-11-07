# Handoff

Format: - [status] YYYY-MM-DD who: what. Status is todo, in progress, blocked, or done, verified.

## Now
- (nothing in progress) 2026-11-07: step 3 (TICKET-142) done and verified, CI green. Step 4 is next.

## Next
- [todo] 2026-11-07 orchestrator: Step 4, final `NOTES.md` (max 2 pages). It must
  include a time an agent got something wrong and how it was caught; see the Log.
  - Fill "What I changed and why", "How I worked with the agents", "What I'd do next" from the
    step 1-3 entries below; the TICKET-142 decisions (incl. "Screen and file details") stay as they are.
  - `plan.md` (untracked) is the step 3 plan; it is never committed.

## Blocked

## Done (verified)
- [done, verified] 2026-11-07 orchestrator: Step 3, TICKET-142 fleet discount.
  - CI green on the user's push of 5075e11: https://github.com/Ian-Italo-Production/dealerdesk/actions/runs/42406032232
    Both jobs (ubuntu-24.04 gcc 13.3.0 /bin/sh dash; windows-latest mingw32-make): `test_calc: 97 checks,
    0 failed`, 20 golden PASS (fleet_type/quote/sell on LF and CRLF), 0 FAIL, no compiler `warning:`
    (the only `warning:` text is the workflow's own grep lines). Read from the job logs.
  - Commits:
  1733746 (goldens stock, help, two-run reload; golden.sh runs `<name>.in2` after a restart),
  1165af6 (FINDINGS rows 7-8, strtok loss made permanent by a save), ba6e921 (C1 calc_quote 4% for F,
  salesman % after it, fees not discounted; test_calc 97 checks), e73936a (C2 Customers option 4,
  Fleet label; golden fleet_type), d63dea0 (NOTES: the user's screen and file answers), 3dd09e9 (C3 Add
  customer Fleet question), ec2e796 (C4 Fleet discount line on quote and preview; golden fleet_quote),
  834bf11 (C5 12th invoices.dat field, View invoice Fleet line; two-run golden fleet_sell), plus the
  FINDINGS line-reference and HANDOFF commits after it.
  - Each test was seen red on the commit before it, then committed with its code. Every commit had a
    fresh reviewer's APPROVE and a local build, lint and test with zero warnings.
  - Fresh clone of 834bf11 (core.autocrlf=true, CRLF data): `mingw32-make build lint test` exit 0,
    97 checks 0 failed, 20 golden PASS under sh and dash, zero `warning:`.
  - Golden trace from 1733746 to 834bf11: quote, invoices, stock and help .out unchanged; customers,
    reload and sell change only by the `4. Change customer type` menu line and `|0.00` on invoices.dat
    lines (NOTES decisions). Non-fleet R/T calc results bit-identical (reviewers: 317M comparisons).
  - Acceptance: fleet quote shows "Fleet discount" and the right total (fleet_quote: 13747.96,
    10001.30, 18661.24); non-fleet quotes and invoices unchanged; old 11-field invoices.dat loads with
    no conversion and displays as before (invoices.out unchanged).
  - Rollback, by the orchestrator on a scratch copy: a72ed67's binary on data written by 834bf11's
    code lists Greenway (F) as Retail, quotes it with no fleet discount (1003: 19429.00), views 50233
    with Discounts -1489.20 / Net 11260.80 / TOTAL 13747.96 and the other invoices with their totals.
    When it re-saves, it drops only the 12th field and keeps 2008 as `F`; the new binary then reads
    those lines as fleet 0 (no Fleet line, -1489.20, 13747.96).
  - Not covered by a golden: a fleet sale at 0% (`Discounts -0.00`, checked by hand by builder and
    reviewer) and a save after a restart (FINDINGS strtok permanence).
  - [done, verified] 2026-11-07: caa6169, globals.h CUSTOMER type comment now lists `F = fleet`
    (user approved). Comment only: reviewer found `gcc -E` output and objects byte-identical; local
    build, lint, test: 97 checks, 20 PASS, zero warnings. Not pushed yet; goes with the step 4 push.
- [done, verified] 2026-11-07 orchestrator: Step 2, CI. Commits be2b31d (`.github/workflows/ci.yml`:
  push to master + workflow_dispatch; matrix ubuntu-24.04/`make` and windows-latest/`mingw32-make`,
  `shell: bash`, fail-fast off; checkout pinned to v7.0.1 SHA; Tools, Build, Lint, Test; Build and
  Test fail on any `warning:`) and 5f094c7 (removed the temporary `plant_regression` input).
  - Green, final workflow: https://github.com/Ian-Italo-Production/dealerdesk/actions/runs/42399359997
    (push of 5f094c7; both jobs: 61 checks, 8 golden PASS, no `warning:`). Read from the job logs.
  - Green, first push: https://github.com/Ian-Italo-Production/dealerdesk/actions/runs/42398695952 (be2b31d).
  - Red on purpose: https://github.com/Ian-Italo-Production/dealerdesk/actions/runs/42398786961
    (dispatch with a 1p TOTAL bug planted in main.c:351 on the runner only). Both jobs: Tools, Build,
    Lint green; Test exit 2 with 61 checks 0 failed, FAIL quote and sell (LF+CRLF), 28 diff lines, all TOTAL.
    So dash keeps golden.sh's exit code through its EXIT trap, and nothing broken was committed.
  - Runners: Ubuntu 24.04 gcc 13.3.0, GNU Make 4.3, /bin/sh = dash, no core.autocrlf (all LF).
    windows-2025-vs2026 gcc 15.2.0 and mingw32-make 4.4.1 from C:\mingw64\bin (not Strawberry),
    Git's sh, core.autocrlf=true from the system gitconfig, as on the user's machine (data/*.dat CRLF).
    First real Linux run of the goldens and of CRLF data through `strcspn`: all pass, trade5 too.
  - The gh token now has the `workflow` scope (the user ran `gh auth refresh -s workflow`).
- [done, verified] 2026-11-07 github-setup: GitHub CLI 2.103.3 installed with winget. It was not on
  Git Bash's PATH in that session, so call `"/c/Program Files/GitHub CLI/gh.exe"`. Signed in as
  Ian-Italo-Production (the user approved it in the browser; token in the Windows keyring), and
  `gh auth setup-git` makes git use it over HTTPS. Created private repo
  https://github.com/Ian-Italo-Production/dealerdesk as remote `mine`; the user pushed master
  (the agent's push was denied). Verified: PRIVATE, default branch master, `mine/master` = local
  master = f90dbab, no other refs on `mine`, `origin` unchanged. No workflow yet (step 2).
- [done, verified] 2026-11-07 orchestrator: Step 1, safety net. Commits 6383123 (Makefile
  build/lint, .gitignore), 9cbe9b0 (.gitattributes), 45ba1f2 (calc_quote unit tests, 61 checks),
  0fd82f5 (goldens quote, invoices, sell, customers, each on LF and CRLF data), 31e13ca
  (AGENTS.md test line). Verified in a fresh clone with core.autocrlf=true: `mingw32-make build
  lint test` exit 0, zero warnings, 61 checks and 8 golden PASS, `data/*.dat` md5 unchanged,
  no app code or data changed. Not yet run on Ubuntu (step 2).
- [done, verified] 2026-11-07 setup-agents: agent kit (AGENTS.md, CLAUDE.md, this file,
  4 subagents, the orchestrate skill, settings.json with the lint hook). Build, lint
  and scripted-run commands each ran and passed.

## Decisions
- 2026-11-07 user: work on master in small commits; every commit is shown first; agents never push.
- 2026-11-07 user: roles are planner, characterizer, builder and reviewer; the main session orchestrates.
- Ticket decisions live in `NOTES.md`; docs-vs-code differences in `FINDINGS.md`.
- 2026-11-07 user: approved `plan.md` for step 1 with the recommended answers:
  `data/*.dat` not pinned in `.gitattributes` (LF and CRLF golden runs prove both load);
  unit tests add 4 edge cases (25% capped, -3% to 0, trade + 5%, 2.5% rounding);
  small golden set now (quote, invoices, sell, customers), Stock/Help/reload goldens in step 3;
  AGENTS.md "Test:" line becomes `make test` in its own commit after the goldens.
- 2026-11-07 user: fix two `golden.sh` gaps before commit d: strip `\r` from stdout only on
  Windows (`OS=Windows_NT`), and add PIPE to the trap.
- 2026-11-07 user: one-time exception for the GitHub setup only: install gh and push master to
  `mine`. The hard walls stand again: agents never push, to `mine` or `origin`. `origin`
  (felipeamarante/dealerdesk) is someone else's repo. Local master tracks `mine/master`, so a
  plain `git push` goes to `mine`.
- 2026-11-07 user: step 2 plan.md answers: remove the `plant_regression` dispatch input after
  the red proof (own commit); pin actions/checkout to the v7.0.1 SHA; Ubuntu runner pinned to
  `ubuntu-24.04` (not ubuntu-latest); plant the 1p bug in main.c:351, not calc.c; the
  orchestrator may start the proof run with `gh workflow run` on master after the user pushes.
- 2026-11-07 user: looser agent rules (replaces "every commit is shown first"). Stop only for:
  anything the ticket and `NOTES.md` don't settle (screen line, prompt, menu number, `.dat`
  format, rounding rule); a test or golden change no `NOTES.md` decision explains, or a test
  failing on unchanged code; a new dependency or tool; editing README.md or the Help screen;
  agent config; anything irreversible or outward-facing. Everything else without asking:
  plan.md needs approval only with open questions; characterize, build, review; commit small
  one-concern commits once build, lint and test pass and a fresh reviewer says APPROVE, then
  show the commit list; edit CI config; update HANDOFF; read-only `gh run list/view/watch`,
  `git fetch`, `git ls-remote`. Hard walls unchanged: agents never push; the user pushes
  master to `mine` when told the exact command, then the orchestrator reads the CI run.

- 2026-11-07 user: step 3 plan.md answers: the Recommended option for every open question (change
  type option 4 R/T/F, "Fleet discount" line, Fleet question after Trade=N, separate line on View
  invoice, `|%.2f` on every invoices.dat line, nearest-penny rounding). Recorded in NOTES.md (d63dea0).

## Log (newest first, one line each)
- 2026-11-07 orchestrator: got it wrong. Left the globals.h `type` comment saying only R and T after C2 made F valid; the builder flagged it twice and I kept deferring it as outside the commit under review. Caught by the user asking why; fixed in caa6169.
- 2026-11-07 orchestrator (step 2 handoff): got it wrong. HANDOFF predicted the `quote` golden would change; it can't, because `data/*.dat` is never committed and the sample Greenway stays R. Caught by the step 3 planner; quote.out stayed byte-identical and was a stop condition throughout.
- 2026-11-07 orchestrator: got it wrong. Committed C1 (ba6e921) and C2 (e73936a) while the user's TICKET-142 screen decisions were still uncommitted in NOTES.md (its review had BLOCKed twice on wording), so e73936a says "as NOTES decides" before HEAD's NOTES held it. Caught by the C3 reviewer; NOTES committed as d63dea0 before C3. The code matched the user's answers throughout.
- 2026-11-07 orchestrator: got it wrong. My first NOTES wording ("next line, no blank line before it") described a terminal, not the piped goldens, and left the sign of the Fleet amount and the label scope open. Caught by two NOTES reviewers (fleet_type.out:44 contradicted it); fixed to their exact wording before any golden depended on it.
- 2026-11-07 builder: got it wrong in its report. Its "new file" listing for commit 2 showed the Test grep as `grep 'warning:` test.log` (backtick for quote), which would break the step. Caught by the orchestrator grepping the real ci.yml (line 52 correct, diff deletions only); the file was fine, only the report was wrong.
- 2026-11-07 orchestrator: got it wrong. Planned and committed the workflow without checking the gh token could push it; the user's `git push mine master` of be2b31d was rejected (`refusing to allow an OAuth App to create or update workflow ... without workflow scope`; token scopes were gist, read:org, repo). Caught by `git ls-remote mine` still showing f90dbab and no runs, then reading the user's terminal. Fix is the user's: `gh auth refresh -s workflow`, then push again.
- 2026-11-07 github-setup: got it wrong. Piped `gh auth login --web` through `grep` to hide token lines; grep buffered into the output file, so the one-time device code never showed. Caught by reading the empty output; stopped it and restarted with `grep --line-buffered`. Also added winget's `--accept-source-agreements --accept-package-agreements` beyond the command given; told the user after.
- 2026-11-07 orchestrator: got it wrong. My proof for the CR fix (`OS= sh tests/golden.sh` must fail on Windows) proved nothing: Git Bash's sed drops `\r`, so it passed. Caught by the characterizer seeing a pass where a fail was expected; proven instead with a `sed -b` shim (8 FAIL) and a reviewer's planted `\r`.
- 2026-11-07 characterizer: got it wrong. The first `golden.sh` stripped every `\r`, hiding a CR leak on Ubuntu (plan.md's Risks line overstated the CRLF check), and leaked a temp dir on SIGPIPE under dash. Caught by the commit-d reviewer (reading dbfile.c; `dash tests/golden.sh | head`). Fixed before 0fd82f5, with the user's OK.
- 2026-11-07 planner: a dry-run keystroke script desynced after "Vehicle is already sold" (that path skips the Customer prompt). Caught by reading the output; every golden was then read by the characterizer, a reviewer and the orchestrator.
- 2026-11-07 reviewer: left temp dir `C:\Users\ianit\AppData\Local\Temp\tmp.DHcSmwhPW1` (its rm was denied); two older `/tmp/tmp.*` dirs from before step 1 also remain. For the user to remove.
- 2026-11-07 setup-agents: kit written. No test command exists yet, so step 1 comes first.
