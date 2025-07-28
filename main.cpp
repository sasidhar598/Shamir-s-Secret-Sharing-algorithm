
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>      
#include "json.hpp"    

using json = nlohmann::json;

double decodeBaseValue(const std::string &value, int base) {
    double result = 0;
    for (char ch : value) {
        int digit = isdigit(ch) ? (ch - '0') : (tolower(ch) - 'a' + 10);
        result = result * base + digit;
    }
    return result;
}

long long computeSecretFromJSON(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return -1;
    }

    json j;
    file >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    std::vector<std::pair<double, double>> points;

    for (int count = 0, key = 1; count < k; ++key) {
        std::string keyStr = std::to_string(key);
        if (j.contains(keyStr)) {
            std::string baseStr = j[keyStr]["base"];
            std::string valStr = j[keyStr]["value"];

            int base = std::stoi(baseStr);
            double y = decodeBaseValue(valStr, base);
            double x = key;
            points.emplace_back(x, y);
            count++;
        }
    }

    double f0 = 0;

    for (int i = 0; i < k; ++i) {
        double xi = points[i].first;
        double yi = points[i].second;

        double li = 1;
        for (int j = 0; j < k; ++j) {
            if (j != i) {
                double xj = points[j].first;
                li *= (-xj) / (xi - xj);
            }
        }

        f0 += yi * li;
    }

    return static_cast<long long>(round(f0));
}

int main() {
    long long secret1 = computeSecretFromJSON("input1.json");
    long long secret2 = computeSecretFromJSON("input2.json");

    std::cout << "Secret from Test Case 1: " << secret1 << std::endl;
    std::cout << "Secret from Test Case 2: " << secret2 << std::endl;

    return 0;
}
