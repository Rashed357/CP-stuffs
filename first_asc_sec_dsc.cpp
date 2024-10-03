bool sortByFirstAscSecondDesc(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first)
        return a.second > b.second; // If first elements are equal, sort by second element in descending order
    return a.first < b.first; // Otherwise, sort by first element in ascending order
}
