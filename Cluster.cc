#include "Cluster.hh"


Cluster::Cluster() {}

void Cluster::construir(BinTree<string>& id_procesadores, map<string, Procesador>& map_procesadores, int& mem_añadida) {
    Procesador p; 
    if (p.leer()) {
        mem_añadida += p.consultar_memoria_disp(); 
        map_procesadores.insert(make_pair(p.consultar_id(), p)); //se inserta en el mapa el procesador leido
        BinTree<string> l; 
        construir(l, map_procesadores, mem_añadida);
        BinTree<string> r; 
        construir(r, map_procesadores, mem_añadida);
        id_procesadores = BinTree<string>(p.consultar_id(), l, r); //se inserta en el arbol el identificador del procesador leido
    } 
}

bool Cluster::alta_proceso_procesador(const string& id, const Proceso& p, char& error) {
    map<string, Procesador>::iterator it; 
    it = map_procesadores.find(id);
    if (it == map_procesadores.end()) {
        error = 4;
        return false; 
    }
    if ((*it).second.existe_proceso(p.consultar_identificador())) {
        error = 3;
        return false; 
    }
    if (not (*it).second.añadir_proceso(p)) {
        error = 5;
        return false; 
    }
    max_hueco -= p.consultar_memoria(); //resta al atributo max_hueco la memoria del proceso añadido
    return true; 
}

bool Cluster::baja_proceso_procesador(const string& id_procesador, const int& id_proceso, char& error) {
    map<string, Procesador>::iterator it; 
    it = map_procesadores.find(id_procesador);
    if (it == map_procesadores.end()) {
        error = 4;
        return false; 
    }
    if (not (*it).second.eliminar_proceso(id_proceso, max_hueco)) { //max_hueco se pasa por referencia para si se elimina el proceso que el hueco nuevo libre se sume al hueco total
        error = 8;
        return false; 
    }
    return true; 
}

void Cluster::avanzar_tiempo(const int& t) {
    map<string, Procesador>::iterator it = map_procesadores.begin(); 
    while (it != map_procesadores.end()) {
        it->second.avanzar_tiempo(t, max_hueco); //max_hueco se pasa por referencia para si se elimina el proceso que el hueco nuevo libre se sume al hueco total
        ++it;
    }
}

bool Cluster::sustituir_arbol(BinTree<string>& aux, const BinTree<string>& arbol, const BinTree<string>& arbol_sustituir, const string& id) {    
    if (arbol.empty()) return false; //caso base
    if (arbol.value() != id) {
        BinTree<string> l;
        bool left = sustituir_arbol(l, arbol.left(), arbol_sustituir, id);
        BinTree<string> r;
        bool right = sustituir_arbol(r, arbol.right(), arbol_sustituir, id);
        aux = BinTree<string>(arbol.value(), l, r);
        return (left or right); 
    }
    if (not arbol.right().empty() or not arbol.left().empty()) {
        return false; 
    }
    aux = arbol_sustituir; //Si arbol.value() == id y no tiene hijos 
    return true; 
}

bool Cluster::modificar_cluster(const string& id, char& error) {
    map<string, Procesador> aux_map; 
    BinTree<string> aux_arbol;
    int mem_añadida = 0; 
    construir(aux_arbol, aux_map, mem_añadida); //aux_arbol y aux_map contienen el cluster que se va a sustituir
    map<string, Procesador>::const_iterator it; 
    it = map_procesadores.find(id); 
    if (it == map_procesadores.end()) {
        error = 4;
        return false;
    }
    if (not it->second.vacio()) {
        error = 6;
        return false; 
    }
    BinTree<string> aux; 
    if (not sustituir_arbol(aux, id_procesadores, aux_arbol, id)) {
        error = 7; 
        return false; 
    }
    max_hueco += mem_añadida;
    map_procesadores.erase(it); //elimina la hoja del mapa que va a quedar sustituida por el arbol
    it = aux_map.begin(); 
    while (it != aux_map.end()) {
        map_procesadores.insert((*it));
        ++it; 
    } //añade los nuevos procesadores al mapa
    id_procesadores = aux;
    return true; 
    
}

void Cluster::aux_mejor_procesador(const BinTree<string>& arbol,const Proceso& p, int& prof, bool& existe_mej_proc, string& id_mej_proc, int& mej_hueco, int& mej_memdisp, int& mej_prof, int& mem_consultada) const {
    if (arbol.empty()) return; //caso base
    int memoria = p.consultar_memoria(); 
    if ((max_hueco - mem_consultada) < memoria) return; //Si el hueco maximo de todos los procesos menos los huecos consultados es menor que la memoria del proceso a añadir, se acaba la funcion

    map<string, Procesador>::const_iterator it = map_procesadores.find(arbol.value());
    mem_consultada += it->second.consultar_memoria_disp();
    int hueco = it->second.hueco_ajustado(memoria);

    ++prof; 
    aux_mejor_procesador(arbol.left(), p, prof, existe_mej_proc, id_mej_proc, mej_hueco, mej_memdisp, mej_prof, mem_consultada);
    aux_mejor_procesador(arbol.right(), p, prof, existe_mej_proc, id_mej_proc, mej_hueco, mej_memdisp, mej_prof, mem_consultada); 
    --prof;

    if (hueco != 0 and not it->second.existe_proceso(p.consultar_identificador())) {
        int memdisp = it->second.consultar_memoria_disp() - memoria;
        if (not existe_mej_proc) {
            existe_mej_proc = true; 
            id_mej_proc = arbol.value();
            mej_hueco = hueco; 
            mej_memdisp = memdisp;
            mej_prof = prof; 
        }
        else {
            if (hueco == mej_hueco) {
                if (memdisp == mej_memdisp) {
                    if (prof < mej_prof) {
                        id_mej_proc = arbol.value();
                        mej_hueco = hueco; 
                        mej_memdisp = memdisp;
                        mej_prof = prof;
                    }
                }
                else if (memdisp > mej_memdisp) {
                    id_mej_proc = arbol.value();
                    mej_hueco = hueco; 
                    mej_memdisp = memdisp; 
                    mej_prof = prof; 
                }
            }
            else if (hueco < mej_hueco) {
                id_mej_proc = arbol.value();
                mej_hueco = hueco; 
                mej_memdisp = memdisp;
                mej_prof = prof; 
            }
        }
    }
    return;         
}

bool Cluster::añadir_mejor_procesador(const Proceso& p) {
    int prof, mej_hueco, mej_memdisp, mej_prof, mem_consultada; 
    prof = mem_consultada = 0; 
    bool existe_mej_proc = false; 
    string id_mej_proc;

    aux_mejor_procesador(id_procesadores, p, prof, existe_mej_proc, id_mej_proc, mej_hueco, mej_memdisp, mej_prof, mem_consultada);

    if (not existe_mej_proc) return false; //Si el booleano pasado por referencia en la funcion recursiva es falso, quiere decir que no se ha encontrado ningun procesador donde quepa el proceso por lo tanto retorna false
    map<string, Procesador>::iterator it = map_procesadores.find(id_mej_proc);
    it->second.añadir_proceso(p);
    return true;     
}

bool Cluster::compactar_memoria_procesador(const string& id, char& error) {
    map<string, Procesador>::iterator it;
    it = map_procesadores.find(id);
    if (it == map_procesadores.end()) {
        error = 4;
        return false;
    }
    it->second.compactar_memoria_procesador();
    return true; 
}

void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = map_procesadores.begin();
    while (it != map_procesadores.end()) {
        it->second.compactar_memoria_procesador();
        ++it;
    }
}

void Cluster::leer() {
    map_procesadores.clear();
    max_hueco = 0; 
    construir(id_procesadores, map_procesadores, max_hueco); 
}

bool Cluster::imprimir_procesador(const string& id, char& error) const { 
    map<string, Procesador>::const_iterator it;
    it = map_procesadores.find(id);
    if (it == map_procesadores.end()) {
        error = 4;
        return false; 
    }
    it->second.imprimir(); 
    return true; 
}


void Cluster::imprimir() const {
    map<string, Procesador>::const_iterator it = map_procesadores.begin();
    while (it != map_procesadores.end()) {
        cout << it->first << endl; 
        it->second.imprimir(); 
        ++it;
    } 
}

void Cluster::imprimir_arbol(const BinTree<string>& arbol) {
    if (not arbol.empty()) {
        cout << '(' << arbol.value(); 
        imprimir_arbol(arbol.left());
        imprimir_arbol(arbol.right());
        cout << ')';
    }
    else cout << " ";
}

void Cluster::imprimir_estructura() const {
    imprimir_arbol(id_procesadores);
    cout << endl; 
}