#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include "TPilha.h"
#define PI 3.1415926535898

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
        case 'l': return prioTran;
        case 's': return prioTran;
        case 'c': return prioTran;
        case 't': return prioTran;
        case 'q': return prioTran;
        case 'a': return prioTran;
    }
    return -1; /// indica erro ou alog assim <----
}

/// função que converte notação infixa para posfixa
vector <string> converte(vector <string> tokens){
    TPilha<string> *pilha = new TPilha<string>();
    vector <string> polonesa;

    for (int i=0; i<(int)tokens.size(); i++){
        string c = tokens[i];

        if (isalpha(c[0]) && isupper(c[0]) || isdigit(c[0]) || c == "p" || c == "_"){
            polonesa.push_back(c);

        }if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^"){
            while(pilha->size() && (prioOp(c[0]) < prioOp(pilha->top()[0]) || (prioOp(c[0]) == prioOp(pilha->top()[0]) && c[0] != '^')) && c[0] != '(' ){
                polonesa.push_back(pilha->pop());
            }
            pilha -> push(c);
        }if (c == "("){
             pilha->push(c);
        }if (c == ")"){
            while(pilha->size() && pilha->top() != "("){
                polonesa.push_back(pilha->pop());
            }

            if (pilha->top() == "("){
                pilha->pop();
            }
        }if (c != "p" && islower(c[0])){
            pilha -> push(c);
        }
    }


    while(pilha->size()) {
        polonesa.push_back(pilha->pop());
    }

    return polonesa;
}

vector<string> tokenizacao(string expressao){
    vector<string> tokens;

    for ( int i = 0; i < expressao.size(); i ++){
        char c = expressao[i];

        if (isupper(c)){
                if (expressao[i+1] == 'I'){
                    tokens.push_back(string(1, 'p'));
                    i++;
                }else tokens.push_back(string(1, c));
        }if (c == '-'){
            if (i == 0 || expressao[i-1] == '('){
                    tokens.push_back(string(1, '_'));
            }else tokens.push_back(string(1, c));
        }if (c == '+' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')'){
            tokens.push_back(string(1, c));
        }if (isalpha(c)){
            if (c == 'l'){
                tokens.push_back(string(1, c));
                i += 2;

            }if (c == 's'){
                if (expressao[i+1] == 'e'){
                    tokens.push_back(string(1, c));
                    i += 2;
                }if (expressao[i+1] == 'q'){
                    tokens.push_back(string(1, 'q'));
                    i += 3;
                }
            }if(c == 'c'){
                tokens.push_back(string(1, c));
                i += 2;
            }if (c == 't'){
                tokens.push_back(string(1, c));
                i += 2;
            }if (c == 'a'){
                tokens.push_back(string(1, c));
                i += 2;
            }

        }if (isdigit(c)){
            string n = "";
            for (int j = i; j < expressao.size(); j ++ ){
                if(isdigit(expressao[j])){
                    n += expressao[j];
                    i ++;
                }else break;
            } tokens.push_back(n);
            i--;
        }
    }
    return tokens;
}

double stringParaDouble(string s){
    double d = 0;
    for (int i = 0; i < s.size(); i++){
        d *= 10;
        d += s[i] - '0';
    }
    return d;
}

double computa(vector<string>polonesa){
    TPilha<double> *pilha = new TPilha<double>();
    double variaveis[26] = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};
    double n;

    for (int i = 0; i < polonesa.size(); i++){
        if(isupper(polonesa[i][0])){
            if(isnan(variaveis[polonesa[i][0]-'A'])) {
                cout << "Insira o valor da variavel " << polonesa[i] << endl;
                cin >> n;
                variaveis[polonesa[i][0]-'A'] = n;
            } else {
                n = variaveis[polonesa[i][0]-'A'];
            }
            pilha->push(n);
        }if(isdigit(polonesa[i][0])){
            pilha->push(stringParaDouble(polonesa[i]));
        }if(polonesa[i] == "+"){
            double topo = pilha->pop();
            double topod = pilha->pop();
            double num = topo + topod;
            pilha->push(num);
        }if(polonesa[i] == "-"){
                double topo = pilha->pop();
                double topod = pilha->pop();
                double num = topod - topo;
                pilha->push(num);
        }if(polonesa[i] == "_"){
                double topo = pilha->pop();
                double num = -topo;
                pilha->push(num);
        }if(polonesa[i] == "*"){
            double topo = pilha->pop();
            double topod = pilha->pop();
            double num = topo * topod;
            pilha->push(num);
        }if(polonesa[i] == "/"){
            double topo = pilha->pop();
            double topod = pilha->pop();
            double num = topod / topo;
            pilha->push(num);
        }if(polonesa[i] == "^"){
            double topo = pilha->pop();
            double topod = pilha->pop();
            double num = pow(topod, topo);
            pilha->push(num);
        }if(polonesa[i] == "l"){
            double topo = pilha->pop();
            double num = log(topo);
            pilha->push(num);
        }if(polonesa[i] == "s"){
            double topo = pilha->pop();
            double num = sin(topo);
            pilha->push(num);
        }if(polonesa[i] == "c"){
            double topo = pilha->pop();
            double num = cos(topo);
            pilha->push(num);
        }if(polonesa[i] == "t"){
            double topo = pilha->pop();
            double num = tan(topo);
            pilha->push(num);
        }if(polonesa[i] == "q"){
            double topo = pilha->pop();
            double num = sqrt(topo);
            pilha->push(num);
        }if(polonesa[i] == "a"){
            double topo = pilha->pop();
            double num = abs(topo);
            pilha->push(num);
        }if(polonesa[i] == "p"){
            pilha->push(PI);
        }
    }

    return pilha->pop();
}

int main(){
    string expressao;
    cout << "-----------------------------------------------Manual do usuario-----------------------------------------------" << endl <<
    "-> Todos os operandos devem estar em caps lock" << endl <<
    "-> Todas as funcoes transcedentais devem ser escritas em letras minusculas. Exemplo: log(operando)" << endl <<
    "-> As funcoes trancendentais aceitas sao:" << endl <<
    "\t Log na base 10: log()" << endl <<
    "\t Seno: sen()" << endl <<
    "\t Cosseno: cos()" << endl <<
    "\t Tangente: tan()" << endl <<
    "\t Raiz quadrada: sqrt()" << endl <<
    "---------------------------------------------------------------------------------------------------------------"<< endl <<
    "Insira a expressao numerica" << endl;
    cin >> expressao;

    vector<string> tokens = tokenizacao(expressao);;
    vector<string> polonesa = converte(tokens);

    double n = computa(polonesa);
    cout << "Resultado = " << n << endl;

    return 0;
}
