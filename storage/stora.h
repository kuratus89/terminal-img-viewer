#pragma once
#include <map>
#include <string>
extern bool gameon;

struct win{
    std::string name="error";
    std::string type;
    std::map<std::string , std::string >sts;
    std::map<std::string , long long> stl;
    std::map<std::string , bool> stb;
};