#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

bool is_safe(const IntList &record) {
  auto max_difference = std::numeric_limits<int>::min();
  auto min_difference = std::numeric_limits<int>::max();

  for (auto i = 0; i + 1 < record.size(); ++i) {
    const auto difference = record[i + 1] - record[i];
    max_difference = std::max(max_difference, difference);
    min_difference = std::min(min_difference, difference);

    if (difference == 0 || std::abs(difference) > 3 ||
        max_difference * min_difference < 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day2.txt"
                              : "../example_inputs/day2.txt";
  FileReader file_reader(input_file);
  auto inputs = convert_to_int(split_by_whitespace(file_reader.get_lines()));

  int result{0};
  for (const auto &record : inputs) {
    if (is_safe(record)) {
      result++;
    } else {
      for (auto i = 0; i < record.size(); ++i) {
        IntList dampened_record{record};
        dampened_record.erase(std::next(dampened_record.begin(), i));
        if (is_safe(dampened_record)) {
          result++;
          break;
        }
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}