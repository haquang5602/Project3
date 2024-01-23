#pragma once
#include <stdio.h>
#include <string>

#define MAX_X 18
#define MAX_Y 250

class Map
{
public:
	Map(std::string fileMap);
	~Map();
	void loadMapData(std::string fileData);
	bool checkCollison(int x, int y);
private:
	int m_map[MAX_X][MAX_Y];
};