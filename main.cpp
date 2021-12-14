#include "tgaimage.h"
const TGAColor white = TGAColor(255, 255, 255, 255);          
const TGAColor red   = TGAColor(255, 0,   0,   255);
int main(int argc, char** argv) {
        TGAImage image(100, 100, TGAImage::RGB);     //TGAImage::RGB = 3, 颜色只有三个分量，没有第四维属性
        image.set(52, 41, red);
        image.flip_vertically(); // 竖直方向翻转
        image.write_tga_file("output.tga");
        return 0;
}
