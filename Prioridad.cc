#include "Prioridad.hh"

Prioridad::Prioridad() {
    aceptados = 0; 
    rechazados = 0;
}

bool Prioridad::añadir_proceso(const Proceso& p) {
    if (not set_procesos.insert(p.consultar_identificador()).second) return false; 
    lista_procesos.insert(lista_procesos.end(), p);
    return true; 
}

bool Prioridad::vacio() const {
    return lista_procesos.empty();
}

void Prioridad::enviar_procesos_cluster(int& n, Cluster& cluster) {
    list<Proceso>::const_iterator it = lista_procesos.begin();

    int marca = -1; //entero para marcar el identificador del primer proceso rechazado
    bool marca_puesta = false; 

    while (n > 0 and not lista_procesos.empty() and it->consultar_identificador() != marca) {
        Proceso aux = *it;

        if (cluster.añadir_mejor_procesador(aux)) {
            set_procesos.erase(it->consultar_identificador());
            lista_procesos.erase(it);  
            --n;
            ++aceptados;
        }
        else {
            lista_procesos.erase(it); //lo elimina de la primera posicion
            lista_procesos.insert(lista_procesos.end(), aux); //lo añade a la ultima posicion
            if (not marca_puesta) {
                marca = aux.consultar_identificador();
                marca_puesta = true; 
            } 
            ++rechazados;
        }

        it = lista_procesos.begin();
    }
}

void Prioridad::imprimir() const {
    list<Proceso>::const_iterator it = lista_procesos.begin(); 
    while (it != lista_procesos.end()) {
        it->imprimir();
        ++it;
    }
    cout << aceptados << ' ' << rechazados << endl;   
}