/*
 * test_calc.c - characterization tests for calc_quote()
 *
 * Pins what calc.c does today, not what the comments or docs say.
 * Every field is compared as a "%.2f" string, which is what the
 * screens and data/invoices.dat show.
 */
#include <stdio.h>
#include <string.h>
#include "calc.h"

static int nchecks = 0;
static int nfailed = 0;

static void check(const char *name, const char *field, double got, const char *want)
{
    char buf[64];

    nchecks++;
    sprintf(buf, "%.2f", got);
    if (strcmp(buf, want) != 0) {
        printf("FAIL %s %s: got %s, expected %s\n", name, field, buf, want);
        nfailed++;
    }
}

int main(void)
{
    QUOTE q;

    /* Invoices: fields mapped as sell_vehicle() stores them in invoices.dat */

    /* 50230: vehicle 1009, customer 2003 (R), 5%, trade-in 1500 */
    calc_quote(&q, 9295.00, 'R', 5, 1500.00);
    check("50230", "list", q.list, "9295.00");
    check("50230", "disc", q.trade_disc + q.disc, "464.75");
    check("50230", "net", q.net, "8830.25");
    check("50230", "vat", q.vat, "1796.05");
    check("50230", "fees", q.delivery + q.reg_fee, "205.00");
    check("50230", "tradein", q.tradein, "1500.00");
    check("50230", "total", q.total, "9331.30");

    /* 50231: vehicle 1012, customer 2002 (T), 0%, no trade-in */
    calc_quote(&q, 13495.00, 'T', 0, 0.00);
    check("50231", "list", q.list, "13495.00");
    check("50231", "disc", q.trade_disc + q.disc, "1349.50");
    check("50231", "net", q.net, "12145.50");
    check("50231", "vat", q.vat, "2459.10");
    check("50231", "fees", q.delivery + q.reg_fee, "205.00");
    check("50231", "tradein", q.tradein, "0.00");
    check("50231", "total", q.total, "14809.60");

    /* 50232: vehicle 1001, customer 2008 (R), 8%, no trade-in */
    calc_quote(&q, 10495.00, 'R', 8, 0.00);
    check("50232", "list", q.list, "10495.00");
    check("50232", "disc", q.trade_disc + q.disc, "839.60");
    check("50232", "net", q.net, "9655.40");
    check("50232", "vat", q.vat, "1961.08");
    check("50232", "fees", q.delivery + q.reg_fee, "205.00");
    check("50232", "tradein", q.tradein, "0.00");
    check("50232", "total", q.total, "11821.48");

    /* Edge cases on list 10995.00: every QUOTE field */

    /* retail 25% is capped to 15% */
    calc_quote(&q, 10995.00, 'R', 25, 0.00);
    check("cap25", "list", q.list, "10995.00");
    check("cap25", "trade_disc", q.trade_disc, "0.00");
    check("cap25", "fleet_disc", q.fleet_disc, "0.00");
    check("cap25", "disc_pct", q.disc_pct, "15.00");
    check("cap25", "disc", q.disc, "1649.25");
    check("cap25", "net", q.net, "9345.75");
    check("cap25", "delivery", q.delivery, "150.00");
    check("cap25", "vat", q.vat, "1899.15");
    check("cap25", "reg_fee", q.reg_fee, "55.00");
    check("cap25", "tradein", q.tradein, "0.00");
    check("cap25", "total", q.total, "11449.90");

    /* retail -3% becomes 0% */
    calc_quote(&q, 10995.00, 'R', -3, 0.00);
    check("neg3", "list", q.list, "10995.00");
    check("neg3", "trade_disc", q.trade_disc, "0.00");
    check("neg3", "disc_pct", q.disc_pct, "0.00");
    check("neg3", "disc", q.disc, "0.00");
    check("neg3", "net", q.net, "10995.00");
    check("neg3", "delivery", q.delivery, "150.00");
    check("neg3", "vat", q.vat, "2229.00");
    check("neg3", "reg_fee", q.reg_fee, "55.00");
    check("neg3", "tradein", q.tradein, "0.00");
    check("neg3", "total", q.total, "13429.00");

    /* trade 10% off list, then 5% off what is left */
    calc_quote(&q, 10995.00, 'T', 5, 0.00);
    check("trade5", "list", q.list, "10995.00");
    check("trade5", "trade_disc", q.trade_disc, "1099.50");
    check("trade5", "fleet_disc", q.fleet_disc, "0.00");
    check("trade5", "disc_pct", q.disc_pct, "5.00");
    check("trade5", "disc", q.disc, "494.78");
    check("trade5", "net", q.net, "9400.72");
    check("trade5", "delivery", q.delivery, "150.00");
    check("trade5", "vat", q.vat, "1910.14");
    check("trade5", "reg_fee", q.reg_fee, "55.00");
    check("trade5", "tradein", q.tradein, "0.00");
    check("trade5", "total", q.total, "11515.86");

    /* retail 2.5%: 274.875 rounds up to 274.88 */
    calc_quote(&q, 10995.00, 'R', 2.5, 0.00);
    check("half2.5", "list", q.list, "10995.00");
    check("half2.5", "trade_disc", q.trade_disc, "0.00");
    check("half2.5", "disc_pct", q.disc_pct, "2.50");
    check("half2.5", "disc", q.disc, "274.88");
    check("half2.5", "net", q.net, "10720.12");
    check("half2.5", "delivery", q.delivery, "150.00");
    check("half2.5", "vat", q.vat, "2174.02");
    check("half2.5", "reg_fee", q.reg_fee, "55.00");
    check("half2.5", "tradein", q.tradein, "0.00");
    check("half2.5", "total", q.total, "13099.14");

    /* Fleet (TICKET-142): 4% off list, then the salesman % off what is left */

    /* fleet 8%, plus the invoice disc as sell_vehicle() stores it */
    calc_quote(&q, 12750.00, 'F', 8, 0.00);
    check("fleet8", "list", q.list, "12750.00");
    check("fleet8", "trade_disc", q.trade_disc, "0.00");
    check("fleet8", "fleet_disc", q.fleet_disc, "510.00");
    check("fleet8", "disc_pct", q.disc_pct, "8.00");
    check("fleet8", "disc", q.disc, "979.20");
    check("fleet8", "net", q.net, "11260.80");
    check("fleet8", "delivery", q.delivery, "150.00");
    check("fleet8", "vat", q.vat, "2282.16");
    check("fleet8", "reg_fee", q.reg_fee, "55.00");
    check("fleet8", "tradein", q.tradein, "0.00");
    check("fleet8", "total", q.total, "13747.96");
    check("fleet8", "inv disc", q.trade_disc + q.fleet_disc + q.disc, "1489.20");

    /* fleet 25% is capped to 15%, trade-in 1000 */
    calc_quote(&q, 10995.00, 'F', 25, 1000.00);
    check("fleet25", "list", q.list, "10995.00");
    check("fleet25", "trade_disc", q.trade_disc, "0.00");
    check("fleet25", "fleet_disc", q.fleet_disc, "439.80");
    check("fleet25", "disc_pct", q.disc_pct, "15.00");
    check("fleet25", "disc", q.disc, "1583.28");
    check("fleet25", "net", q.net, "8971.92");
    check("fleet25", "delivery", q.delivery, "150.00");
    check("fleet25", "vat", q.vat, "1824.38");
    check("fleet25", "reg_fee", q.reg_fee, "55.00");
    check("fleet25", "tradein", q.tradein, "1000.00");
    check("fleet25", "total", q.total, "10001.30");

    /* fleet 0%: 399.9996 rounds to 400.00 */
    calc_quote(&q, 9999.99, 'F', 0, 0.00);
    check("fleetrnd", "list", q.list, "9999.99");
    check("fleetrnd", "trade_disc", q.trade_disc, "0.00");
    check("fleetrnd", "fleet_disc", q.fleet_disc, "400.00");
    check("fleetrnd", "disc_pct", q.disc_pct, "0.00");
    check("fleetrnd", "disc", q.disc, "0.00");
    check("fleetrnd", "net", q.net, "9599.99");
    check("fleetrnd", "delivery", q.delivery, "150.00");
    check("fleetrnd", "vat", q.vat, "1950.00");
    check("fleetrnd", "reg_fee", q.reg_fee, "55.00");
    check("fleetrnd", "tradein", q.tradein, "0.00");
    check("fleetrnd", "total", q.total, "11754.99");

    printf("test_calc: %d checks, %d failed\n", nchecks, nfailed);
    return nfailed ? 1 : 0;
}
