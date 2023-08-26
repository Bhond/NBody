#include "vc.h"

VC::VC()
	: QMainWindow()
{
}

VC::~VC()
{
	delete simulation;
	delete qglcanvas;
	delete playButton;
	delete pauseButton;
	delete resetButton;
	delete scaleWidthField;
	delete scaleHeightField;
	delete gField;
	delete overlayBox;
}

void VC::onInit()
{
	// Parent
	resize(QSize(Width, Height));

	// Init sizes
	float anchorX = 0;
	float anchorY = 0;
	float margin = 10;

	float controlContainerWidth = Width / 4;
	float controlContainerHeight = Height - 2 * anchorY;

	// Simulation
	float posX = anchorX + controlContainerWidth + margin;
	float posY = anchorY;
	float simWidth = Width - posX - anchorX;
	float simHeight = controlContainerHeight;

	/*simulation = new Simulation(this, QPoint(posX, posY), QSize(simWidth, simHeight), 1);
	simulation->show();*/

	qglcanvas = new QGLCanvas(this);
	qglcanvas->resize(QSize(simWidth, simHeight));
	qglcanvas->move(QPoint(posX, posY));

	// Controls
	/*float controlsX = 0.5 * controlContainerWidth;
	float controlsY = margin;
	float controlsStep = 10;

	playButton = new QPushButton("Play", this);
	float playButtonX = controlsX - playButton->size().width() * 0.5;
	playButton->move(QPoint(playButtonX, controlsY));
	connect(playButton, SIGNAL(clicked()), simulation, SLOT(play()));

	pauseButton = new QPushButton("Pause", this);
	float pauseButtonX = controlsX - pauseButton->size().width() * 0.5;
	controlsY += controlsStep + playButton->size().height();
	pauseButton->move(QPoint(pauseButtonX, controlsY));
	connect(pauseButton, SIGNAL(clicked()), simulation, SLOT(pause()));

	resetButton = new QPushButton("Reset", this);
	float resetButtonX = controlsX - resetButton->size().width() * 0.5;
	controlsY += controlsStep + pauseButton->size().height();
	resetButton->move(QPoint(resetButtonX, controlsY));
	connect(resetButton, SIGNAL(clicked()), simulation, SLOT(reset()));

	scaleWidthField = new LabelValuePair("Scale width", 1.0, this);
	scaleWidthField->resize(QSize(std::min(controlContainerWidth - 2 * margin, 300.0f), 70.0));
	float scaleWidthFieldX = controlsX - scaleWidthField->size().width() * 0.5;
	controlsY += controlsStep + resetButton->size().height();
	scaleWidthField->move(QPoint(scaleWidthFieldX, controlsY));
	connect(scaleWidthField, SIGNAL(valueChanged()), this, SLOT(onScaleWidthFieldValueChanged()));

	scaleHeightField = new LabelValuePair("Scale height", 1.0, this);
	scaleHeightField->resize(QSize(std::min(controlContainerHeight - 2 * margin, 300.0f), 70.0));
	float scaleHeightFieldX = controlsX - scaleHeightField->size().width() * 0.5;
	controlsY += controlsStep + scaleWidthField->size().height();
	scaleHeightField->move(QPoint(scaleHeightFieldX, controlsY));
	connect(scaleHeightField, SIGNAL(valueChanged()), this, SLOT(onScaleHeightFieldValueChanged()));

	gField = new LabelValuePair("G", 6.67428e-11, this);
	gField->resize(QSize(std::min(controlContainerWidth - 2 * margin, 300.0f), 70.0));
	float gFieldX = controlsX - gField->size().width() * 0.5;
	controlsY += controlsStep + scaleHeightField->size().height();
	gField->move(QPoint(gFieldX, controlsY));
	connect(gField, SIGNAL(valueChanged()), this, SLOT(onGFieldValueChanged()));

	overlayBox = new QCheckBox("Toggle overlay", this);
	float overlayBoxX = controlsX - overlayBox->size().width() * 0.5;
	controlsY += controlsStep + gField->size().height();
	overlayBox->move(QPoint(overlayBoxX, controlsY));
	connect(overlayBox, SIGNAL(stateChanged(int)), simulation, SLOT(toggleOverlay()));*/
}

void VC::display()
{
	this->show();

	// Update field values at start, not available before
	//scaleWidthField->setValue(simulation->getScaleWidth());
	//scaleHeightField->setValue(simulation->getScaleHeight());
	//gField->setValue(simulation->getG());
}

void VC::onScaleWidthFieldValueChanged()
{
	simulation->setScaleWidth(scaleWidthField->getValue());
}

void VC::onScaleHeightFieldValueChanged()
{
	simulation->setScaleHeight(scaleHeightField->getValue());
}

void VC::onGFieldValueChanged()
{
	simulation->setG(gField->getValue());
}