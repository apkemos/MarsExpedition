
#include "stdafx.h"
#include "SimObjectManager.h"
#include "Sim.h"

SimObjectManager::SimObjectManager()
{
}

SimObjectManager::~SimObjectManager()
{
	std::for_each(_simObjects.begin(),_simObjects.end(),SimObjectDeallocator());
}

void SimObjectManager::Add(int i, VisibleSimObject* simObject)
{
	_simObjects.insert(std::pair<int,VisibleSimObject*>(i,simObject));
}

void SimObjectManager::Remove(int i)
{
	std::map<int, VisibleSimObject*>::iterator results = _simObjects.find(i);
	if(results != _simObjects.end() )
	{
		delete results->second;
		_simObjects.erase(results);
	}
}

VisibleSimObject* SimObjectManager::Get(int i) const
{
	std::map<int, VisibleSimObject*>::const_iterator results = _simObjects.find(i);
	if(results == _simObjects.end() )
		return NULL;
	return results->second;

}

int SimObjectManager::GetObjectCount() const
{
	return _simObjects.size();
}


void SimObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{

	std::map<int,VisibleSimObject*>::const_iterator itr = _simObjects.begin();
	while(itr != _simObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void SimObjectManager::UpdateAll()
{
	std::map<int,VisibleSimObject*>::const_iterator itr = _simObjects.begin();
	float timeDelta = clock.restart().asSeconds(); //returns a Time objects and calls time.asSeconds() which returns float

	while(itr != _simObjects.end())
	{
		itr->second->update(timeDelta);
		itr++;
	}


}
