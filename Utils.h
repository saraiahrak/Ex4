//
// Created by dekel on 18/01/2020.
//

#ifndef EX4__UTILS_H_
#define EX4__UTILS_H_

#include <string>
#include <vector>

using namespace std;

/**
 * Utils class
 * Util methods for program
 **/
class Utils {
 public:

  //strip string from right spaces
  static string rstrip(string s);

  //strip string from left spaces
  static string lstrip(string s);

  //strip string from spaces
  static string strip(string s);

  //split string to vector by delimiter
  static vector<string> splitByDelim(string toSplit, const char *delim);

  //trim the apostrophe from beggining and end of string
  static string trimApostrophe(string &s);

};
#endif //EX4__UTILS_H_
