#include "bhgrid.h"

/// <summary>
/// Ctor
/// </summary>
/// <param name="w">Window to draw the grid on</param>
BHGrid::BHGrid(sf::RenderWindow* w)
	: window(w)
{

}

/// <summary>
/// Dtor
/// </summary>
BHGrid::~BHGrid()
{
	clear();
	delete window;
	delete root;
}

/// <summary>
/// Create the tree to compute des forces
/// </summary>
/// <param name="mn">SW corner postion</param>
/// <param name="mx">NE corner postion</param>
/// <param name="cluster">The cluster of data to build the tree on</param>
void BHGrid::buildTree(const Vector2& mn, const Vector2& mx, std::vector<Particle*> cluster)
{
	// Reset tree
	clear();

	// Setup root
	root = new Node(mn, mx);

	// Loop over all datas in the cluster and build the tree
	for (Particle* data : cluster)
	{
		insertNode(data, root);
	}

	// Compute center of mass
	computeMassDistribution(root);
}

/// <summary>
/// Insert the node into the tree
/// </summary>
/// <param name="data">The data to insert</param>
/// <param name="node">Current node</param>
void BHGrid::insertNode(Particle* data, Node* node)
{
	if (node->hasAtLeastOneChild())
	{
		int quadIdx = getQuadrant(data->position, node);

		Node* next = nullptr;
		if (!node->leafs[quadIdx])
		{
			next = node->createNode(quadIdx);
			node->leafs[quadIdx] = next;
		}
		else
		{
			next = node->leafs[quadIdx];
		}

		insertNode(data, next);
	}
	else if (node->isLeaf())
	{
		// Existing particle
		int existingQuadIdx = getQuadrant(node->data->position, node);
		Node* next = node->createNode(existingQuadIdx);
		node->leafs[existingQuadIdx] = next;
		insertNode(node->data, next);

		// New particle
		int newQuadIdx = getQuadrant(data->position, node);
		if (!node->leafs[newQuadIdx])
		{
			next = node->createNode(newQuadIdx);
			node->leafs[newQuadIdx] = next;
		}
		else
		{
			next = node->leafs[newQuadIdx];
		}
		insertNode(data, next);

		// Clear data
		node->data = nullptr;
	}
	else
	{
		node->data = data;
	}
}

/// <summary>
/// Retrieve the quadrant where the data will be added
/// </summary>
/// <param name="data">The data to insert</param>
/// <param name="node">Current node</param>
/// <returns>The index of the quadrant where the data should be added</returns>
int BHGrid::getQuadrant(const Vector2& position, Node* node)
{
	if (position.x <= node->center.x && position.y > node->center.y) // NW
		return 0;
	else if (position.x > node->center.x && position.y > node->center.y) // NE
		return 1;
	else if (position.x > node->center.x && position.y <= node->center.y) // SE
		return 2;
	else if (position.x <= node->center.x && position.y <= node->center.y) // SW
		return 3;
	else
		throw std::runtime_error("Can'Particle determine quadrant!");
	return -1;
}

/// <summary>
/// Compute the mass distribution of each node
/// </summary>
/// <param name="node">The node to compute mass mastribution</param>
void BHGrid::computeMassDistribution(Node* node)
{
	if (node->isLeaf())
	{
		node->mass = node->data->mass;
		node->centerOfMass = node->data->position;
	}
	else
	{
		for (Node* n : node->leafs)
		{
			if (n)
			{
				computeMassDistribution(n);
				node->mass += n->mass;
				node->centerOfMass += n->centerOfMass * n->mass;
			}
		}
		node->centerOfMass = node->centerOfMass / node->mass;
	}
}

/// <summary>
/// Clear the tree
/// </summary>
void BHGrid::clear()
{
	if (!root) return;
	clearNode(root);
}

/// <summary>
/// Clear the node
/// </summary>
/// <param name="node">The node to clear</param>
void BHGrid::clearNode(Node* node)
{
	for (Node* child : node->leafs)
	{
		if (child)
		{
			clearNode(child);
			child = nullptr;
		}
		node->data = nullptr;
	}
}

/// <summary>
/// Render grid as an overlay
/// </summary>
/// <param name="node">Node to render</param>
/// <param name="origin">Origin of the position of the node's shape</param>
/// <param name="scale">Simulation scale</param>
void BHGrid::render(const Vector2& origin, const Vector2& scale)
{
	if (root)
		renderNode(root, origin, scale);
}

/// <summary>
/// Render node
/// </summary>
/// <param name="node">Node to render</param>
/// <param name="origin">Origin of the position of the node's shape</param>
/// <param name="scale">Simulation scale</param>
void BHGrid::renderNode(Node* node, const Vector2& origin, const Vector2& scale)
{
	for (Node* n : node->leafs)
	{
		if (n)
			renderNode(n, origin, scale);
	}
	
	// Quadrant
	double sizeX = (node->max.x - node->min.x) / scale.x;
	double sizeY = (node->max.y - node->min.y) / scale.y;
	double ox = origin.x + node->center.x / scale.x;
	double oy = origin.y - node->center.y / scale.y;

	sf::RectangleShape shape {sf::Vector2f(sizeX, sizeY)};
	shape.setOrigin(sizeX / 2, sizeY / 2);
	shape.move(ox, oy);
	shape.setOutlineThickness(outlineThickness);
	shape.setOutlineColor(sf::Color(255, 50, 0, 255));
	shape.setFillColor(sf::Color::Transparent);

	window->draw(shape);

}

Node* BHGrid::getRoot()
{
	return root;
}
