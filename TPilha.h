#ifndef TPILHA_H_INCLUDED
#define TPILHA_H_INCLUDED
#include "TLista.h"

using namespace std;

template <typename T> class TPilha{
    TLista<T> *l;

    public:
        TPilha<T>();
        void push(T _info);
        T pop();
        T top();
        ~TPilha<T>();
};

template <typename T> TPilha<T>::TPilha(){
    l = new TLista<T>();
}

template <typename T> void TPilha<T>::push(T _info){
    l -> ins_ini(_info);
}

template <typename T> T TPilha<T>::pop(){
    return(l -> rem_ini());
}

template <typename T> T TPilha<T>::top(){
    return (l -> get(0));
}

template <typename T> TPilha<T>::~TPilha(){
    delete l;
}


#endif // TPILHA_H_INCLUDED
