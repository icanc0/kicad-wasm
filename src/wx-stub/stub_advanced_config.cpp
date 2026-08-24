// Minimum stub of ADVANCED_CFG for the WASM build.
// KiCad's real ADVANCED_CFG reads knobs from a config file at
// ~/.config/kicad/advanced; the WASM port has no such file. Return a
// singleton with the compiled-in defaults for the fields KiCad code
// actually references at link time. Fields not touched here are
// value-initialised to 0/false — harmless for the WASM subset.
#include <advanced_config.h>

// ADVANCED_CFG has a private default ctor plus a private
// loadFromConfigFile() etc. We only need to satisfy the linker for
// GetCfg() and the ctor.
ADVANCED_CFG::ADVANCED_CFG() {
    // Members shape_poly_set / polygon_triangulation actually read.
    // Values match the defaults kicad wires up in advanced_config.cpp
    // (see documented defaults on each field).
    m_TriangulateSimplificationLevel = 50;
    m_TriangulateMinimumArea         = 1000;
    m_TriangulateDelaunayRefine      = false;
}

const ADVANCED_CFG& ADVANCED_CFG::GetCfg() {
    static ADVANCED_CFG cfg;
    return cfg;
}

// Never called in WASM (no config file). Provide no-op body to satisfy
// any weak reference someone else might drag in.
void ADVANCED_CFG::Reload() {}
void ADVANCED_CFG::loadFromConfigFile() {}
void ADVANCED_CFG::loadSettings( wxConfigBase& ) {}
