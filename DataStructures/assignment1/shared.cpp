#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<fstream>
#include<string>
#include<exception>
#include<sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <functional>
#include <stdio.h>

using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
 //==============================================================

  
//check if the string is numerical
bool is_num(string str) {
   for (int i = 0; i < str.length(); i++){
	   	if (isdigit(str[i]) == false){
	   		return false;
	   	}
   }
	return true;
}
