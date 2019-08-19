#include <string>
#include <unordered_map>
#include "gmock/gmock.h"

using namespace testing;

const int maxLength{4};
const std::string NotADigit("*");

std::string padZero(const std::string &str)
{
  if (str.size() < 4) return str + std::string(maxLength - str.size(), '0');
  return str;
}

std::string head(const std::string &word) { return word.substr(0, 1); }
std::string tail(const std::string &word) { return word.substr(1); }
char lower(char ch) { return std::tolower(static_cast<unsigned char>(ch)); }

std::string encodedDigit(char letter)
{
  // clang-format off
  const std::unordered_map<char, std::string> encodings{
      {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
      {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"},
      {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
      {'d', "3"}, {'t', "3"},
      {'l', "4"},
      {'m', "5"}, {'n', "5"},
      {'r', "6"}};
  // clang-format on
  auto it = encodings.find(lower(letter));
  return it == encodings.end() ? NotADigit : it->second;
}

bool IsComplete(std::string word) { return word.size() == maxLength; }

std::string lastDigit(const std::string str)
{
  if (str.empty()) return NotADigit;
  return std::string(1, str.back());
}

std::string encodedDigits(const std::string &word)
{
  std::string result = encodedDigit(word.front());
  for (auto it = word.cbegin(); it != word.cend(); ++it) {
    if (IsComplete(result)) break;
    auto digit = encodedDigit(*it);
    if (digit != NotADigit and encodedDigit(*it) != lastDigit(result))
        result += encodedDigit(*it);
  }
  return result;
}
std::string upperFront(const std::string & string)
{
  return std::string(1,
                     std::toupper(static_cast<unsigned char>(string.front())));
}

class Soundex
{
 public:
  std::string encode(const std::string &word) const
  {
    return padZero(upperFront(head(word)) + tail(encodedDigits(word)));
  }
};

class SoundexEncoding : public testing::Test
{
 public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
  ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
  ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
  ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
  ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
  ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
  ASSERT_THAT(soundex.encode("Dcblb").size(), Eq(4u));
}

// TODO test pass before coding against it.
TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
  ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
  ASSERT_THAT(encodedDigit('b'), Eq(encodedDigit('f')));
  ASSERT_THAT(encodedDigit('c'), Eq(encodedDigit('g')));
  ASSERT_THAT(encodedDigit('d'), Eq(encodedDigit('t')));
  ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}
TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
  ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}
TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
  ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}
TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
  ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}
