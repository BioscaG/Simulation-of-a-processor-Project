/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <map>
#include <set>
#endif

using namespace std; 

/** @class Procesador
    @brief Representa el procesador
 
*/
class Procesador {

private:
    
    /** @brief Indentificador del procesador*/
    string identificador;

    /** @brief Numero de memoria*/
    int mem_total;

    /** @brief Numero de memoria disponible*/
    int mem_disp;

    /** @brief Mapa de identificador y proceso*/
    map <int, Proceso> map_pos_proc;

    /** @brief Mapa de identificador y posicion inicial*/
    map <int, int> map_id_pos;

    /** @brief Mapa de tamaño y set de posiciones iniciales*/
    map <int, set <int> > map_tam_pos;

public:

    //Constructores

    /** @brief Creadora por defecto
        
        Se ejecuta automáticamente al declarar un procesador
        \pre <em>cierto</em>
        \post el resultado es un procesador con <em>identificador</em> vacio, <em>mem_total</em> 0 y <em>mem_disp</em> 0
        \coste O(1)
    */
    Procesador();


    //Consultores

    /** @brief Consultora de si el procesador esta vacio
     
        \pre <em>cierto</em>
        \post El resultado es un booleano que indica si el procesador esta vacio o no
        \coste O(1)
    */
    bool vacio() const;

    /** @brief Consultora de la existencia de un proceso
     
        \pre <em>cierto</em>
        \post El resultado es un booleano que indica si el proceso existe o no
        \coste log(N)
    */
    bool existe_proceso(const int& id) const; 

    /** @brief Consultora de la memoria disponible
     
        \pre <em>cierto</em>
        \post El resultado es un entero que indica la memoria disponible
        \coste O(1)
    */
    int consultar_memoria_disp() const;

    /** @brief Consultora del identificador
     
        \pre <em>cierto</em>
        \post El resultado es un string con el identificador del parámetro implícito
        \coste O(1)
    */
    string consultar_id() const;

    /** @brief Consultora del hueco mas ajustado
     
        \pre <em>cierto</em>
        \post El resultado es un entero que indica el hueco mas ajustado para <em>memoria</em>
        \coste log(N)
    */
    int hueco_ajustado(const int& memoria) const;


    //Modificadores

    /** @brief Añade un proceso
     
        \pre <em>cierto</em>
        \post Si la funcion retorna <em>true</em>, el resultado es el parámetro implícito con sus procesos más <em>proceso</em>
        \coste Olog(N)
    */
    bool añadir_proceso(const Proceso& p);

    /** @brief Elimina un proceso
     
        \pre <em>cierto</em>
        \post El resultado es el parámetro implícito con sus procesos menos el proceso con identificador <em>id_proceso</em>
        \coste Olog(N)
    */
    bool eliminar_proceso(const int& id, int& mem_eliminada);

    /** @brief Compactar memoria
     
        \pre <em>cierto</em>
        \post Queda compactada la memoria del parámetro implícito
        \coste N
    */
    void compactar_memoria_procesador(); 

    /** @brief Avanzar tiempo
     
        \pre <em>cierto</em>
        \post Queda modificado el atributo <em>tiempo</em> de los procesos del parámetro implícito
        \coste N
    */
    void avanzar_tiempo(const int& t, int& mem_eliminada); 


    //Lectura/escritura

    /** @brief Operación de lectura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del canal estándar de entrada en el parámetro implícito
        \coste O(1)
    */
    bool leer();

    /** @brief Operación de escritura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del parámetro implícito por el canal estándar de salida
        \coste N
    */
    void imprimir() const; 
};

#endif
