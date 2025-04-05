#ifndef FILEREADER_H
#define FILEREADER_H

#include "Types.h"

#include <string>
#include <vector>

class FileReader {
public:
  explicit FileReader(const std::string &file_name);
  ~FileReader() = default;

  [[nodiscard]] StringList get_lines() const { return lines; }

private:
  StringList lines;
};

#endif // FILEREADER_H
