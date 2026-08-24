// kicad-wasm sexpr POC — proof of life.
//
// Compiles the KiCad s-expression parser to WASM with embind, exposes:
//   parseSexpr(text: string) -> string  (dumped AST)
//
// The point of this file is: does the toolchain + basic KiCad C++ work
// under emscripten? If this returns valid parsed output for a real
// .kicad_pcb, the whole port strategy is viable.

#include <emscripten/bind.h>
#include "sexpr/sexpr_parser.h"
#include "sexpr/sexpr.h"
#include <string>
#include <sstream>

std::string parseSexpr( const std::string& aInput )
{
    try
    {
        SEXPR::PARSER parser;
        std::unique_ptr<SEXPR::SEXPR> tree = parser.Parse( aInput );

        if( !tree )
            return "ERROR: parser returned null";

        // Serialize back — round-trip proves the tree is well-formed.
        return tree->AsString( 0 );
    }
    catch( const std::exception& e )
    {
        return std::string( "EXCEPTION: " ) + e.what();
    }
}

// Also expose a summary — number of nodes, first-few children — so the
// browser demo can prove it actually parsed structure, not just text.
std::string sexprSummary( const std::string& aInput )
{
    try
    {
        SEXPR::PARSER parser;
        std::unique_ptr<SEXPR::SEXPR> tree = parser.Parse( aInput );

        if( !tree )
            return "{\"error\":\"null tree\"}";

        std::ostringstream ss;
        ss << "{";
        ss << "\"is_list\":" << ( tree->IsList() ? "true" : "false" );
        ss << ",\"is_symbol\":" << ( tree->IsSymbol() ? "true" : "false" );

        if( tree->IsList() )
        {
            ss << ",\"child_count\":" << tree->GetNumberOfChildren();

            if( tree->GetNumberOfChildren() > 0 )
            {
                SEXPR::SEXPR* first = tree->GetChild( 0 );

                if( first && first->IsSymbol() )
                    ss << ",\"root_symbol\":\"" << first->GetSymbol() << "\"";
            }
        }
        ss << "}";
        return ss.str();
    }
    catch( const std::exception& e )
    {
        std::string msg = std::string( "{\"exception\":\"" ) + e.what() + "\"}";
        return msg;
    }
}

EMSCRIPTEN_BINDINGS( kicad_sexpr ) {
    emscripten::function( "parseSexpr", &parseSexpr );
    emscripten::function( "sexprSummary", &sexprSummary );
}
