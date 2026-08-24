#!/bin/bash
# Build kimath to WASM. Simple shell loop; make -j had issues with
# nested $(eval) for the flat obj/ target layout.
set -u

KICAD="$HOME/not-my-projects/kicad"
KIMATH="$KICAD/libs/kimath"
FMT="$KICAD/thirdparty/fmt/include"
CLIPPER="$KICAD/thirdparty/clipper2/Clipper2Lib/include"
CORE_INC="$KICAD/libs/core/include"
CONFIG_H_DIR="$KICAD/build-mini"
BOOST_INC="$HOME/local/kicad-root/usr/include"
WX_STUB="$(cd "$(dirname "$0")/../wx-stub" && pwd)"

CXX="em++"
CXXFLAGS="-O2 -std=c++20 \
  -I$KIMATH/include -I$WX_STUB -I$FMT -I$CLIPPER \
  -I$CORE_INC -I$KICAD/include -I$CONFIG_H_DIR \
  -I$KICAD/thirdparty -I$BOOST_INC \
  -DFMT_HEADER_ONLY=1 -DUSINGZ=1"

mkdir -p obj

ok=0
fail=0
failed_files=()
for src in "$KIMATH"/src/*.cpp \
           "$KIMATH"/src/geometry/*.cpp \
           "$KIMATH"/src/math/*.cpp; do
    base=$(basename "$src" .cpp)
    out="obj/${base}.o"
    err="obj/${base}.err"
    if $CXX $CXXFLAGS -c -o "$out" "$src" 2>"$err"; then
        ok=$((ok+1))
        rm -f "$err"
    else
        fail=$((fail+1))
        failed_files+=("$base")
    fi
done

echo "===== kimath build ====="
echo "ok    = $ok"
echo "fail  = $fail"
if [ $fail -gt 0 ]; then
    echo "failed files:"
    for f in "${failed_files[@]}"; do echo "  - $f"; done
fi
echo

# Archive whatever compiled.
if [ $ok -gt 0 ]; then
    emar rcs libkimath.a obj/*.o
    echo "wrote libkimath.a ($(du -h libkimath.a | cut -f1))"
fi
