#include <bits/stdc++.h>
using namespace std;

int arr[] = {1, 3, 8, 12, 9, 5, 2};

int f(int x) {
    // Just returns the value at index x
    return arr[x];
}

int main() {
    int low = 0;
    int high = 6; // Last index of arr

    while (high - low > 3) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (f(mid1) < f(mid2)) {
            // Maximum is in [mid1+1, high]
            low = mid1;
        } else {
            // Maximum is in [low, mid2-1]
            high = mid2;
        }
    }

    // Final loop to find exact maximum index
    int maxIndex = low;
    for (int i = low + 1; i <= high; i++) {
        if (f(i) > f(maxIndex)) {
            maxIndex = i;
        }
    }

    cout << "Maximum value is at index " << maxIndex << ", value = " << arr[maxIndex] << endl;

    return 0;
}







#include <bits/stdc++.h>
using namespace std;

// Our function: f(x) = (x - 3)^2 + 5 → Minimum at x = 3
double f(double x) {
    return (x - 3) * (x - 3) + 5;
}

int main() {
    double low = 0.0;
    double high = 10.0;
    double eps = 1e-9; // precision

    while (high - low > eps) {
        double mid1 = low + (high - low) / 3.0;
        double mid2 = high - (high - low) / 3.0;

        if (f(mid1) < f(mid2)) {
            // Minimum is in [low, mid2]
            high = mid2;
        } else {
            // Minimum is in [mid1, high]
            low = mid1;
        }
    }

    double ans = (low + high) / 2.0;
    cout << fixed << setprecision(9);
    cout << "Minimum at x = " << ans << ", f(x) = " << f(ans) << endl;

    return 0;
}
