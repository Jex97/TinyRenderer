#pragma once
#include<vector>
#include<string>
#include "geometry.h"

class Model{
private:
	std::vector<Vec3f> vertices_;      // 顶点;
	std::vector<std::verctor<int>> faces_;  //面片
public:
	Model(const std::string& filename);
	~Model();
	int nvertices;           // 顶点的数量
	int nfaces;				 // 面片的数量
	Vec3f vertex(int idx);
	std::vector<int> face(int idx);
	
}
