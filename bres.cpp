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


vector< pair<int,int> > points;
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

void plotPoints(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void bresenham()
{
    int delx = abs(points[1].first - points[0].first);
    int dely = abs(points[1].second - points[0].second);
    int s1,s2,x,y,interchange=0;

    if(points[1].first - points[0].first < 0) s1 = -1;
    else if(points[1].first - points[0].first == 0) s1 = 0;
    else s1 = 1;

    if(points[1].second - points[0].second < 0) s2 = -1;
    else if(points[1].second - points[0].second == 0) s2 = 0;
    else s2 = 1;

    //cout<<"delx:"<<delx<<" dely:"<<dely<<" s1:"<<s1<<" s2:"<<s2<<" inter:"<<interchange<<endl;

    if(dely > delx)
    {
        int t = delx;
        delx = dely;
        dely = t;
        interchange = 1;
    }

    cout<<"delx:"<<delx<<" dely:"<<dely<<" s1:"<<s1<<" s2:"<<s2<<" inter:"<<interchange<<endl;

    float p = (2*dely) - delx;
    x = points[0].first;
    y = points[0].second;
    for(int i=1; i<=delx; i++)
    {
        plotPoints(x,y);
        //cout<<

        while(p > 0)
        {
            if(interchange == 1) x+= s1;
            else y+=s2;

            p -=(2*delx);
        }

        if(interchange == 1) y+=s2;
        else x+= s1;

        p += (2*dely);
    }
}
void mouse_handle(int button, int status, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && status ==  GLUT_DOWN)
    {
        pair<int,int> p;
        p.first = x;
        p.second = SCREEN_HEIGHT - y;

        glColor3d(1,0,0);
        plotPoints(p.first,p.second);

        points.push_back(p);
        cout<<"X: "<<p.first<<" Y: "<<p.second<<endl;
    }

    if(points.size() == 2 && status == GLUT_DOWN)
    {
        bresenham();
    }

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Line drawing");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_handle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
