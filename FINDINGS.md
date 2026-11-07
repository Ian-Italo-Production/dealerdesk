# Findings: docs vs code

Places where the README, the Help screen (menu `9`) or code comments disagree with what the app does. **None of these are fixed**: staff rely on the current behaviour, so each one needs a business decision first. They're candidates for future work.

Reproduce from the repo root with `./dealerdesk`. `3 → 1002 → 2002` means type `3`, press ENTER, type `1002`, press ENTER, and so on.

| # | Docs say | Code does | Reproduce |
|---|---|---|---|
| 1 | Trade discount is 5% (README, Help) | **10%** (`calc.c:29`). Changed from 5% in `8ffd2ad`, a 2016 commit titled only "fix". Invoice 50231 (2021) charged 10%. | `3 → 1002 → 2002 → 0 → 0`: Trade discount −1099.50 on 10995.00 |
| 2 | VAT on the list price; delivery is VAT-free (README, `calc.c:10` comment) | VAT on net price + delivery (`calc.c:40`, commits `9dc21bb`, `3a46905`) | `3 → 1002 → 2001 → 0 → 0`: VAT 2229.00 = 20% × (10995 + 150); the docs would give 2199.00 |
| 3 | Discount over 10% needs a manager PIN (README, Help) | No PIN (removed in `a42d118`). Anything over 15% is silently cut to 15% (`calc.c:33`). | `3 → 1002 → 2001 → 25 → 0`: shows "Discount (15.0%)", no prompt or warning |
| 4 | Plates are upper-cased (Help, `main.c:5` comment) | Stored as typed (removed in `76169d5`). Find by plate only matches the exact case. | `1 → 4 → YF20 HBN`: not found. `1 → 4 → yf20 hbn`: found |
| 5 | README build: `gcc ... main.c dbfile.c screen.c report.c` | `report.c` was deleted (`399a544`) and `calc.c` is missing from the list. Only `gcc -o dealerdesk *.c -lm` works. | Run the README build line: `report.c: No such file or directory` |
| 6 | Data in `C:\DEALERDESK\DATA`; version v2.1; menu has "6. Reports" (README) | Data is `./data` under the folder you start in; the screen says v2.3; `6` is "Invalid option"; `9. Help` isn't documented | Start the app from the parent folder, then `2 → 1`: 0 customers |

## Bug: blank fields shift on reload

`dbfile.c` splits lines with `strtok`, which skips empty fields, so a blank field moves every later field one place left. A trade customer saved with no email comes back as **Retail** after a restart. The same applies to vehicles with a blank make or model. **Risk:** data changes silently, with no error.

Reproduce: `2 → 2`, enter Name `Test`, Phone `07700 900000`, press ENTER for Email, `Y` for Trade. `2 → 1` shows Trade. Exit, restart, `2 → 1`: now Retail, with `T` in the email column.

Restore the sample data afterwards, with the app closed: `git checkout -- data`
