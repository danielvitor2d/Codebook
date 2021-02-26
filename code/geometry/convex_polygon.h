#include <bits/stdc++.h>
using namespace std;

namespace ConvexPolygon {
    vector<point2d> vp;
    void init(const vector<point2d>& aux) {
        vp = convex_hull(aux);
    }
    bool pointInPolygon(const point2d& point) {
        if (vp.size() < 3) return pointInSegment(vp[0], vp[1], point);

        if (!eq(ccw(vp[1], point, vp[0]), 0.0) and 
             sgn(ccw(vp[1], point, vp[0])) != sgn(ccw(vp[1], vp.back(), vp[0]))) return false;

        if (!eq(ccw(vp.back(), point, vp[0]), 0.0) and 
             sgn(ccw(vp.back(), point, vp[0])) != sgn(ccw(vp.back(), vp[1], vp[0]))) return false;

        if (eq(ccw(vp[1], point, vp[0]), 0.0)) return ge(norm(vp[1]-vp[0]), norm(point-vp[0]));

        int pos = 1, l = 1, r = vp.size() - 2;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (le(ccw(vp[mid], point, vp[0]), 0.0)) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return point_in_triangle(vp[0], vp[pos], vp[pos+1], point);
    }
};