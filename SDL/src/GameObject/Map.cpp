#include "Map.h"

Map::Map(std::string fileData)
{
	loadMapData(fileData);
}

Map::~Map()
{

}

void Map::loadMapData(std::string fileData)
{	
	FILE* fp = NULL;
	fopen_s(&fp, fileData.c_str(), "rb");
	if (fp == NULL)
	{
		printf("Error to load map data");
		return;
	}
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			fscanf_s(fp, "%d", &m_map[i][j]);
		}
	}
	//for (int i = 0; i < MAX_X; i++) {
	//	for (int j = 0; j < MAX_Y; j++) {
	//		printf("%d ", m_map[i][j]);
	//	}
	//	printf("\n");
	//}

}

bool Map::checkCollison(int x, int y)
{	
	if (x/32 < MAX_X &&  x/32 >= 0 && y/32 >=0 && y/32 < MAX_Y) {
		if (m_map[(x / 32)][y / 32] >= 0) {
			return true;
		}
	}
	return false;
}