#include <bits/stdc++.h>
using namespace std;

vector<point2d> convex_hull(vector<point2d> a){
    if (a.size() == 1) return a;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    vector<point2d> up, down;
    point2d p1 = a[0], p2 = a.back();
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < (int)a.size(); i++) {
        if ((i == (int)a.size() - 1) or ge(ccw(p2, a[i], p1), 0)) { // Accept collinear points
        // if ((i == (int)a.size() - 1) or gt(ccw(p2, a[i], p1), 0)) { // Don't accept collinear points
            while (up.size() >= 2 and lt(ccw(a[i], up.back(), up[up.size()-2]), 0)) up.pop_back(); // Accept collinear points
            // while (up.size() >= 2 and le(ccw(a[i], up.back(), up[up.size()-2]), 0)) up.pop_back(); // Don't accept collinear points
            up.push_back(a[i]);
        }
        if ((i == (int)a.size() - 1) or ge(ccw(a[i], p2, p1), 0)) { // Accept collinear points
        // if ((i == (int)a.size() - 1) or gt(ccw(a[i], p2, p1), 0)) { // Don't accept collinear points
            while (down.size() >= 2 and gt(ccw(a[i], down.back(), down[down.size()-2]), 0)) down.pop_back(); // Accept collinear points
            // while (down.size() >= 2 and ge(ccw(a[i], down.back(), down[down.size()-2]), 0)) down.pop_back(); // Don't accept collinear points
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++) a.push_back(up[i]);
    for (int i = (int)down.size()-2; i >= 1; i--) a.push_back(down[i]);
    return a;
}