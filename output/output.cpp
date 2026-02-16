#include <thread>
#include <iostream>
void hard_clear(){
    system("cls");
}

void soft_clear(){
    std::cout<<"\033[H";
}
