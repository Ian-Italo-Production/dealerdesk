# Handoff

Format: - [status] YYYY-MM-DD who: what. Status is todo, in progress, blocked, or done, verified.

## Now
- (nothing in progress)

## Next
- [todo] 2026-11-07 orchestrator: Step 2, CI. GitHub Actions on Ubuntu and Windows
  running build (zero warnings), lint and test. Ask first: CI config.
  - Ubuntu: `make build lint test`. Windows: Git Bash with `mingw32-make`; recipes need Git's `sh` on PATH.
  - First real Linux run of `tests/golden.sh` (dash) and of CRLF data through `strcspn`.
    Until now Linux was only simulated (dash under Git Bash, a `sed -b` shim).
  - If `test_calc` case trade5 (494.775 -> 494.78) fails on a runner, that is a real
    floating-point platform difference in the app, not a broken test.
  - The GitHub repo for CI is remote `mine` (private, Ian-Italo-Production/dealerdesk).
    New commits reach it only when the user pushes.
- [todo] 2026-11-07 orchestrator: Step 3, TICKET-142 test-first, as decided in `NOTES.md`.
  - First add the goldens deferred from step 1: Stock, Help, and a two-run reload golden
    (needed for the new invoice field, and the restart half of the FINDINGS strtok bug).
  - `golden.sh` strips `\r` from `.dat` dumps everywhere, so on Linux a `\r` written into a
    saved file is only caught if it also reaches the screen. Mind this if the new field is text.
  - The `customers` and `quote` goldens will change on purpose; each changed golden needs the user's OK.
- [todo] 2026-11-07 orchestrator: Step 4, final `NOTES.md` (max 2 pages). It must
  include a time an agent got something wrong and how it was caught; see the Log.

## Blocked

## Done (verified)
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

## Log (newest first, one line each)
- 2026-11-07 github-setup: got it wrong. Piped `gh auth login --web` through `grep` to hide token lines; grep buffered into the output file, so the one-time device code never showed. Caught by reading the empty output; stopped it and restarted with `grep --line-buffered`. Also added winget's `--accept-source-agreements --accept-package-agreements` beyond the command given; told the user after.
- 2026-11-07 orchestrator: got it wrong. My proof for the CR fix (`OS= sh tests/golden.sh` must fail on Windows) proved nothing: Git Bash's sed drops `\r`, so it passed. Caught by the characterizer seeing a pass where a fail was expected; proven instead with a `sed -b` shim (8 FAIL) and a reviewer's planted `\r`.
- 2026-11-07 characterizer: got it wrong. The first `golden.sh` stripped every `\r`, hiding a CR leak on Ubuntu (plan.md's Risks line overstated the CRLF check), and leaked a temp dir on SIGPIPE under dash. Caught by the commit-d reviewer (reading dbfile.c; `dash tests/golden.sh | head`). Fixed before 0fd82f5, with the user's OK.
- 2026-11-07 planner: a dry-run keystroke script desynced after "Vehicle is already sold" (that path skips the Customer prompt). Caught by reading the output; every golden was then read by the characterizer, a reviewer and the orchestrator.
- 2026-11-07 reviewer: left temp dir `C:\Users\ianit\AppData\Local\Temp\tmp.DHcSmwhPW1` (its rm was denied); two older `/tmp/tmp.*` dirs from before step 1 also remain. For the user to remove.
- 2026-11-07 setup-agents: kit written. No test command exists yet, so step 1 comes first.
