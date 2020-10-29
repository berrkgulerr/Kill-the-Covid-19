#include "MicroOrganism.h"
MicroOrganism::MicroOrganism(){
    id=0;
    _cell = NULL;
    placed = false;
}

MicroOrganism::MicroOrganism(int _id, const vector<Wall*>& _edges){
    id = _id;
    edges.resize(_edges.size());
    for(int i=0 ; i<edges.size() ; i++){
        CurvyWall* derived = dynamic_cast<CurvyWall*>(_edges[i]);
        if (derived == NULL) edges[i] = new Wall(_edges[i]->GetLength());
        else edges[i] = new CurvyWall(derived->GetLength(), derived->GetRadius());
    }
    placed = false;
}

ostream& operator<<(ostream& os, const MicroOrganism& rhs){
    if(rhs.placed) os<<"The microorganism "<<rhs.id<<" was successfully placed into the cell "<< rhs._cell->GetCellID();
    else os<<"The microorganism "<<rhs.id<<" could not be placed into any cell!";
    return os;
}

bool MicroOrganism::DoesFitInto(const Cell& rhs) const{

}

void MicroOrganism::ConnectToCell(Cell* const rhs){
    
}

void MicroOrganism::React(){

}

MicroOrganism::~MicroOrganism(){
    placed = false;
    id = 0;
    for(int i=0 ; i<edges.size() ; i++){
        if(edges[i]) delete edges[i];
    } 
    edges.clear();
    _cell=NULL;
}