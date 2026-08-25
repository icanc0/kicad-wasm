#!/bin/bash
# Compile libs/core to WASM.
set -u

KICAD="$HOME/not-my-projects/kicad"
FMT="$KICAD/thirdparty/fmt/include"
CORE_INC="$KICAD/libs/core/include"
CONFIG_H_DIR="$KICAD/build-mini"
BOOST_INC="$HOME/local/kicad-root/usr/include"
WX_STUB="$(cd "$(dirname "$0")/../wx-stub" && pwd)"

CXX="em++"
CXXFLAGS="-O2 -std=c++20 \
  -I$KICAD/libs/core -I$KICAD/libs/core/include \
  -I$KICAD/include -I$KICAD/libs/kimath/include \
  -I$WX_STUB -I$FMT \
  -I$KICAD/thirdparty -I$BOOST_INC -I$CONFIG_H_DIR \
  -DFMT_HEADER_ONLY=1"

mkdir -p obj
ok=0; fail=0

for src in "$KICAD"/libs/core/*.cpp; do
    base=$(basename "$src" .cpp)
    out="obj/${base}.o"
    err="obj/${base}.err"
    if $CXX $CXXFLAGS -c -o "$out" "$src" 2>"$err"; then
        ok=$((ok+1)); rm -f "$err"
    else
        fail=$((fail+1))
    fi
done

echo "===== libs/core build ====="
echo "ok    = $ok"
echo "fail  = $fail"
if [ $fail -gt 0 ]; then
    echo
    for f in obj/*.err; do
        [ -s "$f" ] && echo "  $(basename $f .err): $(head -1 $f | cut -c1-120)"
    done
fi

if [ $ok -gt 0 ]; then
    emar rcs libcore.a obj/*.o
    echo
    echo "archive: libcore.a ($(du -h libcore.a | cut -f1))"
fi
