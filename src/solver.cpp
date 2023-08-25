#include "solver.h"

Solver::Solver(sf::RenderWindow* w)
{
	grid = new BHGrid(w);
}

Solver::~Solver()
{
	delete grid;
}

void Solver::solve(std::vector<Particle*>& cluster, const double& dt_s)
{

	Vector2 minCorner{ 1e8 / 8, 1e8/ 8 };
	Vector2 maxCorner{ -1e8 / 8, -1e8/ 8 };

	for (Particle* p : cluster)
	{
		minCorner.x = std::min(minCorner.x, p->position.x);
		minCorner.y = std::min(minCorner.y, p->position.y);
		maxCorner.x = std::max(maxCorner.x, p->position.x);
		maxCorner.y = std::max(maxCorner.y, p->position.y);
		p->thetaCount = 0;
	}

	double d = std::max(maxCorner.x - minCorner.x, maxCorner.y - minCorner.y);
	grid->buildTree(Vector2(-d,-d), Vector2(d, d), cluster);
	solveFromTree(cluster, dt_s);
}

void Solver::solveFromTree(std::vector<Particle*>& cluster, const double& dt_s)
{	
	for (Particle* p : cluster)
	{
		p->acceleration = solveNodeAcc(p, grid->getRoot());
		solveSpeed(p, dt_s);
		solvePos(p, dt_s);
	}
}

Vector2 Solver::solveNodeAcc(Particle* pTarget, Node* node)
{
	if (node->isLeaf() && node->data != pTarget)
	{
		return solveAcc(pTarget, node->data);
	}
	else
	{
		Vector2 force{};
		Vector2 rVect = pTarget->position - node->centerOfMass;
		double r = rVect.length();
		double d{ node->max.y - node->min.y };

		if (d / r < theta)
		{
			return solveAcc(pTarget, node);
		}
		else
		{
			for (Node* n : node->leafs)
			{
				if (n)
				{
					force += solveNodeAcc(pTarget, n);
					pTarget->thetaCount++;
				}
			}
		}
		return force;
	}
}

Vector2 Solver::solveAcc(Particle* p0, Particle* p1)
{
		Vector2 r = p0->position - p1->position;
		Vector2 direction = r.unit();
		double d = r.length();
		double c = - G * p0->mass * p1->mass;
		double x = (c / pow(d, 2)) * direction.x;
		double y = (c / pow(d, 2)) * direction.y;
		return Vector2(x, y) * (1 / p0->mass);
}

Vector2 Solver::solveAcc(Particle* p, Node* node)
{
		Vector2 r = p->position - node->centerOfMass;
		Vector2 direction = r.unit();
		double d = r.length();
		double c = - G * p->mass * node->mass;
		double x = (c / pow(d, 2)) * direction.x;
		double y = (c / pow(d, 2)) * direction.y;
		return Vector2(x, y) * (1 / p->mass);
}

void Solver::solveSpeed(Particle* particle, const double& dt_s)
{
	particle->speed += particle->acceleration * dt_s;
}

void Solver::solvePos(Particle* particle, const double& dt_s)
{
	particle->position += particle->speed * dt_s;
}
