#include "Particle.h"

Particle::Particle(float x, float y){
    x_cor = x;
    y_cor = y;
}

Particle::Particle(const Particle& p){
    x_cor = p.x_cor;
    y_cor = p.y_cor;
}

float Particle::X() const{
    return x_cor;
}

float Particle::Y() const{
    return y_cor;
}

float Particle::FindDistance(const Particle& rhs) const{
    return sqrt(abs(x_cor-rhs.x_cor)*abs(x_cor-rhs.x_cor) + abs(y_cor - rhs.y_cor)*abs(y_cor - rhs.y_cor));
}

bool Particle::operator== (const Particle& rhs) const{
    return ((x_cor-EPSILON <= rhs.x_cor) && (rhs.x_cor <= x_cor+EPSILON) && (y_cor-EPSILON <= rhs.y_cor) && (rhs.y_cor <= y_cor+EPSILON));
}

ostream& operator<<(ostream&os, const Particle& particle){
    os<<"("<<particle.x_cor<<","<<particle.y_cor<<")"<<endl;
    return os;
}