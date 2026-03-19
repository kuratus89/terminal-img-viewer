#pragma once
#include <map>
#include <string>
#include <vector>


struct pixel{
    std::string value;
    // bool rgb=0;
    int r=0,g=0,b=0;
    int color;
    bool operator==(const pixel& other)const{
        // return value == other.value && color == other.color && r == other.r && g == other.g && b == other.b && rgb == other.rgb;
        return value == other.value && color == other.color && r == other.r && g == other.g && b == other.b;
    }
};

struct win{
    std::string name="error";
    std::string type;
    std::map<std::string , std::string >sts;
    std::map<std::string , long long> stl;
    std::map<std::string , bool> stb;
    std::map<std::string , std::vector<std::vector<pixel>>> screen;
    std::map<std::string , std::vector<std::string>> stvs;
    // bool adv_scr=0;
};
extern bool gameon;
extern std::vector<std::vector<pixel>> pre_screen;
extern std::vector<std::string> color_pick_vec;
extern bool force_print;
extern bool debug;
extern int pcs;
extern int rcs;
extern bool diab;