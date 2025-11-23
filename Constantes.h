#ifndef CONSTANTES_H
#define CONSTANTES_H

// ----- Configurações da Janela -----
const int LARGURA_JANELA = 800;
const int ALTURA_JANELA = 600;

// ----- Configurações do Jogo -----
const int VIDAS_JOGADOR = 3;
const float INTERVALO_TIRO_ALIEN_SEG = 1.0f;
const int FRAMES_POR_SEGUNDO = 60;

// ----- Configurações do Jogador -----
const float PLAYER_START_X = LARGURA_JANELA / 2.0f;
const float PLAYER_START_Y = 50.0f;
const float PLAYER_WIDTH = 100.0f;
const float PLAYER_HEIGHT = 100.0f;
const float PLAYER_SPEED = 8.0f;

// ----- Configurações dos Projéteis -----
const float PROJETIL_WIDTH = 6.0f;
const float PROJETIL_HEIGHT = 16.0f;
const float VELOCIDADE_TIRO_PLAYER = 15.0f;
const float VELOCIDADE_TIRO_ALIEN = -10.0f;

// ----- Configurações do Enxame -----
const int ENXAME_LINHAS = 5;
const int ENXAME_COLUNAS = 10;
const float ALIEN_WIDTH = 30.0f;
const float ALIEN_HEIGHT = 20.0f;
const float ALIEN_ESPACO = 15.0f;
const float ENXAME_START_X = 50.0f;
const float ENXAME_START_Y = ALTURA_JANELA - 100.0f;
const float ALIEN_VELOCIDADE_X = 2.0f;
const float ALIEN_QUEDA_Y = 15.0f;

#endif