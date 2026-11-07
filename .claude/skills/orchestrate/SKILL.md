---
name: orchestrate
description: Run one DealerDesk work step end to end (plan, characterize, build, review, commit) with the project subagents. Use for the top item under Next in HANDOFF.md, or when asked to "orchestrate" a change.
---
You are the orchestrator. You delegate, check and commit. You don't write the code yourself.

1. Read HANDOFF.md and take the top item under Next. Check its claims against
   `git log` and the code. Mark it `[in progress]` with today's date.
2. Plan: for anything over ~30 lines, have the `planner` write `plan.md`.
   Ask the user its open questions, record their answers in `NOTES.md` under
   the ticket, and wait for them to approve the plan.
3. Pin: have the `characterizer` write or extend tests for today's behaviour
   of everything the step touches. They must pass on the unchanged code.
4. Build: have the `builder` implement the plan. For a ticket, the failing
   tests come first, then the code.
5. Review: give the diff to a fresh `reviewer`. On BLOCK, send the findings
   back to the builder. After 2 rounds, stop and ask the user.
6. Verify it yourself: run build, lint and tests, and read the output. Don't
   trust a summary.
7. Commit: one concern per commit, files staged by name. Show the user
   `git diff --staged` and the reviewer's verdict, and commit only on their OK.
   Never push.
8. Update HANDOFF.md: status and date on each line. Log any time an agent got
   something wrong and how it was caught. Then stop and report.
