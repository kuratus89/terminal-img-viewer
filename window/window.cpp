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
std::stack<win> wino;

std::map<std::string , void(*)()> func_pointer = {
    {"error" ,error},
    {"main_menu" , main_menu},
    {"file_select" , file_select},
    {"load_photo" , load_photo},
    {"screen_resize" , screen_resize}
    
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
        if(wino.top().stb["adv"])adv_printer(wino.top().screen[wino.top().sts["print_screen"]]);
        else printer(wino.top().screen[wino.top().sts["print_screen"]]);
    }

}