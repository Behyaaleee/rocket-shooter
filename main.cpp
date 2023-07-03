#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int phyWidth = 1400, phyHeight = 700;
int logWidth = 200, logHeight = 100;
int centerX = logWidth / 2, centerY = logHeight / 2;
int mouseX = centerX;

int state = 1;
int asteroidcount = 25;
int gameplayTime = 20;
int score = 0;
int gameOver = 0;





class tools {
public:
    void drawCircle(float cx, float cy, float radius, int num_segments, int color) {
        if (color == 1)
            glColor3f(1.0, 0.0, 0.0);

        else if (color == 2)
            glColor3f(0.0, 1.0, 0.0);

        else if (color == 3)
            glColor3f(0.0, 0.0, 1.0);

        glBegin(GL_POLYGON);
        for (int i = 0; i < num_segments; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
    }

    void init2D(float r, float g, float b) {
        glClearColor(r, g, b,1.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0.0, logWidth, 0.0, logHeight);
    }

    void printSome(string str, int x, int y, float r, float g, float b) {
        glColor3f(r, g, b);
        glRasterPos2d(x, y);
        for (int i = 0; i < str.size(); i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        glFlush();
    }
};
tools tool1;
class stars {
public:
    void details() {
    for(int i=0;i<25;i++){
    int x= rand() % 200;
    int y = rand() % 100;
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x, y);
        glEnd();
    }
}

};

tools myTool;
class asteroids {
public:

   int x = 100;
   float y = 100;
   float red, green, blue;
   float rate = 0.2;
   int color = 1 + rand()%3;
   int radius = 3;

   void create() {
      x = 30 + rand() % 160;
      y = 100;
      color = 1 + rand() % 3;
   }

   void draw(int color) {
        if (color == 1){
            red = 1.0f;
            green = 0.0f;
            blue = 0.0f;
        }
        else if (color == 2){
            red = 0.0f;
            green = 1.0f;
            blue = 0.0f;
        }
        else if (color == 3){
            red = 0.0f;
            green = 0.0f;
            blue = 1.0f;
        }
        else
            glColor3f(1, 1, 1);
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 1000; i++) {
            long double angle = i * 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679 / 180;
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
        glEnd();
    }

   void render() {
      draw(color);
      y -= 0.5;
   }

   void kill() {
      y = -10;
   }
};

void drawRocketBeam(int state,int rocketX) {
        switch (state % 3) {
            case 1:
                glColor3f(1.0, 0.0, 0.0);
                break;
            case 2:
                glColor3f(0.0, 1.0, 0.0);
                break;
            default:
                glColor3f(0.0, 0.0, 1.0);
        }
    }
void drawRocket(int rocketX) {

    glColor3f(1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(rocketX-4,5);
    glVertex2i(rocketX,15);
    glVertex2i(rocketX+4,5);
    glEnd();
    glColor3f(0.15, 0.15, 0.15);
    glBegin(GL_POLYGON);
    glVertex2i(rocketX-4,5);
    glVertex2i(rocketX,9);
    glVertex2i(rocketX+4,5);
    glEnd();

    switch(state%3) {
        case 0:
    glColor3f(1.0, 0.0, 0.0);
    break;
        case 1:
    glColor3f(0.0, 1.0, 0.0);
    break;
        case 2:
    glColor3f(0.0, 0.0, 1.0);
    break;
}
    glBegin(GL_POLYGON);
    glVertex2f(rocketX-0.2,15);
    glVertex2f(rocketX+0.2,280);
    glVertex2f(rocketX-0.2,280);
    glVertex2f(rocketX+0.2,15);
    glEnd();
}

tools tool;
asteroids asteroid1;
stars star;

void restart(int key, int x, int y) {
    if(key == GLUT_KEY_F1) {
        score = 0;
        gameplayTime = 20;
        gameOver = 0;
        asteroidcount = 25;
    }

}

void changeBeamColor(unsigned char key, int x, int y) {
    if (key ==' ')
    {
        state++;
    }
    glutPostRedisplay();
}

void passiveMouse(int x, int y) {
if (x>35&&x<1370){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    };
}

void Timer(int value) {
    glutTimerFunc(50, Timer, value);
    glutPostRedisplay();
}

void destroy() {
    int beam = mouseX;
    int L = asteroid1.x - 3;
    int R = asteroid1.x + 3;
    if (R >= beam && L <= beam && (state%3+1) == asteroid1.color) {
        asteroid1.kill();
        score++;
    }
}

void printSomeScore(char* str, int score, int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);

    char scoreStr[12];
    snprintf(scoreStr, sizeof(scoreStr), " SCORE: %d", score);

    for (int i = 0; i < strlen(scoreStr); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, scoreStr[i]);

    glFlush();
}

void printSomeTimer(char* str, int timer, int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);

    char timerStr[12];
    snprintf(timerStr, sizeof(timerStr), " Timer: %d", timer);

    for (int i = 0; i < strlen(timerStr); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, timerStr[i]);

    glFlush();
}
void TimerCountdown(int value) {
    gameplayTime--;
    glutTimerFunc(1000, TimerCountdown, value);
}

void fallingAsteroid() {
    asteroid1.render();
    if (asteroid1.y < 17) {
        asteroidcount--;
        asteroid1.create();
    }
    destroy();
}

void gameOverScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    tool.printSome("GAME OVER", 87, 60, 1, 1, 1);
    stringstream ss;
    ss << "YOUR SCORE: " << score;
    tool.printSome(ss.str().c_str(), 85, 50, 1, 1, 1);
    tool.printSome("Press F1 to restart", 85, 40, 1, 1, 1);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRocket(mouseX);
    printSomeTimer("", gameplayTime, 188, 95);
    printSomeScore("", score, 5, 95);
    star.details();

    if (asteroidcount > 0 && gameplayTime > 0)
        fallingAsteroid();
    else{
        gameOver = 1;
        gameOverScreen();
    }
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(phyWidth, phyHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Space Rocket Game");
    tool.init2D(0.15,0.15,0.15);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(changeBeamColor);
    glutSpecialFunc(restart);
    TimerCountdown(0);
    Timer(0);
    glutMainLoop();
}
