#include "window.h"
#include "../output/output.h"
#include "screen_resize.h"
#include "../input/input.h"

void boot(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"]= "main";
        initilize_screen(wino.top().screen["main"] , -1 , -1 , " " , 0);
        int x,y;
        get_console_size(x,y);
        wino.top().stl["x"]=x;
        wino.top().stl["y"]=y;
        std::vector<std::string> ms = {
            "maximize your console window",
            "press any button to continue"
        };
        initilize_screen(wino.top().screen["ms"] , 30 , 4 , " " , 0);
        add_boders(wino.top().screen["ms"], 0);
        for(int i=0 ; i<ms.size() ; i++){
            add_text_to_screen(ms[i] , wino.top().screen["ms"], 1 , i+1 , 0 , 1);
        }
        hud_window(wino.top().screen["main"] , wino.top().screen["ms"] , -1  , -1 );
    }
    int x,y;
    get_console_size(x,y);
    if((wino.top().stl["x"]!=x)||(wino.top().stl["y"]!=y)){
        wino.top().stb["initilize"]=0;
        return;
    }
    int k = getkey();
    if(k!=-1){
        wino.pop();
        win ma;
        ma.name = "main_menu";
        wino.push(ma);
    }
}