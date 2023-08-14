#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 * 
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();
  
  // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     * 
     * ATENCION:
     * 
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     * 
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      T elem;
      Nodo* sig;
      
      Nodo(const T& elemento ) : elem(elemento){
        sig = NULL;
      }
    };

    Nodo* tope_;
    aed2::Nat tamanio_;
};

template <typename T>
Pila<T>::Pila()
{
  tope_ = NULL;
  tamanio_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
  tamanio_ = 0;
  tope_ = NULL;
  int num = 0;
  while(tamanio_ < otra.tamanio()){
    Nodo* nodoAux = otra.tope_;
    int indice = 1;
      while(indice < otra.tamanio()-num){
        nodoAux = nodoAux->sig;
        indice++;
      }
    apilar(nodoAux->elem);
    num++;
  }
}

template <typename T>
Pila<T>::~Pila()
{
  Nodo* nodoAux = tope_;
  int indice = 1;
  while(indice <= tamanio_){
    nodoAux = nodoAux->sig;
    delete tope_;
    tope_ = nodoAux;
    indice++;
  }
  tamanio_ = 0;
}

template <typename T>
void Pila<T>::apilar(const T& elem)
{
  Nodo* nodoAApilar = new Nodo(elem);
  Nodo* nodoAux = tope_;
  tope_ = nodoAApilar;
  nodoAApilar->sig = nodoAux;
  tamanio_++;
}

template <typename T>
void Pila<T>::desapilar()
{
  Nodo* nodoAux = tope_;
  tope_ = tope_->sig;
  delete nodoAux;
  tamanio_--;
}

template <typename T>
bool Pila<T>::esVacia() const
{
  return tamanio_ == 0;
}

template <typename T>
T& Pila<T>::tope()
{
  return tope_->elem;
}

template <typename T>
const T& Pila<T>::tope() const
{
  return tope_->elem;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
  return tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra)
{
  while(tamanio_ > 0){
	  desapilar();
  }
  
  int num = 0;
  while(tamanio_ < otra.tamanio()){
    Nodo* nodoAux = otra.tope_;
    int indice = 1;
      while(indice < otra.tamanio()-num){
        nodoAux = nodoAux->sig;
        indice++;
      }
    apilar(nodoAux->elem);
    num++;
  }
  
  return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila)
{
  os << "[";
  typename Pila<T>::Nodo* nodoAux = pila.tope_;
  int indice = 1;
  while(indice <= pila.tamanio()){
    os << nodoAux->elem;
    if(indice < pila.tamanio()){
      os << ", ";
    }
    nodoAux = nodoAux->sig;
    indice++;
  }
  os << "]";
  return os;
}
