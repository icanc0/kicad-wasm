# kicad-wasm

Port of KiCad to WebAssembly. **Native code, running in the browser.**

## Motivation

There's a big gap in the "KiCad on the web" space:

- **[KiCanvas](https://github.com/theacodes/kicanvas)** is excellent
  and battle-tested — but it's a *re-implementation* of the render
  path in TypeScript+WebGL, not KiCad itself. It parses the file
  format independently, so bug-for-bug fidelity with the real KiCad
  isn't guaranteed, and features that KiCad adds later have to be
  reimplemented.
- **Actual KiCad in the browser** — running the real C++ code — is
  where you get exact rendering, exact plot output, exact DRC
  results, and every future KiCad feature for free.

WebAssembly makes this achievable now. AutoCAD, Figma, Google Earth,
and Photoshop have all shipped C++-in-browser at scale.

## Scope

This is a **staged port**. Each stage is independently useful.

### Phase 1 — kicad-cli-wasm (headless)

- Compile the parse + plot + export path of `kicad-cli` to WASM.
- Expose a JS/TS API:
  ```ts
  import { plotSVG } from '@icanc0/kicad-wasm'
  const svg: string = await plotSVG(pcbBytes, { layers: ['F.Cu'] })
  ```
- No GUI. `wxWidgets` is stubbed to the minimum surface the
  headless CLI actually uses (`wxString`, `wxFileName`, `wxLog`, …
  none of the widget classes).
- **Deliverables**: `plotSVG`, `plotGerbers`, `plotPDF`,
  `exportSTEP`, `runDRC`, `parseNetlist`, `getBoardStats`.
- **Feasible in weeks.** OCCT-WASM already exists for STEP.
  Boost headers + boost_filesystem/boost_context work under
  Emscripten with `EMBIND_ATLEAST_ONE_WORKAROUND`.

### Phase 2 — pcbnew-web (viewer)

- Bundle Phase 1 with a browser front-end.
- Read-only PCB viewer with pan/zoom/layer-toggle.
- Frontend: SDL2/Emscripten + Dear ImGui **or** reuse KiCanvas's
  UI shell with WASM backend for pixel-perfect rendering.
- **Feasible in months.** SDL2 has a mature Emscripten port; GAL
  (KiCad's Graphics Abstraction Layer) already has an OpenGL
  backend that maps to WebGL 2 via Emscripten's GLES translation.

### Phase 3 — pcbnew-editor (full editor)

- Editing, DRC-live, tool interactions, dialogs, library manager.
- **The wxWidgets barrier.** wxWidgets is not portable to browser —
  someone has to either (a) build a wxWidgets→SDL/Canvas backend,
  which nobody has done for real, (b) rewrite the dialog and tool
  layer in a web-native UI framework (React/Solid over WASM), or
  (c) use an Electron-in-Emscripten trick like Photoshop uses.
- **Years of work.** Realistic plan: rewrite dialogs one at a
  time in React, exposing WASM setters for each field. The
  render surface stays SDL2/WebGL.

## Non-goals

- Full Python plugin runtime in the browser (Pyodide is possible
  but adds ~50 MB; deferred).
- 3D-viewer with real-time raytracing (OCCT+WebGPU is possible;
  Phase 2 uses simple GL polygons like the current 3D-viewer's
  GAL raster path).
- Multi-user real-time collaboration (out of scope, but the
  WASM binary + IndexedDB persistence would let a CRDT layer sit
  on top later).

## What's here today

- `README.md` — this file
- `ROADMAP.md` — detailed phase breakdown, milestones, blockers
- `research/` — surveys of prior art, feasibility notes on
  Boost/OCCT/wxWidgets under emscripten, KiCanvas overlap
- `build/` — CMake toolchain, emsdk setup, per-phase build script
- `src/` — thin C++ shim (headless entry points, JS bindings,
  wxWidgets stubs)
- `www/` — HTML shell + JS/TS front-end code
- `patches/` — patches against KiCad master required to build for
  emscripten (some are the same as
  [icanc0/kicad-perf](https://github.com/icanc0/kicad-perf) — that
  repo's headless-mode gates are half of what this port needs)

## Related work

- **[icanc0/kicad-perf](https://github.com/icanc0/kicad-perf)** —
  same author, 58 patches optimizing KiCad's CPU / RAM / plot path.
  Its headless-mode gates (P5, P36-P39, P57) directly reduce what
  needs to compile into the WASM binary.
- **[KiCanvas](https://github.com/theacodes/kicanvas)** — TypeScript
  browser viewer. Different approach; complementary.
- **[occt-wasm](https://github.com/andymai/occt-wasm)** and
  **[OpenCascade.js](https://ocjs.org/)** — OCCT compiled to WASM.
  Phase 1 STEP export uses one of these directly.
- **[Emscripten SDL2 port](https://github.com/emscripten-ports/SDL2)** —
  what Phase 2 uses for the canvas surface.
