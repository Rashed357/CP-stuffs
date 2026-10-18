
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ============================================================
// 1. GEOMETRY: POINT + CONVEX HULL + TWICE AREA
// ============================================================

struct Point {
    ll x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Cross product of vectors AB and AC.
// > 0 : counter-clockwise turn
// < 0 : clockwise turn
// = 0 : collinear
ll cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

// Returns the vertices of the convex hull in cyclic order.
// Collinear points lying inside hull edges are removed.
vector<Point> convexHull(vector<Point> points) {
    sort(points.begin(), points.end());

    points.erase(
        unique(points.begin(), points.end()),
        points.end()
    );

    int n = (int)points.size();

    if (n <= 1) return points;

    vector<Point> lower, upper;

    // Build the lower hull.
    for (const Point& p : points) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower.back(), p) <= 0) {
            lower.pop_back();
        }

        lower.push_back(p);
    }

    // Build the upper hull.
    for (int i = n - 1; i >= 0; --i) {
        const Point& p = points[i];

        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper.back(), p) <= 0) {
            upper.pop_back();
        }

        upper.push_back(p);
    }

    // Remove duplicate endpoints before combining.
    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());

    return lower;
}

// Shoelace formula: returns TWICE the polygon area.
// Returns 0 for fewer than 3 hull vertices.
ll twiceArea(const vector<Point>& hull) {
    int n = (int)hull.size();

    if (n < 3) return 0;

    ll area = 0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;

        area += hull[i].x * hull[j].y
              - hull[i].y * hull[j].x;
    }

    return abs(area);
}

// ============================================================
// 2. DSU: COMPONENTS + MEMBERS + CACHED CONVEX HULL AREA
// ============================================================

struct DSU {
    vector<int> parent, sz;
    vector<vector<int>> members;

    // Twice the convex hull area of each component root.
    vector<ll> componentArea;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        members.resize(n);
        componentArea.assign(n, 0);

        iota(parent.begin(), parent.end(), 0);

        for (int i = 0; i < n; ++i) {
            members[i].push_back(i);
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;

        return parent[x] = find(parent[x]);
    }

    // Merges the components containing a and b.
    // Returns the root of the resulting component.
    // If already connected, returns their existing root.
    int unite(int a, int b, const vector<Point>& points) {
        a = find(a);
        b = find(b);

        // No change if both towns belong to the same component.
        if (a == b) return a;

        // Union by size: keep the larger component as the root.
        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        // Combine the member lists.
        members[a].insert(
            members[a].end(),
            members[b].begin(),
            members[b].end()
        );

        members[b].clear();

        // Recompute the hull of the entire merged component.
        vector<Point> componentPoints;
        componentPoints.reserve(members[a].size());

        for (int id : members[a]) {
            componentPoints.push_back(points[id]);
        }

        vector<Point> hull = convexHull(componentPoints);

        // Cache the new answer at the resulting root.
        componentArea[a] = twiceArea(hull);

        return a;
    }

    // Returns the current component's twice area.
    ll getArea(int x) {
        return componentArea[find(x)];
    }
};

// ============================================================
// 3. MAIN
// ============================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Point> points(N);

    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    DSU dsu(N);

    while (M--) {
        int a, b;
        cin >> a >> b;

        --a;
        --b;

        int root = dsu.unite(a, b, points);

        cout << dsu.componentArea[root] << '\n';
    }

    return 0;
}
