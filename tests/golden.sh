#!/bin/sh
# Golden end-to-end tests. Each tests/golden/<name>.in is piped into the app
# twice, on fresh temp copies of data/ with LF and with CRLF .dat files; stdout
# plus every .dat afterwards must match the same tests/golden/<name>.out.
# UPDATE=1 sh tests/golden.sh rewrites the .out files from the LF run.
LC_ALL=C
export LC_ALL
root=$(cd "$(dirname "$0")/.." && pwd) || exit 1
tmp=$(mktemp -d) || exit 1
trap 'rm -rf "$tmp"' EXIT
trap 'exit 1' HUP INT TERM PIPE
fail=0

for in_file in "$root"/tests/golden/*.in; do
    name=$(basename "$in_file" .in)
    out_file="$root/tests/golden/$name.out"
    for eol in LF CRLF; do
        d=$(mktemp -d "$tmp/run.XXXXXX") || exit 1
        mkdir "$d/data" || exit 1
        for f in "$root"/data/*.dat; do
            if [ "$eol" = LF ]; then
                tr -d '\r' < "$f" > "$d/data/${f##*/}"
            else
                tr -d '\r' < "$f" | awk '{printf "%s\r\n", $0}' > "$d/data/${f##*/}"
            fi
        done
        (cd "$d" && "$root/dealerdesk") < "$in_file" > "$d/stdout"
        rc=$?
        if [ "$rc" -ne 0 ]; then
            echo "FAIL $name ($eol): app exited $rc"
            fail=1
            continue
        fi
        # The sale date comes from today's clock; only the new invoice 50233 has one.
        {
            # Only Windows' text-mode stdout adds \r; anywhere else a \r on screen is a leak.
            if [ "$OS" = Windows_NT ]; then
                tr -d '\r' < "$d/stdout"
            else
                cat "$d/stdout"
            fi
            for f in "$d"/data/*.dat; do
                echo "== ${f##*/}"
                tr -d '\r' < "$f"
            done
        } | sed '/50233/s/[0-9]\{4\}-[0-9][0-9]-[0-9][0-9]/YYYY-MM-DD/' > "$d/actual"
        if [ "$UPDATE" = 1 ] && [ "$eol" = LF ]; then
            cp "$d/actual" "$out_file" || exit 1
            echo "WROTE tests/golden/$name.out"
        fi
        if diff -u "$out_file" "$d/actual"; then
            echo "PASS $name ($eol)"
        else
            echo "FAIL $name ($eol)"
            fail=1
        fi
    done
done
exit $fail
