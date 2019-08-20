#ifndef CHAR_STRING_UTIL_H_
#define CHAR_STRING_UTIL_H_
#include <string>

char lower(char ch);

bool isVowel(char ch);

std::string head(const std::string &word);

std::string tail(const std::string &word);

std::string paddingChar(const std::string &str, char ch, size_t size);

std::string upperFront(const std::string &string);

#endif
