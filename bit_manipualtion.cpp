// Application: Use bitwise AND to check if a number is odd (last bit is 1) or even (last bit is 0).
bool isOdd(int n) {
    return n & 1;
}


// Application: Set the ith bit of a number to 1 (make it on) using bitwise OR.
int setBit(int n, int i) {
    return n | (1 << i); // 1 << i creates a mask with only the ith bit set to 1
}


// Application: Clear the ith bit of a number (set it to 0) using bitwise AND with NOT.
int clearBit(int n, int i) {
    return n & ~(1 << i); // ~(1 << i) creates a mask with all bits set to 1 except the ith bit
}


// Application: Toggle (flip) the ith bit using bitwise XOR.
int toggleBit(int n, int i) {
    return n ^ (1 << i); // XOR flips the ith bit (1 becomes 0, 0 becomes 1)
}


// Application: Check if the ith bit is set to 1 using bitwise AND.
bool isBitSet(int n, int i) {
    return n & (1 << i); // If result is non-zero, ith bit is set
}


// Application: Counts the number of 1-bits in the binary representation of a number.
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1; // Add the last bit (0 or 1) to count
        n >>= 1; // Shift right to process the next bit
    }
    return count;
}



// Application: Count the number of set bits using a faster method by turning off the lowest set bit in each iteration.
int countSetBitsKernighan(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Removes the lowest set bit
        count++;
    }
    return count;
}


// Application: Isolates the lowest set bit (rightmost 1-bit) of a number.
int lowestSetBit(int n) {
    return n & -n; // Isolates the rightmost 1-bit
}


// Application: Clears the lowest set bit (rightmost 1-bit).
int clearLowestSetBit(int n) {
    return n & (n - 1); // Clears the rightmost 1-bit
}


// Application: A number is a power of two if it has exactly one set bit.
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0; // True if n has exactly one set bit
}



// Application: Find the position of the most significant set bit (1-based index).
int mostSignificantBitPos(int n) {
    int pos = 0;
    while (n) {
        n >>= 1;
        pos++;
    }
    return pos;
}


// Application: Reverse the bits of a 32-bit number.
unsigned int reverseBits(unsigned int n) {
    unsigned int rev = 0;
    for (int i = 0; i < 32; i++) {
        rev <<= 1;
        rev |= (n & 1); // Append the last bit of n to rev
        n >>= 1;
    }
    return rev;
}



// Application: Computes XOR of all numbers from 1 to n in O(1).
int xorFrom1ToN(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}



// Application: Finds the single non-repeating element in an array using XOR in O(n) time.
int findUniqueElement(const vector<int> &arr) {
    int unique = 0;
    for (int num : arr) {
        unique ^= num; // XOR of all elements results in the unique one (XOR cancels pairs)
    }
    return unique;
}



// Application: Finds two non-repeating elements in an array using XOR and partitioning.
pair<int, int> findTwoUniqueElements(const vector<int> &arr) {
    int xorVal = 0;
    for (int num : arr) {
        xorVal ^= num; // XOR of all elements gives xor of two unique elements
    }

    // Find rightmost set bit in xorVal (this bit differentiates the two numbers)
    int setBit = xorVal & ~(xorVal - 1);
    
    int x = 0, y = 0;
    for (int num : arr) {
        if (num & setBit) {
            x ^= num; // XOR elements with the set bit
        } else {
            y ^= num; // XOR elements without the set bit
        }
    }
    return {x, y}; // The two unique numbers
}


// Application: Generates all subsets of a set using bitmasking.
void generateSubsets(const vector<int> &arr) {
    int n = arr.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(arr[i]); // Include arr[i] if ith bit is set in mask
            }
        }
        // Process the subset (e.g., print it or store it)
    }
}



// Application: Finds the next lexicographical number with the same number of set bits.
int nextHigherWithSameSetBits(int n) {
    int c = n & -n;
    int r = n + c;
    return (((r ^ n) >> 2) / c) | r;
}



__builtin_popcount(x): Count number of set bits.
__builtin_clz(x): Count leading zeros.
__builtin_ctz(x): Count trailing zeros.
__builtin_parity(x): Check the parity of the number.
__builtin_ffs(x): Find the position of the first set bit.
__builtin_bswap32(x): Reverse byte order (endian swap).
__builtin_expect(x, expected): Provide branch prediction hints.
__builtin_uadd_overflow(x, y, *result): Detect overflow during addition.

