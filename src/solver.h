#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include "particle.h"
#include "mymath.h"
#include "bhgrid.h"

class Solver
{
public:
	double G { 6.67428e-11 };
	double theta{ 1 };
	BHGrid* grid = nullptr;

public:
	Solver(sf::RenderWindow* w);
	~Solver();

public:
	void solve(std::vector<Particle*>& cluster, const double& dt_s);
	void solveFromTree(std::vector<Particle*>& cluster, const double& dt_s);
	Vector2 solveNodeAcc(Particle* pTarget, Node* node);
	Vector2 solveAcc(Particle* p0, Particle* p1);
	Vector2 solveAcc(Particle* p0, Node* p1);
	void solveSpeed(Particle* particle, const double& dt_s);
	void solvePos(Particle* particle, const double& dt_s);
};