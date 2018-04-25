#include<iostream>
#include <queue>
#include <unistd.h>
#include <set>
#include <iterator>

using namespace std;

// Convertir boolean a string
std::string toString(bool valor) {
    return valor ? "true" : "false";
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
        static bool isBalanceado(string linea) {
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

        static bool isParentesis(char caracter) {
            if (caracter == '(') {
                return false;
            }
            else if (caracter == ')') {
                return false;
            }
            return true;
        }

        static set <string, OrdenLexicografico> balance(string linea) {
            queue <string> current;
            current.push(linea);
            string intento;
            bool solved = false;
            unsigned int solved_size = 0;
            set <string, OrdenLexicografico> soluciones;
            while (!current.empty()) {
                //cout << "\nsize:"<<current.size();
                intento = current.front();
                //cout << "\n intento actual: " << intento;
                current.pop();

                int size_aux = intento.size();
                if (size_aux < solved_size) {
                    break;
                }

                if (Parentesis::isBalanceado(intento)) {
                    soluciones.insert(intento);
                    solved = true;
                    solved_size = intento.size();
                    // Agregar a soluciones
                }

                string intento_aux;
                if (!solved) {
                    for (int i = 0; i < intento.length(); i++) {
                        if (Parentesis::isParentesis(intento[i])) {
                            continue;
                        }
                        intento_aux = intento.substr(0, i) + intento.substr(i + 1, -1);
                        //cout << "\nSubintento: " << intento_aux;
                        current.push(intento_aux);
                        //usleep(50000);
                        
                        


                    }
                }
            }

            return soluciones;
        }
};

int main() {
    // Caso de prueba
    set <string, OrdenLexicografico> salida = Parentesis::balance("()())(+ 1 2)");
    set <string> :: iterator itr;
    for (itr = salida.begin(); itr != salida.end(); ++itr){
        cout << *itr << endl;
    }
}