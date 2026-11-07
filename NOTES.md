# Notes

## What I changed and why

_To do._

## How I worked with the agents

_To do._

## Assumptions and decisions (TICKET-142)

- **Fleet is a customer type.** A customer is retail (`R`), trade (`T`) or fleet (`F`), never more than one. Fleet uses the existing type field in `customers.dat`, so that file's format doesn't change.
  - Trade: motor dealers buying cars to sell on. Fleet: businesses buying cars for their own use (taxis, rental, delivery).
- **Fleet discount:** 4% off the vehicle list price. Delivery and registration are not discounted. Everything after that is worked out as today (VAT on net price + delivery).
- **Discount order:** the salesman discount % applies after the fleet discount, to (list − fleet discount). That's how trade already works.
- **Existing customers:** a new Customers-menu option changes a customer's type (e.g. Greenway Taxis from `R` to `F`).
- **Invoices:** the existing discount field still holds all discounts added together. A new fleet-discount field goes at the end of each invoice line. Old lines read it as 0 and display exactly as before.
- **Rollback:** the previous binary must still run on the new data files. It shows fleet customers as Retail with no automatic discount. Invoices load with correct totals; the old binary drops the fleet breakdown if it saves invoices again.
- **Nothing else changes.** Where the docs and the code disagree, the code wins and the difference goes in [FINDINGS.md](FINDINGS.md) instead of being fixed.

### Screen and file details (user, 2026-11-07, step 3 plan)

- **Change type:** Customers menu line `  4. Change customer type`, after 3. Screen title `Change Customer Type`; prompt `  Customer ID : `; then `  <name>, currently <Retail/Trade/Fleet>` with no leading `\n`, printed the way Change price prints its `current price` line (in a piped run it follows `  Customer ID : ` on the same line), then the prompt `  New type (R/T/F) : `. Only the first character counts, either case, and the upper-case letter is saved. R, T or F saves and shows `\n  Customer <id> is now <Retail/Trade/Fleet>.`; an unknown ID shows `\n  Customer not found.` (no type prompt); anything else, blank included, shows `\n  Type not changed.` and saves nothing. Each ends with the usual Press ENTER.
- **Labels:** type `F` shows as `Fleet` in the TYPE column of List customers and Find customer, and as `(Fleet)` on the `Customer :` line of the quote and the INVOICE PREVIEW. Any type other than T or F still shows Retail.
- **Quote line:** `  Fleet discount           %12.2f`, printed as `-fleet` like Trade discount's `-trade_disc` (e.g. `-510.00`), in the same columns as `Trade discount`, after it and before `Discount (x%)`, only when above 0. The INVOICE PREVIEW shows the same line.
- **Add customer:** `  Trade customer (Y/N)? ` stays. Only after a non-Y answer, it asks `  Fleet customer (Y/N)? `; Y saves type F, anything else saves R, as today. A trade add looks exactly as today.
- **View invoice:** when the fleet amount isn't 0, `  Fleet discount           %12.2f`, printed as `-fleet`, sits between List price and Discounts, and Discounts shows the rest, printed as `-(disc - fleet)`, so the lines still add up to Net (a fleet sale at 0% shows `Discounts -0.00`, as FINDINGS row 7 already does today). When it's 0 (old and non-fleet invoices), the screen is unchanged.
- **invoices.dat:** the fleet amount is written as `|%.2f` at the end of every line. Old lines gain `|0.00` the first time the file is saved again; amounts don't change.
- **Rounding:** the fleet discount is rounded to the nearest penny like the trade discount: `rnd2(list * 0.04)`. 9999.99 gives 400.00.

## What I'd do next

See [FINDINGS.md](FINDINGS.md).
