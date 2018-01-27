#pragma once
#include "Stdafx.h"
#include "VisibleSimObject.h"



class SimObjectManager
{
public:
	SimObjectManager();
	~SimObjectManager();

	void Add(int i, VisibleSimObject* simObject);
	void Remove(int i );
	int GetObjectCount() const;
	VisibleSimObject* Get(int i) const;
    sf::Clock clock;
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

private:
	std::map<int, VisibleSimObject*> _simObjects;



	struct SimObjectDeallocator
	{
		void operator()(const std::pair< int ,VisibleSimObject*> & p) const
		{
			delete p.second;
		}
	};
};
