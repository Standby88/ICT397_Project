#pragma once

#include <unordered_map>
#include "EnvironmentObject.h"
class EnvironmentObjManager
{
private:
	typedef std::unordered_map<std::string, EnvironmentObject* > eOL;
	eOL environmentObjList;
public:
	EnvironmentObjManager();
	~EnvironmentObjManager();
	void addObject(EnvironmentObject* in, std::string key);
	/*voidDrawAllObjects(Shader & S)
	{
		eOL::iterator itr;
		for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
		{
			(*itr).second->Draw(S) << endl;
		}
	}*/
	void DrawAllObjects();//test only
	void removeObject(std::string k);
	EnvironmentObject* getObject(std::string);

};

