//  main.cpp
//  semestre2exercicio4
//
//  Created by Rafael Furlanetto Casamaximo on 24/04/23.
//

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480

void configureDisplay();
void display();
void clearDisplay();
void createMenu();
void keyboard(unsigned char key, int x, int y);
void handle_mouse(int button, int state, int x, int y);
void handle_motion(int x, int y);

bool mouseDown = false;

int main(int argc, char** argv){
    glutInit(&argc, argv);

    int mode = GLUT_SINGLE | GLUT_RGB;
    glutInitDisplayMode(mode);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint - Semestre 2 Exercicio 4");

    configureDisplay();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(handle_mouse);
    glutMotionFunc(handle_motion);
    createMenu();

    glutMainLoop();
    return 0;
    
}

void configureDisplay(){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void clearDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y){
     switch (key) {
        case 27:
        exit(0);
        break;
        case 'd':
        clearDisplay();
        break;
     }
}


void handle_menu(GLint op)
{
    switch (op)
    {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
}

void handle_submenu1(GLint op)
{
    switch (op)
    {
    case 0:
        glPointSize(4.0);
        break;
    case 1:
        glPointSize(8.0);
        break;
    case 2:
        glPointSize(12.0);
        break;
    default:
        break;
    }
}

void handle_submenu2(GLint op)
{
    switch (op)
    {
    case 0:
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 1:
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 2:
        glColor3f(0.0f, 0.0f, 1.0f);
        break;
    default:
        break;
    }
}

void createMenu()
{
    GLint menu, submenu1, submenu2;

    submenu1 = glutCreateMenu(handle_submenu1);
    glutAddMenuEntry("4px", 0);
    glutAddMenuEntry("8px", 1);
    glutAddMenuEntry("12px", 2);

    submenu2 = glutCreateMenu(handle_submenu2);
    glutAddMenuEntry("Vermelho", 0);
    glutAddMenuEntry("Verde", 1);
    glutAddMenuEntry("Azul", 2);

    menu = glutCreateMenu(handle_menu);
    glutAddSubMenu("Espessura", submenu1);
    glutAddSubMenu("Cores", submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void draw_point(int x, int y)
{
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        glutSwapBuffers();
}

void handle_mouse(int button, int state, int x, int y)
{
    if(button == GLUT_RIGHT_BUTTON)
    {
        glutSwapBuffers();
        return;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        draw_point(x, HEIGHT - y);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        mouseDown = false;
        glutSwapBuffers();
    }
}

void handle_motion(int x, int y)
{
    if(mouseDown)
    {
        draw_point(x, HEIGHT - y);
    }
}

