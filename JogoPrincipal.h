#ifndef JOGOPRINCIPAL_H
#define JOGOPRINCIPAL_H

#include "Player.h"
#include "Enxame.h"
#include "Projetil.h"
#include "Constantes.h"
#include <vector>
#include <stdio.h>
#include <GL/glut.h>
#include "TextureLoader.h" // Adicionado para carregar a textura de vida

enum EstadoJogo {
    JOGANDO,
    GAME_OVER,
    VITORIA
};

// Antiga classe Game
class JogoPrincipal {
private:
    GLuint vidaTextureID; // Adicionado para a textura de vida
public:
public:
    Player* player;
    Enxame* enxame;
    std::vector<Projetil*> projeteis; // Lista de "Projetos" (Projeteis)
    
    EstadoJogo estado;
    int pontuacao;

    bool teclas[256];
    bool teclasEspeciais[256];
    int contadorFramesTiroAlien;

JogoPrincipal()
    : vidaTextureID(loadTexture("sprites/vida.png")),   // 1º — está em primeiro no .h
      player(nullptr),                                   // 2º
      enxame(nullptr),                                   // 3º
      estado(JOGANDO),                                   // 4º
      pontuacao(0),                                      // 5º
      contadorFramesTiroAlien(0)                         // 6º (último dos inicializáveis)
{
    for (int i = 0; i < 256; i++) {
        teclas[i] = false;
        teclasEspeciais[i] = false;
    }
}

    ~JogoPrincipal() {
        delete player;
        delete enxame;
        for (Projetil* p : projeteis) delete p;
        projeteis.clear();
    }

    void init() {
        delete player;
        delete enxame;
        for (Projetil* p : projeteis) delete p;
        projeteis.clear();

        player = new Player(PLAYER_START_X, PLAYER_START_Y);
        vidaTextureID = loadTexture("sprites/vida.png"); // Recarrega a textura ao reiniciar o jogo, se necessário.

        enxame = new Enxame();
        enxame->init(ENXAME_LINHAS, ENXAME_COLUNAS);
        
        pontuacao = 0;
        estado = JOGANDO;
        contadorFramesTiroAlien = 0;
    }

    void processarTecla(unsigned char key, bool down) {
        teclas[key] = down;
    }
    void processarTeclaEspecial(int key, bool down) {
        teclasEspeciais[key] = down;
    }

    void update() {
        if (estado != JOGANDO) {
            if (teclas['r'] || teclas['R']) init();
            return;
        }

        // Movimento do Player
        if (teclasEspeciais[GLUT_KEY_LEFT]) player->mover(-1.0f);
        if (teclasEspeciais[GLUT_KEY_RIGHT]) player->mover(1.0f);
        
        // Tiro do Player
        if (teclas[' ']) {
            Projetil* p = player->atirar();
            if (p != nullptr) projeteis.push_back(p);
            teclas[' '] = false; 
        }

        // Updates Gerais
        player->update();
        enxame->update();
        for (Projetil* p : projeteis) p->update();

        // Lógica de Tiro dos Aliens
        contadorFramesTiroAlien++;
        int framesParaTiro = (int)(INTERVALO_TIRO_ALIEN_SEG * FRAMES_POR_SEGUNDO);
        if (contadorFramesTiroAlien >= framesParaTiro) {
            contadorFramesTiroAlien = 0;
            Projetil* p = enxame->atirar();
            if (p != nullptr) projeteis.push_back(p);
        }

        checarColisoes();
        limparProjeteis();

        // Condições de Fim de Jogo
        if (player->isAlive && !enxame->temAliensVivos()) estado = VITORIA;
        if (!player->isAlive) estado = GAME_OVER;
        if (enxame->getYMaisBaixo() <= (player->y + player->height / 2)) {
            estado = GAME_OVER;
            player->isAlive = false;
        }
    }

    void render() {
        player->draw();
        enxame->draw();
        for (Projetil* p : projeteis) p->draw();
        desenharHUD();
        if (estado != JOGANDO) desenharTelaFim();
    }

    void checarColisoes() {
        for (Projetil* p : projeteis) {
            if (!p->isAlive) continue;

            if (p->velocidade > 0) { // Tiro do Jogador (sobe)
                for (Alien* a : enxame->aliens) {
                    if (p->colideCom(a)) {
                        p->isAlive = false;
                        a->isAlive = false;
                        pontuacao += a->valorPontos;
                        break;
                    }
                }
            } else { // Tiro do Alien (desce)
                if (p->colideCom(player)) {
                    p->isAlive = false;
                    player->receberDano();
                }
            }
        }
    }

    void limparProjeteis() {
        player->update(); 
        auto it = projeteis.begin();
        while (it != projeteis.end()) {
            if (!(*it)->isAlive) {
                delete *it;
                it = projeteis.erase(it);
            } else {
                ++it;
            }
        }
    }

    void desenharTexto(float x, float y, const char* text) {
        glRasterPos2f(x, y);
        for (const char* c = text; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

void desenharHUD() {

    // ----- DESLIGA O DEPTH TEST PARA O HUD FICAR NA FRENTE -----
    glDisable(GL_DEPTH_TEST);

    // Projeção ortográfica
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, LARGURA_JANELA, 0.0, ALTURA_JANELA);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // --- SCORE ---
    glColor3f(1.0f, 1.0f, 1.0f);
    char buffer[50];
    sprintf(buffer, "Score: %d", pontuacao);
    desenharTexto(10, ALTURA_JANELA - 25, buffer);

    // --- TEXTO VIDAS ---
    float textoVidasX = 10.0f;
    float textoVidasY = ALTURA_JANELA - 55.0f;
    desenharTexto(textoVidasX, textoVidasY, "Vidas:");

    // --- ÍCONES DE VIDA ---
    float spriteSize = 40.0f;
    float spacing = 6.0f;

    float inicioVidasX = textoVidasX + 70.0f;
    float inicioVidasY = textoVidasY - 20.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, vidaTextureID);
    glColor3f(1,1,1);

    for (int i = 0; i < player->vidas; ++i) {

        glPushMatrix();
        glTranslatef(inicioVidasX + i * (spriteSize + spacing), inicioVidasY, 0);

        glBegin(GL_QUADS);
            glTexCoord2f(0,1); glVertex2f(0,0);
            glTexCoord2f(1,1); glVertex2f(spriteSize,0);
            glTexCoord2f(1,0); glVertex2f(spriteSize,spriteSize);
            glTexCoord2f(0,0); glVertex2f(0,spriteSize);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);

    // Restaurar matrizes
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // ----- REATIVA O DEPTH TEST PARA O JOGO NORMAL -----
    glEnable(GL_DEPTH_TEST);
}

    void desenharTelaFim() {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, LARGURA_JANELA, 0.0, ALTURA_JANELA);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        const char* msg = (estado == GAME_OVER) ? "GAME OVER" : "VITORIA!";
        glColor3f(estado == GAME_OVER ? 1.0f : 0.0f, estado == GAME_OVER ? 0.0f : 1.0f, 0.0f);
        desenharTexto(LARGURA_JANELA / 2 - 50, ALTURA_JANELA / 2, msg);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        desenharTexto(LARGURA_JANELA / 2 - 80, ALTURA_JANELA / 2 - 30, "Aperte 'R' para Reiniciar");

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
};

#endif