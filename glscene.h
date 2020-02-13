#ifndef GLSCENE_H
#define GLSCENE_H
#include <QGLWidget>
#include <QTimer>

class glScene : public QGLWidget
{
    QTimer timer;
public:
    glScene();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLSCENE_H
