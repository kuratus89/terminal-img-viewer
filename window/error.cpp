#include "window.h"
#include "../output/output.h"
#include <iostream>

void error(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        hard_clear();
        std::cout<<"program crashed"<<std::endl<<"reason: ";
        if(!wino.top().sts.count("value"))wino.top().sts["value"] = "No defined reason";
        std::cout<<wino.top().sts["value"];
    }
}