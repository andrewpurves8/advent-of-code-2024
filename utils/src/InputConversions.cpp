#include "InputConversions.h"

#include <sstream>

StringGrid split_by_whitespace(const StringList &input) {
  StringGrid result;
  for (const auto &line : input) {
    std::istringstream iss(line);
    StringList words((std::istream_iterator<std::string>(iss)),
                     std::istream_iterator<std::string>());
    result.push_back(words);
  }
  return result;
}

StringGrid transpose(const StringGrid &input) {
  StringGrid result;
  if (input.empty()) {
    return result;
  }

  auto num_rows = input.size();
  auto num_cols = input[0].size();

  result.resize(num_cols, StringList(num_rows));

  for (auto i = 0; i < num_rows; ++i) {
    for (auto j = 0; j < num_cols; ++j) {
      result[j][i] = input[i][j];
    }
  }
  return result;
}

IntGrid convert_to_int(const StringGrid &input) {
  IntGrid result;
  for (const auto &row : input) {
    IntList int_row;
    for (const auto &val : row) {
      int_row.push_back(std::stoi(val));
    }
    result.push_back(int_row);
  }
  return result;
}

DoubleGrid convert_to_double(const StringGrid &input) {
  DoubleGrid result;
  for (const auto &row : input) {
    DoubleList double_row;
    for (const auto &val : row) {
      double_row.push_back(std::stod(val));
    }
    result.push_back(double_row);
  }
  return result;
}