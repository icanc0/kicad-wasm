#!/bin/bash
# Try to compile every kiplatform/os/{common,unix}/*.cpp to WASM.
set -u

KICAD="$HOME/not-my-projects/kicad"
FMT="$KICAD/thirdparty/fmt/include"
CORE_INC="$KICAD/libs/core/include"
CONFIG_H_DIR="$KICAD/build-mini"
BOOST_INC="$HOME/local/kicad-root/usr/include"
WX_STUB="$(cd "$(dirname "$0")/../wx-stub" && pwd)"

CXX="em++"
CXXFLAGS="-O2 -std=c++20 \
  -I$KICAD/libs/kiplatform/include -I$KICAD/include \
  -I$CORE_INC -I$WX_STUB -I$FMT \
  -I$KICAD/thirdparty -I$BOOST_INC -I$CONFIG_H_DIR \
  -DFMT_HEADER_ONLY=1 -DUSINGZ=1 -DKICAD_WAYLAND=0"

mkdir -p obj

ok=0
fail=0

# common (portable) sources — always try these.
for src in "$KICAD"/libs/kiplatform/os/common/*.cpp; do
    base=$(basename "$src" .cpp)
    out="obj/common_${base}.o"
    err="obj/common_${base}.err"

    if $CXX $CXXFLAGS -c -o "$out" "$src" 2>"$err"; then
        ok=$((ok+1))
        rm -f "$err"
    else
        fail=$((fail+1))
    fi
done

# unix files: io.cpp, drivers.cpp, policy.cpp, sysinfo.cpp compile
# without external deps (with wx/crt.h stub). The others need
# glib/poppler/libsecret and are replaced by the wasm variant below.
for uf in io drivers policy sysinfo; do
    src="$KICAD/libs/kiplatform/os/unix/${uf}.cpp"
    if $CXX $CXXFLAGS -c -o "obj/unix_${uf}.o" "$src" 2>"obj/unix_${uf}.err"; then
        ok=$((ok+1))
        rm -f "obj/unix_${uf}.err"
    else
        fail=$((fail+1))
    fi
done

# wasm-specific replacement for unix files that need glib/poppler/libsecret.
if $CXX $CXXFLAGS -c -o "obj/wasm_kiplatform.o" \
        kiplatform_wasm.cpp 2>"obj/wasm_kiplatform.err"; then
    ok=$((ok+1))
    rm -f "obj/wasm_kiplatform.err"
else
    fail=$((fail+1))
fi

emar rcs libkiplatform.a obj/*.o
echo "archive: libkiplatform.a ($(du -h libkiplatform.a | cut -f1))"

echo "===== kiplatform build ====="
echo "ok    = $ok"
echo "fail  = $fail"

if [ $fail -gt 0 ]; then
    echo
    echo "failed:"
    for f in obj/*.err; do
        [ -s "$f" ] && echo "  $(basename $f .err): $(head -1 $f | cut -c1-120)"
    done
fi
