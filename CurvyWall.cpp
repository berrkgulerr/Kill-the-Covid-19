#include "CurvyWall.h"

CurvyWall::CurvyWall(float length, float r){
    radius = r;
    initial = NULL;
    final = NULL;
    center = NULL;
    length = 2*PI*r;
}


CurvyWall::CurvyWall(const Particle& s, const Particle& e, const Particle& c){
    initial = new Particle(s);
    final = new Particle(e);
    center = new Particle(c);
    radius = c.FindDistance(s);
    length = 2*PI*radius;
}



CurvyWall::CurvyWall(const CurvyWall& rhs){
    initial = new Particle(*rhs.initial);
    final = new Particle(*rhs.final);
    center = new Particle(*rhs.center);
    length = rhs.length;
    radius = rhs.radius;
}



float CurvyWall::GetRadius() const{
    return radius;
}



const Particle& CurvyWall::GetCenter() const{
    return *center;
}



void CurvyWall::ComputeLength(){
    length = 2*PI*radius;
}



Wall* CurvyWall::Clone() const{
    CurvyWall* mywall = new CurvyWall(*this);
    return mywall;
}



bool CurvyWall::IsContinuousLinear(const Wall& rhs) const{
    return false;
}

const Wall& CurvyWall::operator+(const Wall& rhs) const{
    Wall* p = rhs.Clone();
    CurvyWall* derived = dynamic_cast <CurvyWall*>(p);
    if(derived!=NULL){
        if(*initial == *rhs.final && *center == derived->GetCenter()){
            CurvyWall* mywall = new CurvyWall(*rhs.initial, *final,* center);
            if(derived) delete derived;
            return *mywall;
        }

        else if(*final == *rhs.initial && *center == derived->GetCenter()){
            CurvyWall* mywall = new CurvyWall(*initial, *rhs.final,* center);
            if(derived) delete derived;
            return *mywall;
        }
        else{
            if(derived) delete derived;
            throw ApplePearException();
        }
    }
    else {
        throw ApplePearException();
    }
    
}

CurvyWall::~CurvyWall(){
    if(center) delete center;
}