#include <windows.h>
#include <commdlg.h>
#include<iostream>
#include "window.h"
#include "error.h"


std::string wchar_to_string(const wchar_t* c){
    if(!c)return "";
    int n = WideCharToMultiByte(CP_UTF8 , 0 , c , -1, NULL , 0 , NULL , NULL );
    std::string s(n-1 , 0);
    WideCharToMultiByte(CP_UTF8 , 0 , c , -1 , &s[0] , n , NULL , NULL);
    return s;
}

std::string open_dialog(const wchar_t* filter){
    OPENFILENAMEW ofn;
    wchar_t name[MAX_PATH]=L"";
    ZeroMemory(&ofn , sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = name;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter =filter;
    ofn.nFilterIndex =1;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if(GetOpenFileNameW(&ofn))return wchar_to_string(name);
    return "";
}


void file_select(){
    std::string api = wino.top().sts["api"];
    std::string type = wino.top().sts["type"];
    wino.pop();
    const wchar_t* filter;
    if(api==""){
        error_push(wino.top().name , "api is not valid");
        return;
    }
    if(type=="photo")filter = L"Photos (*.png;*.jpg;*.jpeg)\0*.png;*.jpg;*.jpeg\0All Files (*.*)\0*.*\0";
    else if(type=="video")filter = L"Video Files (*.mp4;*.mkv;*.avi;*.mov)\0*.mp4;*.mkv;*.avi;*.mov\0All Files (*.*)\0*.*\0";
    else {
        error_push(wino.top().name , "format type is not valid");
        return;
    }
    std::string heu = open_dialog(filter);
    wino.top().sts[api] = heu;
    wino.top().stb[api]=1;
}