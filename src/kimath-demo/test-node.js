const factory = require('./kimath-demo.js');

(async () => {
    const M = await factory();
    console.log(M.info());

    console.log('\n=== SEG::Length ===');
    console.log('length of (0,0)-(3,4) =', M.segLength(0, 0, 3, 4), '(expect 5)');
    console.log('length of (0,0)-(0,10) =', M.segLength(0, 0, 0, 10));

    console.log('\n=== SEG::SquaredDistance ===');
    console.log('point (0,3) to seg (0,0)-(0,10) sq =',
                M.segNearestSq(0, 0, 0, 10, 0, 3), '(expect 0)');
    console.log('point (5,0) to seg (0,0)-(0,10) sq =',
                M.segNearestSq(0, 0, 0, 10, 5, 0), '(expect 25)');

    console.log('\n=== polygon area (unit square) ===');
    const sq = [0, 0, 100, 0, 100, 100, 0, 100];
    console.log('area of 100x100 square =', M.polygonArea(sq), '(expect 10000)');

    console.log('\n=== convex hull ===');
    const pts = [0, 0, 10, 0, 10, 10, 0, 10, 5, 5, 3, 3];
    const hull = M.convexHull(pts);
    console.log('hull of', pts, '=', hull, '(expect the 4 corners)');
})();
