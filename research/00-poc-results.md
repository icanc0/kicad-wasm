# M1.1 — sexpr POC results

Ran 2026-08-24.

## What was built

- `src/sexpr-poc/sexpr.cpp` + `sexpr_parser.cpp` — the real KiCad
  s-expression parser (`libs/sexpr` copied from
  `~/not-my-projects/kicad`). Three tiny patches to get it off
  `wxString` / `wxFile`:
  - `#include <wx/file.h>` → std::ifstream in `GetFileContents`
  - `wxString stmp; stmp.ToCDouble(&f)` → `std::strtod(tmp.c_str(), nullptr)`
  - `#include <wx/debug.h>` — stubbed via `src/wx-stub/wx/debug.h`
- `src/sexpr-poc/main.cpp` — embind bindings exposing
  `parseSexpr(text)` and `sexprSummary(text)` to JS.
- `src/sexpr-poc/Makefile` — 8-line em++ invocation.
- `src/wx-stub/wx/debug.h` — 8-line wxASSERT/wxCHECK stub.
- `www/index.html` — browser demo, drop-file → summary.

## Real numbers

Compile command (single line):

```
em++ -O2 -std=c++20 --bind
  -I. -I../wx-stub -I~/not-my-projects/kicad/thirdparty/fmt/include
  -DFMT_HEADER_ONLY=1
  -sMODULARIZE=1 -sEXPORT_ES6=0 -sENVIRONMENT=node,web,worker
  -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=1048576
  -o sexpr.js main.cpp sexpr.cpp sexpr_parser.cpp
```

Artifacts:

| file       | size    |
|------------|--------:|
| sexpr.js   |  29 KB  |
| sexpr.wasm | 228 KB  |

Node runtime:

```
$ node test-node.js
=== simple ===
parseSexpr:  (kicad_pcb (version 20221018) (generator "test"))
sexprSummary: {"is_list":true,"is_symbol":false,"child_count":3,
               "root_symbol":"kicad_pcb"}

=== real PCB: simple.kicad_pcb (4,281,966 bytes) ===
parse+summarise: 601 ms
summary: {"is_list":true,"is_symbol":false,"child_count":2339,
          "root_symbol":"kicad_pcb"}

=== real PCB: starfish.kicad_pcb (4,728,434 bytes) ===
parse+summarise: 656 ms
summary: {"is_list":true,"is_symbol":false,"child_count":2386,
          "root_symbol":"kicad_pcb"}
```

## What this proves

1. The **toolchain works** — emscripten 6.0.8 compiles C++20 KiCad
   code and produces a runnable WASM binary.
2. **KiCad C++ code links** — parser depends on `<string>`,
   `<vector>`, `<memory>`, `<fstream>`, `<sstream>`, `<fmt>`.
   All fine under emscripten with `FMT_HEADER_ONLY`.
3. **Real KiCad files parse correctly** — 4.3-4.7 MB `.kicad_pcb`
   files parse in 600-700 ms, structural output matches what the
   native parser produces.
4. **Bundle size scales well** — 228 KB WASM + 29 KB JS glue
   for the parser alone. Full `kicad-cli export svg` in-browser
   is estimated at 5-15 MB compressed based on this ratio (parser
   is <1% of the codebase; full path adds board model, plotter,
   fonts).
5. **wxWidgets can be surgically stubbed** — just replacing
   `wx/debug.h` was enough for the parser. Every other wx use in
   this file was in one method (`GetFileContents`) that I
   rewrote to plain std::ifstream in 15 lines.

## Next: M1.2

`libs/kimath` is header-heavy: templates on VECTOR2, BOX2, EDA_ANGLE.
Compile it against the same toolchain, expose a couple of geometry
predicates, verify results match the native build's.

## Blockers to watch

None yet in Phase 1. The concerning items in ROADMAP.md are all
for later phases:

- Boost::thread and Boost::filesystem for the wider build
- wxWidgets stubbing at scale (there are ~150 wx symbols across
  kicommon and pcbnew; will need a more systematic stub library)
- OpenCascade for STEP export — occt-wasm exists, just need to
  bridge the API surface

## Reproducer

```
$ cd ~/not-my-projects/kicad-wasm
$ source build/emsdk-env.sh
$ cd src/sexpr-poc
$ make
$ make test
```
