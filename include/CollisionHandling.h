#pragma once
#include "GameObject.h"
#include <typeindex>
#include <typeinfo>



using CollisionFunc = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using CollisionsTable = std::map<Key, CollisionFunc>;



class CollisionHandling
{
	CollisionHandling() = default;
	CollisionsTable initializeTable();
	CollisionFunc search(const std::type_index&, const std::type_index&);
	
public:

	static CollisionHandling& instance();
	void handleCollision(GameObject&, GameObject&);
};