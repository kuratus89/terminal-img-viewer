#include <windows.h>
#include <iostream>
#include <thread>

void init_console(){
    SetConsoleOutputCP(CP_UTF8);
}

int main(){
    init_console();
    std::cout<<"\033[?25l]";
}