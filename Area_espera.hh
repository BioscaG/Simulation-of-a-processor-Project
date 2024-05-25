/** @file Area_espera.hh
    @brief Especificación de la clase Area_espera
*/

#ifndef AREA_ESPERA_HH
#define AREA_ESPERA_HH

#include "Prioridad.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <map>
#endif

using namespace std; 

/** @class Area_espera
    @brief Representa el area de espera
 
*/
class Area_espera {

private:

    /** @brief Mapa de prioridades*/
    map<string, Prioridad> map_prioridades;

public:

    //Constructores

    /** @brief Creadora por defecto
        
        Se ejecuta automáticamente al declarar un Procesos_pendientes
        \pre <em>cierto</em>
        \post El resultado es una area de espera
        \coste O(1)
    */
    Area_espera(); 


    //Modificadores

    /** @brief Añade un proceso
        
        \pre El identificador es una cadena de caracteres no vacía
        \post Si la funcion retorna <em>true</em> la prioridad con identificador <em>id_prioridad</em> pasa a contener <em>proceso</em>. En caso contrario el parametro <em>error</em> contiene el error.
        \coste Olog(N)
    */
    bool alta_proceso_espera(const string& id, const Proceso& p, char& error);

    /** @brief Añade una prioridad
        
        \pre El identificador es una cadena de caracteres no vacía
        \post Si la funcion retorna <em>true</em> el  parámetro implícito pasa a contener sus prioridades originales más la prioridad con identificador <em>id_prioridad</em>. En caso contrario el parametro <em>error</em> contiene el error.
        \coste Olog(N)
    */
    bool alta_prioridad(const string& id, char& error);

    /** @brief Elimina una prioridad
        
        \pre <em>cierto</em>
        \post Si la funcion retorna <em>true</em> el parámetro implícito pasa a contener sus prioridades originales menos la prioridad con identificador <em>identificador_prioridad</em>. En caso contrario el parametro <em>error</em> contiene el error.
        \coste Olog(N)
    */
    bool baja_prioridad(const string& id, char& error);

    /** @brief Añade un número n de procesos del área de espera
        
        \pre n es un número natural
        \post Los procesadores del parametro <em>cluster</em> pasan a contener hasta un maximo de n procesos del parametro implicito. Estos n procesos enviados quedan eliminados del parametro implicito.
        \coste ONlog(N)
    */
    void enviar_procesos_cluster(Cluster& cluster, int n);


    //Lectura/escritura

    /** @brief Operación de lectura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del canal estandar de entrada en el parámetro implícito.
        \coste N
    */
    void leer();

    /** @brief Operación de escritura de una prioridad
        
        \pre <em>cierto</em>
        \post Si la funcion devuelve <em>true</em> escribe el contenido de la prioridad con identificador <em>id_prioridad</em> del parámetro implícito por el canal estandar de salida. En caso contrario el parametro <em>error</em> contiene el error.
        \coste log(N) + M
    */
    bool imprimir_prioridad(const string& id, char& error) const;

    /** @brief Operación de escritura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del parámetro implícito por el canal estandar de salida
        \coste N
    */
    void imprimir() const;
};

#endif