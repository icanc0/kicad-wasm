// Minimal wx/debug.h stub for kicad-wasm.
// Just enough for what libs/sexpr + libs/kimath use.
#pragma once
#include <cassert>
#include "wx/defs.h"

// Note: msg deliberately dropped rather than && -combined with cond, because
// msg is commonly a wxString/std::string with no bool conversion.
#define wxASSERT(cond)              assert(cond)
#define wxASSERT_MSG(cond, msg)     do { (void)(msg); assert(cond); } while(0)
#define wxASSERT_MIN_BITSIZE(t, n)  static_assert(sizeof(t)*8 >= (n))
// wxCHECK / wxCHECK_MSG expand differently depending on whether "ret" is
// void. KiCad code commonly writes  wxCHECK( cond, /*void*/ );  Deal with
// the empty case by making the return statement conditional at parse time
// via a helper macro.
#define WX_STUB_RETURN_(ret)  return ret
#define WX_STUB_RETURN_VOID   return
#define wxCHECK(cond, ret)          do { if(!(cond)) return ret; } while(0)
#define wxCHECK2(cond, x)           do { if(!(cond)) { x; } } while(0)
#define wxCHECK2_MSG(cond, x, msg)  do { if(!(cond)) { x; } } while(0)
#define wxCHECK_MSG(cond, ret, msg) do { if(!(cond)) return ret; } while(0)
#define wxCHECK_RET(cond, msg)      do { if(!(cond)) return; } while(0)
#define wxFAIL_MSG(msg)             do { (void)(msg); assert(0 && "wxFAIL_MSG"); } while(0)
// wxFAIL is a bare identifier in real wxWidgets, no parens.
#define wxFAIL                      assert(0 && "wxFAIL")
#define wxCOMPILE_TIME_ASSERT(cond, msg)  static_assert(cond, #msg)
#define wxDEBUG_LEVEL 0
