#include <thread>
#include <iostream>
#include <vector>
#include "../storage/stora.h"
void hard_clear(){
    system("cls");
}

void soft_clear(){
    std::cout<<"\033[H";
}

void initilize_screen(std::vector<std::vector<pixel>> &scr , int x , int y , std::string value , int color){
    pixel pe;
    pe.value = value ;
    pe.color = color;
    scr = std::vector<std::vector<pixel>> (y , std::vector<pixel> (x , pe));
}

void add_text_to_screen(std::string s,std::vector<std::vector<pixel>> &scr , int x , int y , int color , bool are){
    long long it=0;
    long long temp=x;
    for(long long b=y ; b<scr.size() && it<s.size() ; b++){
        
        for(long long a=temp;a<scr[b].size() && it<s.size() ; a++){
            pixel p;
            p.value = std::string(1,s[it]);
            p.color = color;
            scr[b][a] = p;
            it++;
        }
        if(are)temp = x;
        else temp = 0;
    }
}
void compare_printer(std::vector<std::vector<pixel>> pre , std::vector<std::vector<pixel>> fro , std::string &s){
    //not now
}
void bulk_printer(std::vector<std::vector<pixel>> &scr , std::string &s){
    for(auto vao:scr){
        for(auto val:vao){
            s+=val.value;
            s+=color_pick_vec[val.color];
        }
        s.push_back('\n');
    }
}

void printer(std::vector<std::vector<pixel>> &scr){
    if((pre_screen==scr)&&(!force_print))return;
    std::string print;
    // if((pre_screen.size()&&scr.size())&&(pre_screen.size()==scr.size())&&(pre_screen[0].size()==scr[0].size())){
    // }
    bulk_printer(scr , print);
    if((pre_screen.size()<scr.size())||(pre_screen[0].size()<scr[0].size())|| force_print)hard_clear();
    else soft_clear();
    std::cout<<print;
    pre_screen = scr;
    if(force_print)force_print=0;

}
