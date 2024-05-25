/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std; 

/** @class Proceso
    @brief Representa un proceso
*/
class Proceso {

private:

    /** @brief Constante identificador vacio*/
    static const int ID_VACIA = -1;

    /** @brief Identificador del proceso*/
    int identificador;

    /** @brief Memoria del proceso*/
    int memoria;
    
    /** @brief Tiempo del proceso*/
    int tiempo;

public: 

    //Constructores

     /** @brief Creadora por defecto
        
        Se ejecuta automáticamente al declarar una Proceso
        \pre <em>cierto</em>
        \post el resultado es un proceso con identificador -1, memoria 0 y tiempo 0
        \coste O(1)
    */
    Proceso();


    //Consultores

    /** @brief Consultora del identificador
        \pre <em>cierto</em>
        \post El resultado es el identificador del parámetro implícito
        \coste O(1)
    */
    int consultar_identificador() const; 

    /** @brief Consultora de la memoria
        \pre <em>cierto</em>
        \post El resultado es la memoria del parámetro implícito
        \coste O(1)
    */
    int consultar_memoria() const; 

    /** @brief Consultora del tiempo
        \pre <em>cierto</em>
        \post El resultado es el tiempo del parámetro implícito
        \coste O(1)
    */
    int consultar_tiempo() const; 

    /** @brief Avanzar tiempo
     
        \pre <em>cierto</em>
        \post Queda modificado el atributo tiempo
        \coste O(1)
    */
    bool avanzar_tiempo(const int& t);


    //Entrada/salida

    /** @brief Operación de lectura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del canal estándar de entrada en el parámetro implícito
        \coste O(1)
    */
    void leer();

    /** @brief Operación de escritura
        
        \pre <em>cierto</em>
        \post Escribe el contenido del parámetro implícito por el canal estándar de salida
        \coste O(1)
    */
    void imprimir() const; 

};
#endif
