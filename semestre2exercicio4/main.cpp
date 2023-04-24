//
//  main.cpp
//  opengl_aula1
//
//  Created by Gilberto Fernandes Junior on 27/03/23.
//

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void configureDisplay();
void display();
void clearDisplay();
void createMenu();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
    glutInit(&argc, argv);

    int mode = GLUT_SINGLE | GLUT_RGB;
    glutInitDisplayMode (mode);

    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Paint - Semestre 2 Exercicio 4");

    configureDisplay();
    createMenu();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

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

        glBegin(GL_TRIANGLES);

        glVertex2f(100, 50); // desenha 3 pontos
        glVertex2f(100, 130);
        glVertex2i(150, 130);

        glEnd();

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
        case 'd': case 'D':
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
        break;
    case 1:
        break;
    case 2:
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
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}

void createMenu()
{
    GLint menu, submenu1, submenu2;

    submenu1 = glutCreateMenu(handle_submenu1);
    glutAddMenuEntry("Linhas", 0);
    glutAddMenuEntry("Pontos", 1);
    glutAddMenuEntry("Poligonos", 2);

    submenu2 = glutCreateMenu(handle_submenu2);
    glutAddMenuEntry("Verde", 0);
    glutAddMenuEntry("Vermelho", 1);
    glutAddMenuEntry("Azul", 2);

    menu = glutCreateMenu(handle_menu);
    glutAddSubMenu("Primitivas", submenu1);
    glutAddSubMenu("Cores", submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
