#include<iostream>

using namespace std;

// Convertir boolean a string
std::string toString(bool valor) {
    return valor ? "true" : "false";
}

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
};

int main() {
    // Caso de prueba
    string prueba = "((())";
    cout << "Está balanceado? " << toString(Parentesis::isBalanceado(prueba));
}