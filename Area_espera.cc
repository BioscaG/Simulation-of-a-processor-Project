#include "Area_espera.hh"

Area_espera::Area_espera() {}

void Area_espera::leer() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) {
        string id; 
        cin >> id; 
        map_prioridades[id]; 
    }
}

bool Area_espera::alta_prioridad(const string& id, char& error) {
    map<string, Prioridad>::const_iterator it;
    it = map_prioridades.find(id);
    if (it != map_prioridades.end()) {
        error = 0;
        return false; 
    }
    Prioridad p; 
    map_prioridades.insert(it, make_pair(id, p));
    return true; 
}

bool Area_espera::baja_prioridad(const string& id, char& error) {
    map<string, Prioridad>::const_iterator it;
    it = map_prioridades.find(id);
    if (it == map_prioridades.end()) {
        error = 1;
        return false; 
    }
    if (not it->second.vacio()) {
        error = 2;
        return false; 
    }
    map_prioridades.erase(it);
    return true; 
}

bool Area_espera::alta_proceso_espera(const string& id, const Proceso& p, char& error) { 
    map<string, Prioridad>::iterator it;
    it = map_prioridades.find(id);
    if (it == map_prioridades.end()) {
        error = 1;
        return false; 
    }
    if (not it->second.añadir_proceso(p)) {
        error = 3;
        return false; 
    }
    return true; 
}

void Area_espera::enviar_procesos_cluster(Cluster& cluster, int n) {
    map<string, Prioridad>::iterator it = map_prioridades.begin(); 
    while (n > 0 and it != map_prioridades.end()) {
        it->second.enviar_procesos_cluster(n, cluster);
        ++it; 
    }
}

bool Area_espera::imprimir_prioridad(const string& id, char& error) const {
    map<string, Prioridad>::const_iterator it;
    it = map_prioridades.find(id);
    if (it == map_prioridades.end()) {
        error = 1; 
        return false; 
    }
    it->second.imprimir(); 
    return true; 
}

void Area_espera::imprimir() const {
    map<string, Prioridad>::const_iterator it = map_prioridades.begin(); 
    while (it != map_prioridades.end()) {
        cout << it->first << endl; 
        it->second.imprimir();
        ++it; 
    }
}
