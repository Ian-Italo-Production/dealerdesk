# Handoff

Format: - [status] YYYY-MM-DD who: what. Status is todo, in progress, blocked, or done, verified.

## Now
- (nothing in progress)

## Next
- [todo] 2026-11-07 orchestrator: Step 1, safety net (set up tests). Run it with `/orchestrate`.
  - Makefile with `build`, `lint` and `test` targets (`mingw32-make` on Windows).
  - `.gitignore` for the binary; `.gitattributes` to pin line endings.
  - `calc_quote` unit tests pinned to invoices 50230-50232, to the penny.
  - Golden end-to-end tests: piped keystroke scripts on a temp copy of `data/`.
- [todo] 2026-11-07 orchestrator: Step 2, CI. GitHub Actions on Ubuntu and Windows
  running build (zero warnings), lint and test. Ask first: CI config.
- [todo] 2026-11-07 orchestrator: Step 3, TICKET-142 test-first, as decided in `NOTES.md`.
- [todo] 2026-11-07 orchestrator: Step 4, final `NOTES.md` (max 2 pages). It must
  include a time an agent got something wrong and how it was caught; see the Log.

## Blocked

## Done (verified)
- [done, verified] 2026-11-07 setup-agents: agent kit (AGENTS.md, CLAUDE.md, this file,
  4 subagents, the orchestrate skill, settings.json with the lint hook). Build, lint
  and scripted-run commands each ran and passed.

## Decisions
- 2026-11-07 user: work on master in small commits; every commit is shown first; agents never push.
- 2026-11-07 user: roles are planner, characterizer, builder and reviewer; the main session orchestrates.
- Ticket decisions live in `NOTES.md`; docs-vs-code differences in `FINDINGS.md`.

## Log (newest first, one line each)
- 2026-11-07 setup-agents: kit written. No test command exists yet, so step 1 comes first.
