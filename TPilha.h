#ifndef TPILHA_H_INCLUDED
#define TPILHA_H_INCLUDED
#include "TLista.h"

using namespace std;

template <typename T> class TPilha{
    TLista<T> *l;
    int _size;

    public:
        TPilha<T>();
        void push(T _info);
        T pop();
        T top();
        int size();
        ~TPilha<T>();
};

template <typename T> TPilha<T>::TPilha(){
    l = new TLista<T>();
    _size = 0;
}

template <typename T> void TPilha<T>::push(T _info){
    l -> ins_ini(_info);
    _size++;
}

template <typename T> T TPilha<T>::pop(){
    _size--;
    return(l -> rem_ini());
}

template <typename T> T TPilha<T>::top(){
    return (l -> get(0));
}

template <typename T> int TPilha<T>::size(){
    return _size;
}

template <typename T> TPilha<T>::~TPilha(){
    delete l;
}


#endif // TPILHA_H_INCLUDED
