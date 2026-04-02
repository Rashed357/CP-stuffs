#include <bits/stdc++.h>
using namespace std;

// -------------------- MACROS --------------------
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>

#define vi vector<int>
#define vll vector<ll>
#define vpii vector<pair<int,int>>

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define F first
#define S second

#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

// -------------------- DEBUG --------------------
#define debug(x) cerr << #x << " = " << x << endl;

// -------------------- VECTOR --------------------
void vector_example() {
    vector<int> v = {3,1,4,1,5};

    v.pb(10);                 // insert
    v.pop_back();             // remove last

    sort(all(v));             // ascending
    sort(rall(v));            // descending

    reverse(all(v));

    cout << v.size() << endl;

    // binary search
    if (binary_search(all(v), 4)) cout << "Found\n";

    // lower_bound / upper_bound
    auto it = lower_bound(all(v), 4); // first >= 4
    auto it2 = upper_bound(all(v), 4); // first > 4
}

// -------------------- SET --------------------
void set_example() {
    set<int> s;

    s.insert(5);
    s.insert(1);
    s.insert(3);

    s.erase(3);

    if (s.count(5)) cout << "Exists\n";

    auto it = s.lower_bound(2);
}

// -------------------- MULTISET --------------------
void multiset_example() {
    multiset<int> ms;

    ms.insert(5);
    ms.insert(5);

    ms.erase(ms.find(5)); // erase one occurrence

    cout << ms.count(5) << endl;
}

// -------------------- UNORDERED SET --------------------
void unordered_set_example() {
    unordered_set<int> us;

    us.insert(10);
    us.count(10);
}

// -------------------- MAP --------------------
void map_example() {
    map<int,int> mp;

    mp[1] = 10;
    mp[2]++;

    cout << mp[1] << endl;

    if (mp.count(2)) cout << "Yes\n";

    for (auto [k,v] : mp) {
        cout << k << " " << v << endl;
    }
}

// -------------------- MULTIMAP --------------------
void multimap_example() {
    multimap<int,int> mm;

    mm.insert({1,10});
    mm.insert({1,20});

    auto range = mm.equal_range(1);

    for (auto it = range.first; it != range.second; it++) {
        cout << it->S << endl;
    }
}

// -------------------- UNORDERED MAP --------------------
void unordered_map_example() {
    unordered_map<int,int> ump;

    ump[1] = 100;
    ump[2]++;
}

// -------------------- STACK --------------------
void stack_example() {
    stack<int> st;

    st.push(1);
    st.push(2);

    cout << st.top() << endl;

    st.pop();
}

// -------------------- QUEUE --------------------
void queue_example() {
    queue<int> q;

    q.push(1);
    q.push(2);

    cout << q.front() << endl;

    q.pop();
}

// -------------------- DEQUE --------------------
void deque_example() {
    deque<int> dq;

    dq.push_back(1);
    dq.push_front(2);

    dq.pop_back();
    dq.pop_front();
}

// -------------------- PRIORITY QUEUE --------------------
void pq_example() {
    // max heap
    priority_queue<int> pq;
    pq.push(5);
    pq.push(1);

    cout << pq.top() << endl;

    // min heap
    priority_queue<int, vector<int>, greater<int>> minpq;
}

// -------------------- PAIR --------------------
void pair_example() {
    pair<int,int> p = {1,2};

    cout << p.F << " " << p.S << endl;
}

// -------------------- ALGORITHMS --------------------
void algo_example() {
    vector<int> v = {1,2,3,4,5};

    // gcd
    cout << __gcd(10,5) << endl;

    // min / max
    cout << *min_element(all(v)) << endl;
    cout << *max_element(all(v)) << endl;

    // sum
    cout << accumulate(all(v), 0) << endl;

    // count
    cout << count(all(v), 3) << endl;
}

// -------------------- STRING --------------------
void string_example() {
    string s = "hello";

    reverse(all(s));

    s += " world";

    cout << s.substr(0,3) << endl;
}

// -------------------- BITSET --------------------
void bitset_example() {
    bitset<8> b("10101010");

    cout << b.count() << endl; // number of 1s
    cout << b.to_string() << endl;
}

// -------------------- MAIN --------------------
int main() {
    fast_io;

    // call any example for testing

    return 0;
}
