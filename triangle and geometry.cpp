#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    ============================================================
                    TRIGONOMETRY + GEOMETRY
    ============================================================

    IMPORTANT:
    C++ trig functions use RADIANS, NOT degrees.

    Degree <-> Radian:
        radian = degree * PI / 180
        degree = radian * 180 / PI
*/

// ============================================================
// CONSTANTS
// ============================================================

const double PI = acos(-1.0);
const double EPS = 1e-9;

// ============================================================
// DEGREE <-> RADIAN
// ============================================================

double rad(double degree)
{
    return degree * PI / 180.0;
}

double deg(double radian)
{
    return radian * 180.0 / PI;
}

// ============================================================
// BASIC TRIGONOMETRY
// ============================================================

/*
    sin(theta) = opposite / hypotenuse
    cos(theta) = adjacent / hypotenuse
    tan(theta) = opposite / adjacent

    sin^2(theta) + cos^2(theta) = 1
    tan(theta) = sin(theta) / cos(theta)

    Common values:

        angle      0     30      45      60      90
        ------------------------------------------------
        sin        0     1/2     1/sqrt2 sqrt3/2  1
        cos        1     sqrt3/2 1/sqrt2 1/2      0
        tan        0     1/sqrt3 1       sqrt3    undefined
*/

// ============================================================
// INVERSE TRIGONOMETRY
// ============================================================

/*
    asin(x) -> radians
    acos(x) -> radians
    atan(x) -> radians

    atan2(y, x) is better for finding angle of a point/vector.
*/

// Safe versions for floating-point errors
double safe_acos(double x)
{
    x = max(-1.0, min(1.0, x));
    return acos(x);
}

double safe_asin(double x)
{
    x = max(-1.0, min(1.0, x));
    return asin(x);
}

// ============================================================
// DISTANCE BETWEEN TWO POINTS
// ============================================================

double distance(double x1, double y1, double x2, double y2)
{
    return hypot(x2 - x1, y2 - y1);
}

// Example:
// distance(0, 0, 3, 4) = 5

// ============================================================
// ANGLE OF A VECTOR / POINT
// ============================================================

double vectorAngle(double x, double y)
{
    double theta = atan2(y, x);

    // Make range [0, 2*PI)
    if(theta < 0)
        theta += 2 * PI;

    return theta;
}

// Example:
// vectorAngle(1, 0)  = 0
// vectorAngle(0, 1)  = PI/2
// vectorAngle(-1, 0) = PI
// vectorAngle(1, -1) -> converted to [0, 2PI)

// ============================================================
// ANGLE BETWEEN TWO VECTORS
// ============================================================

double angleBetweenVectors(
    double ax, double ay,
    double bx, double by
)
{
    double dot = ax * bx + ay * by;

    double magA = hypot(ax, ay);
    double magB = hypot(bx, by);

    double x = dot / (magA * magB);

    return safe_acos(x);
}

// Example:
// angleBetweenVectors(1, 0, 0, 1) = PI/2

// ============================================================
// DOT PRODUCT
// ============================================================

double dotProduct(
    double ax, double ay,
    double bx, double by
)
{
    return ax * bx + ay * by;
}

// ============================================================
// 2D CROSS PRODUCT
// ============================================================

double crossProduct(
    double ax, double ay,
    double bx, double by
)
{
    return ax * by - ay * bx;
}

// ============================================================
// LAW OF COSINES
// ============================================================

/*
    c^2 = a^2 + b^2 - 2ab*cos(C)

    Find C:
    C = acos((a^2 + b^2 - c^2) / (2ab))
*/

double cosineLawAngle(double a, double b, double c)
{
    double x = (a * a + b * b - c * c) / (2.0 * a * b);

    return safe_acos(x);
}

// ============================================================
// LAW OF SINES
// ============================================================

/*
    a / sin(A) = b / sin(B) = c / sin(C)

    Example:
    Find B:

    B = asin(b * sin(A) / a)
*/

double sineLawAngle(double a, double b, double A)
{
    double x = b * sin(A) / a;

    return safe_asin(x);
}

// ============================================================
// TRIANGLE AREA
// ============================================================

/*
    Using two sides + included angle:

    Area = 0.5 * a * b * sin(C)
*/

double triangleArea(double a, double b, double C)
{
    return 0.5 * a * b * sin(C);
}

// ============================================================
// HERON'S FORMULA
// ============================================================

/*
    s = (a + b + c) / 2

    Area = sqrt(s(s-a)(s-b)(s-c))
*/

double heronArea(double a, double b, double c)
{
    double s = (a + b + c) / 2.0;

    return sqrt(max(
        0.0,
        s * (s - a) * (s - b) * (s - c)
    ));
}

// ============================================================
// ROTATE A POINT
// ============================================================

/*
    Rotate (x, y) by theta radians counter-clockwise:

    x' = x*cos(theta) - y*sin(theta)
    y' = x*sin(theta) + y*cos(theta)
*/

pair<double, double> rotatePoint(
    double x,
    double y,
    double theta
)
{
    double nx = x * cos(theta) - y * sin(theta);
    double ny = x * sin(theta) + y * cos(theta);

    return {nx, ny};
}

// ============================================================
// CIRCLE
// ============================================================

double circleArea(double r)
{
    return PI * r * r;
}

double circleCircumference(double r)
{
    return 2.0 * PI * r;
}

// ============================================================
// ARC LENGTH
// ============================================================

/*
    theta MUST be in radians.

    Arc length = r * theta
*/

double arcLength(double r, double theta)
{
    return r * theta;
}

// ============================================================
// SECTOR AREA
// ============================================================

/*
    theta MUST be in radians.

    Sector area = 0.5 * r^2 * theta
*/

double sectorArea(double r, double theta)
{
    return 0.5 * r * r * theta;
}

// ============================================================
// CHORD LENGTH
// ============================================================

/*
    theta = central angle in radians

    chord = 2*r*sin(theta/2)
*/

double chordLength(double r, double theta)
{
    return 2.0 * r * sin(theta / 2.0);
}

// ============================================================
// IMPORTANT TRIG IDENTITIES
// ============================================================

/*
    sin(-x) = -sin(x)
    cos(-x) =  cos(x)

    sin(PI-x) =  sin(x)
    cos(PI-x) = -cos(x)

    sin(PI+x) = -sin(x)
    cos(PI+x) = -cos(x)

    sin(2x) = 2*sin(x)*cos(x)

    cos(2x) = cos^2(x) - sin^2(x)
            = 2*cos^2(x) - 1
            = 1 - 2*sin^2(x)

    sin^2(x) + cos^2(x) = 1

    1 + tan^2(x) = sec^2(x)
    1 + cot^2(x) = csc^2(x)
*/

// ============================================================
// USEFUL GEOMETRY FORMULAS
// ============================================================

/*
    Distance:
        sqrt((x2-x1)^2 + (y2-y1)^2)

    Midpoint:
        ((x1+x2)/2, (y1+y2)/2)

    Circle:
        Area        = PI*r^2
        Circumference = 2*PI*r

    Arc:
        L = r*theta

    Sector:
        Area = 0.5*r^2*theta

    Chord:
        2*r*sin(theta/2)

    Triangle:
        Area = 0.5*a*b*sin(C)

    Heron's:
        s = (a+b+c)/2
        Area = sqrt(s(s-a)(s-b)(s-c))

    Law of Cosines:
        c^2 = a^2+b^2-2ab*cos(C)

    Dot product:
        A.B = ax*bx + ay*by

    2D Cross product:
        A x B = ax*by - ay*bx
*/

// ============================================================
// FLOATING POINT
// ============================================================

bool equal(double a, double b)
{
    return abs(a - b) < EPS;
}

bool isZero(double x)
{
    return abs(x) < EPS;
}

// ============================================================
// EXAMPLE SOLVE
// ============================================================

void solve()
{
    // -------------------------------
    // Degree -> Radian
    // -------------------------------

    double theta = rad(60);

    cout << "sin(60) = " << sin(theta) << endl;
    cout << "cos(60) = " << cos(theta) << endl;
    cout << "tan(60) = " << tan(theta) << endl;

    // -------------------------------
    // Inverse trig
    // -------------------------------

    cout << "asin(0.5) = "
         << deg(safe_asin(0.5))
         << " degree" << endl;

    cout << "acos(0.5) = "
         << deg(safe_acos(0.5))
         << " degree" << endl;

    cout << "atan(1) = "
         << deg(atan(1.0))
         << " degree" << endl;

    // -------------------------------
    // atan2
    // -------------------------------

    double angle = vectorAngle(1, 1);

    cout << "angle of (1,1) = "
         << deg(angle)
         << " degree" << endl;

    // -------------------------------
    // Distance
    // -------------------------------

    cout << "distance = "
         << distance(0, 0, 3, 4)
         << endl;

    // -------------------------------
    // Angle between vectors
    // -------------------------------

    double x = angleBetweenVectors(1, 0, 0, 1);

    cout << "vector angle = "
         << deg(x)
         << " degree" << endl;

    // -------------------------------
    // Law of Cosines
    // 3,4,5 triangle
    // -------------------------------

    double C = cosineLawAngle(3, 4, 5);

    cout << "C = "
         << deg(C)
         << " degree" << endl;

    // -------------------------------
    // Triangle area
    // -------------------------------

    cout << "triangle area = "
         << triangleArea(3, 4, rad(90))
         << endl;

    // -------------------------------
    // Heron's formula
    // -------------------------------

    cout << "Heron area = "
         << heronArea(3, 4, 5)
         << endl;

    // -------------------------------
    // Circle
    // -------------------------------

    double r = 5;

    cout << "circle area = "
         << circleArea(r)
         << endl;

    cout << "circle circumference = "
         << circleCircumference(r)
         << endl;

    // -------------------------------
    // Arc / sector
    // -------------------------------

    double a = rad(60);

    cout << "arc length = "
         << arcLength(r, a)
         << endl;

    cout << "sector area = "
         << sectorArea(r, a)
         << endl;

    // -------------------------------
    // Chord
    // -------------------------------

    cout << "chord = "
         << chordLength(r, a)
         << endl;

    // -------------------------------
    // Rotate point
    // -------------------------------

    auto [nx, ny] = rotatePoint(1, 0, rad(90));

    // Remove floating-point noise
    if(abs(nx) < EPS) nx = 0;
    if(abs(ny) < EPS) ny = 0;

    cout << "rotated point = "
         << nx << " " << ny << endl;
}

// ============================================================
// MAIN
// ============================================================

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
