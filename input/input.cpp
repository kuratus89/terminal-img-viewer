#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else 
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

void initilize_linux_terminal(){
    #ifdef __linux__
    termios t;
    tcgetattr(STDIN_FILENO , $t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO , TCSANOW , &t);
    fcntl(STDIN_FILENO , F_SETFL , O_NONBLOCK);

    #endif
}

int getkey(){
    #ifdef _WIN32
    if(_kbhit())return _getch();
    #else 
    char ch;
    if(read(STDIN_FILENO , &ch , 1)>0)return ch;
    #endif
    return -1;
}