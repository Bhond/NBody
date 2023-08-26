#pragma once

#include <iostream>

#include <qglwidget>
#include <GL/glut.h>

class QGLCanvas : public QGLWidget
{
    Q_OBJECT

public:
    QGLCanvas(QWidget* parent = nullptr);
    ~QGLCanvas();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

};