#include <windows.h>
#include <iostream>
#include "error.h"
#include "window.h"
#include "../output/output.h"
#include "../input/input.h"


bool get_console_size(int &w , int &h){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &csbi)){
        // w = csbi.srWindow.Right - csbi.srWindow.Left;
        // h = csbi.srWindow.Bottom - csbi.srWindow.Top;
        w = csbi.dwSize.X-1;
        h = csbi.dwSize.Y-1;
        return 1;
    }
    return 0;
}

void screen_resize(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"] = "juju";
        wino.top().stb["adv"]=1;
    }
    int w, h;
    get_console_size(w,h);
    pixel pe;
    pe.b=0;
    pe.g=0;
    pe.r=0;
    if((w>=wino.top().stl["x"])&&(h*2>=(wino.top().stl["y"])))pe.g=255;
    else pe.r = 255;
    wino.top().screen["juju"] = std::vector<std::vector<pixel>> ((std::min(h*2 ,(int) wino.top().stl["y"])) , std::vector<pixel> (std::min(w ,(int) wino.top().stl["x"]) , pe));
    int k = getkey();
    // if((k==' ')&&(w>=wino.top().stl["x"])&&(h*2>=(wino.top().stl["y"]))){
    if(k==' '){
        std::string apix = wino.top().sts["apix"];
        std::string apiy = wino.top().sts["apiy"];
        wino.pop();
        wino.top().stl["apix"] = w;
        wino.top().stl["apiy"] = h;
        hard_clear();
        return;
    }
    
    
}
