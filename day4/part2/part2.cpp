#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

bool is_block_xmas(const StringGrid &input, int row, int col) {
  if (input[row + 1][col + 1] != "A") {
    return false;
  }

  auto first_combo_valid =
      (input[row][col] == "M" && input[row + 2][col + 2] == "S") ||
      (input[row][col] == "S" && input[row + 2][col + 2] == "M");

  if (!first_combo_valid) {
    return false;
  }

  auto second_combo_valid =
      (input[row][col + 2] == "M" && input[row + 2][col] == "S") ||
      (input[row][col + 2] == "S" && input[row + 2][col] == "M");

  return second_combo_valid;
}

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day4.txt"
                              : "../example_inputs/day4.txt";
  FileReader file_reader{input_file};
  const auto input = split_all_letters(file_reader.get_lines());

  long result = 0;

  for (auto row = 0; row + 2 < input.size(); ++row) {
    for (auto col = 0; col + 2 < input[row].size(); ++col) {
      if (is_block_xmas(input, row, col)) {
        result++;
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}