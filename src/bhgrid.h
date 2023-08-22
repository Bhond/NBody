#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "mymath.h"
#include "particle.h"

struct Node
{
public:
	Particle* data = nullptr;
	double mass = .0;
	Vector2 centerOfMass;
	Node* leafs[4] =
	{
		nullptr, // NW
		nullptr, // NE
		nullptr, // SE
		nullptr  // SW
	};

	Vector2 min { 0, 0 };
	Vector2 max { 0, 0 };
	Vector2 center { 0, 0 };

public:
	Node(const Vector2& mn, const Vector2& mx)
		: min(mn), max(mx)
	{
		center = (max + min) * 0.5;
	}

public:
	bool isEmpty()
	{
		for (Node* leaf : leafs)
		{
			if (leaf)
				return false;
		}
		return true;
	}

	bool isLeaf()
	{
		return data;
	}

	bool hasAtLeastOneChild()
	{
		for (Node* leaf : leafs)
		{
			if (leaf)
				return true;
		}
		return false;
	}

	Node* createNode(int quadIdx)
	{
		Node* newNode = nullptr;
		switch (quadIdx)
		{
		case 0:
			newNode = new Node(Vector2(min.x, center.y), Vector2(center.x, max.y));
			break;
		case 1:
			newNode = new Node(center, max);
			break;
		case 2:
			newNode = new Node(Vector2(center.x, min.y), Vector2(max.x, center.y));
			break;
		case 3:
			newNode = new Node(min, center);
			break;
		}
		return newNode;
	}
};


class BHGrid
{
private:
	const int outlineThickness = 2;
	Node* root = nullptr;
	sf::RenderWindow* window = nullptr;

public:
	BHGrid(sf::RenderWindow* w);
	~BHGrid();

public:
	void buildTree(const Vector2& mn, const Vector2& mx, std::vector<Particle*> cluster);
	void render(const Vector2& origin, const Vector2& scale);
	void renderNode(Node* node, const Vector2& origin, const Vector2& scale);
	Node* getRoot();

private:
	void insertNode(Particle* data, Node* node);
	int getQuadrant(const Vector2& position, Node* node);
	void computeMassDistribution(Node* node);
	void clear();
	void clearNode(Node* node);
};
