#include "window.h"
#include "../output/output.h"
#include <iostream>
#include "../input/input.h"

void error_push( std::string reason){
    win er;
    er.name = "error";
    er.sts["value"] = "error handler = error_push \n error window = "+ wino.top().name+ "\n reason = "+ reason;
    wino.push(er);
}

void error(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        hard_clear();
        std::cout<<"program crashed"<<std::endl<<"reason: ";
        if(!wino.top().sts.count("value"))wino.top().sts["value"] = "No defined reason";
        std::cout<<wino.top().sts["value"];
        std::cout<<std::endl<<"press any key to exit";
    }
    int k = getkey();
    if(k!=-1)gameon=0;
}