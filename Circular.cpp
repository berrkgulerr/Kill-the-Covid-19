#include "Circular.h"

Circular::Circular(int _id, float _radius){
    id = _id;
    radius = _radius;
}

Circular::~Circular(){
    if(center) delete center;
    radius=0;
}

void Circular::ConnectToCell(Cell* const rhs){
    CurvyWall* derived = dynamic_cast<CurvyWall*>(rhs->GetCellWall()[0]);
    radius = derived->GetRadius();
    center = new Particle(derived->GetCenter());
    edges.resize(rhs->GetCellWall().size());
    for(int i=0 ; i<edges.size() ; i++){
        CurvyWall* derived1 = dynamic_cast<CurvyWall*>(rhs->GetCellWall()[i]);
        edges[i] = new CurvyWall(*derived1);
    }
    _cell = rhs;
    placed=true;
}

bool Circular::DoesFitInto(const Cell& rhs) const{
    Cell* mycell = new Cell(rhs);
    mycell->StrengthenCellWall();
    if(mycell->GetCellWall().size()==1){
        CurvyWall* derived = dynamic_cast<CurvyWall*>(mycell->GetCellWall()[0]);
        if (derived->GetRadius() + EPSILON > radius  && derived->GetRadius() - EPSILON < radius ) {
            if(mycell) delete mycell;
            derived = NULL;
            return true;
        }
    }
    if(mycell) delete mycell;
    return false;
}

void Circular::React(){
    vector<Wall*>newwalls;
    newwalls.resize(_cell->GetCellWall().size());
    float ssx,ssy,ffx,ffy;
    for(int i=0 ; i<newwalls.size() ; i++){
        float sx = _cell->GetCellWall()[i]->GetInitialParticle().X();
        float sy = _cell->GetCellWall()[i]->GetInitialParticle().Y();
        float fx = _cell->GetCellWall()[i]->GetFinalParticle().X();
        float fy = _cell->GetCellWall()[i]->GetFinalParticle().Y();
        float cx = center->X();
        float cy = center->Y();
        ssx = sx+(sx-cx);
        ffx = fx+(fx-cx);
        ssy = sy+(sy-cy);
        ffy = fy+(fy-cy);
        Particle* _s = new Particle(ssx,ssy);
        Particle* _f = new Particle(ffx,ffy);
        newwalls[i] = new CurvyWall(*_s,*_f,*center);
        if(_s) delete _s;
        if(_f) delete _f;
    }
    _cell->RenewCellWall(newwalls);
}

bool Circular::DoesContain(const Particle& rhs) const{
    return (center->FindDistance(rhs) - EPSILON < radius);
}