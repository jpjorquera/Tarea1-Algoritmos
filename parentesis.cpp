#include<iostream>
#include <queue>
#include <sstream>
#include <string.h>
#include <set>
#include <unordered_map>
#include <unordered_set>

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

// Adaptación de https://stackoverflow.com/a/3846589/2213659
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
    string input = "_";
    string testString;
    stringstream temporal;
    queue<string> removidos;
    
    int i;
    int largoString;
    int largoInput;
    int levelSolucion;
    typedef unordered_set<string> map1;
    typedef unordered_map<int, map1> map2;


    while(getline(cin,input)){
        bool flag = false;
        map2 vistos;
        set<string, OrdenLexicografico> salida;
        set <string> :: iterator itr;
        removidos.push(input);
        largoInput = input.length();
        levelSolucion = largoInput;

        // Iteramos mientras la queue no este vacia
        while(removidos.size() != 0){
            testString = removidos.front();
            removidos.pop();

            // Es string valido, agregamos a resultados, terminamos la busqueda por esta rama y seteamos el nivel
            if(Parentesis::isBalanced(testString)){
             //   cout << testString << "|" << removidos.size() << endl;
                if(!flag){
                    levelSolucion = largoInput - testString.length();
                    flag = true;
                }
                salida.insert(testString);
                
            }
            else{
                // Sacamos otro caracter para ver si ahora si es valido.
                largoString = (int)testString.length();
                if(largoInput - largoString <= levelSolucion){
                    for (i = 0; i < largoString ; ++i){
                        if(isParentesis(testString[i])){
                            temporal.str(" ");
                            temporal << testString.substr(0, i) << testString.substr(i+1) ;
                            if(vistos.find(largoString) == vistos.end()){
                                removidos.push( temporal.str() );
                                vistos[largoString].insert(temporal.str());
                            }
                            else{
                                if(vistos[largoString].find(temporal.str()) == vistos[largoString].end()){
                                    removidos.push( temporal.str() );
                                    vistos[largoString].insert(temporal.str());
                                }
                            }
                        }
                        
                    }
                } 
                
                
            }

            
        }


        for (itr = salida.begin(); itr != salida.end(); ++itr){
            cout << *itr << endl;
        }
        cout << endl;
    }


}