// This file is a solution to https://adventofcode.com/2024/day/3.
// Using a regex is a more obvious choice, but a more manual algorithm is implemented here.

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Must provide input file path." << std::endl;
        return 1;
    }

    // So many locals!
    std::ifstream input(argv[1]);
    unsigned result = 0;
    unsigned result_with_enable = 0;
    static const std::string enable_format = "do()";
    static const std::string disable_format = "don't()";
    static const std::string format = "mul(1,2)";
    bool enabled = true;
    unsigned enable_format_position = 0;
    unsigned disable_format_position = 0;
    unsigned format_position = 0;
    unsigned numbers[2];

    while (input.good()) {
        char format_char = format[format_position];
        char enable_format_char = enable_format[enable_format_position];
        char disable_format_char = disable_format[disable_format_position];

        if (format_char == '1' || format_char == '2') {
            std::string number_string;
            for (int i = 0; i < 3; ++i) {
                char input_char = input.peek();
                if (input_char >= '0' && input_char <= '9') {
                    number_string += input_char;
                    input.get();
                } else {
                    break;
                }
            }

            if (number_string.size()) {
                numbers[format_char - '1'] = std::stoi(number_string);
                ++format_position;
            } else {
                format_position = numbers[0] = numbers[1] = 0;
            }
        } else {
            char input_char;
            input >> input_char;

            // Handle format.
            if (input_char == format_char) {
                if (++format_position == format.size()) {
                    result += numbers[0] * numbers[1];
                    if (enabled) {
                        result_with_enable += numbers[0] * numbers[1];
                    }
                    format_position = numbers[0] = numbers[1] = 0;
                }
            } else {
                format_position = numbers[0] = numbers[1] = 0;
            }

            // Handle enable format.
            if (input_char == enable_format_char) {
                if (++enable_format_position == enable_format.size()) {
                    enabled = true;
                    enable_format_position = 0;
                }
            } else {
                enable_format_position = 0;
            }

            // Handle disable format.
            if (input_char == disable_format_char) {
                if (++disable_format_position == disable_format.size()) {
                    enabled = false;
                    disable_format_position = 0;
                }
            } else {
                disable_format_position = 0;
            }
        }
    }

    std::cout << result << std::endl;
    std::cout << result_with_enable << std::endl;
}
