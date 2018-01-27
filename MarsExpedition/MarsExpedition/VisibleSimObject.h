#pragma once

class VisibleSimObject
{
public:
	VisibleSimObject();
	virtual ~VisibleSimObject();

	virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow & window);
	virtual void update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual sf::Rect<float> GetBoundingRect() const;
	virtual bool IsLoaded() const;

	sf::Sprite& GetSprite();
    sf::Vector2i veh_pos; //Must make SimObjectManager to take vehicles* not VisibleSimObject*
private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;

	bool _isLoaded;

};

