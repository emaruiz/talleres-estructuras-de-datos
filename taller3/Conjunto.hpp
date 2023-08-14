#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der; 
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;
		unsigned int cantElem;

	// funciones auxiliares

		void padrePierdeHoja(typename Conjunto<T>::Nodo* & nPadre, const T& clave);
		void padreSeConectaConSubArbolDelNodoAEliminar(typename Conjunto<T>::Nodo* & nPadre, typename Conjunto<T>::Nodo* & nElim, const T& clave);
		void buscarClave(typename Conjunto<T>::Nodo* & nPadre, typename Conjunto<T>::Nodo* & nElim, const T& clave );
		void buscarElMasGrandeDeLosMasChicos(typename Conjunto<T>::Nodo* & nPadreDeADC, typename Conjunto<T>::Nodo* & nAntecesorDeClave);
		void mostrarABB(const typename Conjunto<T>::Nodo* raizDeArbol, std::ostream& os, const T& maxDeArbol)const;

};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL), cantElem(0)
{}

template <class T>
Conjunto<T>::~Conjunto()
{ 
	while(raiz_ != 0){
		remover(raiz_->valor);
	}
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	bool estaClave = false;
	if(raiz_ != NULL){//si no es conj vacio
		Nodo* nodoActual = raiz_;
		while(nodoActual != 0 && !estaClave){
			if(nodoActual->valor == clave){
				estaClave = true;
			}else{
				if(clave < nodoActual->valor){
					nodoActual = nodoActual->izq;
				}else{
					nodoActual = nodoActual->der;
				}
			}
		}
	}
	return estaClave;
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	if(!pertenece(clave)){//si no esta la clave en conj
		Nodo* nodoAInsertar = new Nodo(clave);
		if(raiz_ == 0){//si es conj vacio
			raiz_ = nodoAInsertar;
			cantElem++;
		}else{//si no es conj vacio
			Nodo* nodoActual = raiz_;
			bool inserte = false;
			while(!inserte){
				if(clave < nodoActual->valor && nodoActual->izq == 0){
					nodoActual->izq = nodoAInsertar;
					inserte = true;
					cantElem++;
				}else{
					if(clave < nodoActual->valor && nodoActual->izq != 0){
						nodoActual = nodoActual->izq;	
					}else{
						if(!(clave < nodoActual->valor) && nodoActual->der == 0){
							nodoActual->der = nodoAInsertar;
							inserte = true;
							cantElem++;
						}else{
							if(!(clave < nodoActual->valor) && nodoActual->der != 0){
								nodoActual = nodoActual->der;
							}
						}
					}
				}
			}
		}
	}
}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	return cantElem;
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{
	if(pertenece(clave)){//si pertence, entonces hay elementos
		Nodo* nPadre = 0;
		Nodo* nElim = raiz_;
		
		buscarClave(nPadre, nElim, clave);
		
		if(nElim->izq != 0 && nElim->der != 0){/***si nElim tiene dos hijos***/
			Nodo* nPadreDeADC = nElim;
			Nodo* nAntecesorDeClave = nElim->izq;
			
			buscarElMasGrandeDeLosMasChicos(nPadreDeADC, nAntecesorDeClave);
			
			T antecesorDeClave(nAntecesorDeClave->valor);
			
			if(nAntecesorDeClave->izq == 0 && nAntecesorDeClave->der == 0){//si nAntecesorDeClave no tiene hijos
				padrePierdeHoja(nPadreDeADC, nAntecesorDeClave->valor);
				delete nAntecesorDeClave;
				cantElem--;
			}else{//si nAntecesorDeClave tiene un unico hijo
				padreSeConectaConSubArbolDelNodoAEliminar(nPadreDeADC, nAntecesorDeClave, nAntecesorDeClave->valor);
				delete nAntecesorDeClave;
				cantElem--;
			}
			
			Nodo* nodoAInsertar = new Nodo(antecesorDeClave);
			nodoAInsertar->izq = nElim->izq;
			nodoAInsertar->der = nElim->der;
			
			if(nPadre == 0){//si nPadre es 0, entonces nElim es el nodo apuntado por la raiz y hacemos que la rais apunte al nodoAInsertar
				raiz_ = nodoAInsertar;
			}else{//si nPadre es 0, entonces nElim no es el nodo apuntado por la raiz y hacemos que nPadre se conecte al nodoAInsertar
				if(clave < nPadre->valor){
					nPadre->izq = nodoAInsertar;
				}else{
					nPadre->der = nodoAInsertar;
				}
			}
			delete nElim;
			
		}else{
			if(nElim->izq != 0 || nElim->der != 0){/***si nElim tiene un hijo***/
				if(nPadre == 0){//si nPadre es 0, entonces nElim es el nodo apuntado por la raiz
					if(nElim->izq != 0){//si nElim tiene hijo izq, entonces la raiz se conecta con ese hijo
						raiz_ = nElim->izq;
					}else{//si nElim tiene hijo der, entonces la raiz se conecta con ese hijo
						raiz_ = nElim->der;
					}
				}else{//si nPadre no es 0, entonces nElim es un nodo que no es el apuntado por la raiz
					padreSeConectaConSubArbolDelNodoAEliminar(nPadre, nElim, clave);
				}
				delete nElim;
				cantElem--;
			}else{/***si nElim no tiene hijos***/
				if(nPadre == 0){
					raiz_ = 0;
				}else{
					padrePierdeHoja(nPadre, clave);
				}
				delete nElim;
				cantElem--;
			}
		}
	}
}

//auxiliares para remover
template <class T>
void Conjunto<T>::padrePierdeHoja(typename Conjunto<T>::Nodo* & nPadre, const T& clave){
	if(clave < nPadre->valor){
		nPadre->izq = 0;
	}else{
		nPadre->der = 0;
	}
}

template <class T>
void Conjunto<T>::padreSeConectaConSubArbolDelNodoAEliminar(typename Conjunto<T>::Nodo* & nPadre, typename Conjunto<T>::Nodo* & nElim, const T& clave){
	if(clave < nPadre->valor){
		if(nElim->izq != 0){
			nPadre->izq = nElim->izq;
		}else{
			nPadre->izq = nElim->der;
		}
	}else{
		if(nElim->izq != 0){
			nPadre->der = nElim->izq;
		}else{
			nPadre->der = nElim->der;
		}
	}
}

template <class T>
void Conjunto<T>::buscarClave(typename Conjunto<T>::Nodo* & nPadre, typename Conjunto<T>::Nodo* & nElim, const T& clave ){
	while(clave != nElim->valor){
		nPadre = nElim;
		if(clave < nElim->valor){
			nElim = nElim->izq;
		}else{
			nElim = nElim->der;
		}
	}
}

template <class T>
void Conjunto<T>::buscarElMasGrandeDeLosMasChicos(typename Conjunto<T>::Nodo* & nPadreDeADC, typename Conjunto<T>::Nodo* & nAntecesorDeClave){
	while(nAntecesorDeClave->der != 0){
		nPadreDeADC = nAntecesorDeClave;
		nAntecesorDeClave = nAntecesorDeClave->der;
	}
}
//fin de auxiliares para remover


//requiere que haya elementos en conj
template <class T>
const T&  Conjunto<T>::minimo() const
{
	Nodo* nodoActual = raiz_;
	while(nodoActual->izq != 0){
		nodoActual = nodoActual->izq;
	}
	return nodoActual->valor;
}

template <class T>
const T&  Conjunto<T>::maximo() const
{
	Nodo* nodoActual = raiz_;
	while(nodoActual->der != 0){
		nodoActual = nodoActual->der;
	}
	return nodoActual->valor;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	os << "{";
	if(raiz_ != 0){
		mostrarABB(raiz_, os, maximo());
	}
	os << "}";
}

//auxiliar de mostrar
template <class T>
void Conjunto<T>::mostrarABB(const typename Conjunto<T>::Nodo* raizDeArbol, std::ostream& os, const T& maxDeArbol)const{
	if(raizDeArbol != 0){
		if(raizDeArbol->valor == maxDeArbol){
			mostrarABB(raizDeArbol->izq, os, maxDeArbol);
			os << raizDeArbol->valor;
		}else{
			mostrarABB(raizDeArbol->izq, os, maxDeArbol);
			os << raizDeArbol->valor << ", ";
			mostrarABB(raizDeArbol->der, os, maxDeArbol);
		}
	}
}
//fin de auxiliar de mostrar

#endif // CONJUNTO_HPP_
