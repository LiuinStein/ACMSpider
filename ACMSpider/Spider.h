#pragma once
#include <string>

bool login_acm(const std::string & __username, const std::string & __pwd);

bool get_submit_code(const char * __url, std::string & __code, std::string & __lang, int & __page);
