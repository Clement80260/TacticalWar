#include "pch.h"
#include "Environment.h"

using namespace tw;

Environment::Environment(int width, int height, int environmentId)
{
	this->obstacleCacheInitDone = false;
	this->id = environmentId;
	this->width = width;
	this->height = height;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			mapData[i][j] = new CellData(i, j);
		}
	}
}

CellData* Environment::getMapData(int x, int y)
{
	CellData* result = NULL;

	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		result = mapData[x][y];
	}

	return result;
}