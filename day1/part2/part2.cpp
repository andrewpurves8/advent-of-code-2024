#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day1.txt"
                              : "../example_inputs/day1.txt";
  FileReader file_reader(input_file);
  auto inputs =
      convert_to_int(transpose(split_by_whitespace(file_reader.get_lines())));

  assert(inputs.size() == 2);
  assert(inputs[0].size() == inputs[1].size());

  long long result{0};
  for (auto i = 0; i < inputs[0].size(); ++i) {
    result += inputs[0][i] *
              std::count(inputs[1].begin(), inputs[1].end(), inputs[0][i]);
  }

  std::cout << result << std::endl;

  return 0;
}