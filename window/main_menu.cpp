#include "window.h"
#include "../output/output.h"
#include "../input/input.h"

void load_img(){
    win hio;
    hio.name = "load_photo";
    wino.push(hio);
    hio.name = "file_select";
    hio.sts["api"] = "img";
    hio.sts["type"] = "photo";
    wino.push(hio);
}

void main_menu(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"] = "hello";
        initilize_screen(wino.top().screen["hello"] , 5 , 1 , " " , 0);
        initilize_screen(wino.top().screen["bye"] , 3 , 1 , " " , 0);
        add_text_to_screen("hello" , wino.top().screen["hello"] , 0,0, 0 , 1);
        add_text_to_screen("bye" , wino.top().screen["bye"] , 0,0 ,0,1);
        
    }
    if(wino.top().stb["inp"]){
        wino.top().stb["inp"]=0;
        if(wino.top().sts["inp"]=="")wino.top().sts["inp"]="no file selected";
        initilize_screen(wino.top().screen["fle"] , wino.top().sts["inp"].size() , 1 , " " , 0);
        add_text_to_screen(wino.top().sts["inp"] , wino.top().screen["fle"] , 0,0 , 0 , 1 );
        wino.top().sts["print_screen"] = "fle";
    }
    int k = getkey();
    if(k=='w'){
        load_img();
        return;
    }
    

}