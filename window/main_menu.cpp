#include "window.h"
#include "../output/output.h"
#include "../input/input.h"
#include "screen_resize.h"

void load_img_win(std::string win_name){
    win hio;
    hio.name = win_name;
    wino.push(hio);
    hio.name = "file_select";
    hio.sts["api"] = "img";
    hio.sts["type"] = "photo";
    wino.push(hio);
}

void build_options(){
    initilize_screen(wino.top().screen["opt"] ,20 , 3 , " " , 0 );
    add_options(wino.top().screen["opt"], wino.top().stvs["options"] , wino.top().stl["selecter"]);
    hud_window(wino.top().screen["main"] , wino.top().screen["opt"] , 0 , -1);
}

void handle_inpt(){
    int k = getkey();
    if(k=='w'){
        wino.top().stl["selecter"]--;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().stvs["options"].size()-1;
        build_options();
    }
    if(k=='s'){
        wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]==wino.top().stvs["options"].size())wino.top().stl["selecter"] = 0;
        build_options();
    }
    if(k==' '){
        if(wino.top().stl["selecter"]==0)load_img_win("load_photo");
        if(wino.top().stl["selecter"]==1)load_img_win("load_img");
    }
}

void main_menu(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"] = "main";
        initilize_screen(wino.top().screen["main"] , -1 , -1 , " " , 0);
        std::string title = "media player";
        initilize_screen(wino.top().screen["title"] , 14 , 3 , " " , 0);
        add_boders(wino.top().screen["title"] , 0);
        add_text_to_screen(title , wino.top().screen["title"],  1 , 1 , 0 , 1 );
        hud_window(wino.top().screen["main"] , wino.top().screen["title"] , -1 , 2);
        wino.top().stl["selecter"]=0;
        wino.top().stvs["options"] = {
            "image renderer",
            "image renderer v2",
            "video renderer"
        };
        build_options();
    }
    handle_inpt();
      
    

}