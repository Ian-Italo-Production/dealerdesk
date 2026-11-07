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

## What I'd do next

See [FINDINGS.md](FINDINGS.md).
