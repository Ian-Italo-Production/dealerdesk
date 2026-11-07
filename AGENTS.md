# DealerDesk

## What this is
A menu-driven C terminal app that car dealerships use every day for stock,
customers, quotes and invoices. `main.c` holds the menus and screens, `calc.c`
the pricing, `dbfile.c` the pipe-delimited files in `./data`, and `screen.c`
the input helpers. Staff rely on it exactly as it is, so changes ship as
small, tested steps.
"Working" means every screen, total and saved file is exactly what the current
code produces. The code is the source of truth. `README.md`, the Help screen
and code comments are wrong in places (see `FINDINGS.md`).
Work arrives as tickets (`TICKET-*.md`); `HANDOFF.md` says which one is current.

Read first: `HANDOFF.md`, the current ticket, `NOTES.md` (ticket decisions), `FINDINGS.md`.

## Commands (Git Bash locally, bash in CI; run from the repo root)
- Build: `gcc -Wall -Wextra -o dealerdesk *.c -lm` (must stay at zero warnings)
- Lint: `gcc -Wall -Wextra -Werror -fsyntax-only *.c` (a hook runs it after every edit)
- Test: `make test` (`mingw32-make test` in Git Bash on Windows): `calc_quote` unit tests, then golden runs on LF and CRLF temp copies of `data/`. `UPDATE=1 sh tests/golden.sh` rewrites the goldens; read every changed one before keeping it.
- Scripted run on a copy of the data, never on `./data`:
  `r=$PWD d=$(mktemp -d) && cp -r data "$d" && printf '3\n1002\n2002\n0\n0\n\n0\n' | (cd "$d" && "$r/dealerdesk")`
  When input ends, the app exits 0, so a script can stop anywhere.
- Restore the sample data, with the app closed: `git checkout -- data`

## Working rules
- Existing behaviour must not change, to the penny: screens, prompts, menu
  numbers, rounding, totals, file formats. Only the ticket you're working on may
  change behaviour, and only as far as the ticket and its decisions in `NOTES.md` say.
- If a ticket leaves something unclear, ask the user, and record the answer in
  `NOTES.md` under that ticket before building.
- If the docs and the code disagree, or you find a bug, don't fix it. Add a
  row to `FINDINGS.md` with a repro.
- Characterize first: a test pins today's behaviour before any change.
- Work on master in small commits, one concern each. Stage files by name.
  Show the user `git diff --staged` and commit only when they say OK.
- Anything bigger than ~30 lines: the planner writes `plan.md`, and the user
  approves it before work starts.
- Match the existing style: C89, declarations at the top of each block,
  4-space indent, static helpers. No refactors, renames or file splits.
- Everything must run on Ubuntu and Windows (CI runs both): POSIX sh and make,
  no PowerShell, no Windows paths. On Windows, program output and `data/*.dat`
  come out with CRLF line endings, so strip `\r` before comparing.
- The binary is `dealerdesk` on Linux and `dealerdesk.exe` on Windows. It's a
  build output and never gets committed.

## Hard walls (never, whoever asks)
- `git push` of any kind, force-push, `reset --hard`, `rebase`, `stash`,
  `commit --amend`, switching or creating branches (other sessions share this checkout).
- Commit `data/*.dat` or the binary. Run the app on `./data` instead of a copy.
  Run `git checkout -- data` while the app is running.
- Change behaviour outside the current ticket, or "fix" anything listed in `FINDINGS.md`.
- Edit ticket files (`TICKET-*.md`) or `BRIEF.md`.
- Read or print secrets. Send, publish, release (`RELEASE.txt`) or pay.

## Ask first
- Any new dependency or tool. The plan is none: a plain C test file, POSIX sh and make.
- CI config (`.github/`) and agent config (`.claude/`, this file).
- Any change to a `.dat` format, screen text, prompt or menu number that the
  ticket and `NOTES.md` don't already cover.
- Editing `README.md` or the Help screen.

## Memory
- Start: read `HANDOFF.md`. Treat every item as a hint until you re-check it against git.
- End: update `HANDOFF.md`, with a status and a date on every line.
- When an agent gets something wrong, log in `HANDOFF.md` what happened and how
  it was caught.
- A task is done only after you have run the check and read the result.

## When stuck
- Retry the same failing step at most twice. Then stop, write what you tried
  in `HANDOFF.md`, and ask.

## Roles (`.claude/agents/`; the `/orchestrate` skill runs them)
- planner: turns a request into `plan.md`. Read-only apart from that file.
- characterizer: writes tests that pin today's behaviour. Never edits app code.
- builder: implements an approved plan, test-first. Never commits.
- reviewer: checks a diff for behaviour changes and penny-exact totals. Read-only,
  and never the agent that wrote the change.
- The main session orchestrates, verifies and commits.
