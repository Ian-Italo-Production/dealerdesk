/*
 * calc.c - pricing
 *
 * Price build-up:
 *     list price
 *   - trade discount       (trade customers get 5%)
 *   - salesman discount    (max 10% without manager PIN)
 *   = net price
 *   + delivery
 *   + VAT 20% on list price
 *   + registration fee
 *   - trade-in
 *   = total
 */
#include "calc.h"

void calc_quote(QUOTE *q, double list, char cust_type, double disc_pct, double tradein)
{
    q->list = list;

    q->trade_disc = 0;
    if (cust_type == 'T')
        q->trade_disc = list * 0.05;

    if (disc_pct < 0)
        disc_pct = 0;
    if (disc_pct > 15)
        disc_pct = 15;
    q->disc_pct = disc_pct;
    q->disc = (list - q->trade_disc) * disc_pct / 100.0;

    q->net = list - q->trade_disc - q->disc;
    q->delivery = 150.00;
    q->vat = q->net * 0.20;
    q->reg_fee = 55.00;
    q->tradein = tradein;

    q->total = q->net + q->delivery + q->vat + q->reg_fee - q->tradein;
}
