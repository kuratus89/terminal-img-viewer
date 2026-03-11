#include "window.h"
#include "../output/output.h"
#include <iostream>

void error_push(std::string windo , std::string reason){
    win er;
    er.name = "error";
    er.sts["value"] = "error handler = error_push \n error window = "+ windo + "\n reason = "+ reason;
    wino.push(er);
}

void error(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        hard_clear();
        std::cout<<"program crashed"<<std::endl<<"reason: ";
        if(!wino.top().sts.count("value"))wino.top().sts["value"] = "No defined reason";
        std::cout<<wino.top().sts["value"];
    }
}