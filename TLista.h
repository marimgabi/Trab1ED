#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED

#include <iostream>
#include <string>
#include "TNo.h"

using namespace std;

template <typename T> class TLista{
      TNo<T> *prim, *ult;
      int n; //número de elementos na lista
      string tipo;
   public:
      TLista(); ///construtor default
      TLista(const string &_tipo); ///construtor parametrizado
      TLista(TLista<T> &L); ///construtor de cópia
      void setprim(TNo<T> *p);
      void setult(TNo<T> *p);
      void settipo(const string &str);
      TNo<T>* getprim();
      TNo<T>* getult();
      string gettipo();
      int size() const; ///método para consultar o número de elementos na lista
      void ins_ini(const T &_info); ///inserir um elemento no início da lista
      void ins_fim(const T &_info); ///inserir um elemento no final da lista
      void ins(int i, const T &_info); ///inserir um elemento na posição i da lista (0 é o primeiro)
      T rem_ini(); ///remove e retorna o primeiro elemento da lista
      T rem_fim(); ///remove e retorna o último elemento da lista
      T rem(int i); ///remove e retorna o i-ésimo elemento da lista
      void update(int i, const T &_ninfo); ///atualiza o i-ésimo elemento da lista
      T get(int i); ///retornar o valor do i-ésimo elemento da lista
      TNo<T>* get_p(int i); ///retornar um ponteiro que indica o i-ésimo elemento da lista
      void print(); ///exibir todos os elementos da lista
      TLista<T>& operator=(TLista<T> &L);
      ~TLista<T>();
};

template <typename T> TLista<T>::TLista(){
   prim = nullptr;
   ult = nullptr;
   n = 0;
   tipo = "";
}

template <typename T> TLista<T>::TLista(const string &_tipo){
   prim = nullptr;
   ult = nullptr;
   n = 0;
   tipo = _tipo;
}

template <typename T> TLista<T>::TLista(TLista<T> &L){
   TNo<T> *p;
   int i;

   //A instanciação de um objeto pela chamada explícita ao construtor de cópia
   //não invoca o construtor default. Portanto as inicializações devem ser
   //realizadas também dentro deste construtor.
   prim = nullptr;
   ult = nullptr;
   n = 0;
   tipo = L.gettipo(); //Se o objeto L é const, chamar um de seus métodos causa erro,
   i = L.size();       //pois não há garantia que o método não faz alteração de alguma propriedade do objeto L.
   p = L.getprim();    //Por isso no construtor de cópia e no operator= L não é mais constante.

   while (i > 0){
      this->ins_fim(p->getinfo());
      p = p->getprox();
      --i;
   }
}

template <typename T> void TLista<T>::setprim(TNo<T> *p){
   prim = p;
}

template <typename T> void TLista<T>::setult(TNo<T> *p){
   ult = p;
}

template <typename T> void TLista<T>::settipo(const string &str){
   tipo = str;
}

template <typename T> TNo<T>* TLista<T>::getprim(){
   return prim;
}

template <typename T> TNo<T>* TLista<T>::getult(){
   return ult;
}

template <typename T> string TLista<T>::gettipo(){
   return tipo;
}

template <typename T> int TLista<T>::size() const{
   return n;
}

template <typename T> void TLista<T>::ins_ini(const T &_info){
   TNo<T> *p = new TNo<T>();

   p->setinfo(_info);
   p->setprox(prim);
   prim = p;
   if (n==0) ult = p;
   ++n;
}

template <typename T> void TLista<T>::ins_fim(const T &_info){
   TNo<T> *p = new TNo<T>();

   p->setinfo(_info);
   p->setprox(nullptr);
   if (n==0) prim = p;
   else ult->setprox(p);
   ult = p;
   ++n;
}

template <typename T> void TLista<T>::ins(int i, const T &_info){
   TNo<T> *p, *q;

   if (i >= n) ins_fim(_info);
   else{
      if (i == 0) ins_ini(_info);
      else{
         p = get_p(i-1);
         q = new TNo<T>();
         q->setinfo(_info);
         q->setprox(p->getprox());
         p->setprox(q);
         ++n;
      }
   }
}

template <typename T> T TLista<T>::rem_ini(){
   TNo<T> *p;
   T temp;

   if (n == 0){
      cout << "Erro! Acesso ilegal. A lista esta vazia!" << endl;
      exit(0);
   }
   else {
      p = prim;
      prim = p->getprox();
      temp = p->getinfo();
      delete p;
      --n;
      if (n == 0) ult = nullptr;
   }
   return temp;
}

template <typename T> T TLista<T>::rem_fim(){
   TNo<T> *p, *q;
   T temp;

   if (n == 0){
      cout << "Erro! Acesso ilegal. A lista esta vazia!" << endl;
      exit(0);
   }
   else{
      if (n == 1){
         return (rem_ini());
      }
      else{
         p = get_p(n - 2);
         q = ult;
         p->setprox(nullptr);
         ult = p;
         temp = q->getinfo();
         delete q;
         --n;
         return(temp);
      }
   }
}

template <typename T> T TLista<T>::rem(int i){
   TNo<T> *p, *q;
   T temp;

   if (i >= n){
      cout << "Erro! Acesso ilegal!" << endl;
      exit(0);
   }
   else{
      if (i == 0) return(rem_ini());
      else{
         if (i == (n - 1)) return (rem_fim());
         else{
            p = get_p(i - 1);
            q = p->getprox();
            temp = q->getinfo();
            p->setprox(q->getprox());
            --n;
            delete q;
            return(temp);
         }
      }
   }
}

template <typename T> void TLista<T>::update(int i, const T &_ninfo){
   TNo<T> *p;

   if (i >= n){
      cout << "Erro! Acesso ilegal!" << endl;
      exit(0);
   }
   else{
      p = get_p(i);
      p->setinfo(_ninfo);
   }
}

template <typename T> T TLista<T>::get(int i){
   TNo<T> *p;

   if (i >= n){
      cout << "Erro! Acesso ilegal!" << endl;
      exit(0);
   }
   else{
      p = get_p(i);
      return(p->getinfo());
   }
}

template <typename T> TNo<T>* TLista<T>::get_p(int i){
   TNo<T> *p;

   if (i >= n){
      cout << "Erro! Acesso ilegal!" << endl;
      exit(0);
   }
   else{
      if (i ==  (n - 1)) p = ult;
      else{
         p = prim;
         while (i > 0){
            p = p->getprox();
            --i;
         }
      }
   return p;
   }
}

template <typename T> void TLista<T>::print(){
   TNo<T> *p;

   cout << "Lista de --> " << tipo << endl;
   cout << "Tamanho da lista = " << n << endl;

   p = prim;
   while (p != nullptr){
      cout << p->getinfo() << " ";
      p = p->getprox();
   }
   cout << endl << "Fim da lista" << endl;
}

template <typename T> TLista<T>& TLista<T>::operator=(TLista<T> &L){
   TNo<T> *p;
   int i;

   if (this == &L) return *this;
   else{
      while (this->n > 0){
         this->rem_ini();
      }

      i = L.size();
      p = L.getprim();

      while (i > 0){
         this->ins_fim(p->getinfo());
         p = p->getprox();
         --i;
      }
      this->settipo(L.gettipo());
   }
   return (*this);
}

template <typename T> TLista<T>::~TLista(){
   TNo<T> *p, *q;

   p = prim;
   while (p != nullptr){
      q = p->getprox();
      delete p;
      p = q;
   }

   prim = nullptr;
   ult = nullptr;
   n = 0;
}


#endif // TLISTA_H_INCLUDED
