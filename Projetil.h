#ifndef PROJETIL_H
#define PROJETIL_H

#include "Jogo.h"
#include "Constantes.h"
#include <GL/glut.h>

// Antiga classe Projectile (agora Projetil, herdando de Jogo)
class Projetil : public Jogo {
public:
    float velocidade;

    Projetil(float x, float y, float vel)
        : Jogo(x, y, PROJETIL_WIDTH, PROJETIL_HEIGHT), velocidade(vel) {}

    void update() override {
        if (!isAlive) return;
        y += velocidade;

        if (y > ALTURA_JANELA || y < 0) {
            isAlive = false;
        }
    }

    void draw() override {
        if (!isAlive) return;

        glPushMatrix();
        glTranslatef(x, y, 0);
        
        if (velocidade > 0)
            glColor3f(1.0f, 1.0f, 1.0f); // Branco (Player)
        else
            glColor3f(1.0f, 0.5f, 0.0f); // Laranja (Alien)

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