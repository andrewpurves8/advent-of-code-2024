#ifndef INPUTCONVERSIONS_H
#define INPUTCONVERSIONS_H

#include "Types.h"

#include <string>
#include <vector>

StringGrid split_by_whitespace(const StringList &input_lines);

StringGrid split_all_letters(const StringList &input_lines);

StringList combine_letters(const StringGrid &input_lines);

StringGrid transpose(const StringGrid &input);

IntGrid convert_to_int(const StringGrid &input);

DoubleGrid convert_to_double(const StringGrid &input);

#endif // INPUTCONVERSIONS_H
