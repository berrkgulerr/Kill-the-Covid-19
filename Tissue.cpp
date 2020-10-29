#include "Tissue.h"


Tissue::Tissue(){
    minx = 0;
    maxx = 0;
    miny = 0;
    maxy = 0;
    coord[0] = minx;
    coord[1] = maxx;
    coord[2] = miny;
    coord[3] = maxy;
}

Tissue::Tissue(float x, float xx, float y, float yy){
    minx = x;
    maxx = xx;
    miny = y;
    maxy = yy;
    coord[0] = minx;
    coord[1] = maxx;
    coord[2] = miny;
    coord[3] = maxy;
}

Tissue::Tissue(const Tissue& rhs){
    mycells.resize(rhs.mycells.size());
    for(int i=0 ; i<mycells.size() ; i++){
        mycells[i] =rhs.mycells[i];
    }
    minx = rhs.minx;
    maxx = rhs.maxx;
    miny = rhs.miny;
    maxy = rhs.maxy;
    coord[0] = minx;
    coord[1] = maxx;
    coord[2] = miny;
    coord[3] = maxy;
}

Tissue::~Tissue(){
    for(int i=0 ; i<mycells.size() ; i++){
        if(mycells[i]) delete mycells[i];
    }
    mycells.clear();
}

float* Tissue::GetCoordinates(){
    return coord;
}

void Tissue::AddCell(Cell& rhs){
    Cell* _cell = &rhs;
    mycells.push_back(_cell);
}

void Tissue::RemoveCell(Cell& rhs){
    for(int i=0 ; i<mycells.size() ; i++){
        if(mycells[i]->GetCellID() == rhs.GetCellID()) {
            mycells.erase(mycells.begin() + i);
        }
    }
}

const Cell& Tissue::GetCell(int rhsid) const{
    for(int i=0 ; i<mycells.size() ; i++){
        if(mycells[i]->GetCellID() == rhsid) return *mycells[i];
    }

    throw DeadCellException();
}

void Tissue::Interact(const vector<MicroOrganism*>& rhs){
    for(int i=0 ; i<rhs.size() ; i++){
        for(int j=0 ; j<mycells.size() ; j++){
            if(rhs[i]->DoesFitInto(*mycells[j])){
                rhs[i]->ConnectToCell(mycells[j]);
            }
        }
    }
}