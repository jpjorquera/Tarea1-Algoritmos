#include<iostream>
#include <queue>
#include <sstream>
#include <string.h>
#include <set>

using namespace std;

// Convertir boolean a string
std::string toString(bool valor) {
    return valor ? "true" : "false";
}

bool isParentesis(char caracter){
    if(caracter == '(' || caracter == ')'){
        return true;
    }
    return false;
}

struct OrdenLexicografico {
    bool operator () (const std::string & palabra1, const std::string & palabra2) {
        return palabra1 < palabra2;
    }
};

class Parentesis {

    public:
        // Verificar si el string está balanceado
        static bool isBalanced(string linea) {
            unsigned int i = 0;
            int contador = 0;
            while (i < linea.length()) {
                if (linea[i] == '(') {
                    contador++;
                }
                else if (linea[i] == ')') {
                    contador--;
                    if (contador < 0) {
                        return false;
                    }
                }
                i++;
            }
            if (contador == 0) {
                return true;
                
            }
            return false;
        }
};

int main() {
    string input;
    string testString;
    stringstream temporal;
    queue<string> removidos;
    set<string, OrdenLexicografico> salida;
    set <string> :: iterator itr;
    int i;
    int largoString;
    int largoInput;

    getline(cin,input);
    removidos.push(input);
    largoInput = input.length();

    int levelSolucion = largoInput;

    
    // Por cada nivel vemos si esta balanceado y si no esta bajamos un nivel, si esta lo agregamos al output
    while(removidos.size() != 0){
        testString = removidos.front();
        // Es string valido, agregamos a resultados y terminamos la busqueda por esta rama
        if(Parentesis::isBalanced(testString)){
            levelSolucion = largoInput - testString.length();
            salida.insert(testString);
            removidos.pop();
        }
        else{
            // Sacamos otro caracter para ver si ahora si es valido.
            
            largoString = (int)testString.length();
            if(largoInput - largoString <= levelSolucion){
                for (i = 0; i < largoString ; ++i){
                    if(isParentesis(testString[i])){
                        temporal.str(" ");
                        temporal << testString.substr(0, i) << testString.substr(i+1) ;
                        removidos.push( temporal.str() );
                    }
                    
                }
            }
            
            removidos.pop();
        }

        
    }


    for (itr = salida.begin(); itr != salida.end(); ++itr){
        cout << *itr << endl;
    }



}