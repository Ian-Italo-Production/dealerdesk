DEALERDESK v2.0
===============

Dealer management for the showroom: stock, customers, quotes and invoices.


BUILD
-----

    gcc -o dealerdesk main.c dbfile.c screen.c report.c

(Windows releases are built with the Borland compiler on the old build PC.)


RUN
---

    ./dealerdesk

Data files are read from C:\DEALERDESK\DATA

    stock.dat       vehicles
    customers.dat   customers
    invoices.dat    invoices
    next_ids.dat    id counters

Do NOT edit the .dat files by hand while the program is running!


MENU
----

    1. Stock
    2. Customers
    3. Quote
    4. Sell vehicle
    5. Invoices
    6. Reports (monthly sales, margin per vehicle)
    0. Exit


PRICING RULES
-------------

* VAT (20%) is calculated on the list price. Discounts are then taken off
  the VAT inclusive price.
* Trade customers get a 5% trade discount.
* Salesman discount is up to 10%. Anything above 10% asks for a manager PIN.
* Delivery (150.00) and first registration (55.00) are added to every sale.
  Both are VAT exempt.
* Trade-in value is taken off the final total.


RELEASE
-------

See RELEASE.txt


Problems: ask Phil (ext. 214).
