#!/bin/bash
# Try to compile every KiCad common/*.cpp to WASM. Log which succeed
# and which don't, with a top-line categorisation of failure reasons
# so the stub work can be prioritised.
set -u

KICAD="$HOME/not-my-projects/kicad"
COMMON="$KICAD/common"
FMT="$KICAD/thirdparty/fmt/include"
CLIPPER="$KICAD/thirdparty/clipper2/Clipper2Lib/include"
CORE_INC="$KICAD/libs/core/include"
CONFIG_H_DIR="$KICAD/build-mini"
BOOST_INC="$HOME/local/kicad-root/usr/include"
WX_STUB="$(cd "$(dirname "$0")/../wx-stub" && pwd)"

CXX="em++"
CXXFLAGS="-O2 -std=c++20 \
  -I$COMMON -I$KICAD/include -I$KICAD/libs/kimath/include \
  -I$CORE_INC -I$KICAD/include/libraries \
  -I$WX_STUB -I$FMT -I$CLIPPER \
  -I$KICAD/thirdparty -I$KICAD/thirdparty/fast_float/include \
  -I$KICAD/thirdparty/argparse/include \
  -I$KICAD/thirdparty/expected \
  -I$KICAD/thirdparty/nlohmann_json \
  -I$BOOST_INC \
  -I$CONFIG_H_DIR -I$CONFIG_H_DIR/common -I$CONFIG_H_DIR/include \
  -I$COMMON/dialogs -I$COMMON/widgets \
  -DFMT_HEADER_ONLY=1 -DUSINGZ=1 \
  -Wno-macro-redefined -Wno-nan-infinity-disabled"

mkdir -p obj

ok=0
fail=0
declare -A fail_reason

for src in "$COMMON"/*.cpp; do
    base=$(basename "$src" .cpp)
    out="obj/${base}.o"
    err="obj/${base}.err"

    if $CXX $CXXFLAGS -c -o "$out" "$src" 2>"$err"; then
        ok=$((ok+1))
        rm -f "$err"
    else
        fail=$((fail+1))
        # Categorise by first "fatal error" line.
        first_reason=$(grep -m1 -E 'fatal error|error:' "$err" | head -c 100)
        fail_reason["$base"]="$first_reason"
    fi
done

echo "===== common/ compile results ====="
echo "ok    = $ok"
echo "fail  = $fail"
echo
echo "===== failure categories ====="
# Extract just the missing header or symbol name.
declare -A cat_count
for base in "${!fail_reason[@]}"; do
    line="${fail_reason[$base]}"
    if [[ "$line" =~ file[[:space:]]not[[:space:]]found ]]; then
        hdr=$(echo "$line" | grep -oE "'[^']+'" | head -1)
        key="missing header $hdr"
    elif [[ "$line" =~ undeclared[[:space:]]identifier ]]; then
        sym=$(echo "$line" | grep -oE "'[^']+'" | head -1)
        key="undeclared $sym"
    elif [[ "$line" =~ no[[:space:]]member[[:space:]]named ]]; then
        member=$(echo "$line" | grep -oE "'[^']+'" | head -1)
        key="no member $member"
    else
        key="other"
    fi
    cat_count["$key"]=$((${cat_count["$key"]:-0}+1))
done

for k in "${!cat_count[@]}"; do
    printf "%4d  %s\n" "${cat_count[$k]}" "$k"
done | sort -rn | head -20
