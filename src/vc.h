#pragma once

#include <qmainwindow.h>
#include <qpushbutton.h>
#include "labelvaluepair.h"
#include <qcheckbox.h>

#include "simulation.h"

class VC : public QMainWindow
{
	Q_OBJECT

private:
	const float Width = 1800;
	const float Height = 1500;

	Simulation* simulation = nullptr;
	QPushButton* playButton = nullptr;
	QPushButton* pauseButton = nullptr;
	QPushButton* resetButton = nullptr;
	LabelValuePair* scaleWidthField = nullptr;
	LabelValuePair* scaleHeightField = nullptr;
	LabelValuePair* gField = nullptr;
	QCheckBox* overlayBox = nullptr;

public:
	VC();
	~VC();

	void onInit();
	void display();

private slots:
	void onScaleWidthFieldValueChanged();
	void onScaleHeightFieldValueChanged();
	void onGFieldValueChanged();
};
