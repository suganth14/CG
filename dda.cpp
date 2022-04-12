
#include <windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1000
using namespace std;


vector< pair<float,float> > points;
void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glFlush();
}

void plotPoint(float x,float y)
{
    glColor3d(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void DDA()
{
    // cout<<"inside";
    float m = (float) ((points[1].second - points[0].second)/(points[1].first - points[0].first));
    float x = points[0].first, y = points[0].second;

    while(x != points[1].first && y != points[1].second)
    {
        if(m<=1)
        {
            x += 1;
            y += m;
        }

        else {
            x += (1/m);
            y += 1;
        }

        plotPoint(round(x),round(y));
        //cout<<"X: "<<x<<" Y: "<<y<<endl;

    }
}

void mouseHandle(int button ,int status, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON &&  status == GLUT_DOWN)
    {
        pair<float,float> p;
        p.first = x;
        p.second = SCREEN_HEIGHT - y;

        plotPoint(p.first,p.second);
        cout<<"X: "<<p.first<<" Y: "<<p.second<<endl;

        points.push_back(p);
    }

    if(points.size() == 2 && status == GLUT_DOWN)
    {
        DDA();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("DAA");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseHandle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
