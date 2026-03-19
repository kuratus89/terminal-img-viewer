#include <thread>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "../storage/stora.h"
#include "../window/screen_resize.h"
#include "../window/diagnose.h"

void hard_clear(){
    system("cls");
}

void soft_clear(){
    std::cout<<"\033[H";
}

void initilize_screen(std::vector<std::vector<pixel>> &scr , int x , int y , std::string value , int color){
    int w,h;
    get_console_size(w,h);
    if(x<=0)x =w;
    if(y<=0)y =h;

    pixel pe;
    pe.value = value ;
    pe.color = color;
    scr = std::vector<std::vector<pixel>> (y , std::vector<pixel> (x , pe));
}

void add_text_to_screen(std::string s,std::vector<std::vector<pixel>> &scr , int x , int y , int color , bool are){
    long long it=0;
    long long temp=x;
    for(long long b=y ; b<scr.size() && it<s.size() ; b++){
        
        for(long long a=temp;a<scr[b].size() && it<s.size() ; a++){
            pixel p;
            p.value = std::string(1,s[it]);
            p.color = color;
            scr[b][a] = p;
            it++;
        }
        if(are)temp = x;
        else temp = 0;
    }
}

std::string rgb_text(int r , int g , int b){
    return ("\x1b[38;2;"+ std::to_string(r)+";"
    + std::to_string(g) + ";"
    + std::to_string(b) + "m");
}

std::string rgb_bg(int r , int g , int b){
    return ("\x1b[48;2;"+
    std::to_string(r)  + ";" +
    std::to_string(g) + ";" +
    std::to_string(b) + "m"
    );
}

void bulk_printer(std::vector<std::vector<pixel>> &scr , std::string &s){
    for(auto vao:scr){
        for(auto val:vao){
            s+=color_pick_vec[val.color];
            s+=val.value;
        }
        s.push_back('\n');
    }
}

void printer(std::vector<std::vector<pixel>> &scr){
    if((pre_screen==scr)&&(!force_print))return;
    std::string print;
    // if((pre_screen.size()&&scr.size())&&(pre_screen.size()==scr.size())&&(pre_screen[0].size()==scr[0].size())){
    // }
    bulk_printer(scr , print);
    if((pre_screen.size()>scr.size())||(pre_screen[0].size()>scr[0].size()))hard_clear();
    else soft_clear();
    std::cout<<print;
    pre_screen = scr;
    if(force_print)force_print=0;

}

void adv_bulk_printer(std::vector<std::vector<pixel>> &scr , std::string &s){
    int h = scr.size();
    std::string ch = "▀";
    for(long long y = 0 ; y<h-1 ; y+=2){
        int rt=-1 , gt=-1 , bt=-1;
        int rb=-1 , gb =-1 , bb=-1;
            
        for(long long x = 0 ; x<scr[y].size() ; x++){
            if((rt!=scr[y][x].r)||(gt!=scr[y][x].g)||(bt!=scr[y][x].b)){
                s+= rgb_text(scr[y][x].r , scr[y][x].g , scr[y][x].b);
                rt = scr[y][x].r;
                gt = scr[y][x].g;
                bt = scr[y][x].b;
            }
            if((rb!=scr[y+1][x].r)||(gb!=scr[y+1][x].g)||(bb!=scr[y+1][x].b)){
                s+= rgb_bg(scr[y+1][x].r , scr[y+1][x].g , scr[y+1][x].b);
                rb = scr[y+1][x].r;
                gb = scr[y+1][x].g;
                bb = scr[y+1][x].b;
            }
            s+=ch;

        }
        s += "\x1b[0m";
        s.push_back('\n');
    }
    if(h&1){
        for(long long x = 0 ; x<scr[h-1].size(); x++){
            
            s+=rgb_text(scr[h-1][x].r , scr[h-1][x].g , scr[h-1][x].b);
            s+=rgb_bg(0,0,0);
            s+=ch;
        }
        
        s += "\x1b[0m";
        s.push_back('\n');
    }


}

std::string move_cursor(int x , int y){
    return ("\033["+std::to_string(y)+";"+std::to_string(x)+"H");
}

void comp_printer(std::vector<std::vector<pixel>> &scr ,std::vector<std::vector<pixel>> &pre , std::string &s , int sx , int sy , int bx , int by ){
    int h= std::min((int)scr.size() , by);
    std::string ch = "▀";
    int rt=-1 , gt=-1 , bt=-1;
    int rb=-1 , gb=-1 , bb=-1;
    int cx=-1 , cy=-1;

    for(int y=sy ; y<h-1 ; y+=2){
        int ty = (y/2)+1;
        for(int x=sx ; x<std::min((int)scr[y].size() , bx)  ; x++){
            int tx = x+1;
            bool td=1;
            if((y<pre.size()) &&(x<pre[y].size())){
                td = !(scr[y][x]==pre[y][x]);
            }
            bool bd=1;
            if((y+1<pre.size())&&(x<pre[y+1].size())){
                bd = !(scr[y+1][x]==pre[y+1][x]);
            }



            if(td||bd){
                if((cx!=tx)||(cy!=ty)){
                    s+=move_cursor(tx , ty);
                    cx = tx;
                    cy=ty;
                }

                if((rt!=scr[y][x].r)||(gt!=scr[y][x].g)||(bt!=scr[y][x].b)){
                    s += rgb_text(scr[y][x].r , scr[y][x].g , scr[y][x].b);
                    rt = scr[y][x].r;
                    gt = scr[y][x].g;
                    bt = scr[y][x].b;
                }

                if((rb!= scr[y+1][x].r)||(gb!=scr[y+1][x].g)||(bb!=scr[y+1][x].b)){
                    s += rgb_bg(scr[y+1][x].r , scr[y+1][x].g , scr[y+1][x].b);
                    rb = scr[y+1][x].r;
                    gb = scr[y+1][x].g;
                    bb = scr[y+1][x].b;
                }
                s+=ch;
                cx++;
            }
            

        }
    }
    // if(h&1){
    //     int y=h-1;
    //     int ty= (y/2)+1;
    //     for(int x=0 ; x<scr[y].size() ; x++){
    //         int tx = x+1;
    //         bool td = 1;
    //         if((y < pre.size()) && (x < pre[y].size())){
    //             td = !(scr[y][x] == pre[y][x]);
    //         }
    //         if(td){
    //             if((cx!=tx)||(cy!=ty)){
    //                 s+=move_cursor(tx, ty);
    //                 cx = tx;
    //                 cy = ty;
    //             }
                        
    //             if((rt!=scr[y][x].r)||(gt!=scr[y][x].g)||(bt!=scr[y][x].b)){
    //                 s+= rgb_text(scr[y][x].r , scr[y][x].g , scr[y][x].b);
    //                 rt = scr[y][x].r;
    //                 gt = scr[y][x].g;
    //                 bt = scr[y][x].b;
    //             }

    //             if((rb!=0)||(gb!=0) ||(bb!=0)){
    //                 s+=rgb_bg(0 ,0 , 0);
    //                 rb = 0;
    //                 gb = 0;
    //                 bb = 0;
    //             }
    //             s+=ch;
    //             cx++;

    //         }

    //     }
    // }
    if(cx!=-1){
        s+="\x1b[0m";
    }
}

void multi_threader(std::vector<std::vector<pixel>> &scr , std::string &s){
    int cube_size =  300;
    std::vector<std::thread> threads;
    std::vector<std::string> vec (((scr.size()/cube_size)+1)*((scr[0].size()/cube_size)+1));
    int id=0;
    for(int y=0 ; y<scr.size() ; y+=cube_size){
        for(int x=0 ; x<scr[y].size() ; x+=cube_size){
            threads.emplace_back(comp_printer , std::ref(scr) , std::ref(pre_screen) , std::ref(vec[id]) , x , y , x+cube_size , y+cube_size);
            id++;
        }
    }
    for(auto &val : threads){
        val.join();
    }
    for(auto val:vec)s+=val;

}


void adv_printer(std::vector<std::vector<pixel>> &scr ){
    if((pre_screen==scr)&&(!force_print))return;
    std::string print;
    print.reserve(scr.size() * (scr[0].size() * 8 + 2));
    // adv_bulk_printer(scr , print);
    if(pre_screen.empty()||((pre_screen.size()>scr.size())||(pre_screen[0].size()>scr[0].size()))){
        hard_clear();
        adv_bulk_printer(scr , print);
    }
    else {
        soft_clear();
        // hard_clear();
        // if((pre_screen.size()==scr.size())&&(pre_screen[0].size()==scr[0].size()))
        multi_threader(scr , print);
        // else adv_bulk_printer(scr , print);
        
    }
    
    std::cout<<print;
    pre_screen = scr;
    if(diab){
        end_d();
    }
    if(force_print)force_print=0;
}

// void hud_window(std::vector<std::vector<pixel>> &main , std::vector<std::vector<pixel>> &secondary , int x , int y){
//     if(x<0)x = (main[0].size()- secondary[0].size())/2;
//     if(y<0)y = (main.size() - secondary.size())/2;
//     for(int h=y ; h<secondary.size() ; h++){
//         for(int w = x ; w<secondary[h].size() ; w++){
//             main[h+y][w+x] = secondary[h][w];
//         }
//     }
// }
void hud_window(std::vector<std::vector<pixel>> &main,
                std::vector<std::vector<pixel>> &secondary,
                int x, int y)
        {
    if (main.empty()||main[0].empty()||secondary.empty()||secondary[0].empty())return;
    int w,h;
    get_console_size(w,h);
    if(x<0)x=std::max(0,(w-(int)secondary[0].size())/2);
    if(y<0)y=std::max(0,(h - (int)secondary.size())/2);

    for (int sy = 0; sy < (int)secondary.size(); sy++) {
        int my=y+sy;
        if (my<0||my>=(int)main.size()) continue;
        for (int sx=0;sx<(int)secondary[sy].size(); sx++) {
            int mx=x+sx;
            if(mx<0||mx>=(int)main[my].size()) continue;
            main[my][mx] = secondary[sy][sx];
        }
    }
}

void add_boders(std::vector<std::vector<pixel>> &scr , int col){
    pixel pe;
    pe.color = col;
    pe.value = "─";
    for(long long i=1 ; i<scr[0].size()-1 ; i++){
        scr[0][i] = pe;
        scr[scr.size()-1][i]=pe;
    }
    pe.value = "|";
    for(long long i=1 ; i<scr.size()-1 ; i++){
        scr[i][0] = pe;
        scr[i][scr[i].size()-1] = pe;
    }
    pe.value = "╭";
    scr[0][0]=pe;
    pe.value = "╯";
    scr[scr.size()-1][scr[0].size()-1] = pe;
    pe.value = "╮";
    scr[0][scr[0].size()-1]= pe;
    pe.value = "╰";
    scr[scr.size()-1][0] = pe;
    
}

void add_options(std::vector<std::vector<pixel>> &scr , std::vector<std::string> s , int selecter){
    int y=0;
    for(auto val:s){
        if(y==selecter)add_text_to_screen("->"+ val , scr , 0 , y , 0 , 1);
        else add_text_to_screen(" "+val , scr , 0 , y , 0 , 1);
        y++;
    }
}

void hud_printer(std::vector<std::vector<pixel>> &scr , int x , int y){
    int a,b;
    get_console_size(a,b);
    if(x<=0)x = std::max(0,(int)(a - scr[0].size())/2);
    if(y<=0)y = std::max(0 , (int)(b - scr.size())/2);
    
    std::string s;
    for(int h=0 ; (h+y<=b)&&(h<scr.size()) ; h++){
        s+=move_cursor(x,h+y);
        for(int w =0 ; (w+x<=a)&&(w<scr[h].size()) ; w++){
            s+=color_pick_vec[scr[h][w].color];
            s+=scr[h][w].value;
        }
        s.push_back('\n');
    }
    soft_clear();
    std::cout<<s;
}