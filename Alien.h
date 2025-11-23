#ifndef ALIEN_H
#define ALIEN_H

#include "Jogo.h"
#include "Constantes.h"
#include <GL/glut.h>
#include "TextureLoader.h" // Adicionado para carregar a textura

class Alien : public Jogo {
private:
    GLuint textureID; // Adicionado para a textura do alien
public:
    int valorPontos;

    Alien(float x, float y)
        : Jogo(x, y, ALIEN_WIDTH, ALIEN_HEIGHT), 
          textureID(loadTexture("sprites/alien.png")), // Carrega a textura do alien
          valorPontos(10) {}

    void update() override {
        // Movimento controlado pelo Enxame
    }

    void draw() override {
        if (!isAlive) return;

        glPushMatrix();
        glTranslatef(x, y, 0);
        
        if (textureID != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para não colorir a textura
            
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(-width / 2, -height / 2);
                glTexCoord2f(1.0f, 1.0f); glVertex2f( width / 2, -height / 2);
                glTexCoord2f(1.0f, 0.0f); glVertex2f( width / 2,  height / 2);
                glTexCoord2f(0.0f, 0.0f); glVertex2f(-width / 2,  height / 2);
            glEnd();
            
            glDisable(GL_TEXTURE_2D);
        } else {
            // Fallback para o quadrado roxo original
            glColor3f(0.8f, 0.0f, 0.8f); 
            glBegin(GL_QUADS);
                glVertex2f(-width / 2, -height / 2);
                glVertex2f( width / 2, -height / 2);
                glVertex2f( width / 2,  height / 2);
                glVertex2f(-width / 2,  height / 2);
            glEnd();
        }
        
        glPopMatrix();
    }
};

#endif