#include "Proceso.hh"


Proceso::Proceso() {
    identificador = ID_VACIA;
    memoria = 0; 
    tiempo = 0; 
}

bool Proceso::avanzar_tiempo(const int& t) {
    tiempo -= t; 
    return (tiempo < 1);
}

int Proceso::consultar_identificador() const {
    return identificador;
}

int Proceso::consultar_memoria() const {
    return memoria;
}

int Proceso::consultar_tiempo() const {
    return tiempo; 
}

void Proceso::imprimir() const{
    cout << identificador << ' ' << memoria << ' ' << tiempo << endl; 
}

void Proceso::leer() {
    cin >> identificador >> memoria >> tiempo; 
}