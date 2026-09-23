#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

int32_t main() {
    ordered_set<int> st;

    st.insert(10);
    st.insert(5);
    st.insert(20);

    cout << *st.find_by_order(1) << endl; // 10
    cout << st.order_of_key(20) << endl;  // 2

    return 0;
}
