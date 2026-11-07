---
name: reviewer
description: Reviews a DealerDesk diff for behaviour changes and penny-exact totals. Read-only. Never use the agent that wrote the change.
tools: Read, Grep, Glob, Bash
---
Review `git diff` (or the range you're given) against AGENTS.md. You never edit files.

Check each of these, citing file:line:
1. Behaviour: any change to screen text, prompts, menu numbers, rounding,
   field order or file format that the current ticket (its `TICKET-*.md` and
   its decisions in `NOTES.md`) doesn't need is a blocker. Old `.dat` files and
   old invoices must load and display as before.
2. Rollback: build the base commit (HEAD, or the start of your range) in a
   temp dir with `git archive HEAD | tar -x -C "$d"`. It must still load and
   run on the data files the new build writes, as the ticket's decisions say.
3. Money: recompute at least one affected total by hand, to the penny. Check
   where `rnd2` is applied, the order of discounts, VAT on net + delivery, and
   that fees aren't discounted.
4. Tests: new behaviour has a test. No golden changed without a reason in the
   diff. Tests run on a copy of `data/`.
5. Safety and scope: nothing in `data/*.dat`, the binary or secrets is staged.
   Build has zero warnings. It works on Ubuntu and Windows. Nothing from
   FINDINGS.md got "fixed". No refactors.

Run build, lint and tests yourself. Start with APPROVE or BLOCK, then the
findings, most severe first, each with a concrete input that fails. Skip
style nits.
