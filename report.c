/*
 * report.c - management reports
 */
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "screen.h"
#include "report.h"

static void monthly_sales(void)
{
    char months[60][8];
    int count[60];
    double total[60];
    int nm = 0, i, j;

    header("Monthly Sales");
    for (i = 0; i < ninv; i++) {
        for (j = 0; j < nm; j++)
            if (strncmp(months[j], inv[i].date, 7) == 0)
                break;
        if (j == nm) {
            if (nm >= 60)
                continue;
            strncpy(months[nm], inv[i].date, 7);
            months[nm][7] = 0;
            count[nm] = 0;
            total[nm] = 0;
            nm++;
        }
        count[j]++;
        total[j] += inv[i].total;
    }
    printf("  %-8s %6s %14s\n", "MONTH", "SOLD", "TOTAL");
    printf("  ------------------------------\n");
    for (j = 0; j < nm; j++)
        printf("  %-8s %6d %14.2f\n", months[j], count[j], total[j]);
    pause_enter();
}

static void margin_report(void)
{
    int i, j;
    VEHICLE *v;

    header("Margin per Vehicle");
    printf("  %-6s %-10s %-22s %10s %10s %10s\n", "INV", "PLATE", "MODEL", "COST", "NET", "MARGIN");
    printf("  ------------------------------------------------------------------------\n");
    for (i = 0; i < ninv; i++) {
        v = NULL;
        for (j = 0; j < nveh; j++)
            if (veh[j].id == inv[i].veh_id)
                v = &veh[j];
        if (!v)
            continue;
        printf("  %-6d %-10s %-22.22s %10.2f %10.2f %10.2f\n",
               inv[i].no, v->plate, v->model, v->cost, inv[i].net, inv[i].net - v->cost);
    }
    pause_enter();
}

void reports_menu(void)
{
    int opt;

    for (;;) {
        header("Reports");
        printf("  1. Monthly sales\n");
        printf("  2. Margin per vehicle\n");
        printf("  0. Back\n\n");
        opt = read_int("  Option: ");
        switch (opt) {
        case 1: monthly_sales(); break;
        case 2: margin_report(); break;
        case 0: return;
        default:
            printf("  Invalid option\n");
            pause_enter();
        }
    }
}
