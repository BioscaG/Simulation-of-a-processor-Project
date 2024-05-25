/**
 * @mainpage Simulación del rendimiento de procesadores interconectados
*/

/** @file program.cc

    @brief Programa principal para el ejercicio <em>Simulación del rendimiento
de procesadores interconectados</em>
*/

#include "Area_espera.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;


void imprimir_error(const char& error) {
    if (error == 0) cout << "error: ya existe prioridad" << endl;
    else if (error == 1) cout << "error: no existe prioridad" << endl;
    else if (error == 2) cout << "error: prioridad con procesos" << endl;
    else if (error == 3) cout << "error: ya existe proceso" << endl;
    else if (error == 4) cout << "error: no existe procesador" << endl;
    else if (error == 5) cout << "error: no cabe proceso" << endl;
    else if (error == 6) cout << "error: procesador con procesos" << endl;
    else if (error == 7) cout << "error: procesador con auxiliares" << endl; 
    else if (error == 8) cout << "error: no existe proceso" << endl;
}

/** @brief Programa principal para el ejercicio <em>Simulación del rendimiento
de procesadores interconectados</em>.
*/
int main() {
    Cluster cluster;
    cluster.leer(); 
    Area_espera area_espera;
    area_espera.leer(); 
    string comando; 
    cin >> comando; 
    while (comando != "fin") {
        if (comando == "configurar_cluster" or comando == "cc") {
            cout << '#' << comando << endl; 
            cluster.leer(); 
        }
        else if (comando == "modificar_cluster" or comando == "mc") {
            string id; 
            cin >> id; 
            cout << '#' << comando << ' ' << id << endl; 
            char error; 
            if (not cluster.modificar_cluster(id, error)) imprimir_error(error);
        }
        else if (comando == "alta_prioridad" or comando == "ap") { 
            string id;
            cin >> id; 
            cout << '#' << comando << ' ' << id << endl;  
            char error; 
            if (not area_espera.alta_prioridad(id, error)) imprimir_error(error);
        }
        else if (comando == "baja_prioridad" or comando == "bp") { 
            string id; 
            cin >> id; 
            cout << '#' << comando << ' ' << id << endl;  
            char error; 
            if (not area_espera.baja_prioridad(id, error)) imprimir_error(error);  
        }
        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string id; 
            cin >> id;
            Proceso p; 
            p.leer(); 
            cout << '#' << comando << ' ' << id << ' ' << p.consultar_identificador() << endl;
            char error;  
            if (not area_espera.alta_proceso_espera(id, p, error)) imprimir_error(error);
        }
        else if (comando == "alta_proceso_procesador" or comando == "app") { 
                string id; 
                cin >> id; 
                Proceso p; 
                p.leer(); 
                cout << '#' << comando << ' ' << id << ' ' << p.consultar_identificador() << endl;  
                char error; 
            if (not cluster.alta_proceso_procesador(id, p, error)) imprimir_error(error);
        }
        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
                string id_procesador; 
                int id_proceso;  
                cin >> id_procesador >> id_proceso;
                cout << '#' << comando << ' ' << id_procesador << ' ' << id_proceso << endl;  
                char error; 
            if (not cluster.baja_proceso_procesador(id_procesador, id_proceso, error)) imprimir_error(error);
        }
        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            cout << '#' << comando << ' ' << n << endl;  
            area_espera.enviar_procesos_cluster(cluster, n);
        }
        else if (comando == "avanzar_tiempo" or comando == "at") { 
            int t; 
            cin >> t; 
            cout << '#' << comando << ' ' << t << endl;  
            cluster.avanzar_tiempo(t);
        }
        
        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id; 
            cin >> id; 
            cout << '#' << comando << ' ' << id << endl;  
            char error; 
            if (not area_espera.imprimir_prioridad(id, error)) imprimir_error(error); 
        }
        else if (comando == "imprimir_area_espera" or comando == "iae") {
            cout << '#' << comando << endl;  
            area_espera.imprimir();
        }
        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id; 
            cin >> id; 
            cout << '#' << comando << ' ' << id << endl;  
            char error; 
            if (not cluster.imprimir_procesador(id, error)) imprimir_error(error);
        }
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << '#' << comando << endl;  
            cluster.imprimir(); 
        }
        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << '#' << comando << endl;  
            cluster.imprimir_estructura();
        }
        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string id;
            cin >> id;
            cout << '#' << comando << ' ' << id << endl;  
            char error; 
            if (not cluster.compactar_memoria_procesador(id, error)) imprimir_error(error);
        }
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cout << '#' << comando << endl;  
            cluster.compactar_memoria_cluster(); 
        }
       cin >> comando; 
    }
}
