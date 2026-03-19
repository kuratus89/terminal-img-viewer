#include "window.h"
#include "../output/output.h"
#include "error.h"
#include "../input/input.h"

void input_builder(){
    int y=1;
    if(wino.top().sts.count("title")){
        initilize_screen(wino.top().screen["main"] , 15 , 4 ," " , 0 );
        add_text_to_screen(wino.top().sts["title"] , wino.top().screen["main"] , 1 , y , 0 ,1);
        y++;
    }
    else initilize_screen(wino.top().screen["main"] , 15 , 3 , " " , 0);
    add_boders(wino.top().screen["main"] , 0); 
    add_text_to_screen(wino.top().sts["input"] , wino.top().screen["main"] , 1 , y , 0 , 1);
}

void input_t(){
    int k = getkey();
    if(k==' '){
        std::string s = wino.top().sts["input"];
        std::string api = wino.top().sts["api"];
        wino.pop();
        wino.top().sts[api]=s;
        return;
        
    }
    if((wino.top().sts["type"]=="int")&&(k>='0')&&(k<='9')){
        wino.top().sts["input"].push_back(k);
        input_builder();
    }
    else if(wino.top().sts["type"]=="str"){
        wino.top().sts["input"].push_back(k);
        input_builder();
    }
}

void input(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        if(!wino.top().sts.count("api")){
            error_push("api not found");
            return;
        }
        if(!wino.top().sts.count("type")){
            error_push("input type not defined");
            return;
        }        
        input_builder();
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"]="main";
        wino.top().stb["hud"]=1;
        wino.top().stl["hudx"]=-1;
        wino.top().stl["hudy"] = -1;
    }
    input_t();
}