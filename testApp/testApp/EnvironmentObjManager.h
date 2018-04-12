#pragma once

#include <unordered_map>
#include "EnvironmentObject.h"

/**
* @class EnvironmentObjManager
* @brief Used to store environment objects
* Objects can be drawn, added, removed and accessed from list
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class EnvironmentObjManager
{
private:
	/// used to store a lsit of enviromnet objects
	typedef std::unordered_map<std::string, EnvironmentObject* > eOL;
	eOL environmentObjList;
public:

	/**
	* @brief Constructor for EnvironmentObjManager
	*/
	EnvironmentObjManager();

	/**
	* @brief destructor for EnvironmentOjtManager used to reales 
	*/
	~EnvironmentObjManager();

	/**
	* @brief add objects to the list
	*
	*@param GameObject* in, std::string key
	*/
	void addObject(GameObject* in, std::string key);
	/*voidDrawAllObjects(Shader & S)
	{
		eOL::iterator itr;
		for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
		{
			(*itr).second->Draw(S) << endl;
		}
	}*/

	/**
	* @brief Draw all the objects stored in the list
	*
	*/
	void DrawAllObjects();//test only

	/**
	* @brief remove an npc from the list
	*
	* @param string k
	*/
	void removeObject(std::string k);

	/**
	* @brief returns a pointer to an object from the list given a string
	* 
	* @param string key
	* @return EnvironmentObject*
	*/
	EnvironmentObject* getObject(std::string);

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

};

