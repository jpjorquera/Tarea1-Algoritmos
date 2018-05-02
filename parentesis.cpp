#include<iostream>
#include <queue>
#include <set>
#include <iterator>
//#include <ctime>
#include <unordered_set>

using namespace std;

// Uso de iteradores para devolver el orden lexicografico en el set
struct OrdenLexicografico {
    bool operator () (const std::string & palabra1, const std::string & palabra2) {
        return palabra1 < palabra2;
    }
};

// Clase con los métodos utilizados para el trabajo de paréntesis
class Parentesis {
    public:
        // Método para verificar si el string está balanceado
        static bool isBalanceado(string linea) {
            unsigned int i = 0;
            int contador = 0;
            // Usar contador
            // Sumar al abrir
            while (i < linea.length()) {
                if (linea[i] == '(') {
                    contador++;
                }
                // Restar al cerrar
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

        // Método para verificar si el caracter entregado es paréntesis
        static bool isParentesis(char caracter) {
            if (caracter == '(') {
                return false;
            }
            else if (caracter == ')') {
                return false;
            }
            return true;
        }

        // Método que recibe una línea y retorna un unordered_set
        // con todas las soluciones balanceadas, eliminando
        // la cantidad mínima posible de paréntesis
        static set <string, OrdenLexicografico> balance(string linea) {
            unordered_set<string> visitados;
            // Guardar combinaciones ya verificadas
            visitados.insert(linea);
            // Usar cola para el backtracking e ir iterando
            // sobre las siguientes posibles soluciones
            queue <string> current;
            current.push(linea);
            string intento;
            bool solved = false; 
            unsigned int solved_size = 0;
            set <string, OrdenLexicografico> soluciones;
            // Mientras queden posibles soluciones en la cola
            while (!current.empty()) {
                intento = current.front();
                current.pop();

                unsigned int size_aux = intento.size();
                // Si hay que saltar, ya que la cola está con combinaciones
                // de menor tamaño
                if (size_aux < solved_size) {
                    break;
                }

                // Caso base:
                // verificar si solución actual está balanceada
                if (Parentesis::isBalanceado(intento)) {
                    soluciones.insert(intento);
                    solved = true;
                    solved_size = intento.size();
                }

                string intento_aux;
                // Si no ha sido resuelto, encolar siguiente nivel de combinaciones
                if (!solved) {
                    // Avanzar eliminando cada paréntesis
                    for (unsigned int i = 0; i < intento.length(); i++) {
                        if (Parentesis::isParentesis(intento[i])) {
                            continue;
                        }
                        intento_aux = intento.substr(0, i) + intento.substr(i + 1, -1);
                        // Actualizar visitados
                        if (visitados.find(intento_aux) == visitados.end()) {
                            visitados.insert(intento_aux);
                        }
                        // Si ya fue visitado, saltar
                        else {
                            continue;
                        }
                        // Encolar
                        current.push(intento_aux);
                    }
                }
            }
            return soluciones;
        }
};

int main() {
    //int start_s=clock();
    string input = "";
    set <string, OrdenLexicografico> salida;
    set <string> :: iterator itr;
    // Recibir input hasta EOF
    while(getline(cin,input)) {
        // Obtener set
        set <string, OrdenLexicografico> salida = Parentesis::balance(input);
        // Imprimir soluciones
        for (itr = salida.begin(); itr != salida.end(); ++itr) {
            cout << *itr << endl;
        }
        cout << endl;
    }
    //int stop_s=clock();
    //cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
}