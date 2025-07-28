#include <iostream>
#include <vector>
#include <string>
using namespace std;

using bigint = __int128;

bigint toBigInt(const string& s, int base) {
    bigint res = 0;
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
        res = res * base + d;
    }
    return res;
}

string bigIntToStr(bigint n) {
    if (n == 0) return "0";
    string s;
    bool neg = n < 0;
    if (neg) n = -n;
    while (n > 0) {
        s = char('0' + n % 10) + s;
        n /= 10;
    }
    return neg ? "-" + s : s;
}

bigint lagrange(const vector<bigint>& x, const vector<bigint>& y) {
    int k = x.size();
    bigint res = 0;
    for (int i = 0; i < k; ++i) {
        bigint num = 1, den = 1;
        for (int j = 0; j < k; ++j)
            if (i != j) num *= -x[j], den *= x[i] - x[j];
        res += y[i] * (num / den);
    }
    return res;
}

void solve1() {
    vector<bigint> x = {1, 2, 3};
    vector<bigint> y = {
        toBigInt("4", 10),
        toBigInt("111", 2),
        toBigInt("12", 10)
    };
    cout << "Secret (c) from Testcase 1 = " << bigIntToStr(lagrange(x, y)) << endl;
}

void solve2() {
    vector<string> vals = {
        "13444211440455345511", "aed7015a346d63", "6aeeb69631c227c", "e1b5e05623d881f",
        "316034514573652620673", "2122212201122002221120200210011020220200",
        "20120221122211000100210021102001201112121", "20220554335330240002224253",
        "45153788322a1255483", "1101613130313526312514143"
    };
    vector<int> bases = {6, 15, 15, 16, 8, 3, 3, 6, 12, 7};
    vector<bigint> x, y;
    for (int i = 0; i < 7; ++i) {
        x.push_back(i + 1);
        y.push_back(toBigInt(vals[i], bases[i]));
    }
    cout << "Secret (c) from Testcase 2 = " << bigIntToStr(lagrange(x, y)) << endl;
}

int main() {
    solve1();
    solve2();
    return 0;
}
