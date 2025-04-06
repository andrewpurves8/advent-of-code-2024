#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

LongList find_indices_of_delimiter(std::string s,
                                   const std::string &delimiter) {
  LongList result;
  std::size_t pos = 0;
  std::size_t total_removed_chars = 0;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    result.push_back(static_cast<int>(pos + total_removed_chars));
    auto removed_chars = pos + delimiter.length();
    s = s.substr(removed_chars);
    total_removed_chars += removed_chars;
  }
  return result;
}

LongGrid get_enabled_ranges(const std::string &input) {
  LongGrid ranges;
  auto do_indices = find_indices_of_delimiter(input, "do()");
  auto dont_indices = find_indices_of_delimiter(input, "don't()");

  auto start_index = 0;
  auto end_index = 0;
  bool enabled = true;
  while (true) {
    if (enabled) {
      auto next_dont = std::find_if(
          dont_indices.begin(), dont_indices.end(),
          [&start_index](int index) { return index > start_index; });
      if (next_dont == dont_indices.end()) {
        break;
      }
      end_index = *next_dont + 7;
      ranges.push_back({start_index, end_index});
      enabled = false;
    } else {
      auto next_do =
          std::find_if(do_indices.begin(), do_indices.end(),
                       [&end_index](int index) { return index > end_index; });
      if (next_do == do_indices.end()) {
        break;
      }
      start_index = *next_do + 4;
      enabled = true;
    }
  }

  if (enabled) {
    ranges.push_back({start_index, static_cast<long>(input.size())});
  }

  return ranges;
}

bool is_in_ranges(const LongGrid &ranges, long value) {
  return std::any_of(ranges.begin(), ranges.end(),
                     [value](const LongList &range) {
                       return value >= range[0] && value < range[1];
                     });
}

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day3.txt"
                              : "../example_inputs/day3_part2.txt";
  FileReader file_reader{input_file};
  auto inputs = file_reader.get_lines();
  assert(inputs.size() == 1);
  auto input = inputs[0];

  auto enabled_ranges = get_enabled_ranges(input);

  long result = 0;
  long first_int;
  long second_int;
  long total_removed_characters = 0;

  while (true) {
    auto mul_index = input.find("mul(");
    if (mul_index == std::string::npos || input.size() < 5) {
      break;
    }

    bool include =
        is_in_ranges(enabled_ranges, mul_index + total_removed_characters);

    auto removed_chars = mul_index + 4;
    input = input.substr(removed_chars);
    total_removed_characters += removed_chars;

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

    if (include) {
      result += first_int * second_int;
    }
    input = input_after_comma.substr(closing_brace_index + 1);
    total_removed_characters += closing_brace_index + 1 + comma_index + 1;
  }

  std::cout << result << std::endl;

  return 0;
}