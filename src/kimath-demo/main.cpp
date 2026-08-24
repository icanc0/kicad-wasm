// M1.2b — kimath binding POC.
//
// Prove libkimath.a is not just linkable but usable from JS.
// Exposes a couple of geometry predicates:
//   segArea(x1,y1, x2,y2)                       -> area under the segment
//   segLength(x1,y1, x2,y2)                     -> segment length
//   convexHull([[x,y],...])                     -> convex hull points
//   polygonArea([[x,y],...])                    -> signed polygon area
//
// Build:  make (in this dir), then:
//   node -e "require('./kimath-demo.js')().then(m=>console.log(m.segLength(0,0,3,4)))"

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <geometry/seg.h>
#include <geometry/shape_line_chain.h>
#include <geometry/shape_poly_set.h>
#include <geometry/convex_hull.h>

#include <string>
#include <vector>

using emscripten::val;

double segLength( double x1, double y1, double x2, double y2 ) {
    SEG s( VECTOR2I( (int)x1, (int)y1 ), VECTOR2I( (int)x2, (int)y2 ) );
    return s.Length();
}

double segNearestSq( double x1, double y1, double x2, double y2, double px, double py ) {
    SEG s( VECTOR2I( (int)x1, (int)y1 ), VECTOR2I( (int)x2, (int)y2 ) );
    return s.SquaredDistance( VECTOR2I( (int)px, (int)py ) );
}

// Compute the signed area of a polygon given a flat array of point pairs.
// aFlatXY: [x0, y0, x1, y1, x2, y2, ...]
double polygonArea( val aFlatXY ) {
    std::vector<double> flat = emscripten::vecFromJSArray<double>( aFlatXY );
    SHAPE_LINE_CHAIN chain;
    for( size_t i = 0; i + 1 < flat.size(); i += 2 )
        chain.Append( VECTOR2I( (int)flat[i], (int)flat[i + 1] ) );
    chain.SetClosed( true );
    return chain.Area( true );
}

// Convex hull of a flat point array, returns a flat point array.
val convexHullOf( val aFlatXY ) {
    std::vector<double> flat = emscripten::vecFromJSArray<double>( aFlatXY );
    std::vector<VECTOR2I> input;
    for( size_t i = 0; i + 1 < flat.size(); i += 2 )
        input.emplace_back( (int)flat[i], (int)flat[i + 1] );

    std::vector<VECTOR2I> hull;
    BuildConvexHull( hull, input );

    val out = val::array();
    int idx = 0;
    for( const auto& p : hull ) {
        out.set( idx++, p.x );
        out.set( idx++, p.y );
    }
    return out;
}

std::string info() {
    return "kicad-wasm kimath binding: SEG, SHAPE_LINE_CHAIN, convex_hull "
           "linked from libkimath.a";
}

EMSCRIPTEN_BINDINGS( kimath_demo ) {
    emscripten::function( "info",         &info );
    emscripten::function( "segLength",    &segLength );
    emscripten::function( "segNearestSq", &segNearestSq );
    emscripten::function( "polygonArea",  &polygonArea );
    emscripten::function( "convexHull",   &convexHullOf );
}
