#include "Procesador.hh"

Procesador::Procesador()
{
    identificador = " ";
    mem_total = 0;
    mem_disp = 0;
}

bool Procesador::leer()
{
    cin >> identificador;
    if (identificador == "*") return false;
    cin >> mem_total;
    mem_disp = mem_total;
    map_tam_pos[mem_total].insert(0); //inserta el hueco inicial con posicion 0 y tamaño igual a la memoria total del procesador
    return true;
}

bool Procesador::vacio() const
{
    return (map_id_pos.empty());
}

bool Procesador::existe_proceso(const int& id) const
{
    map<int, int>::const_iterator it;
    it = map_id_pos.find(id);
    return (it != map_id_pos.end());
}

bool Procesador::añadir_proceso(const Proceso &p)
{
    if (map_tam_pos.empty()) return false;
    int mem = p.consultar_memoria();
    if (mem_disp < mem) return false;

    map<int, set<int>>::iterator it = map_tam_pos.lower_bound(mem);
    if (it == map_tam_pos.end()) return false;

    int id = p.consultar_identificador();
    int pos = *it->second.begin();

    map_id_pos.insert(map_id_pos.end(), make_pair(id, pos)); //añade el proceso en el mapa de identificador posicion
    map_pos_proc.insert(map_pos_proc.end(), make_pair(pos, p)); //añade el proceso en el mapa de posicion proceso
    it->second.erase(it->second.begin()); //elimina el hueco ocupado por el proceso del mapa tamaño posicion

    int tam = it->first - mem; //saca el tamaño resultante al añadir el proceso
    if (tam > 0) map_tam_pos[tam].insert(pos + mem); //si el tamaño es mayor que cero lo añade
    if (it->second.empty()) map_tam_pos.erase(it); //si el set de tamaño esta vacio elimina esa clave del mapa

    mem_disp -= mem;

    return true;
}

bool Procesador::eliminar_proceso(const int& id, int& mem_eliminada)
{
    map<int, int>::const_iterator it_id_pos = map_id_pos.find(id);
    if (it_id_pos == map_id_pos.end()) return false; // si el proceso no existe devuelve falso y se acaba la función

    map<int, Proceso>::iterator it_pos_proc = map_pos_proc.find(it_id_pos->second);
    map_id_pos.erase(it_id_pos); // elimina el proceso del mapa identificación-posición

    int pos = it_pos_proc->first;
    int hueco = it_pos_proc->second.consultar_memoria(); // hueco = memoria proceso
    it_pos_proc = map_pos_proc.erase(it_pos_proc); // elimina proceso del mapa de posición-proceso y el iterador apunta al siguiente elemento del mapa
    mem_disp += hueco;
    int next_hueco = mem_total - (pos + hueco); // next_hueco = espacio entre posición final proceso y posición final memoria

    if (it_pos_proc != map_pos_proc.end()) next_hueco = it_pos_proc->first - (pos + hueco); // si existe proceso siguiente: next_hueco = diferencia entre posición inicial del siguiente proceso y posición final del proceso

    if (next_hueco > 0) { // si existe hueco después del proceso
        map<int, set<int>>::iterator it_tam_pos = map_tam_pos.find(next_hueco);
        it_tam_pos->second.erase(pos + hueco); // elimina la posición encontrada de espacio disponible del mapa tamaño-set(posición)
        if (it_tam_pos->second.empty())
            map_tam_pos.erase(it_tam_pos); // si el set queda vacío se elimina
        hueco += next_hueco;
    }

    int ant_hueco = pos; // se supone que no hay más procesos antes del proceso inicial entonces el hueco es desde la posición 0 hasta la posición inicial - 1
    int pos_ant_hueco = 0;

    if (it_pos_proc != map_pos_proc.begin()) { // la suposición de que no hay más procesos delante es falsa
        --it_pos_proc; // el iterador apunta al proceso anterior
        pos_ant_hueco = it_pos_proc->first + it_pos_proc->second.consultar_memoria(); // pos_ant_hueco = suma de la posición inicial del proceso anterior más su memoria para así conseguir la posción final
        ant_hueco = pos - pos_ant_hueco;
    }

    if (ant_hueco > 0) { // si existe hueco
        map<int, set<int>>::iterator it_tam_pos = map_tam_pos.find(ant_hueco);
        it_tam_pos->second.erase(pos_ant_hueco); // elimina la posición encontrada de espacio disponible del mapa tamaño-set(posición)
        if (it_tam_pos->second.empty()) map_tam_pos.erase(it_tam_pos); // si el set queda vacío se elimina
        pos = pos_ant_hueco; // la posición del hueco cambia ya que hay más espacio delante del proceso inicial
        hueco += ant_hueco;
    }

    map_tam_pos[hueco].insert(pos); //si no existe una clave con tamaño igual a hueco se crea uno nuevo. Se inserta la posción en el set del tamaño

    mem_eliminada += hueco; //para la memoria disponible cluster

    return true;
}

void Procesador::avanzar_tiempo(const int &t, int& mem_eliminada)
{
    map<int, Proceso>::iterator it_pos_proc = map_pos_proc.begin();
    while (it_pos_proc != map_pos_proc.end())
    {
        if (it_pos_proc->second.avanzar_tiempo(t))
        {
            int id = it_pos_proc->second.consultar_identificador();
            ++it_pos_proc;
            eliminar_proceso(id, mem_eliminada);
        }
        else ++it_pos_proc;
    }
}

int Procesador::hueco_ajustado(const int& memoria) const {
    if (map_tam_pos.empty()) return 0; 
    map<int, set<int>>::const_iterator it = map_tam_pos.lower_bound(memoria);
    if (it == map_tam_pos.end()) return 0; 
    return it->first;
}


void Procesador::compactar_memoria_procesador() {
    map<int, Proceso>::const_iterator it = map_pos_proc.begin();
    int pos = 0;  
    while (it != map_pos_proc.end()) { 
        Proceso aux = it->second;
        if (it->first != pos) { 
            it = map_pos_proc.erase(it);
            it = map_pos_proc.insert(it, make_pair(pos, aux));
            map_id_pos[aux.consultar_identificador()] = pos;
            pos = pos + aux.consultar_memoria(); //se consigue la siguiente posicion que debe tener el siguiente proceso
        }
        else pos = pos + aux.consultar_memoria(); //se consigue la siguiente posicion que debe tener el siguiente proceso
        ++it;
    }
    if (mem_disp > 0) {
        map_tam_pos.clear();
        map_tam_pos[mem_disp].insert(pos); //se añade un tamaño correspondiente a la memoria total disponible del procesador ya que la memoria esta compactada
    }
}


int Procesador::consultar_memoria_disp() const {
    return mem_disp;
}

string Procesador::consultar_id() const
{
    return identificador;
}

void Procesador::imprimir() const
{
    map<int, Proceso>::const_iterator it = map_pos_proc.begin();
    while (it != map_pos_proc.end())
    {
        cout << it->first << ' ';
        it->second.imprimir();
        ++it;
    }
}