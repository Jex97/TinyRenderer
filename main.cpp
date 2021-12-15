#include "tgaimage.h"
#include "Model.h"
#include<iostream>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);          
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

void Line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
    
    bool isTrans = false;
    if(abs(x1-x0) < abs(y1 - y0)){
        isTrans = true;
        swap(x0, y0);
        swap(x1, y1);
    }
    
    if(x0 > x1){
        swap(x0, x1);
        swap(y0, y1);
    }
    

    int dx = x1 - x0;    
    int dy = y1 - y0;
    int derror = abs(dy) * 2;     
    int error = 0;
    int y = y0;
    const int yincr = y1 > y0 ? 1 : -1; 
    for(int x = x0; x <= x1; ++x){
        if(isTrans) image.set(y, x, color);
        else image.set(x, y, color);
        error += derror;          
        if(error > dx){
            y += yincr;
            error -= dx*2;
        }
    }
}

void Line(Vec2i t0, Vec2i t1, TGAImage& image, TGAColor color) {
    int x0 = t0.x;
    int y0 = t0.y;
    int x1 = t1.x;
    int y1 = t1.y;
    bool isTrans = false;
    if (abs(x1 - x0) < abs(y1 - y0)) {
        isTrans = true;
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }


    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror = abs(dy) * 2;
    int error = 0;
    int y = y0;
    const int yincr = y1 > y0 ? 1 : -1;
    for (int x = x0; x <= x1; ++x) {
        if (isTrans) image.set(y, x, color);
        else image.set(x, y, color);
        error += derror;
        if (error > dx) {
            y += yincr;
            error -= dx * 2;
        }
    }
}

void Triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color) {

    if (t0.y > t1.y) swap(t0, t1);     // 保证t0.y < t1.y
    if (t0.y > t2.y) swap(t0, t2);     // 保证t0.y < t2.y
    if (t1.y > t2.y) swap(t1, t2);     // 保证t1.y < t2.y

    
    // 绘制三角形边框
    /*Line(t0, t1, image, color);
    Line(t1, t2, image, color);
    Line(t2, t0, image, color);*/

    // 下半个三角形
    if (t0.y != t1.y) {
        float d10 = 1.0*(t1.x - t0.x) / (t1.y - t0.y);
        float d20 = 1.0*(t2.x - t0.x) / (t2.y - t0.y);
       
        if (d10 > d20) swap(d10, d20);
        float x1 = t0.x;
        float x2 = t0.x;
        for (int y = t0.y; y < t1.y; ++y) {
            x1 += d10;
            x2 += d20;
            Line((int)x1, y, (int)x2, y, image, color);
        }
    }
    // 上半个三角形
    if (t1.y != t2.y) {
        double d21 = 1.0 * (t2.x - t1.x) / (t2.y - t1.y);
        double d20 = 1.0 * (t2.x - t0.x) / (t2.y - t0.y);
        float x1 = t1.x;
        float x2 = t0.x + d20 * (t1.y - t0.y);
        if (x1 > x2) {
            swap(x1, x2);
            swap(d21, d20);
        }
        for (int y = t1.y; y < t2.y; ++y) {
            x1 += d21;
            x2 += d20;
            Line((int)x1, y, (int)x2, y, image, color);
        }
    }
}

void DrawFaceTest(TGAImage& image) {
    Vec2i face1[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
    Vec2i face2[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
    Vec2i face3[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };
    Triangle(face1[0], face1[1], face1[2], image, red);
    Triangle(face2[0], face2[1], face2[2], image, white);
    Triangle(face3[0], face3[1], face3[2], image, blue);
}
void DrawWireframe(TGAImage& image,  Model& model, TGAColor color){
    const int width = image.get_width();
    const int height = image.get_height();
    for(int i = 0; i < model.nfaces(); ++i){
        vector<int> face = model.face(i);
        for(int j = 0; j < 3; ++j){
            Vec3f v0 = model.vertex(face[j]);
            Vec3f v1 = model.vertex(face[(j+1)%3]);
            int x0 = (v0.x + 1.0) * width / 2.0;
            int y0 = (v0.y + 1.0) * height / 2.0;
            int x1 = (v1.x + 1.0) * width / 2.0;
            int y1 = (v1.y + 1.0) * height / 2.0;
            Line(x0, y0, x1, y1, image, color);
        }
    }
}
int main(int argc, char** argv) {
        TGAImage image(300, 300, TGAImage::RGB);     
        // Model model("../TinyRenderer/obj/african_head.obj");
        // DrawWireframe(image, model, white);
        DrawFaceTest(image);
        image.flip_vertically();         
        image.write_tga_file("output.tga");
        return 0;
}
