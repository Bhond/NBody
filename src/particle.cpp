#include "particle.h"

Particle::Particle(sf::RenderWindow* w, const double& r, const Vector2& o, const Vector2& startingPosition)
	: window(w), radius(r), origin(o), position(startingPosition), startingPosition(startingPosition), startingSpeed(startingSpeed)
{
	init();
}

Particle::Particle(sf::RenderWindow* w, const double& r, const Vector2& o, const Vector2& startingPosition, const Vector2& startingSpeed)
	: window(w), radius(r), origin(o), position(startingPosition), speed(startingSpeed), startingPosition(startingPosition), startingSpeed(startingSpeed)
{
	init();
}

Particle::Particle(sf::RenderWindow* w, const double& r, const Vector2& o, const double& m, const Vector2& startingPosition, const Vector2& startingSpeed)
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

void Particle::render(const double& colorMinBound, const double& colorMaxBound, const double& colorCoeff, const double& scaleWidth, const double& scaleHeight, const double& zoomFactor)
{
	// Offset to the window's center
	float ox = origin.x + (position.x / scaleWidth);
	float oy = origin.y - (position.y / scaleHeight);

	double d = (colorMaxBound - colorMinBound);
	double c = d > 0.0 ? (colorCoeff - colorMinBound) / d : 1;
	
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