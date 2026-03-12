#include <windows.h>
#include <iostream>
#include <thread>
#include "input/input.h"
#include "storage/stora.h"
#include "window/window.h"
#include "output/output.h"
void init_console(){
    SetConsoleOutputCP(CP_UTF8);
    win temp;
    temp.name = "main_menu";
    wino.push(temp);
    initilize_screen(pre_screen , 1,1," " , 0);
}

int main(){
    init_console();
    std::cout<<"\033[?25l";
    while(gameon){
        window();
    }
}