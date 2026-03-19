#include "window.h"
#include <thread>
#include "../lib/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include "error.h"
#include "../output/output.h"
#include "screen_resize.h"
#include <iostream>


std::vector<std::vector<double>> cn (10 , std::vector<double> (10));
std::chrono::time_point<std::chrono::_V2::system_clock> st;
std::chrono::time_point<std::chrono::_V2::system_clock>end;
void end_d(){
    end = std::chrono::high_resolution_clock::now();
    cn[(rcs/100)-1][(pcs/100)-1] = std::chrono::duration_cast<std::chrono::microseconds>(end - st).count()/1000.0;
}
int drcs=0;
int dpcs=0;
std::vector<unsigned char> dpx;

unsigned char* px;

void render_d(int tx , int ty , int bx , int by , int sw , int sh , float s){    
    for(int y = ty ; y<by ; y++){
        for(int x = tx ; x<bx ; x++){
            int sx = (int)x*s;
            int sy = (int)y*s;
            if(sx<0)sx=0;
            if(sy<0)sy=0;
            if(sx>=sw)sx = sw-1;
            if(sy>=sh)sy = sh-1;

            int it = ((sy*sw)+sx)*4;

            wino.top().screen["render"][y][x].r = px[it];
            wino.top().screen["render"][y][x].g = px[it+1];
            wino.top().screen["render"][y][x].b = px[it+2];

        }
    }

}

void multi_thr(){
    int cube_size= rcs;
    int cw = wino.top().stl["x"];
    int ch = wino.top().stl["y"];

    int sw = wino.top().stl["w"];
    int sh = wino.top().stl["h"];

    float sx = (float)sw/(float)cw;
    float sy = (float)sh/(float)ch;

    float s = std::max(sx , sy);

    int rw = (int)(sw/s);
    int rh = (int)(sh/s);

    if(rh<1)rh =1;
    if(rw<1)rw = 1;

    wino.top().screen["render"] = std::vector<std::vector<pixel>> (rh , std::vector<pixel>(rw));

    std::vector<std::thread> threads;
    for(int y=0 ; y<wino.top().stl["y"] ; y+=cube_size){
        int by = std::min(y+cube_size , rh);
        for(int x = 0 ; x<wino.top().stl["x"] ;x+=cube_size ){
            int bx = std::min(x+cube_size , rw);
            threads.emplace_back(render_d , x , y,  bx , by , sw , sh , s);
        }
    }
    for(auto &val:threads)val.join();
}
void diagnose(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        if(wino.top().sts["img"]==""){
            wino.pop();
            return;
        }
        std::ifstream img_bin(wino.top().sts["img"] , std::ios::binary);
        if(!img_bin){
            error_push("cant load image in bin");
            return;
        }
        img_bin.seekg(0 , std::ios::end);
        size_t size = img_bin.tellg();
        img_bin.seekg(0 , std::ios::beg);
        dpx = std::vector<unsigned char> (size);
        img_bin.read(reinterpret_cast<char*> (dpx.data()) , size);
        int w,h,c;
        px = stbi_load_from_memory(dpx.data() , dpx.size() ,&w , &h , &c , 4);
        if(!px){
            error_push("image cant load");
            return;
        }
        int x;
        int y;
        get_console_size(x,y);
        wino.top().stl["w"]=w;
        wino.top().stl["h"]=h;
        wino.top().stl["c"]=c;
        wino.top().stl["x"]=x;
        wino.top().stl["y"]=y;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"]="render";
        wino.top().stb["adv"]=1;
        diab=1;
        rcs =100;
        pcs=0;
        force_print=1;
    }
    pcs+=100;
    if(pcs>1000){
        pcs=100;
        rcs+=100;
    }
    if(rcs>1000){
        hard_clear();
        for(int i=100 ; i<=1000 ; i+=100){
            for(int j=100 ; j<=1000 ; j+=100){
                std::cout<<"rcs- "<<i+100 <<" pcs"<<j+100<<"==>"<<cn[(i/100)-1][(j/100)-1]<<std::endl;
            }
        }
        gameon=0;
        return;
    }
    st = std::chrono::high_resolution_clock::now();
    multi_thr();
    // std::cout<<rcs<<" "<<pcs<<std::endl;

}