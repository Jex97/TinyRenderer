#include "tgaimage.h"
#include "Model.h"

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);          
const TGAColor red   = TGAColor(255, 0,   0,   255);

void Line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
    // 首先判定一个基方向，跨越像素多的方向为基方向，避免采样稀疏
    bool isTrans = false;
    if(abs(x1-x0) < abs(y1 - y0)){
        isTrans = true;
        swap(x0, y0);
        swap(x1, y1);
    }
    
    // 其次判定基方向顺序为从小到大
    if(x0 > x1){
        swap(x0, x1);
        swap(y0, y1);
    }
    
    // 计算误差
    int dx = x1 - x0;    //必然大于0;
    int dy = y1 - y0;
    int derror = abs(dy) * 2;     // dy/dx  * 2dx
    int error = 0;
    int y = y0;
    const int yincr = y1 > y0 ? 1 : -1; 
    for(int x = x0; x <= x1; ++x){
        if(isTrans) image.set(y, x, color);
        else image.set(x, y, color);
        error += derror;          
        if(error2 > dx){
            y += yincr;
            error2 -= dx*2;
        }
    }
}
void DrawWireframe(TGAImage& image, const Model& model, TGAColor color){
    const int width = image.get_width();
    const int hight = image.get_height();
    for(int i = 0; i < model->nfaces(); ++i){
        vector<int> face = model->face(i);
        for(int j = 0; j < 3; ++j){
            // 默认-1.0 <= v0, v1 <= 1.0
            Vec3f v0 = model->vertex(face[j]);
            Vec3f v1 = model->vertex(face[(j+1)%3]);
            int x0 = (v0.x + 1.0) * width / 2.0;
            int y0 = (v0.y + 1.0) * height / 2.0;
            int x1 = (v1.x + 1.0) * width / 2.0;
            int y1 = (v1.y + 1.0) * height / 2.0;
            line(x0, y0, x1, y1, image, color);
        }
    }
}
int main(int argc, char** argv) {
        TGAImage image(800, 800, TGAImage::RGB);     //TGAImage::RGB = 3, 颜色只有三个分量，没有第四维属性
        Model model = new Model("obj/african_head.obj");
        image.flip_vertically();          // 竖直方向翻转
        image.write_tga_file("output.tga");
        return 0;
}
