#include "window.h"
#include "../output/output.h"
#include "error.h"
#include "../input/input.h"



void msg(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"]="msg";
        // wino.top().screen["main"] = pre_screen;
        wino.top().stb["hud"]=1;
        wino.top().stl["hudx"]=-1;
        wino.top().stl["hudy"]=-1;
        if(!wino.top().stvs.count("msg")){
            error_push("msg data not found");
            return;
        }
        if(!wino.top().stl.count("color")){
            error_push("color not found");
            return;
        }
        int w=0;
        for(auto  val:wino.top().stvs["msg"])w= std::max(w , (int)val.size());
        
        initilize_screen(wino.top().screen["msg"] , w+2 , wino.top().stvs["msg"].size()+2 , " " , wino.top().stl["color"] );
        add_boders(wino.top().screen["msg"] , wino.top().stl["color"]);
        int it=1;
        for(auto &val:wino.top().stvs["msg"]){
            add_text_to_screen(val , wino.top().screen["msg"] , 1 , it , wino.top().stl["color"] , 1);
            it++;
        }
        // hud_window(wino.top().screen["main"] , wino.top().screen["msg"] , -1 , -1);
    }
    int k = getkey();
    if(k!=-1){
        wino.pop();
        hard_clear();
    }
}