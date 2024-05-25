/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <string>
#include <set>
#endif

using namespace std; 

/** @class Prioridad
    @brief Representa la prioridad

    Puede contener procesos con el mismo identificador de prioridad que la cola
 
*/
class Prioridad {

private: 

    /** @brief Lista de procesos*/
    list<Proceso> lista_procesos;

    /** @brief Set de procesos*/
    set<int> set_procesos;

    /** @brief Numero de procesos aceptados*/
    int aceptados; 

    /** @brief Numero de procesos rechazados*/
    int rechazados; 

public:

    //Constructores

    /** @brief Creadora por defecto
     
        \pre <em>cierto</em>
        \post El resultado es una Prioridad sin identificador
        \coste O(1)
    */
    Prioridad(); 


    //Modificadores

    /** @brief Añade un proceso a la Prioridad
        
        \pre <em>cierto</em>
        \post Si la funcion retorna true el parámetro implícito pasa a contener sus procesos originales más el Proceso <em>p</em>.
        \coste log(N)
    */
    bool añadir_proceso(const Proceso& p);

    /** @brief Enviar procesos al cluster
        
        \pre <em>cierto</em>
        \post Los procesadores del parametro <em>cluster</em> pasan a contener hasta un maximo de n procesos del parametro implicito. Estos n procesos enviados quedan eliminados del parametro implicito.
        \coste ONlog(N)
    */
    void enviar_procesos_cluster(int& n, Cluster& cluster);


    //Consultores

    /** @brief Consultora de si existen procesos
        
        \pre <em>cierto</em>
        \post Devuelve un booleano <em>true</em> si la prioridad no contiene ningun proceso. De lo contrario devuelve <em>false</em>.
        \coste O(1)
    */
    bool vacio() const;


    //Salida

    /** @brief Operación de escritura 
        
        \pre <em>cierto</em>
        \post Escribe el contenido del parámetro implícito por el canal estandar de salida
        \coste N
    */
    void imprimir() const;  
};


#endif