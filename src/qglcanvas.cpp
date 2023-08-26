#include "qglcanvas.h"

QGLCanvas::QGLCanvas(QWidget* parent)
	: QGLWidget(parent)
{

}

QGLCanvas::~QGLCanvas()
{
}

void QGLCanvas::initializeGL()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

void QGLCanvas::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glutSolidSphere(1, 20, 20);

}

void QGLCanvas::resizeGL(int w, int h)
{

}
