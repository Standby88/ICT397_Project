#pragma once

template <class T>
class GameAssetCreator
{
public:
	virtual ~GameAssetCreator() {}
	virtual T* Create() = 0;
};