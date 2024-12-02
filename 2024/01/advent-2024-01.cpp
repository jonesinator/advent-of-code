// This file is a solution to https://adventofcode.com/2024/day/1.

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Path to input file must be given." << std::endl;
        return 1;
    }

    // Read in the input file into two vectors.
    std::ifstream input(argv[1]);
    std::vector<int> column_1;
    std::vector<int> column_2;
    while (input.good()) {
        int column_1_value = -1, column_2_value = -1;
        input >> column_1_value >> column_2_value;
        if (column_1_value == -1 || column_2_value == -1) {
            break;
        }
        column_1.push_back(column_1_value);
        column_2.push_back(column_2_value);
    }
    if (!input.eof()) {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }

    // Compute the sum of the element-wise differences of the sorted columns.
    int difference = 0;
    std::ranges::sort(column_1);
    std::ranges::sort(column_2);
    for (auto c1 = column_1.begin(), c2 = column_2.begin(); c1 != column_1.end(); ++c1, ++c2) {
        difference += std::abs(*c1 - *c2);
    }
    std::cout << "Difference: " << difference << std::endl;

    // Convert the second column into a map that tracks the number of occurrences of each value in
    // the column.
    std::map<int, int> column_2_counts;
    for (auto c2 = column_2.begin(); c2 != column_2.end(); ++c2) {
        column_2_counts[*c2]++;
    }

    // Compute the "similarity" by multiplying each value in the first column by its number of
    // occurrences in the second column.
    int similarity = 0;
    for (auto c1 = column_1.begin(); c1 != column_1.end(); ++c1) {
        similarity += *c1 * column_2_counts[*c1];
    }
    std::cout << "Similarity: " << similarity << std::endl;
}
