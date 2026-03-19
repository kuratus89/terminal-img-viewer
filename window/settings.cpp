#include "window.h"
#include "../output/output.h"
#include "../storage/stora.h"
#include "../input/input.h"
// #include <iostream>

void opt_adi(){
    wino.top().stvs["opt"] = {
            "render cube size [current size->"+std::to_string(rcs)+"]",
            "print cube size [current size->"+ std::to_string(pcs)+"]",
            "diagnose",
            "return"
    };
    int ma=0;
    for(auto val:wino.top().stvs["opt"])ma = std::max(ma , (int)val.size());
    initilize_screen(wino.top().screen["settings"] , ma+5 ,wino.top().stvs["opt"].size()+6 , " " , 0);
    add_boders(wino.top().screen["settings"] , 0);
    initilize_screen(wino.top().screen["opt"] , ma+3 , wino.top().stvs["opt"].size() , " " , 0);
    add_options(wino.top().screen["opt"] , wino.top().stvs["opt"] , wino.top().stl["selecter"]);
    hud_window(wino.top().screen["settings"] , wino.top().screen["opt"] , 1, 1);
}

void in_pt(){
    int k = getkey();
    if(k==' '){
        if(wino.top().stl["selecter"]==0){
            win pe;
            pe.name = "input";
            pe.sts["type"]="int";
            pe.sts["api"] = "rcs";
            wino.push(pe);
        }
        else if(wino.top().stl["selecter"]==1){
            win pe;
            pe.name = "input";
            pe.sts["type"]= "int";
            pe.sts["api"] = "pcs";
            wino.top().stb["initilize"]=0;
            wino.push(pe);
        }
        else if(wino.top().stl["selecter"]==2){
            win pe;
            pe.name = "diagnose";
            wino.push(pe);
            pe.name = "file_select";
            pe.sts["api"] =  "img";
            pe.sts["type"] = "photo";
            wino.push(pe);
        }
        else if(wino.top().stl["selecter"]==3){
            wino.pop();
            // pre_screen.clear();
        }
    }
    else if(k=='w'){
        wino.top().stl["selecter"]--;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().stvs["opt"].size()-1;
        opt_adi();
    }
    else if(k=='s'){
        wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]==wino.top().stvs["opt"].size())wino.top().stl["selecter"]=0;
        opt_adi();
    }

}

void settings(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"] = "settings";
        wino.top().stl["selecter"]=0;
        wino.top().stb["hud"]=1;
        wino.top().stl["hudx"]=-1;
        wino.top().stl["hudy"]=-1;
        opt_adi();
    }
    if(wino.top().sts.count("rcs")){
        rcs = std::stoi(wino.top().sts["rcs"]);
        if(rcs==0)rcs = INT_MAX;
        wino.top().sts.erase("rcs");
        opt_adi();
    }
    if(wino.top().sts.count("pcs")){
        pcs = std::stoi(wino.top().sts["pcs"]);
        if(pcs==0)pcs = INT_MAX;
        wino.top().sts.erase("pcs");
        opt_adi();
    }
        
    in_pt();
}