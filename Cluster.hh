/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <string>
#endif

using namespace std; 

/** @class Cluster
    @brief Representa el cluster
 
*/
class Cluster {

private:

    /** @brief Arbol de identificadores de procesador*/
    BinTree<string> id_procesadores;

    /** @brief Mapa con clave identificador de procesador y resultado procesador con ese identificador*/
    map<string, Procesador> map_procesadores; 

    /** @brief Hueco total existente entre todos los procesadores*/
    int max_hueco;

    /** @brief Operacion de lectura sobre <em>map_procesadores</em> y <em>id_procesadores</em>
        
        \pre <em>cierto</em>
        \post <em>id_procesadores</em> y <em>map_procesadores</em> pasan a contener los datos del canal de entrada. Y <em>mem_añadida</em> pasa a contener la memoria nueva total añadida.
        \coste N
    */
    static void construir(BinTree<string>& id_procesadores, map<string,Procesador>& map_procesadores, int& mem_añadida);

    /** @brief Operacion de escritura
        
        \pre <em>cierto</em>
        \post Escribe en el canal estandar de salida los datos de <em>arbol</em>
        \coste N
    */
    static void imprimir_arbol(const BinTree<string>& arbol);

    /** @brief Operacion auxiliar de <em>modificar_cluster</em>
        
        \pre <em>cierto</em>
        \post El parametro <em>aux</em> pasa a contener el nuevo arbol donde <em>arbol_sustituir</em> queda sustituido en la hoja de <em>arbol</em> con identificador <em>id</em>. Si <em>id</em> no es una hoja, la funcion devuelve <em>false</em>, en el caso contrario devuelve <em>true</em>
        \coste N + M
    */
    static bool sustituir_arbol(BinTree<string>& aux, const BinTree<string>& arbol, const BinTree<string>& arbol_sustituir, const string& id);

    /** @brief Consultora de mejor procesador
        
        \pre <em>cierto</em>
        \post El parametro <em>existe_mej_proc</em> contiene un booleano que indica si se ha encontrado un procesador apto para añadir <em>p</em> proceso. Si <em>existe_mej_proc</em> es <em>true</em> entonces, <em>id_mej_proc</em> contiene el string del mejor procesador, <em>mej_hueco</em> contiene un entero indicando el hueco mas ajustado del mejor procesador para el proceso, <em>mej_memdisp</em> contiene un entero que indica la memoria disponible que quedaria al añadir el proceso al mejor procesador, <em>mej_prof</em> contiene la profundidad del mejor procesador.
        \coste Olog(N)
    */
    void aux_mejor_procesador(const BinTree<string>& arbol,const Proceso& p, int& prof, bool& existe_mej_proc, string& id_mej_proc, int& mej_hueco, int& mej_memdisp, int& mej_prof, int& mem_consultada) const;

public:

    //Constructores

    /** @brief Creadora por defecto
        
        Se ejecuta automáticamente al declarar un Cluster
        \pre <em>cierto</em>
        \post El resultado es un Cluster vacio
        \coste constante
    */
    Cluster(); 


    //Modificadores

    /** @brief Añade un proceso
        
        \pre El identificador es una cadena de caracteres no vacía
        \post Si la funcion devuelve <em>true</em>, el procesador del cluster con identificador <em>id</em> pasa a contener <em>proceso</em>. De lo contrario el parametro <em>error</em> contiene el error de la funcion.
        \coste Olog(N) + Olog(M)
    */
    bool alta_proceso_procesador(const string& id, const Proceso& p, char& error);

    /** @brief Elimina un proceso
        
        \pre El identificador es una cadena de caracteres no vacía
        \post Si la funcion devuelve <em>true</em>, el procesador del cluster con identificador </em>id_procesador</em> pasa a no contener el proceso con identificador <em>id_proceso</em>. De lo contrario el parametro <em>error</em> contiene el error de la funcion.
        \coste Olog(N) + Olog(m)
    */
    bool baja_proceso_procesador(const string& id_procesador, const int& id_proceso, char& error);

    /** @brief Modificador del cluster
        
        \pre El identificador es una cadena de caracteres no vacía
        \post Si la funcion devuelve <em>true</em>, el cluster aumenta. La hoja con identificador <em>id</em> queda sustituida por el arbol leido por el canal estandar de entrada. De lo contrario el parametro <em>error</em> contiene el error de la funcion.
        \coste N + M
    */
    bool modificar_cluster(const string& id, char& error);

    /** @brief Modifica el tiempo
        
        \pre t es un número natural
        \post Queda modificado el atributo tiempo de los procesos de los procesadores.
        \coste Nlog(M)
    */
    void avanzar_tiempo(const int& t);

    /** @brief Compactar memoria procesador
        
        \pre <em>cierto</em>
        \post Si la funcion devuelve <em>true</em> el procesador con identificador <em>id_procesador</em> pasa a tener la memoria compactada. De lo contraro el parametro <em>error</em> contiene el error de la funcion.
        \coste log(N) + Olog(M)
    */
    bool compactar_memoria_procesador(const string& id, char& error);

    /** @brief Compactar memoria
        
        \pre <em>cierto</em>
        \post Los procesadores pasan a tener la memoria compactada.
        \coste ONlog(M)
    */
    void compactar_memoria_cluster(); 


    //Consultores

    /** @brief Añadir proceso en mejor procesador
        \pre <em>cierto</em>
        \post Añade el proceso <em>p</em> en el procesador con mejores caracteristicas para el proceso <em>p</em>.
        \coste Olog(N)
    */
    bool añadir_mejor_procesador(const Proceso& p);

    /** @brief Operacion de lectura
        \pre <em>cierto</em>
        \post Se han asignado a los atributos los valores del canal de entrada
        \coste N
    */
    void leer();

    /** @brief Operacion de escritura
        
        \pre <em>cierto</em>
        \post Si la funcion devuelve <em>true</em> se han escrido por el canal estandar de salida los atributos del procesador. De lo contrario el parametro <em>error</em> contiene el error de la funcion.
        \coste log(N) + M
    */
    bool imprimir_procesador(const string& id, char& error) const; 

    /** @brief Operación de escritura 
        
        \pre <em>cierto</em>
        \post Se han escrido por el canal estandar de salida los procesadores
        \coste N
    */
    void imprimir() const; 

    /** @brief Operación de escritura 
        
        \pre <em>cierto</em>
        \post Escribe la estructura de los procesadores
        \coste N
    */
    void imprimir_estructura() const;
};

#endif

