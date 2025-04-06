#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day3.txt"
                              : "../example_inputs/day3.txt";
  FileReader file_reader{input_file};
  auto inputs = file_reader.get_lines();
  assert(inputs.size() == 1);
  auto input = inputs[0];

  int result = 0;
  int first_int;
  int second_int;

  while (true) {
    auto mul_index = input.find("mul(");
    if (mul_index == std::string::npos || input.size() < 5) {
      break;
    }
    input = input.substr(mul_index + 4);

    auto comma_index = input.find(',');
    if (comma_index == std::string::npos) {
      break;
    }

    auto first = input.substr(0, comma_index);
    try {
      std::size_t pos = 0;
      first_int = std::stoi(first, &pos);
      if (pos != first.size()) {
        throw std::invalid_argument("Invalid number");
      }
    } catch (const std::invalid_argument &) {
      continue;
    }

    auto input_after_comma = input.substr(comma_index + 1);
    auto closing_brace_index = input_after_comma.find(')');
    if (closing_brace_index == std::string::npos) {
      break;
    }

    auto second = input_after_comma.substr(0, closing_brace_index);
    try {
      std::size_t pos = 0;
      second_int = std::stoi(second, &pos);
      if (pos != second.size()) {
        throw std::invalid_argument("Invalid number");
      }
    } catch (const std::invalid_argument &) {
      continue;
    }

    result += first_int * second_int;
    input = input_after_comma.substr(closing_brace_index + 1);
  }

  std::cout << result << std::endl;

  return 0;
}