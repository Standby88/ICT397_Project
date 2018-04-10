#pragma once

#include <vector>
#include "EnvironmentObject.h"
class EnvironmentObjManager
{
private:
	std::vector<EnvironmentObject> eOL;

public:
	EnvironmentObjManager();
	~EnvironmentObjManager();
	void addObject(EnvironmentObject& in);
	void DrawObjects(Shader S)
	{
		for (int i = 0; i < eOL.size(); i++)
		{
			eOL[i].Draw(S);
		}
	}
};

