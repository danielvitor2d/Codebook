#include <bits/stdc++.h>
using namespace std;

#define eps 1e-9
#define eq(a, b) (abs(a - b) < eps)
#define lt(a, b) (a < b - eps)
#define gt(a, b) (a > b + eps)
#define le(a, b) (a < b + eps)
#define ge(a, b) (a > b - eps)
#define ftype long double
/*#define eq(a, b) (a == b)
#define lt(a, b) (a < b)
#define gt(a, b) (a > b)
#define le(a, b) (a <= b)
#define ge(a, b) (a >= b)
#define ftype long long*/

// Begin Point 2D
struct point2d {
    ftype x, y;

    point2d() : x(0.0), y(0.0) {}
    point2d(const ftype& x, const ftype& y) : x(x), y(y) {}

    point2d& operator=(const point2d& oth) {
        x = oth.x; y = oth.y;
        return (*this);
    }
    point2d& operator+=(const point2d& oth) {
        x += oth.x; y += oth.y;
        return (*this);
    }
    point2d& operator-=(const point2d& oth) {
        x -= oth.x; y -= oth.y;
        return (*this);
    }
    point2d& operator*=(const ftype& factor) {
        x *= factor; y *= factor;
        return (*this);
    }
    point2d& operator/=(const ftype& factor) {
        x /= factor; y /= factor;
        return (*this);
    }
};
point2d operator+(const point2d& a, const point2d& b) {
    return point2d(a.x + b.x, a.y + b.y);
}
point2d operator-(const point2d& a, const point2d& b) {
    return point2d(a.x - b.x, a.y - b.y);
}
point2d operator*(const point2d& a, const ftype& factor) {
    return point2d(a.x * factor, a.y * factor);
}
point2d operator*(const ftype& factor, const point2d& a) {
    return point2d(factor * a.x, factor * a.y);
}
point2d operator/(const point2d& a, const ftype& factor) {
    return point2d(a.x / factor, a.y / factor);
}
bool operator==(const point2d& a, const point2d& b) {
    return (eq(a.x, b.x) and eq(a.y, b.y));
}
bool operator!=(const point2d& a, const point2d& b) {
    return !(a==b);
}
bool operator < (const point2d& a, const point2d& b) {
    return (lt(a.x, b.x) or (eq(a.x, b.x) and lt(a.y, b.y)));
}
bool operator > (const point2d& a, const point2d& b) {
    return (b < a);
}
bool operator <= (const point2d& a, const point2d& b) {
    return !(a > b);
}
bool operator >= (const point2d& a, const point2d& b) {
    return !(a < b);
}
// > 0 if |angle| < pi/2
// = 0 if |angle| = pi
// < 0 if |angle| > pi/2
ftype operator*(const point2d& a, const point2d& b) {
    return (a.x * b.x + a.y * b.y);
}
// < 0 if a comes before b in ccw
// = 0 if a is collinear to b
// > 0 if a comes after b in ccw
ftype operator^(const point2d& a, const point2d& b) {
    return (a.x * b.y - a.y * b.x);
}
ftype ccw(const point2d& a, const point2d& b) { 
    return (a ^ b);
}
// ccw(a, b, c) : > 0 if a comes before b counterclockwise in origin
// ccw(a, b, c) : < 0 if a comes after b counterclockwise in origin
ftype ccw(const point2d& a, const point2d& b, const point2d& origin) {
    return ccw(a - origin, b - origin);
}
ftype abs(const point2d& a) {
    return (a * a);
}
ftype norm(const point2d& a) {
    return sqrt(abs(a));
}
ftype dist(const point2d& a, const point2d& b) {
    return norm(a - b);
}
ftype dist2(const point2d& a, const point2d& b) {
    return abs(a - b);
}
ftype dist_point_to_line(const point2d& a, const point2d& p1, const point2d& p2) {
    return (a-p1)^(p2-p1)/norm(p2-p1);
}
ftype distance_segment_to_point(const point2d& p, const point2d& q, const point2d& a) {
    ftype l2 = dist2(p, q);
    if (eq(l2, 0)) return dist(p, a);
    ftype t = max((ftype)0, min((ftype)1, (a-p)*(q-p)/l2));
    point2d proj = p + t * (q-p);
    return dist(a, proj);
}
ftype proj(const point2d& a, const point2d& b) {
    return (a*b)/(b*b);
}
point2d pointProj(const point2d& a, const point2d& b) {
    return proj(a, b)*b;
}
ftype angle(const point2d& a) {
    return atan2(a.y, a.x);
}
ftype angle(const point2d& a, const point2d& b) {
    return atan2(a ^ b, a * b);
}
ftype angle(const point2d& a, const point2d& b, const point2d& origin) {
    return angle(a - origin, b - origin);
}
// Left rotation. Angle (rad)
point2d rotate(const point2d& a, const ftype& angleSin, const ftype& angleCos) {
    return point2d(a.x * angleCos - a.y * angleSin, a.x * angleSin + a.y * angleCos);
}
point2d rotate(const point2d& a, const ftype& angle) {
    return rotate(a, sin(angle), cos(angle));
}
// Pi/2 left rotation
point2d perp(const point2d& a) {
    return point2d(-a.y, a.x);
}
// 0 to 1 and 2 quadrant. 1 to 3 and 4
int half(const point2d& p) {
    if (gt(p.y, 0) or (eq(p.y, 0) and ge(p.x, 0))) return 0;
    return 1;
}
// angle(a) < angle(b)
bool cmpByAngle(const point2d& a, const point2d& b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    ftype c = a^b;
    if (eq(c, 0)) return lt(norm(a), norm(b));
    return gt(c, 0);
}
inline int sgn(ftype x) {
    return (ge(x, 0) ? (eq(x, 0) ? 0 : 1) : -1);
}
// Intersection of lines r : a + d1 * t
point2d intersect(const point2d& a1, const point2d& d1, const point2d& a2, const point2d& d2) {
    return a1 + ((a2-a1)^d2)/(d1^d2) * d1;
}
ftype area(vector<point2d> &pts){
    ftype ret = 0.0;
    for (int i = 2; i < (int)pts.size(); i++) {
        ret += ccw(pts[i] - pts[0], pts[i - 1] - pts[0]);
    }
    return abs(ret * 0.5);
}
ftype signed_area_parallelogram(const point2d& a, const point2d& b, const point2d& c) {
    return ccw(a, b, c);
}
ftype triangle_area(const point2d& a, const point2d& b, const point2d& c) {
    return abs(signed_area_parallelogram(a, b, c) * 0.5);
}
bool point_in_triangle(const point2d& a, const point2d& b, const point2d& c, const point2d& p) {
    ftype s1 = abs(ccw(b, c, a));
    ftype s2 = abs(ccw(a, b, p)) + abs(ccw(b, c, p)) + abs(ccw(c, a, p));
    return eq(s1, s2);
}
bool pointInSquare(const point2d& A, const point2d& B, const point2d& C, const point2d& D, const point2d& P) {
    ftype s1 = 2*abs((B-A)^(D-A));
    ftype s2 = abs((B-P)^(A-P)) + abs((C-P)^(B-P)) + abs((D-P)^(C-P)) + abs((A-P)^(D-P));
    return eq(s1, s2);
}
bool between(ftype l, ftype r, ftype x) {
    return (le(min(l, r), x) and ge(max(l, r), x));
}
bool pointInSegment(const point2d& a, const point2d& b, const point2d& p) {
    if (!eq(ccw(a, b, p), 0.0)) return false;
    return between(a.x, b.x, p.x) and between(a.y, b.y, p.y);
}
ftype up2(ftype a) {
    return (ftype)a * a;
}
// End Point 2D

// Begin Line
ftype det(ftype a, ftype b, ftype c, ftype d){
  return a * d - b * c;
}
struct Line {
    ftype a, b, c;
    Line () {}
    Line (ftype a1, ftype b1, ftype c1) : a(a1), b(b1), c(c1) {
        normalize();
    }
    Line (const point2d& p1, const point2d& p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
        normalize();
    }
    void normalize() {
        ftype z = sqrt(up2(a) + up2(b));
        if (!eq(z, 0)) { a /= z, b /= z, c /= z; }
        if (lt(a, 0.0) or (eq(a, 0.0) and lt(b, 0.0))) {
            a = -a;
            b = -b;
            c = -c;
        }
    }
};
bool intersection_point_of_lines(const Line& m, const Line& n, point2d &res) {
    ftype zn = det(m.a, m.b, n.a, n.b);
    if (eq(zn, 0.0)) return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}
bool parallel(const Line& m, const Line& n) {
    return eq(det(m.a, m.b, n.a, n.b), 0.0);
}
bool equivalent(const Line& m, const Line& n) {
    return eq(det(m.a, m.b, n.a, n.b), 0.0) and 
           eq(det(m.a, m.c, n.a, n.c), 0.0) and 
           eq(det(m.b, m.c, n.b, n.c), 0.0);
}
ftype dist(const Line& m, const point2d& p) {
    return abs(m.a * p.x + m.b * p.y + m.c) / 
           sqrt(up2(m.a) + up2(m.b));
}
// End Line
// Begin Segment
struct Segment {
    point2d a, b;
    Segment () {}
    Segment (const point2d& a1, const point2d b1) : a(a1), b(b1) {}
};
bool inter1(ftype a, ftype b, ftype c, ftype d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return le(max(a, c), min(b, d));
}
bool check_intersection(const Segment& s1, const Segment& s2) {
    point2d a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    if (ccw(a, d, c) == 0 and ccw(b, d, c) == 0)
        return (inter1(a.x, b.x, c.x, d.x) and 
                inter1(a.y, b.y, c.y, d.y)); 
    return sgn(ccw(b, c, a) != ccw(b, d, a) and 
               ccw(d, a, c) != ccw(d, b, c));
}
bool intersection_point_of_segments(const Segment& s1, const Segment& s2, Segment &ans) {
    point2d a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    if (!inter1(a.x, b.x, c.x, d.x) or 
        !inter1(a.y, b.y, c.y, d.y)) return false;
    Line m(a, b);
    Line n(c, d);
    if (parallel(m, n)) {
        if (!equivalent(m, n)) return false;
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        ans = Segment(max(a, c), min(b, d));
        return true;
    } else {
        point2d p(0, 0);
        intersection_point_of_lines(m, n, p);
        ans = Segment(p, p);
        return between(a.x, b.x, p.x) and between(a.y, b.y, p.y) and 
               between(c.x, d.x, p.x) and between(c.y, d.y, p.y);
    }
}
// End Segment

// Begin Circle
struct Circle {
    ftype x, y, r;
    Circle () {}
    Circle(ftype x1, ftype y1, ftype r1) : x(x1), y(y1), r(r1) {}
};
bool pointInCircle(const Circle& c, const point2d& p) {
    return ge(c.r, dist(point2d(c.x, c.y), p));
}
Circle circumCicle(const point2d& a, const point2d& b, const point2d& c) {
    point2d u((b-a).y, -((b-a).x));
    point2d v((c-a).y, -((c-a).x));
    point2d n = (c-b) * 0.5;
    ftype t = (u^n) / (v^u);
    point2d ct = (((a+c) * 0.5) + (v * t));
    ftype r = dist(ct, a);
    return Circle(ct.x, ct.y, r);
}
Circle inCircle(const point2d& a, const point2d& b, const point2d& c) {
    ftype m1 = dist(a, b);
    ftype m2 = dist(a, c);
    ftype m3 = dist(b, c);
    point2d ct = ((c * m1) + (b * m2) + a * m3) / (m1 + m2 + m3);
    ftype sp = 0.5 * (m1 + m2 + m3);
    ftype r = sqrt(sp * (sp - m1) * (sp - m2) * (sp - m3)) / sp;
    return Circle(ct.x, ct.y, r);
}
// Minimum enclosing circle
Circle minimumCircle(vector<point2d> p) {
    random_shuffle(p.begin(), p.end());
    Circle c = Circle(p[0].x, p[0].y, 0.0);
    for (int i = 0; i < (int)p.size(); ++i) {
        if (pointInCircle(c, p[i])) continue;
        c = Circle(p[i].x, p[i].y, 0.0);
        for (int j = 0; j < i; ++j) {
            if (pointInCircle(c, p[j])) continue;
            c = Circle((p[j].x + p[i].x)*0.5, (p[j].y + p[i].y)*0.5, 0.5*dist(p[j], p[i]));
            for (int k = 0; k < j; ++k) {
                if (pointInCircle(c, p[k])) continue;
                c = circumCicle(p[j], p[i], p[k]);
            }
        }
    }
    return c;
}
int circle_line_intersection(const Circle& circ, const Line& line, point2d& p1, point2d& p2) {
    ftype r = circ.r;
    ftype a = line.a, b = line.b, c = line.c + line.a * circ.x + line.b * circ.y; //take a circle to the (0, 0)
    ftype x0 = -a * c / (up2(a) + up2(b)), y0 = -b * c / (up2(a) + up2(b));       //(x0, y0) is the shortest distance point of the line for (0, 0)
    if (gt(up2(c), up2(r) * (up2(a) + up2(b)))) return 0;
    if (eq(up2(c), up2(r) * (up2(a) + up2(b)))) {
        p1.x = p2.x = x0 + circ.x;
        p1.y = p2.y = y0 + circ.y;
        return 1;
    } else {
        ftype d_2 = up2(r) - up2(c) / (up2(a) + up2(b));
        ftype mult = sqrt(d_2 / (up2(a) + up2(b)));
        p1.x = x0 + b * mult + circ.x;
        p2.x = x0 - b * mult + circ.x;
        p1.y = y0 - a * mult + circ.y;
        p2.y = y0 + a * mult + circ.y;
        return 2;
    }
}
int circle_intersection(const Circle& c1, const Circle& c2, point2d& p1, point2d& p2) {
    if (eq(c1.x, c2.x) and eq(c1.y, c2.y)){
        if (eq(c1.r, c2.r)) return -1; //INF
        else return 0;
    } else {
        Circle circ(0, 0, c1.r);
        Line line;
        line.a = -2 * (c2.x - c1.x);
        line.b = -2 * (c2.y - c1.y);
        line.c = up2(c2.x - c1.x) + up2(c2.y - c1.y) + up2(c1.r) - up2(c2.r);
        int sz = circle_line_intersection(circ, line, p1, p2);
        p1.x += c1.x;
        p2.x += c1.x;
        p1.y += c1.y;
        p2.y += c1.y;
        return sz;
    }
}
bool check_segment_covered_by_circles(const vector<Circle> &vc, const Segment& s) {
    vector<point2d> v = {s.a, s.b};
    Line l(s.a, s.b);
    for (Circle c : vc){
        point2d p1, p2;
        int inter = circle_line_intersection(c, l, p1, p2);
        if (inter >= 1 and between(s.a.x, s.b.x, p1.x) and between(s.a.y, s.b.y, p1.y))
        v.push_back(p1);
        if (inter == 2 and between(s.a.x, s.b.x, p2.x) and between(s.a.y, s.b.y, p2.y))
        v.push_back(p2);
    }
    sort(v.begin(), v.end());
    bool ans = true;
    for (int i = 1; i < (int)v.size(); i++){
        bool has = false;
        for (Circle c : vc){
            if (pointInCircle(c, v[i - 1]) and pointInCircle(c, v[i])) {
                has = true;
                break;
            }
        }
        ans &= has;
    }
    return ans;
}
void tangents(const point2d& c, double r1, double r2, vector<Line> &ans) {
    double r = r2 - r1;
    double z = up2(c.x) + up2(c.y);
    double d = z - up2(r);
    if (lt(d, 0)) return;
    d = sqrt(abs(d));
    Line l;
    l.a = (c.x * r + c.y * d) / z;
    l.a = (c.y * r + c.x * d) / z;
    l.c = r1;
    ans.push_back(l);
}
vector<Line> tangents(const Circle& a, const Circle& b) {
    vector<Line> ans;
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            tangents(point2d(b.x - a.x, b.y - a.y), a.r * i, b.r * j, ans);
    for (int i = 0; i < (int)ans.size(); ++i) {
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
        ans[i].normalize();
    }
    return ans;
}
// End Circle