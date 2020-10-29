#include "NucleoBase.h"

NucleoBase::NucleoBase(string rna, NucleoBase* rhs){
    base = rna[0];
    prev = rhs;
    if(rna.size()!=1) next = new NucleoBase(rna.substr(1,rna.size()), this);
    else next = NULL;
}

NucleoBase::NucleoBase(const NucleoBase& rhs){
    base = rhs.base;
    if(rhs.next != NULL){
        next = new NucleoBase(*rhs.next);
        next->prev=this;
    }
    else next=NULL;
    if(rhs.prev==NULL) prev = NULL;
}


NucleoBase::~NucleoBase(){
    
}

NucleoBase* NucleoBase::GetLast(){
    if(next!=NULL) return next->GetLast();
    else return this;
}

ostream& operator<<(ostream& os, const NucleoBase& rhs){
    os<<rhs.base;
    NucleoBase* x = rhs.next;
    for( ; x!=NULL ; ){
        os<<x->base;
        x=x->next;
    }
    return os;

}