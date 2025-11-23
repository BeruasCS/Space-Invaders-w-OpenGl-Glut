#ifndef ALIEN_H
#define ALIEN_H

#include "Jogo.h"
#include "Constantes.h"
#include <GL/glut.h>

class Alien : public Jogo {
public:
    int valorPontos;

    Alien(float x, float y)
        : Jogo(x, y, ALIEN_WIDTH, ALIEN_HEIGHT), valorPontos(10) {}

    void update() override {
        // Movimento controlado pelo Enxame
    }

    void draw() override {
        if (!isAlive) return;

        glPushMatrix();
        glTranslatef(x, y, 0);
        glColor3f(0.8f, 0.0f, 0.8f); // Roxo
        
        glBegin(GL_QUADS);
            glVertex2f(-width / 2, -height / 2);
            glVertex2f( width / 2, -height / 2);
            glVertex2f( width / 2,  height / 2);
            glVertex2f(-width / 2,  height / 2);
        glEnd();
        glPopMatrix();
    }
};

#endif