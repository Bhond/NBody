#pragma once

#include <SFML/Graphics.hpp>
#include "mymath.h"
#include "misc.h"

class Particle
{
public:
	double mass = 5000;
	double radius { 5.0 };
	Vector2 position { .0, .0 };
	Vector2 startingPosition { .0, .0 };
	Vector2 speed { .0, .0 };
	Vector2 startingSpeed { .0, .0 };
	Vector2 acceleration { .0, .0 };
	
	const sf::Color& color { 255, 0, 0, 255 };
	Vector2 origin;
	sf::RenderWindow* window = nullptr;
	sf::CircleShape* p_shape = nullptr;

public:
	Particle() = delete;
	Particle(sf::RenderWindow* w,  double r, const Vector2& o, Vector2 startingPosition);
	Particle(sf::RenderWindow* w,  double r, const Vector2& o, Vector2 startingPosition, Vector2 startingSpeed);
	Particle(sf::RenderWindow* w,  double r, const Vector2& o, double m, Vector2 startingPosition, Vector2 startingSpeed);
	~Particle();

private:
	void init();

public:
	void render(double minAcc, double maxAcc, double scaleWidth, double scaleHeight, double zoomFactor);
	void reset();
};