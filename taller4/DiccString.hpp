#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
	public:
		/**
		CONSTRUCTOR
		* Construye un diccionario vacio.
		**/
		DiccString();

		/**
		CONSTRUCTOR POR COPIA
		* Construye un diccionario por copia.
		**/
		DiccString(const DiccString<T>&);

		/**
		DESTRUCTOR
		**/
		~DiccString();

		/**
		DEFINIR
		* Recibe una clave con su significado de tipo T y la define.
		* Si ya estaba definida, la reescribe.
		**/
		void Definir(const string& clave, const T& significado);

		/**
		DEFINIDO?
		* Devuelve un bool, que es true si la clave pasada está definida en
		* el diccionario.
		**/
		bool Definido(const string& clave) const;

		/**
		OBTENER
		* Dada una clave, devuelve su significado.
		* PRE: La clave está definida.
		--PRODUCE ALIASING--
		-- Versión modificable y no modificable
		**/
		const T& Obtener(const string& clave) const;
		T& Obtener(const string& clave);

		/**
		OBTENER
		* Dada una clave, la borra del diccionario junto a su significado.
		* PRE: La clave está definida.
		--PRODUCE ALIASING--
		**/
		void Borrar(const string& clave);

		/**
		CLAVES
		* Devuelve las claves del diccionario.
		--NO PRODUCE ALIASING--
		**/
		const Conj<string>& Claves() const;

	private:

		struct Nodo{
			Nodo** siguientes;
			T* definicion;
			Nodo(){
				siguientes = new Nodo*[256];
				for (int i = 0; i < 256; i++){
					siguientes[i] = NULL;
				}
				definicion = NULL;
			}
			~Nodo(){
				delete definicion;
				delete [] siguientes;
			}
		};

		Nodo* raiz;
		Conj<string> claves;
		
		// funciones auxiliares
		void buscarClave(Nodo* & nodoActual, const string& clave);
		bool esNodoInterno(Nodo& nodoActual);
		void moverse(Nodo* & nodoActual, Nodo* & nodoHijo, const string& clave, const int indice);
		bool hayRamificacion(Nodo& nodoActual);
};

template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}

template <typename T>
DiccString<T>::DiccString(const DiccString& d) : claves(){
	this->raiz = NULL;
    Conj<string> miConj(d.claves);
    while(miConj.cardinal() != 0){
		std::string m = miConj.minimo();
		T s(d.Obtener(m));
		Definir(m, s);
		miConj.remover(miConj.minimo());
	}
}

template <typename T>
DiccString<T>::~DiccString(){
    while(claves.cardinal() != 0){
		Borrar(claves.minimo());
	}
}

template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    if(raiz == NULL){
		raiz = new Nodo();
	}
	
	Nodo* nodoActual = raiz;
	int indice = 0;
	while(indice < clave.length()){
		if(nodoActual->siguientes[int(clave[indice])] == NULL){
			nodoActual->siguientes[int(clave[indice])] = new Nodo();
		}
		nodoActual = nodoActual->siguientes[int(clave[indice])];
		indice++;
	}
	
	T* psignificado = new T(significado);
	if(nodoActual->definicion == NULL){
		nodoActual->definicion = psignificado;
	}else{
		delete nodoActual->definicion;
		nodoActual->definicion = psignificado;
	}
	
	claves.insertar(clave);
}

template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    bool estaDef = false;
    if(raiz != NULL){
		Nodo* nodoActual = raiz;
		int indice = 0;
		while(indice < clave.length() && nodoActual != 0){
			nodoActual = nodoActual->siguientes[int(clave[indice])];
			indice++;
		}
		if(nodoActual != NULL){
			if(nodoActual->definicion != NULL){
				estaDef = true;
			}
		}
	}
	return estaDef;
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave){
    Nodo* nodoActual = raiz;
    int indice = 0;
    while(indice < clave.length()){
		nodoActual = nodoActual->siguientes[int(clave[indice])];
		indice++;
	}
	return *(nodoActual->definicion);
}

template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const{
    Nodo* nodoActual = raiz;
    int indice = 0;
    while(indice < clave.length()){
		nodoActual = nodoActual->siguientes[int(clave[indice])];
		indice++;
	}
	return *(nodoActual->definicion);
}

template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}

template <typename T>
void DiccString<T>::Borrar(const string& clave){
    Nodo* nodoActual = raiz;
    buscarClave(nodoActual, clave);
    
    if(esNodoInterno(*nodoActual)){
		delete nodoActual->definicion;
		nodoActual->definicion = NULL;
	}else{
		delete nodoActual->definicion;
		nodoActual->definicion = NULL;
		int indice = 1;
		bool debeFrenar = false;
		while(!debeFrenar && indice <= clave.length()){
			nodoActual = raiz;
			Nodo* nodoHijo = nodoActual->siguientes[int(clave[0])];
			moverse(nodoActual, nodoHijo, clave, indice);
			delete nodoHijo;
			nodoActual->siguientes[int(clave[clave.length()-indice])] = NULL;
			if(nodoActual->definicion != NULL || hayRamificacion(*nodoActual)){
				debeFrenar = true;
			}
			indice++;
		}
		if(claves.cardinal() == 1){
			delete raiz;
			raiz = NULL;
		}
	}
	claves.remover(clave);
}

//auxiliares para borrar
template <typename T>
void DiccString<T>::buscarClave(Nodo* & nodoActual, const string& clave){
	int indice = 0;
	while(indice < clave.length()){
		nodoActual = nodoActual->siguientes[int(clave[indice])];
		indice++;
	}
}

template <typename T>
bool DiccString<T>::esNodoInterno(Nodo& nodoActual){
	bool esNI = false;
	int indice = 0;
	while(indice < 256 && !esNI){
		esNI = nodoActual.siguientes[indice] != NULL;
		indice++;
	}
	return esNI;
}

template <typename T>
void DiccString<T>::moverse(Nodo* & nodoActual, Nodo* & nodoHijo, const string& clave, const int indice){
	int indice2 = 0;
	while(indice2 < clave.length()-indice){
		nodoActual = nodoHijo;
		nodoHijo = nodoHijo->siguientes[int(clave[indice2+1])];
		indice2++;
	}
}

template <typename T>
bool DiccString<T>::hayRamificacion(Nodo& nodoActual){
	return esNodoInterno(nodoActual);
}
//finAuxiliares para borrar
#endif
