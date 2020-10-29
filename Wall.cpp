#include "Wall.h"

Wall::Wall(){
    initial = NULL;
    final = NULL;
}

Wall::Wall(float x){
    length = x;
    initial = NULL;
    final = NULL;
}



Wall::Wall(const Particle& init, const Particle& fin){
    length = init.FindDistance(fin);
    initial = new Particle(init);
    final = new Particle(fin);
}



Wall::Wall(const Wall& rhs){
    initial = new Particle(*rhs.initial);
    final = new Particle(*rhs.final);
    length = rhs.length;
}



const Particle& Wall::GetInitialParticle() const{
    return *initial;
}



const Particle& Wall::GetFinalParticle() const{
    return *final;
}



float Wall::FindAngleBetween(const Wall& rhs) const{
    float ax = initial->X();
    float ay = initial->Y();
    float cx = final->X();
    float cy = final->Y();
    float bx = rhs.initial->X();
    float by = rhs.initial->Y();
    float dx = rhs.final->X();
    float dy = rhs.final->Y();
    float a_0 = atan2(abs(cy-ay), (cx-ax));
    float a_1 = atan2(abs(dy-by), (dx-bx));
    return abs((a_0 - a_1));
}



float Wall::GetLength() const{
    return length;
}



void Wall::ComputeLength(){
    length = initial->FindDistance(*final);
}



Wall* Wall::Clone() const{
    Wall* mywall = new Wall(*this);
    return mywall;
}



bool Wall::IsContinuousLinear(const Wall& rhs) const{
    return (((*final == *rhs.initial) || (*initial == *rhs.final)) && (((this->FindAngleBetween(rhs) - EPSILON) <= 0)&& ((this->FindAngleBetween(rhs) + EPSILON) >= 0 )));
}



const Wall& Wall::operator+(const Wall& rhs) const{
    if(this->IsContinuousLinear(rhs)){
        if(*initial==*rhs.final && (((this->FindAngleBetween(rhs) - EPSILON) <= 0)&& ((this->FindAngleBetween(rhs) + EPSILON) >= 0 ))){
            Wall* mywall = new Wall(*rhs.initial, *final);
            return *mywall;
        }

        else if(*final == *rhs.initial && (((this->FindAngleBetween(rhs) - EPSILON) <= 0)&& ((this->FindAngleBetween(rhs) + EPSILON) >= 0 ))){
            Wall* mywall = new Wall(*initial, *rhs.final);
            return *mywall;
        }
        else throw ApplePearException();
    }
    else throw ApplePearException();
}



Wall::~Wall(){
    if(initial) delete initial;
    if(final) delete final;
}