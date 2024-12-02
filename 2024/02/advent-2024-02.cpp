// This file is a solution to https://adventofcode.com/2024/day/2.

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <vector>

using report = std::vector<int>;

std::vector<report> read_reports(const char* path) {
    std::vector<report> reports;

    // Read from the file until we hit the end-of-file indicator.
    std::ifstream input(path);
    while(input.good()) {
        // Read a line from the file. Each report is on its own line.
        std::string line;
        std::getline(input, line);
        if (line.size() == 0) {
            break;
        }

        // Parse the report line as a vector of integers.
        report r;
        std::stringstream line_stream(line);
        while (line_stream.good()) {
            int value = -1;
            line_stream >> value;
            if (value == -1) {
                break;
            }
            r.push_back(value);
        }

        if (!line_stream.eof()) {
            throw std::runtime_error("Error reading input file.");
        }

        reports.push_back(r);
    }

    if (!input.eof()) {
        throw std::runtime_error("Error reading input file.");
    }

    return reports;
}

bool is_safe(const report& r) {
    std::optional<bool> increasing;
    for (report::const_iterator i = r.begin(), j = std::next(i); j != r.end(); ++i, ++j) {
        int difference = std::abs(*i - *j);
        bool this_increasing = *i < *j;
        if (difference == 0 || difference > 3) {
            return false;
        } else if (!increasing.has_value()) {
            increasing = this_increasing;
        } else if (increasing != this_increasing) {
            return false;
        }
    }
    return true;
}

bool is_safe_with_dampener(const report& r) {
    if (is_safe(r)) {
        return true;
    }

    for (std::size_t i = 0; i < r.size(); ++i) {
        report copy = r;
        copy.erase(copy.begin() + i);
        if (is_safe(copy)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Path to input file must be given." << std::endl;
        return 1;
    }

    const std::vector<report> reports = read_reports(argv[1]);
    std::cout << std::ranges::count_if(reports, is_safe) << std::endl;
    std::cout << std::ranges::count_if(reports, is_safe_with_dampener) << std::endl;
}
