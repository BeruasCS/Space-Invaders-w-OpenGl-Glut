#ifndef PLAYER_H
#define PLAYER_H

#include "Jogo.h"
#include "Projetil.h"
#include "Constantes.h"
#include <GL/glut.h>

class Player : public Jogo {
public:
    int vidas;
    float velocidade;
    Projetil* tiroAtivo; 

    Player(float x, float y) 
        : Jogo(x, y, PLAYER_WIDTH, PLAYER_HEIGHT), 
          vidas(VIDAS_JOGADOR), 
          velocidade(PLAYER_SPEED), 
          tiroAtivo(nullptr) {}

    void update() override {
        if (!isAlive) return;
        if (tiroAtivo != nullptr && !tiroAtivo->isAlive) {
            tiroAtivo = nullptr;
        }
    }

    void draw() override {
        if (!isAlive) return;

        glPushMatrix();
        glTranslatef(x, y, 0);
        glColor3f(0.0f, 1.0f, 0.0f); // Verde
        
        glBegin(GL_QUADS);
            glVertex2f(-width / 2, -height / 2);
            glVertex2f( width / 2, -height / 2);
            glVertex2f( width / 2,  height / 2);
            glVertex2f(-width / 2,  height / 2);
        glEnd();
        glPopMatrix();
    }

    void mover(float direcao) {
        if (!isAlive) return;
        x += direcao * velocidade;

        if (x < width / 2) x = width / 2;
        if (x > LARGURA_JANELA - width / 2) x = LARGURA_JANELA - width / 2;
    }

    Projetil* atirar() {
        if (!isAlive || tiroAtivo != nullptr) {
            return nullptr;
        }
        Projetil* tiro = new Projetil(x, y + height / 2, VELOCIDADE_TIRO_PLAYER);
        tiroAtivo = tiro;
        return tiro;
    }

    void receberDano() {
        if (!isAlive) return;
        vidas--;
        if (vidas <= 0) {
            isAlive = false;
        } else {
            resetarPosicao();
        }
    }

    void resetarPosicao() {
        x = PLAYER_START_X;
        y = PLAYER_START_Y;
    }
};

#endif