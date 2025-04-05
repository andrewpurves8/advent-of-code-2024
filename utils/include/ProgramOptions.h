#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <string>

char *get_cmd_option(char **begin, char **end, const std::string &option);
bool cmd_option_exists(char **begin, char **end, const std::string &option);

#endif // PROGRAMOPTIONS_H
