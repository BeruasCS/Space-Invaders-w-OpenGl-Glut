#ifndef ENXAME_H
#define ENXAME_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Alien.h"
#include "Projetil.h"
#include "Constantes.h"

class Enxame {
public:
    std::vector<Alien*> aliens;
    float direcaoMovimento;
    float velocidadeMovimento;

    Enxame() 
        : direcaoMovimento(1.0f), velocidadeMovimento(ALIEN_VELOCIDADE_X) {
        srand(time(NULL));
    }

    ~Enxame() {
        for (Alien* a : aliens) delete a;
        aliens.clear();
    }

    void init(int linhas, int colunas) {
        for (int r = 0; r < linhas; r++) {
            for (int c = 0; c < colunas; c++) {
                float x = ENXAME_START_X + c * (ALIEN_WIDTH + ALIEN_ESPACO);
                float y = ENXAME_START_Y - r * (ALIEN_HEIGHT + ALIEN_ESPACO);
                aliens.push_back(new Alien(x, y));
            }
        }
    }

    void update() {
        bool bateuBorda = false;
        for (Alien* a : aliens) {
            if (!a->isAlive) continue;

            a->x += direcaoMovimento * velocidadeMovimento;

            if (a->x > LARGURA_JANELA - a->width / 2 || a->x < a->width / 2) {
                bateuBorda = true;
            }
        }

        if (bateuBorda) {
            direcaoMovimento *= -1.0f;
            for (Alien* a : aliens) {
                a->y -= ALIEN_QUEDA_Y;
                a->x += direcaoMovimento * velocidadeMovimento * 2.0f; 
            }
        }
    }

    void draw() {
        for (Alien* a : aliens) {
            a->draw();
        }
    }

    Projetil* atirar() {
        std::vector<Alien*> aliensDeBaixo;
        
        for (int c = 0; c < ENXAME_COLUNAS; c++) {
            Alien* alienMaisBaixo = nullptr;
            for (int r = ENXAME_LINHAS - 1; r >= 0; r--) {
                // Verifica limites do vetor para evitar crash se mudar constantes
                int idx = r * ENXAME_COLUNAS + c;
                if (idx >= 0 && (size_t)idx < aliens.size()) {
                     Alien* a = aliens[idx];
                     if (a->isAlive) {
                        alienMaisBaixo = a;
                        break;
                    }
                }
            }
            if (alienMaisBaixo) {
                aliensDeBaixo.push_back(alienMaisBaixo);
            }
        }

        if (aliensDeBaixo.empty()) return nullptr;

        int indexSorteado = rand() % aliensDeBaixo.size();
        Alien* atirador = aliensDeBaixo[indexSorteado];

        return new Projetil(atirador->x, atirador->y - atirador->height / 2, VELOCIDADE_TIRO_ALIEN);
    }

    bool temAliensVivos() {
        for (Alien* a : aliens) {
            if (a->isAlive) return true;
        }
        return false;
    }

    float getYMaisBaixo() {
        float yMin = ALTURA_JANELA;
        for (Alien* a : aliens) {
            if (a->isAlive) {
                float baseAlien = a->y - a->height / 2;
                if (baseAlien < yMin) yMin = baseAlien;
            }
        }
        return yMin;
    }
};

#endif