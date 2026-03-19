#include <stack>
#include "../storage/stora.h"
#include <map>
#include <string>
#include "error.h"
#include "main_menu.h"
#include "../output/output.h"
#include "file_select.h"
#include "load_photo.h"
#include "screen_resize.h"
#include "msg.h"
#include "boot.h"
#include "load_img.h"
#include "settings.h"
#include "input.h"
#include "diagnose.h"


std::stack<win> wino;

std::map<std::string , void(*)()> func_pointer = {
    {"error" ,error},
    {"main_menu" , main_menu},
    {"file_select" , file_select},
    {"load_photo" , load_photo},
    {"screen_resize" , screen_resize},
    {"msg" , msg},
    {"boot",  boot},
    {"load_img" , load_img},
    {"settings" , settings},
    {"input" , input},
    {"diagnose" , diagnose}
};

void crash_handler(){
    if(wino.empty()){
        win s;
        s.name = "error";
        s.sts["value"] = "stack empty";
        wino.push(s);
    }
    if(!func_pointer.count(wino.top().name)){
        win s;
        s.name = "error";
        s.sts["value"] = "window " + wino.top().name + " not found!";
        wino.push(s);
    }
}

void window(){
    crash_handler();
    func_pointer[wino.top().name]();
    crash_handler();
    if(wino.top().stb["print_screen"]){
        if(!wino.top().screen.count(wino.top().sts["print_screen"])){
            error_push("screen not found");
        }
        if(wino.top().stb["hud"])hud_printer(wino.top().screen[wino.top().sts["print_screen"]] , wino.top().stl["hudx"] , wino.top().stl["hudy"]);
        else if(wino.top().stb["adv"])adv_printer(wino.top().screen[wino.top().sts["print_screen"]]);
        else printer(wino.top().screen[wino.top().sts["print_screen"]]);
    }

}