#include "window.h"
#include <vector>
#include <thread>
#include "error.h"
#include "../stb_image.h"
#include <fstream>
#include "screen_resize.h"
#define STB_IMAGE_IMPLEMENTATION

std::vector<unsigned char> imgv;

unsigned char* pixelv;

// void render(){ 
//     if((wino.top().stl["x"]<wino.top().stl["w"])||(wino.top().stl["y"]<wino.top().stl["h"])){
//         float sx=wino.top().stl["w"]/wino.top().stl["x"];
//         float sy=wino.top().stl["h"]/wino.top().stl["y"];
//         float s=std::max(sx,sy);
//         int rw=(int)(wino.top().stl["w"]/s);
//         int rh=(int)(wino.top().stl["h"]/s);
//         wino.top().screen["render"]=std::vector<std::vector<pixel>>(rh , std::vector<pixel>(rw));
//         for(int y=0 ; y<rh ; y++){
//             for(int x=0 ; x<rw ; x++){
//                 int sx=(int)(x*s);
//         int sy=(int)(y*s);

//             if(sx<0)sx=0;
//             if(sy<0)sy=0;
//             if(sx>=wino.top().stl["w"])sx=wino.top().stl["w"] - 1;
//             if(sy>=wino.top().stl["h"])sy=wino.top().stl["h"] - 1;

//             int it=((sy*wino.top().stl["w"])+ sx)* 4;
//                 // int it=(((y*s)*wino.top().stl["w"])+ (x*s))*4;
//                 wino.top().screen["render"][y][x].r=pixelv[it];
//                 wino.top().screen["render"][y][x].g=pixelv[it+1];
//                 wino.top().screen["render"][y][x].b=pixelv[it+2];
//             }
//         }
//     }
//     else {
//         wino.top().screen["render"]=std::vector<std::vector<pixel>>(wino.top().stl["h"] , std::vector<pixel> (wino.top().stl["w"]));
//         for(int y=0 ; y<wino.top().stl["h"] ; y++){
//             for(int x=0 ; x<wino.top().stl["w"] ; x++){
//                 int it=((y*wino.top().stl["w"])+x)*4;
//                 wino.top().screen["render"][y][x].r=pixelv[it];
//                 wino.top().screen["render"][y][x].g=pixelv[it+1];
//                 wino.top().screen["render"][y][x].b=pixelv[it+2];
//             }
//         }
//     }
// }
// void render(){
//     int cw=(int)wino.top().stl["x"];
//     int ch=(int)wino.top().stl["y"];

//     int cw=cw;
//     int ch=ch*2;

//     int src_w=(int)wino.top().stl["w"];
//     int src_h=(int)wino.top().stl["h"];
//     float sx=(float)src_w/(float)cw;
//     float sy=(float)src_h/(float)ch;
//     float s=std::max(sx, sy);
//     if(s<1.0f)s=1.0f;

//     int rw=(int)(src_w/s);
//     int rh=(int)(src_h/s);
//     if(rh<2)rh=2;
//     if(rh % 2==1)rh--;
//     if(rw<1)rw=1;
//     wino.top().screen["render"]=std::vector<std::vector<pixel>>(rh, std::vector<pixel>(rw));

//     for(int y=0 ; y<rh ; y++){
//         for(int x=0 ; x<rw ; x++){
//             int sx=(int)(x*s);
//             int sy=(int)(y*s);

//             if(sx<0)sx=0;
//             if(sy<0)sy=0;
//             if(sx>=src_w)sx=src_w-1;
//             if(sy>=src_h)sy=src_h-1;

//             int it=((sy*src_w)+ sx)* 4;
//             wino.top().screen["render"][y][x].r=pixelv[it];
//             wino.top().screen["render"][y][x].g=pixelv[it+1];
//             wino.top().screen["render"][y][x].b=pixelv[it+2];
//         }
//     }
// }

void render(int tx , int ty , int bx , int by , int sw , int sh , float s){
    
    
    for(int y = ty ; y<by ; y++){
        for(int x = tx ; x<bx ; x++){
            int sx = (int)x*s;
            int sy = (int)y*s;
            if(sx<0)sx=0;
            if(sy<0)sy=0;
            if(sx>=sw)sx = sw-1;
            if(sy>=sh)sy = sh-1;

            int it = ((sy*sw)+sx)*4;

            wino.top().screen["render"][y][x].r = pixelv[it];
            wino.top().screen["render"][y][x].g = pixelv[it+1];
            wino.top().screen["render"][y][x].b = pixelv[it+2];

        }
    }

}

void multi_th(){
    int cube_size= 300;
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
            threads.emplace_back(render , x , y,  bx , by , sw , sh , s);
        }
    }
    for(auto &val:threads)val.join();
}


void load_img(){
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
        size_t size=img_bin.tellg();
        img_bin.seekg(0 , std::ios::beg);
        imgv=std::vector<unsigned char> (size);
        img_bin.read(reinterpret_cast<char*> (imgv.data()), size);
        int w,h,c;
        pixelv=stbi_load_from_memory(imgv.data(), imgv.size(), &w , &h , &c , 4);
        if(!pixelv){
            error_push("image cant load");
            return;
        }
        wino.top().stl["w"]=w;
        wino.top().stl["h"]=h;
        wino.top().stl["c"]=c;
        wino.top().stl["x"]=-1;
        wino.top().stl["y"]=-1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"]="render";
        wino.top().stb["adv"]=1;       
    }
    int x,y;
    get_console_size(x,y);
    if((wino.top().stl["x"]!=x)||(wino.top().stl["y"]!=y*2)){
        wino.top().stl["x"]=x;
        wino.top().stl["y"]=y*2;
        multi_th();
    }

}
