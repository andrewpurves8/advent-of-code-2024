#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

long xmas_instances_in_list(const StringList &list) {
  long result = 0;
  for (const auto &line : list) {
    std::size_t pos = line.find("XMAS", 0);
    while (pos != std::string::npos) {
      result++;
      pos = line.find("XMAS", pos + 1);
    }

    auto line_reversed = std::string(line.rbegin(), line.rend());
    pos = line_reversed.find("XMAS", 0);
    while (pos != std::string::npos) {
      result++;
      pos = line_reversed.find("XMAS", pos + 1);
    }
  }
  return result;
}

StringList get_diagonal_strings(const StringGrid &letter_grid,
                                bool flip_direction) {
  StringList result_list;
  const auto width = letter_grid.front().size();
  const auto height = letter_grid.size();

  auto start_row = height - 1;
  auto start_column = 0;
  std::size_t column;

  while (start_column < width) {
    std::string result_string;
    auto row = start_row;
    column = start_column;

    while ((row < height) && (column < width)) {
      result_string +=
          letter_grid[row][flip_direction ? width - 1 - column : column];
      ++row;
      ++column;
    }

    result_list.push_back(result_string);

    if (start_row > 0) {
      --start_row;
    } else {
      ++start_column;
    }
  }

  return result_list;
}

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day4.txt"
                              : "../example_inputs/day4.txt";
  FileReader file_reader{input_file};
  const auto inputs = file_reader.get_lines();

  long result = 0;
  result += xmas_instances_in_list(inputs);

  const auto letter_grid = split_all_letters(inputs);
  const auto letter_grid_transposed = transpose(letter_grid);
  StringList inputs_transposed = combine_letters(letter_grid_transposed);
  result += xmas_instances_in_list(inputs_transposed);

  result += xmas_instances_in_list(get_diagonal_strings(letter_grid, false));
  result += xmas_instances_in_list(get_diagonal_strings(letter_grid, true));

  std::cout << result << std::endl;

  return 0;
}