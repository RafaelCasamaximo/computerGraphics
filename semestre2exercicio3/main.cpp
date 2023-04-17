//
//  main.cpp
//  opengl_semestre2exercicio3
//
//  Created by Rafael Furlanetto Casamaximo on 17/04/23.
//

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void myInit(void);
void myDisplay(void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa o GLUT e processa qualquer parâmetro passado pela linha de comandos. Deve ser chamada antes de qualquer outra rotina GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Especifica como o vídeo será utilizado, no caso será alocado um buffer e o sistema de cor será RGB.
    glutInitWindowSize (640, 480); // Especifica as dimensões da janela em pixels.
    glutInitWindowPosition (100, 100); // Especifica a coordenada superior esquerda da janela. Define a localização da janela dentro da tela
    glutCreateWindow ("Primeiro programa"); // Cria a janela e devolve um identificador único para a janela. Até que o comando glutMainLoop seja chamado, a janela não será mostrada.
    myInit(); // Rotina que implementa as configurações iniciais do programa.
    glutDisplayFunc(myDisplay); // Chamada para a função de desenho
        // Toda vez que o GLUT determinar que a janela tem de ser desenhada, ele chamará a função aqui determinada.
    glutKeyboardFunc(keyboard); // Determinam as funções que usaremos para ler o teclado e o mouse respectivamente.
    glutMainLoop( ); // É o último comando que chamamos. Ele faz com que todas as janelas criadas sejam mostradas. Uma vez que entramos neste loop, só saímos quando o programa se encerra.
    return 0;
    
}

void myInit(void){
    
    glClearColor(1.0,1.0,1.0,0.0);     // cor de fundo branco
    glColor3f(0.0f, 0.0f, 0.0f);          // Define cor corrente de desenho
    glPointSize(4.0);             // Define o tamanho do ponto: 4 por 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
                                           // janela com resolução de 640 por 480
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}



void myDisplay(void)
{
        glClear(GL_COLOR_BUFFER_BIT); // limpa a janela

        // Base da case
        glColor3f((float)125/255, (float)125/255, (float)125/255);
        glBegin(GL_QUADS);
            glVertex2f(100, 0); // desenha 3 pontos
            glVertex2f(400, 0);
            glVertex2i(400, 300);
            glVertex2i(100, 300);
        glEnd();

        // Chaminé
        glColor3f((float)110/255, (float)48/255, (float)0/255);
        glBegin(GL_QUADS);
            glVertex2f(150, 300); // desenha 3 pontos
            glVertex2f(200, 300);
            glVertex2i(200, 450);
            glVertex2i(150, 450);
        glEnd();

        // Janela
        glColor3f((float)107/255, (float)255/255, (float)211/255);
        glBegin(GL_QUADS);
            glVertex2f(220, 200); // desenha 3 pontos
            glVertex2f(380, 200);
            glVertex2i(380, 100);
            glVertex2i(220, 100);
        glEnd();

        // Porta
        glColor3f((float)107/255, (float)255/255, (float)211/255);
        glBegin(GL_QUADS);
            glVertex2f(120, 0); // desenha 3 pontos
            glVertex2f(200, 0);
            glVertex2i(200, 200);
            glVertex2i(120, 200);
        glEnd();

        // Telhado
        glColor3f((float)158/255, (float)26/255, (float)0/255);
        glBegin(GL_TRIANGLES);
            glVertex2f(100, 300); // desenha 3 pontos
            glVertex2f(400, 300);
            glVertex2i(250, 400);
        glEnd();

        glutSwapBuffers(); // Garante a execução de todas as rotinas de desenho
}


// A rotina a seguir termina o programa com a tecla Esc
void keyboard(unsigned char key, int x, int y){
     switch (key) {
         case 27:
         exit(0);
         break;
     }
}


