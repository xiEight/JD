#include "glscene.h"
#include <QGLWidget>
#include <QTimer>
#include <math.h>
#include <QSound>

int xMin = 200;
int xMax = 600;
int yMin = 40;
int yMax = 600;
int nLines = 80;
int nPoints = 100;
float dx = (xMax - xMin) / nPoints;
float dy = (yMax - yMin) / nLines;
int x = xMin;
int y = yMin;

double rand(float min, float max){
    return (rand()/ double(RAND_MAX)) * (max - min) + min;
}

int randInt(float min, float max){
    return floor(rand()/ double(RAND_MAX) * (max - min + 1) - min);
}

double randNormal(float mu, float sigma){
    double sum = 0;
    for (int i = 0; i < 6; i++)
        sum += rand(-1,1);
    sum /= 6;
    return mu + sigma * sum;
}

double normalPDF(float x, float mu, float sigma){
    const double PI  =3.141592653589793238463;
    double sigma2 = pow(sigma,2);
    double numerator = exp(-pow(x - mu,2) / (2 * sigma2));
    double denumerator = sqrt(2 * PI * sigma2);
    return  numerator / denumerator;
}

glScene::glScene()
{
    QSound::play(":/3164.wav");
    setWindowTitle("Unknown Pleasures");
    connect(&timer, SIGNAL(timeout()),this, SLOT(repaint()));
    timer.start(100);
}

void glScene::initializeGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,800,600,0, 0, 1);
}

void glScene::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void glScene::paintGL(){
    qglColor(Qt::darkCyan);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int x = xMin, y = yMin;
    qglColor(Qt::white);
    float mx = (xMin + xMax) / 2;
    for (int i = 0; i < nLines; i++){
        glBegin(GL_LINE_STRIP);
        int size = randInt(1,4);
        float w = y;
        for (int j = 0; j < nPoints; j++){
        x = x + dx;
        float noise = 0;
        for (int l = 0; l < size; l++)
            noise += normalPDF(x,rand(mx - 50,mx + 50), randNormal(24,30));

        float yy = 0.3 * w + 0.7 * (y - 600 * noise + noise * rand()/ double(RAND_MAX) * 200 + rand()/ double(RAND_MAX)) ;
        glVertex2d(x,yy);
        w = yy;
        }
        x = xMin;
        y += dy;
        glEnd();
    }
}
