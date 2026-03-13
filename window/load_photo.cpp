#include "window.h"
#include <vector>
#include <fstream>
// #include <iostream>
#include "error.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

std::vector<unsigned char> img;
int h , w , c;
unsigned char* pixels;
void load_photo(){
    if(!wino.top().stb["initilize"]){
        wino.top().stb["initilize"]=1;
        if(wino.top().sts["img"]==""){
            wino.pop();
            return;
        }
        std::ifstream img_bin(wino.top().sts["img"] , std::ios::binary);
        if(!img_bin){
            error_push( "cannot open image!");
            return;
        }
        img_bin.seekg(0,std::ios::end);
        size_t size = img_bin.tellg();
        img_bin.seekg(0 , std::ios::beg);
        img = std::vector<unsigned char> (size);
        img_bin.read(reinterpret_cast<char*>(img.data()) , size);

    }
    if(!wino.top().stb["loaded_rgb"]){
        wino.top().stb["loaded_rgb"]=1;
        pixels = stbi_load_from_memory(
            img.data(),
            img.size(),
            &w,
            &h,
            &c,
            3
        );
        if(!pixels){
            error_push( "image can't load");
            return;
        }
        win te;
        te.name = "screen_resize";
        te.stl["x"] = w;
        te.stl["y"] = h;
        wino.push(te);
        return;
    }
    // if(!wino.top().stb["rendered"]){
    //     wino.top().stb["rendered"]=1;
    //     wino.top().stb["print_screen"]=1;
    //     wino.top().sts["print_screen"] = "render";
    //     wino.top().stb["adv"]=1;
    //     wino.top().screen["render"] = std::vector<std::vector<pixel>> (h , std::vector<pixel> (w));
    //     for(int y =0 ; y<h ; y++){
    //         for(int x = 0 ; x<w ; x++){
    //             int it = ((y*w)+x)*3;
    //             wino.top().screen["render"][y][x].r = pixels[it];
    //             wino.top().screen["render"][y][x].g = pixels[it+1];
    //             wino.top().screen["render"][y][x].b = pixels[it+2];
    //         }
    //     }

    // }
    if(!wino.top().stb["rendered"]){
        wino.top().stb["rendered"]=1;
        wino.top().stb["print_screen"]=1;
        wino.top().sts["print_screen"] = "render";
        wino.top().stb["adv"]=1;
        
        int console_w = wino.top().stl["apix"];
        int console_h = wino.top().stl["apiy"] * 2;
        
        float scale_x = (float)w / console_w;
        float scale_y = (float)h / console_h;
        float scale = std::max(scale_x, scale_y);
        int render_w = (int)(w / scale);
        int render_h = (int)(h / scale);
        
        if((console_w<w)||(console_h<h)){
            wino.top().screen["render"] = std::vector<std::vector<pixel>>(render_h, std::vector<pixel>(render_w));
            for(int y = 0; y < render_h; y++){
                for(int x = 0; x < render_w; x++){
                    int src_x = (int)(x * scale);
                    int src_y = (int)(y * scale);
                    int it = ((src_y * w) + src_x) * 3;
                    wino.top().screen["render"][y][x].r = pixels[it];
                    wino.top().screen["render"][y][x].g = pixels[it+1];
                    wino.top().screen["render"][y][x].b = pixels[it+2];
                }
            }
        }
        else {
            wino.top().screen["render"] = std::vector<std::vector<pixel>> (h , std::vector<pixel> (w));
            for(int y =0 ; y<h ; y++){
                for(int x = 0 ; x<w ; x++){
                    int it = ((y*w)+x)*3;
                    wino.top().screen["render"][y][x].r = pixels[it];
                    wino.top().screen["render"][y][x].g = pixels[it+1];
                    wino.top().screen["render"][y][x].b = pixels[it+2];
                }
            }
        }
        free(pixels);
    }
    

}