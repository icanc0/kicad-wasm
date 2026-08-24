// Node.js test harness for the sexpr WASM POC.
// Loads a real .kicad_pcb, feeds the first chunk to the parser, dumps summary.

const fs = require('fs');
const path = require('path');

// The generated sexpr.js is an ES-module-ish emscripten glue.
// Use require() — Emscripten's default output is compatible with CJS
// when MODULARIZE is off (default).
const factory = require('./sexpr.js');

(async () => {
    const Module = await factory();

    // Feed a small handmade sexp first.
    const simple = '(kicad_pcb (version 20221018) (generator "test"))';
    console.log('=== simple ===');
    console.log('parseSexpr:', Module.parseSexpr(simple).slice(0, 120));
    console.log('sexprSummary:', Module.sexprSummary(simple));

    // Now feed a real PCB file.
    const pcbPath = process.argv[2] || path.resolve(
        process.env.HOME,
        'not-my-projects/kicad-references/kicanvas/debug/examples/simple.kicad_pcb'
    );
    if (!fs.existsSync(pcbPath)) {
        console.log('no PCB fixture at', pcbPath, '— skip large test');
        return;
    }
    const bytes = fs.readFileSync(pcbPath, 'utf-8');
    console.log('\n=== real PCB:', pcbPath, '(', bytes.length, 'bytes ) ===');
    const t0 = Date.now();
    const summary = Module.sexprSummary(bytes);
    const dt = Date.now() - t0;
    console.log('parse+summarise:', dt, 'ms');
    console.log('summary:', summary);
})();
