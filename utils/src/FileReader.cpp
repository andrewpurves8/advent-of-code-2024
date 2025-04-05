#include "FileReader.h"

#include <fstream>

FileReader::FileReader(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + file_name);
  }

  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
}