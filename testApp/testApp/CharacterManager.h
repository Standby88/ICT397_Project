#pragma once
#include <unordered_map>
#include "Player.h"
#include "NPC.h"
/**
* @class ChacterManager
* @brief Used to manage character objects like player, enemies and NPC
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
class CharacterManager
{
private:
	///pointer to player object
	Player* p;

	///used to store NPC 
	std::unordered_map<std::string, NPC* > nPCList;

	std::vector<NPC*> npcUpdateList;
public:
	
	std::vector<NPC*>& getUpdateList()
	{
		return npcUpdateList;
	}
	/**
	* @brief Constructor for charactermanager
	*/
	CharacterManager();

	/**
	* @brief destructor for manager. Correctly releases memory used for pointer
	*
	*/
	~CharacterManager();

	/**
	* @brief Used to add player to player pointer by dynamic cast from gameobj to player type.
	*
	* @param GameObject* in
	*/
	void addPlayer(GameObject* in);

	/**
	* @brief Used to add NPC to character list pointer pointer by dynamic cast from gameobj to objtype type.
	*currently no NPC are used so store int pointer for test
	* @param string key, int* in
	*/
	void addNPC( GameObject* in,std::string key );


	/**
	* @brief used to render the player from the model details
	*
	*/
	void DrawPlayer(Shader & S);
	/**
	* @brief Draw all the NPCs stored in the list
	*
	*/
	void drawNPCs(Shader &s);

	/**
	* @brief accessor for the player
	*
	* @return Player*
	*/
	Player* getPlayer();

	/**
	* @brief returns a pointer to an npc from the list given a string
	* no npcs at the moment so it returns a pointer to an int
	* @param string key
	* @return NPC*
	*/
	NPC* getNPC(std::string);

	/**
	* @brief remove an npc from the list
	*
	* @param string key
	*/
	void removeNPC(std::string);

	/**
	* @brief remove player
	*
	*/
	void removePlayer();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	std::unordered_map<std::string, NPC* >& getCharMap();
	
};

