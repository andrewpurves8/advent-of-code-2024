#include "FileReader.h"
#include "InputConversions.h"
#include "ProgramOptions.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>

void split_input(const StringList &full_input, StringList &rule_inputs,
                 StringList &update_inputs) {
  bool break_found = false;
  for (const auto &input : full_input) {
    if (input.empty()) {
      break_found = true;
      continue;
    }

    if (!break_found) {
      rule_inputs.push_back(input);
    } else {
      update_inputs.push_back(input);
    }
  }
}

bool is_update_valid(const IntList &update, const IntGrid &rules) {
  std::unordered_set<int> completed_pages;
  for (auto page : update) {
    for (const auto &rule : rules) {
      assert(rule.size() == 2);
      if (rule[1] == page &&
          std::find(update.begin(), update.end(), rule[0]) != update.end() &&
          completed_pages.find(rule[0]) == completed_pages.end()) {
        return false;
      }
    }
    completed_pages.insert(page);
  }
  return true;
}

int main(int argc, char *argv[]) {
  const auto input_file = cmd_option_exists(argv, argv + argc, "--real")
                              ? "../inputs/day5.txt"
                              : "../example_inputs/day5.txt";
  FileReader file_reader{input_file};
  const auto inputs = file_reader.get_lines();

  StringList rule_inputs;
  StringList update_inputs;

  split_input(inputs, rule_inputs, update_inputs);

  const auto rules = convert_to_int(split_by_char(rule_inputs, '|'));
  const auto updates = convert_to_int(split_by_char(update_inputs, ','));

  long result = 0;
  IntGrid valid_updates;

  for (const auto &update : updates) {
    if (is_update_valid(update, rules)) {
      valid_updates.push_back(update);
    }
  }

  for (const auto &update : valid_updates) {
    result += update[update.size() / 2];
  }

  std::cout << result << std::endl;

  return 0;
}