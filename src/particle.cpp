#include "particle.h"

Particle::Particle(sf::RenderWindow* w, double r, const Vector2& o, Vector2 startingPosition)
	: window(w), radius(r), origin(o), position(startingPosition), startingPosition(startingPosition), startingSpeed(startingSpeed)
{
	init();
}

Particle::Particle(sf::RenderWindow* w, double r, const Vector2& o, Vector2 startingPosition, Vector2 startingSpeed)
	: window(w), radius(r), origin(o), position(startingPosition), speed(startingSpeed), startingPosition(startingPosition), startingSpeed(startingSpeed)
{
	init();
}

Particle::Particle(sf::RenderWindow* w, double r, const Vector2& o, double m, Vector2 startingPosition, Vector2 startingSpeed)
	: window(w), radius(r), origin(o), mass(m), position(startingPosition), speed(startingSpeed), startingPosition(startingPosition), startingSpeed(startingSpeed)
{
	init();
}

Particle::~Particle()
{
	delete p_shape;
}

void Particle::init()
{
	p_shape = new sf::CircleShape(radius, 100);
	p_shape->setOrigin(sf::Vector2f(radius, radius));
	p_shape->setFillColor(color);
}

void Particle::render(double minAcc, double maxAcc, double scaleWidth, double scaleHeight, double zoomFactor)
{
	// Offset to the window's center
	float ox = origin.x + (position.x / scaleWidth);
	float oy = origin.y - (position.y / scaleHeight);

	double d = (maxAcc - minAcc);
	double c = d > 0.0 ? 1 - (maxAcc - acceleration.length()) / (maxAcc - minAcc) : 1;
	Color col = linearGradient(c);

	p_shape->setFillColor(sf::Color(col.r, col.g, col.b, col.a));
	p_shape->setPosition(ox, oy);
		
	p_shape->setRadius(radius / zoomFactor);

	// Draw shape
	window->draw(*p_shape);
}

void Particle::reset()
{
	position = startingPosition;
	speed = startingSpeed;
}