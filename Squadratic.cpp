#include "Squadratic.h"

Squadratic::Squadratic(int _id, float _length){
    id = _id;
    length = _length;
}

Squadratic::Squadratic(const Squadratic& rhs){
    id = rhs.id;
    length = rhs.length;
    edges.resize(rhs.edges.size());
    for(int i=0 ; i<edges.size() ; i++) edges[i] = new Wall(*rhs.edges[i]);
    _cell = rhs._cell;
    placed = rhs.placed;
}

Squadratic::~Squadratic(){
    length = 0;
    for(int i=0 ; i<childs.size() ; i++){
        if(childs[i]) delete childs[i];
    }
    childs.clear();
}

void Squadratic::ConnectToCell(Cell* const rhs){
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

bool Squadratic::DoesFitInto(const Cell& rhs)const{
    float _length,angle;
    int k=0;
    Cell* mycell = new Cell(rhs);
    mycell->StrengthenCellWall();
    if(mycell->GetCellWall().size()==4){
        for(int i=0 ; i<3 ; i++){
            _length = mycell->GetCellWall()[i]->GetLength();
            angle = (mycell->GetCellWall()[i]->FindAngleBetween(*mycell->GetCellWall()[i+1]));
            if((abs(angle-EPSILON) <= 90*PI/180) && (abs(angle+EPSILON)>=90*PI/180)) k++;
            if(((length-EPSILON) <= _length) && ((length+EPSILON) >= _length)) k++;
        }
        if(k==6) return true;
    }
    if(mycell) delete mycell;
    return false;
}

void Squadratic::React(){
    float tx,ty,bx,by,rx,ry,lx,ly,mx,my;
    Cell* mycell = new Cell(*_cell);
    mycell->RenewCellWall(edges);
    mycell->StrengthenCellWall();
    tx = (mycell->GetCellWall()[0]->GetInitialParticle().X() + mycell->GetCellWall()[1]->GetInitialParticle().X()) / 2.0;
    ty = (mycell->GetCellWall()[0]->GetInitialParticle().Y() + mycell->GetCellWall()[1]->GetInitialParticle().Y()) / 2.0;
    
    lx = (mycell->GetCellWall()[1]->GetInitialParticle().X() + mycell->GetCellWall()[2]->GetInitialParticle().X()) / 2.0;
    ly = (mycell->GetCellWall()[1]->GetInitialParticle().Y() + mycell->GetCellWall()[2]->GetInitialParticle().Y()) / 2.0;
    
    bx = (mycell->GetCellWall()[2]->GetInitialParticle().X() + mycell->GetCellWall()[3]->GetInitialParticle().X()) / 2.0;
    by = (mycell->GetCellWall()[2]->GetInitialParticle().Y() + mycell->GetCellWall()[3]->GetInitialParticle().Y()) / 2.0;
    
    rx = (mycell->GetCellWall()[3]->GetInitialParticle().X() + mycell->GetCellWall()[0]->GetInitialParticle().X()) / 2.0;
    ry = (mycell->GetCellWall()[3]->GetInitialParticle().Y() + mycell->GetCellWall()[0]->GetInitialParticle().Y()) / 2.0;

    mx = (tx+bx)/2.0;
    my = (ly+ry)/2.0;
    Squadratic* child1 = new Squadratic(121, length/2);
    Squadratic* child2 = new Squadratic(122, length/2);
    Squadratic* child3 = new Squadratic(123, length/2);
    Squadratic* child4 = new Squadratic(124, length/2);
    child1->placed=true;
    child1->_cell=_cell;
    child2->placed=true;
    child2->_cell=_cell;
    child3->placed=true;
    child3->_cell=_cell;
    child4->placed=true;
    child4->_cell=_cell;

    Particle* t = new Particle(tx,ty);
    Particle* l = new Particle(lx,ly);
    Particle* b = new Particle(bx,by);
    Particle* r = new Particle(rx,ry);
    Particle* tr = new Particle((mycell->GetCellWall()[0]->GetInitialParticle().X()), (mycell->GetCellWall()[0]->GetInitialParticle().Y()));
    Particle* tl = new Particle((mycell->GetCellWall()[1]->GetInitialParticle().X()), (mycell->GetCellWall()[1]->GetInitialParticle().Y()));
    Particle* bl = new Particle((mycell->GetCellWall()[2]->GetInitialParticle().X()), (mycell->GetCellWall()[2]->GetInitialParticle().Y()));
    Particle* br = new Particle((mycell->GetCellWall()[3]->GetInitialParticle().X()), (mycell->GetCellWall()[3]->GetInitialParticle().Y()));
    Particle* m = new Particle(mx,my);

    Wall* w1,*w2,*w3,*w4,*w5,*w6,*w7,*w8,*w9,*_w9,*w10,*_w10,*w11,*_w11,*w12,*_w12;
    w1 = new Wall(*tr,*t);
    w2 = new Wall(*t,*tl);
    w3 = new Wall(*tl,*l);
    w4 = new Wall(*l,*bl);
    w5 = new Wall(*bl,*b);
    w6 = new Wall(*b,*br);
    w7 = new Wall(*br,*r);
    w8 = new Wall(*r,*tr);
    w9 = new Wall(*t,*m);
    w10 = new Wall(*l,*m);
    w11 = new Wall(*b,*m);
    w12 = new Wall(*r,*m);
    _w9 = new Wall(*m,*t);
    _w10 = new Wall(*m,*l);
    _w11 = new Wall(*m,*b);
    _w12 = new Wall(*m,*r);
    child1->edges.push_back(w1);
    child1->edges.push_back(w9);
    child1->edges.push_back(_w12);
    child1->edges.push_back(w8);
    child2->edges.push_back(w2);
    child2->edges.push_back(w3);
    child2->edges.push_back(w10);
    child2->edges.push_back(_w9);
    child3->edges.push_back(_w10);
    child3->edges.push_back(w4);
    child3->edges.push_back(w5);
    child3->edges.push_back(w11);
    child4->edges.push_back(w12);
    child4->edges.push_back(_w11);
    child4->edges.push_back(w6);
    child4->edges.push_back(w7);
    childs.push_back(child1);
    childs.push_back(child2);
    childs.push_back(child3);
    childs.push_back(child4);
}


Squadratic& Squadratic::GetChild(float _minx, float _maxx, float _miny, float _maxy) const{
    if(childs.size() != 0){
        for(int i=0 ; i<childs.size() ; i++){
            if(childs[i]->edges.size()!=0){
                float minx = childs[i]->edges[0]->GetInitialParticle().X();
                float miny = childs[i]->edges[0]->GetInitialParticle().Y();
                float maxx = minx;
                float maxy = miny;
                for(int j=0 ; j<childs[i]->edges.size() ; j++){
                    float ix = childs[i]->edges[j]->GetInitialParticle().X();
                    float fx = childs[i]->edges[j]->GetFinalParticle().X();
                    float iy = childs[i]->edges[j]->GetInitialParticle().Y();
                    float fy = childs[i]->edges[j]->GetFinalParticle().Y();
                    minx = min(minx,ix);
                    minx = min(minx,fx);
                    maxx = max(maxx,ix);
                    maxx = max(maxx,fx);
                    miny = min(miny,iy);
                    miny = min(miny,fy);
                    maxy = max(maxy,iy);
                    maxy = max(maxy,fy);
                }
                if(maxx + EPSILON >= _maxx && maxx - EPSILON <= _maxx && minx + EPSILON >= _minx && minx - EPSILON <= _minx &&  maxy + EPSILON >= _maxy && maxy - EPSILON <= _maxy && miny + EPSILON >= _miny && miny - EPSILON <= _miny){
                    return *childs[i];
                }
            }
        }
    }
    for(int i=0 ; i<childs.size() ; i++){
        return childs[i]->GetChild(_minx,_maxx,_miny,_maxy);
    }
    throw NotBornChildException();
}