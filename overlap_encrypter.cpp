#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
#include <algorithm>
#include <iterator>
using std::istringstream;


int NumberOfCharactersOverlap(const string& s1, const string& s2) {
  int countChars = 1, numOverlap = 0;
  // Special case checking
  if (s1 == "" || s2 == "") return 0;
  if (s1 == s2) return static_cast<int>(s2.length());
  // Loop through each set of substrings in the second word
  for (int i = 0; i < static_cast<int>(s2.length()); i++) {
    // Checks if count is greater length than any substring
    if (countChars > static_cast<int>(s1.length()) ||
        countChars > static_cast<int>(s2.length()))
      break;
    // Get substring for previous word based on loop iteration
    string s2sub = s2.substr(0, countChars);
    string s1sub =
        s1.substr(static_cast<int>(s1.length()) - countChars, countChars);
    // If the substring is at the beginning of the first word
    if (s1sub == s2sub) {
      numOverlap = countChars;
      countChars++;
    } else
      countChars++;
  }
  return numOverlap;
}

string CombineWords(const string& s1, const string& s2) {
  // Get number of overlap chars
  int countchars = NumberOfCharactersOverlap(s1, s2);
  string finalstr = s1, currentsub;
  // If overlap is possible combine the 2 words
  if (countchars != 0) {
    string s2sub = s2.substr(0, countchars);
    string s1sub =
        s1.substr(static_cast<int>(s1.length()) - countchars, countchars);
    currentsub =
        s2.substr(countchars, static_cast<int>(s2.length()) - countchars);
    // append the combined word to the final string
    finalstr += currentsub;
  } else
    finalstr = s1 + " " + s2;  // return the two words separated by space if
                               // they cannot be combined
  return finalstr;
}

string TranslateLine(const string& line) {
  string newLine;
  // lines 59 & 60 referenced from http://cplusplus.com/forum/beginner/161714/
  istringstream iss(line);  // put input string in stream and then add to vector
  vector<string> words(std::istream_iterator<string>(iss),
                       std::istream_iterator<string>{});  // populate vector
  if (static_cast<int>(words.size()) <= 1) {  // return line if empty or only has 1 word
    newLine = words.at(0);
  } else {
    string prevWord = "", finalLine = "";
    for (auto currentWord : words) {
      // iterate through words and combine them by calling CombineWords()
      if (prevWord == "") {
        prevWord = currentWord;
        continue;
      }
      finalLine = CombineWords(prevWord, currentWord);
      prevWord = finalLine;
    }
    newLine = finalLine;
  }
  return newLine;
}

int main() {
  string line;
  while (getline(cin, line)) {
    cout << TranslateLine(line) << endl;
  }
}
