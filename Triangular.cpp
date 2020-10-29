#include "Triangular.h"

Triangular::Triangular(int _id, const vector<Wall*>& _edges, const NucleoBase& rhs){
    id = _id;
    edges.resize(_edges.size());
    for(int i=0 ; i<edges.size() ; i++){
        edges.at(i) = new Wall(_edges.at(i)->GetLength());
    }
    chain = new NucleoBase(rhs);
}

Triangular::~Triangular(){
    if(chain) delete chain;
}

void Triangular::ConnectToCell(Cell* const rhs){
    _cell = rhs;
    placed = true;
    for(int i=0 ; i<edges.size() ; i++){
        if(edges[i]!=NULL) delete edges[i];
    } 
    edges.clear();
    edges.resize(rhs->GetCellWall().size());
    for(int i=0 ; i< edges.size() ; i++){
        edges[i] = new Wall(*rhs->GetCellWall()[i]);
    }
}

bool Triangular::DoesFitInto(const Cell& rhs) const{
    float _l0,l0,_l1,l1,_l2,l2;
    Cell* mycell = new Cell(rhs);
    mycell->StrengthenCellWall();
    if(mycell->GetCellWall().size()==3){
        _l0 = edges[0]->GetLength();
        _l1 = edges[1]->GetLength();
        _l2 = edges[2]->GetLength();
        l0 = mycell->GetCellWall()[0]->GetLength();
        l1 = mycell->GetCellWall()[1]->GetLength();
        l2 = mycell->GetCellWall()[2]->GetLength();
        if((_l0 + EPSILON >= l0) && (_l0 - EPSILON <= l0) && (_l1 + EPSILON >= l1) && (_l1 - EPSILON <= l1) && (_l2 + EPSILON >= l2) && (_l2 - EPSILON <= l2)) {
            if(mycell) delete mycell; 
            return true;
        }
        if((_l0 + EPSILON >= l0) && (_l0 - EPSILON <= l0) && (_l1 + EPSILON >= l2) && (_l1 - EPSILON <= l2) && (_l2 + EPSILON >= l1) && (_l2 - EPSILON <= l1)) {
            if(mycell) delete mycell; 
            return true;
        }

        if((_l0 + EPSILON >= l1) && (_l0 - EPSILON <= l1) && (_l1 + EPSILON >= l0) && (_l1 - EPSILON <= l0) && (_l2 + EPSILON >= l2) && (_l2 - EPSILON <= l2)) {
            if(mycell) delete mycell;  
            return true;
        }
        if((_l0 + EPSILON >= l1) && (_l0 - EPSILON <= l1) && (_l1 + EPSILON >= l2) && (_l1 - EPSILON <= l2) && (_l2 + EPSILON >= l0) && (_l2 - EPSILON <= l0)) {
            if(mycell) delete mycell;  
            return true;
        }

        if((_l0 + EPSILON >= l2) && (_l0 - EPSILON <= l2) && (_l1 + EPSILON >= l0) && (_l1 - EPSILON <= l0) && (_l2 + EPSILON >= l1) && (_l2 - EPSILON <= l1)){
            if(mycell) delete mycell;  
            return true;
        }
        if((_l0 + EPSILON >= l2) && (_l0 - EPSILON <= l2) && (_l1 + EPSILON >= l1) && (_l1 - EPSILON <= l1) && (_l2 + EPSILON >= l0) && (_l2 - EPSILON <= l0)){
            if(mycell) delete mycell;  
            return true;
        }
    }
    if(mycell) delete mycell; 
    return false;
}

void Triangular::React(){
    _cell->GetTissue()->RemoveCell(*_cell);
}

const NucleoBase& Triangular::GetRNA() const{
    return *chain;
}

void Triangular::Mutate(Triangular& rhs){
    int i = 0;
    int k = 0;
    int size = 0;
    NucleoBase* p = this->chain;
    NucleoBase* r = rhs.chain;
    NucleoBase* startp;
    NucleoBase* startr;
    startp=p;
    for(size;startp!=NULL;size++){
        startp=startp->next;
    }
    for(;p->base == r->base ;i++){
        p=p->next;
        r=r->next;
    }
    startp = p;
    startr = r;
    p=p->GetLast();
    r=r->GetLast();
    for(;p->base==r->base;k++){
        p=p->prev;
        r=r->prev;
    }
    p=startp;
    r=startr;
    for(int x=i;x<size-k;x++){
        if(p->base == 'G' && r->base == 'S'){
            p->base ='S';
            r->base = 'G';
            p=p->next;
            r=r->next;
        }
        else if(p->base == 'S' && r->base == 'G'){
            p->base ='G';
            r->base = 'S';
            p=p->next;
            r=r->next;
        }

        else if(p->base == 'A' && r->base == 'U'){
            p->base ='U';
            r->base = 'A';
            p=p->next;
            r=r->next;
        }

        else if(p->base == 'U' && r->base == 'A'){
            p->base ='A';
            r->base = 'U';
            p=p->next;
            r=r->next;
        }
        else{
            p->prev->next = p->next;
            p->next->prev = p->prev;
            r->prev->next = r->next;
            r->next->prev = r->prev;
            p=p->next;
            r=r->next;
        }
    }
}

