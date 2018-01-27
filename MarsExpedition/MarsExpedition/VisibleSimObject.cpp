
#include "StdAfx.h"
#include "VisibleSimObject.h"


VisibleSimObject::VisibleSimObject()
	: _isLoaded(false)
{
	//_isLoaded = false; Slightly faster to use the above constructor initialization.
}


VisibleSimObject::~VisibleSimObject()
{
}

void VisibleSimObject::Load(std::string filename)
{
	if(_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;


	}
}

void VisibleSimObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void VisibleSimObject::update(float elapsedTime)
{
}

void VisibleSimObject::SetPosition(float x, float y)
{
	if(_isLoaded)
	{
		_sprite.setPosition(x,y);
	}
}

sf::Vector2f VisibleSimObject::GetPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}

float VisibleSimObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleSimObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleSimObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& VisibleSimObject::GetSprite()
{
  return _sprite;
}

bool VisibleSimObject::IsLoaded() const
{
  return _isLoaded;
}


