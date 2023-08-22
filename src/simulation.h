#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "qsfmlcanvas.h"
#include "SFML/Graphics.hpp"

#include "particle.h"
#include "solver.h"

class Simulation : public QSFMLCanvas
{
	Q_OBJECT

public:
	Solver* solver = nullptr;

private:
	const double simulatedWidth  { 1e10 };
	const double simulatedHeight { 1e10 };
	const std::string Name { "NBody simulation" };
	const int NbParticles { 2500 };
	double scaleWidth { 1 };
	double scaleHeight { 1 };
	double zoomFactor { 1 };
	bool overlayOn { false };

private:
	const sf::Color BackgroundColor = sf::Color(5, 5, 10, 255);
	sf::RectangleShape Background;
	std::vector<Particle*> cluster;
	std::vector<sf::Shape*> overlay;

public:
	Simulation(QWidget* parent, unsigned int frameTime = 0);
	Simulation(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);
	~Simulation();
	
public:
	void onInit() override;
	void reset() override;
	double getScaleWidth();
	double getScaleHeight();
	double getG();
	void setScaleWidth(const double& amt);
	void setScaleHeight(const double& amt);
	void setG(const double& amt);

protected:
	void onUpdate() override;

private:
	void onScroll(const double& amt) override;
	void renderParticles();
	void renderOverlay();

public slots:
	void render();
	void toggleOverlay();
};