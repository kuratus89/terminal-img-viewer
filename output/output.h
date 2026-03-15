#pragma once
#include <string>
#include <vector>
#include "../storage/stora.h"


void soft_clear();
void hard_clear();
void initilize_screen(std::vector<std::vector<pixel>> &scr , int x , int y, std::string value , int color);
void add_text_to_screen(std::string s , std::vector<std::vector<pixel>> &scr , int x , int y, int color , bool are);
void printer(std::vector<std::vector<pixel>> &scr);
void adv_printer(std::vector<std::vector<pixel>> &scr);
void hud_window(std::vector<std::vector<pixel>> &main , std::vector<std::vector<pixel>> &secondary , int x , int y);
void add_boders(std::vector<std::vector<pixel>> &scr , int col);
void add_options(std::vector<std::vector<pixel>> &scr , std::vector<std::string>s , int selecter);
void hud_printer(std::vector<std::vector<pixel>> &scr , int x, int y);