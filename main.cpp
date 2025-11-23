#include <GL/glut.h>
#include "JogoPrincipal.h"  // Novo nome
#include "Constantes.h"     // Novo nome

// Instância global renomeada
JogoPrincipal g_jogo;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_jogo.render(); // Renderiza o JogoPrincipal
    
    glutSwapBuffers();
}

void update(int value) {
    g_jogo.update(); // Atualiza o JogoPrincipal

    glutTimerFunc(1000 / FRAMES_POR_SEGUNDO, update, 0);
    glutPostRedisplay();
}

void handleKeysDown(unsigned char key, int x, int y) {
    g_jogo.processarTecla(key, true);
}

void handleKeysUp(unsigned char key, int x, int y) {
    g_jogo.processarTecla(key, false);
}

void handleSpecialKeysDown(int key, int x, int y) {
    g_jogo.processarTeclaEspecial(key, true);
}

void handleSpecialKeysUp(int key, int x, int y) {
    g_jogo.processarTeclaEspecial(key, false);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, LARGURA_JANELA, 0.0, ALTURA_JANELA);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP03 - Space Invaders (Modificado)");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Habilitar transparência (blending) para o sprite PNG // <--- NOVO
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Habilitar texturas 2D // <--- NOVO
    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {
    Init(argc, argv);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / FRAMES_POR_SEGUNDO, update, 0);
    
    glutKeyboardFunc(handleKeysDown);
    glutKeyboardUpFunc(handleKeysUp);
    glutSpecialFunc(handleSpecialKeysDown);
    glutSpecialUpFunc(handleSpecialKeysUp);
    
    g_jogo.init();
    
    glutMainLoop();
    return 0;
}
