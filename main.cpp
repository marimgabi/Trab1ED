#include <iostream>
#include <cstring>
#include "TPilha.h"
#define PI 3,1415926535898

using namespace std;

///Prioridades
int prioMais=1, prioMult=2, prioExp=3, prioTran=4, prioUni=4;


/// função que verifica a prioridade dos operadores
int prioOp(char c){
    switch(c){
        case '+': return prioMais;
        case '-': return prioMais;
        case '*': return prioMult;
        case '/': return prioMult;
        case '^': return prioExp;
    }
}

/// função que converte notação infixa para posfixa
string converte(string expressao){
    TPilha<char> *pilha;


    for (int i=0; i<expressao.size(); i++){
        char c = expressao[i];

        if (isalpha(c) && isupper(c)){
            cout << c;
        }if (c == '+' || c == '-' || c == '*' || c == '/'){
            while(prioOp(c) < prioOp(pilha->top()) || prioOp(c) == prioOp(pilha->top()) && c != '(' ){
                count << pilha->pop();
            }
            pilha -> push(c);
        }if (c == '('){
             count << pilha->push(c);
        }if (c == ')'){
            while(pilha->top() != '('){
                count << pilha->pop();
                }
                count << pilha->pop();
                delete(pilha->pop);
        }if (pilha->top != nullptr){
                    count << pilha->pop();
        }if (c == '\0'){
            while ()
        }
    }
}

int main(){

    string expressao;

    cout << "-----------------------------------------------Manual do usuario-----------------------------------------------" << endl <<
    "-> Todos os operandos devem estar em caps lock" << endl <<
    "-> Todas as funcoes transcedentais devem ser escritas em letras minusculas e usando colchetes. Exemplo: log[]" << endl <<
    "---------------------------------------------------------------------------------------------------------------"<< endl <<
    "Insira a expressao numerica" << endl;
    cin >> expressao;

    //cout << strlen(expressao);

    return 0;
}
