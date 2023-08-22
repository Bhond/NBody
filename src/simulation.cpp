#include "simulation.h"

Simulation::Simulation(QWidget* parent, unsigned int frameTime)
    : QSFMLCanvas(parent, frameTime)
{
}

Simulation::Simulation(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime)
    : QSFMLCanvas(parent, position, size, frameTime)
{
}

Simulation::~Simulation()
{
    for (Particle* p : cluster)
    {
        delete p;
    }
    cluster.clear();
    for (sf::Shape* s : overlay)
    {
        delete s;
    }
    overlay.clear();

    delete solver;
}

void Simulation::onInit()
{
    sf::Vector2<float> size(width(), height());
    scaleWidth = simulatedWidth / width();
    scaleHeight = simulatedHeight / height();

    Background = sf::RectangleShape(size);
    Background.setFillColor(BackgroundColor);
    
    solver = new Solver(this);

    std::default_random_engine generator;
    std::normal_distribution<double> massDistrib { 1e20,  1e10 };
    std::normal_distribution<double> vxDistrib { 388800, 388800};
    std::normal_distribution<double> vyDistrib { 388800, 388800};
    std::normal_distribution<double> xDistrib { 0, simulatedWidth /  8};
    std::normal_distribution<double> yDistrib { 0, simulatedHeight / 8};


    Vector2 origin{ width() / 2.0, height() / 2.0 };
    //Vector2 pos{ .0,.0 };
    //Vector2 offset{ 0, 151e6 };
    //Vector2 speed{ .0, .0 };
    //Vector2 speedOffset{ 388800, 0};
    //double mass = 2e30; 
    //double massOffset = 0.33e6;

    std::vector<Vector2> tp{Vector2(0,0), Vector2(1e8, 0)};
    std::vector<Vector2> tv{Vector2(0,0), Vector2(0, 2.500e3)};
    std::vector<double> tm{5.970e24, 1};

    //cluster.push_back(new Particle(this, 5, origin, 1e23, Vector2(0, 0), Vector2(0, 0)));

    Vector2 minCorner{ -simulatedWidth / 8, -simulatedHeight / 8 };
    Vector2 maxCorner{ -simulatedWidth / 8, -simulatedHeight / 8 };

    for (int i = 0; i < NbParticles; i++)
    {
        double mass = massDistrib(generator);
        double xx = xDistrib(generator);
        double yy = yDistrib(generator);

        minCorner.x = std::min(minCorner.x, xx);
        minCorner.y = std::min(minCorner.y, yy);
        maxCorner.x = std::max(maxCorner.x, xx);
        maxCorner.y = std::max(maxCorner.y, yy);

        Vector2 pos{ xx, yy };
        Vector2 speed{  -pos.y, pos.x} ; // vxDistrib(generator), vyDistrib(generator)
        speed = speed.unit() * 5e2;
        //Vector2 toCenter = (pos * -1).unit();
        /*double vel = speed.length();
        speed = toCenter * vel;*/

        cluster.push_back(new Particle(this, 2, origin, mass, pos, speed));
        //cluster.push_back(new Particle(this, origin, tm[i], tp[i], tv[i]));


        //pos -= offset;
        //speed += speedOffset;
        //mass = mass / massOffset;
    }

    cluster.push_back(new Particle(this, 10, origin, 1e25, Vector2{}, Vector2{}));
}

void Simulation::onScroll(const double& amt)
{
    if (amt < 0) // up Wheel
        zoomFactor += 1;
    else if (amt > 0 && zoomFactor > 1) //down Wheel
        zoomFactor -= 1;
}

void Simulation::onUpdate()
{
    if (playing)
    {
        for (int i = 0; i < 1; i++)
        {
            solver->solve(cluster, 10000000 * ((double)myTimer.interval()) / 1000);
        }
    }
    render();
}

void Simulation::reset()
{
    pause();
    for (Particle* p : cluster)
    {
        p->reset();
    }
}

void Simulation::render()
{
    // Clear canvas
    clear();

    // Draw background
    draw(Background);

    // Draw particles
    renderParticles();

    // Draw ovelay
    if (overlayOn)
    {
        renderOverlay();
    }
}

void Simulation::renderParticles()
{
    /* TEMP */
    
    double minAcc = cluster[0]->speed.length();
    double maxAcc = cluster[0]->speed.length();
	
    for (Particle* p : cluster)
    {
        double acc = p->speed.length();
        minAcc = std::min(minAcc, acc);
        maxAcc = std::max(maxAcc, acc);
    }

    /* TEMP */

    for (Particle* p : cluster)
    {
        p->render(minAcc, maxAcc, scaleWidth, scaleHeight, zoomFactor);
    }
}

void Simulation::renderOverlay()
{
    Vector2 origin { width() / 2.0, height() / 2.0 };
    Vector2 scale { scaleWidth, scaleHeight };
    solver->grid->render(origin, scale);
}

double Simulation::getScaleWidth()
{
    return scaleWidth;
}

double Simulation::getScaleHeight()
{
    return scaleHeight;
}

double Simulation::getG()
{
    return solver->G;
}

void Simulation::setScaleWidth(const double& amt)
{
    scaleWidth = amt;
}

void Simulation::setScaleHeight(const double& amt)
{
    scaleHeight = amt;
}

void Simulation::setG(const double& amt)
{
    solver->G = amt;
}

void Simulation::toggleOverlay()
{
    overlayOn = !overlayOn;
}
