#include <algorithm>
#include <string>

#include <string.h>

void to_lower(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), tolower);
}

bool wild_match(std::string str, std::string pat) {
  to_lower(str);
  to_lower(pat);

  std::string::const_iterator str_it = str.begin();
  for (std::string::const_iterator pat_it = pat.begin(); pat_it != pat.end();
       ++pat_it) {
    switch (*pat_it) {
      case '?':
        if (str_it == str.end()) {
          return false;
        }

        ++str_it;
        break;
      case '*': {
        if (pat_it + 1 == pat.end()) {
          return true;
        }

        const size_t max = strlen(&*str_it);
        for (size_t i = 0; i < max; ++i) {
          if (wild_match(&*(pat_it + 1), &*(str_it + i))) {
            return true;
          }
        }

        return false;
      }
      default:
        if (*str_it != *pat_it) {
          return false;
        }

        ++str_it;
    }
  }

  return str_it == str.end();
}

