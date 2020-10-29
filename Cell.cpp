#include "Cell.h"



Cell::Cell(int _id, const vector<Wall*>& _walls, Tissue* _tissue){
    id = _id;
    walls.resize(_walls.size());
    for(int i=0 ; i<walls.size() ; i++){
        CurvyWall* derived = dynamic_cast<CurvyWall*>(_walls[i]);
        if (derived == NULL) walls[i] = new Wall(*_walls[i]);
        else walls[i] = new CurvyWall(*derived);
    }
    tissue = _tissue;
}



Cell::Cell(const Cell& rhs){
    id = rhs.id;
    walls.resize(rhs.walls.size());
    for(int i=0 ; i<walls.size() ; i++){
        CurvyWall* derived = dynamic_cast<CurvyWall*>(rhs.walls[i]);
        if (derived == NULL) walls[i] = new Wall(*rhs.walls[i]);
        else walls[i] = new CurvyWall(*derived);
    }
    tissue = rhs.tissue;
}



int Cell::GetCellID() const{
    return id;
}



Tissue* Cell::GetTissue() const{
    return tissue;
}



const vector<Wall*>& Cell::GetCellWall() const{
    return walls;
}



void Cell::RenewCellWall(vector<Wall*>& rhs){
    for(int i=0 ; i<walls.size() ; i++){
        if(walls[i]) delete walls[i];
    }
    walls.resize(rhs.size());
    for(int i=0 ; i<walls.size() ; i++){
        CurvyWall* derived = dynamic_cast<CurvyWall*>(rhs[i]);
        if (derived == NULL) walls[i] = new Wall(*rhs[i]);
        else walls[i] = new CurvyWall(*derived);
    }
}



void Cell::StrengthenCellWall(){
    int k=0;
    vector<Wall*> mywalls;
    mywalls.resize(walls.size());
    CurvyWall* derived = dynamic_cast<CurvyWall*>(walls[0]);
    if(derived==NULL) mywalls[0] = new Wall(*walls[0]);
    else mywalls[0] = new CurvyWall(*derived);
    for(int i=1 ; i<walls.size() ; i++){
        try{
            *mywalls[k] = mywalls[k]->operator+(*walls[i]);
        }
        catch(ApplePearException){
            k++;
            CurvyWall* derived = dynamic_cast<CurvyWall*>(walls[i]);
            if(derived==NULL) mywalls[k] = new Wall(*walls[i]);
            else mywalls[k] = new CurvyWall(*derived);
        }
    }
    try{
        *mywalls[0] = mywalls[0]->operator+(*mywalls[k]);
        if(k!=0){
            if(mywalls[k]) delete mywalls[k];
            mywalls[k]=NULL;
        }
    }
    catch(ApplePearException){};

    int a=0;
    for(int i=0 ; i<mywalls.size();i++){
        if(mywalls[i]==NULL) a++;
    }
    for(int i=0 ; i<a;i++) mywalls.pop_back();

    this->RenewCellWall(mywalls);
}



Cell::~Cell(){
    for(int i=0 ; i<walls.size() ; i++){
        if(walls[i]!=NULL) delete walls[i];
    }
    walls.clear();
}



ostream& operator<<(ostream& os, const Cell& rhs){
    for(int i=0 ; i<rhs.walls.size()-1; i++){
        os<<"("<<rhs.walls[i]->GetInitialParticle().X()<<","<<rhs.walls[i]->GetInitialParticle().Y()<<")"<<" - ";
    }
    os<<"("<<rhs.walls.back()->GetInitialParticle().X()<<","<<rhs.walls.back()->GetInitialParticle().Y()<<")";
    return os;
}