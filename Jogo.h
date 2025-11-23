#ifndef JOGO_H
#define JOGO_H

// Classe base (antigo GameObject)
class Jogo {
public:
    float x, y, width, height;
    bool isAlive;

    Jogo(float x, float y, float w, float h)
        : x(x), y(y), width(w), height(h), isAlive(true) {}
    
    virtual ~Jogo() {} 

    virtual void update() = 0;
    virtual void draw() = 0;

    // Lógica de colisão AABB
    bool colideCom(Jogo* outro) {
        if (!this->isAlive || !outro->isAlive) return false;

        float this_min_x = this->x - this->width / 2;
        float this_max_x = this->x + this->width / 2;
        float this_min_y = this->y - this->height / 2;
        float this_max_y = this->y + this->height / 2;

        float other_min_x = outro->x - outro->width / 2;
        float other_max_x = outro->x + outro->width / 2;
        float other_min_y = outro->y - outro->height / 2;
        float other_max_y = outro->y + outro->height / 2;

        if (this_max_x < other_min_x || 
            this_min_x > other_max_x || 
            this_max_y < other_min_y || 
            this_min_y > other_max_y)   
        {
            return false;
        }
        return true;
    }
};

#endif