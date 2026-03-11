#pragma once
#include <map>
#include <string>
#include <vector>


struct pixel{
    std::string value;
    int color;
    bool operator==(const pixel& other)const{
        return value == other.value && color == other.color;
    }
};

struct win{
    std::string name="error";
    std::string type;
    std::map<std::string , std::string >sts;
    std::map<std::string , long long> stl;
    std::map<std::string , bool> stb;
    std::map<std::string , std::vector<std::vector<pixel>>> screen;
};
extern bool gameon;
extern std::vector<std::vector<pixel>> pre_screen;
extern std::vector<std::string> color_pick_vec;
extern bool force_print;