# Roadmap

Concrete steps, ordered by dependency. Each M-milestone is a
checkpoint with a demonstrable artifact.

## Phase 0 — bootstrap  (this session)

- **M0.1** Repo scaffolded, README + ROADMAP + research notes.
- **M0.2** Emscripten installed and verified (`emcc --version`).
- **M0.3** Toolchain shim (`build/emcmake-wrap.sh`) that runs the
  KiCad cmake with `emcmake` and the sysroot pointing at
  Boost-emscripten headers.

## Phase 1 — kicad-cli-wasm

### M1.1 — sexpr parser POC (~1-2 days)

Compile `libs/sexpr` + a stub `main` to WASM. Feed a
`.kicad_pcb` sexp; parse; dump the token stream. **No wxWidgets,
no board data model, no plotter.** This proves the toolchain +
Boost basics work.

### M1.2 — kimath to WASM (~1 day)

`libs/kimath` is header-heavy + a few .cpp. Templates on
`VECTOR2<T>`, `BOX2<T>`, `EDA_ANGLE`. Compile and link with M1.1.
Simple test: JS calls a `distanceToSegment(v1, v2, p)` binding
and gets an answer.

### M1.3 — wxWidgets stub minimal surface (~3-5 days)

The headless kicad-cli imports a lot of wxWidgets types
(`wxString`, `wxFileName`, `wxLog*`, `wxFile`, `wxTranslations`).
Instead of porting wxWidgets:

  1. Grep the whole tree that Phase 1 compiles for the wx symbols
     it actually references.
  2. Write a `wx-stub` C++ library with a header-compatible
     subset backed by `std::string` + `std::filesystem` +
     spdlog-equivalent.
  3. Compile everything against that stub instead of real wx.

This is the biggest single-item risk. If the stub explodes
because of macros or virtual overrides, Plan B is to compile a
minimal wxBase-emscripten (no wxCore, no wxGTK).

### M1.4 — kicad-cli plot path (~2 weeks)

- Build `libs/kimath`, `libs/kiplatform`, `common`, and the
  subset of `pcbnew` needed for parse+plot (no zone filling, no
  DRC, no connectivity — the P3 fast-path from kicad-perf).
- Link against wx-stub.
- Expose a first `plotSVG` binding.
- **Demo**: page loads a `.kicad_pcb` via `<input type="file">`
  and inlines the rendered SVG.

### M1.5 — Gerber + PDF + STEP (~1 week each)

- Gerber: same pipeline, different plotter target.
- PDF: PDF_PLOTTER + libpng WASM port + zlib (already Emscripten
  builtin).
- STEP: link occt-wasm for the OCC piece; write a thin bridge
  from KiCad's step exporter.

## Phase 2 — pcbnew-web (viewer)

### M2.1 — SDL2 surface + GAL OpenGL backend (~2 weeks)

- Wire GAL's `OPENGL_GAL` class to Emscripten SDL2 + WebGL 2.
- Verify a static frame renders correctly against Phase 1's
  parsed board.

### M2.2 — pan / zoom / layer-toggle UI shell (~2 weeks)

- Solid.js or vanilla web-components UI on top of the canvas.
- No editing; just view.

### M2.3 — 3D viewer (~months)

- Reuse `3d-viewer` code, WebGL backend.
- Optional STEP-visual via occt-wasm.

## Phase 3 — pcbnew-editor (full editor)

Deferred. Blockers require serious upstream work or a big
rewrite. Notes only:

- Dialog and property-panel rewrite (dozens of dialogs in
  wxFormBuilder XRC — needs mechanical translation to React
  components, one at a time)
- Tool framework (`TOOL_MANAGER`, `EVENTS`) — already event-
  driven, so wiring to browser events is direct
- Library manager / project manager — full file-system access
  via File System Access API + IndexedDB
- Live-DRC — same code, works when Phase 1 is done
- Undo/redo — same code, works when Phase 1 is done

## Risk table

| risk                                    | plan A                          | plan B                          |
|-----------------------------------------|---------------------------------|---------------------------------|
| Boost::thread doesn't build under wasm  | Emscripten pthread build        | Serial fallback (single thread) |
| wx-stub misses a used symbol            | Grep + iterate                  | Vendor real wxBase for wasm     |
| OCCT-WASM API drifts from KiCad's usage | Wrap it in a thin adapter       | Vendor a compatible OCCT snapshot|
| WebGL 2 doesn't cover a GAL feature     | Downgrade to WebGL 1 path       | WebGPU (needs 2026 baseline)    |
| Bundle size > 50 MB compressed          | Split by feature (SVG-only demo | Lazy-load STEP module           |
|                                         | is small)                       |                                 |
| Persistent storage for library dbs      | IndexedDB                       | Origin Private FS (OPFS)        |

## What ships at each milestone

| milestone | shippable artifact                                    |
|-----------|------------------------------------------------------|
| M1.1      | JS console page: paste sexp text, get parsed AST     |
| M1.4      | Web page: upload .kicad_pcb, download rendered SVG   |
| M1.5      | Same, choose format: SVG / Gerber / PDF / STEP       |
| M2.2      | View-only browser PCB viewer at kicad-wasm.dev       |
| M3        | Full editor                                          |
