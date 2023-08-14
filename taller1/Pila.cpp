
#include "Pila.h"

// Constructor y destructor
Pila::Pila(){
	prim = 0;
	tam = 0;
}

Pila::~Pila(){
	Nodo* nodoAux = prim;
	int indice = 1;
	while(indice <= tam){
		if(indice < tam){
			nodoAux = nodoAux->sig;
		}else{
			nodoAux = 0;
		}
		delete prim;
		prim = nodoAux;
		indice++;
	}
	tam = 0;
}

// Generadores
void Pila::apilar(ElemPila& elem){
	//creo un nodo cuyo sig no apunte a nada y elem sea el valor del que pasan por paremetro
	Nodo* nodoAApilar = new Nodo;
	(*nodoAApilar).sig = 0;
	(*nodoAApilar).elem = elem;
	
	if(prim == 0){//en caso de que tam sea 0, prim apunta al nodoAApilar
		prim = nodoAApilar;
	}else{//en caso de que tam sea >=1, recorro la pila hasta llegar al ultimo nodo y el puntero sig de ese ult nodo que apunte al nodoAApilar 
		Nodo* nodoAux = prim;
		while(nodoAux->sig != 0){
			nodoAux = nodoAux->sig;
		}
		nodoAux->sig = nodoAApilar;
	}
	tam++;
}

// Observadores básicos
bool Pila::esVacia(){
	return tam == 0;
}

ElemPila& Pila::tope(){
	//la pila no es vacia
	Nodo* nodoAux = prim;
	while(nodoAux->sig != 0){//recorro la pila hasta llegar al ultimo nodo
		nodoAux = nodoAux->sig;
	}
	return nodoAux->elem;
}

void Pila::desapilar(){
	//la pila no es vacia
	if(tam == 1){//si hay uno solo nodo, libero la memoria de ese nodo y luego prim apunta a la nada
		delete prim;
		prim = 0;
	}else{//si hay mas de un nodo, recorro la pila hata llegar al anterior del ultimo, libero la memoria del nodo al que apunta sig del anterior del ultimo y asi apuntara a la nada
		Nodo* nodoAux = prim;
		int indice = 1;
		while(indice < tam-1){
			nodoAux = nodoAux->sig;
			indice++;
		}
		delete nodoAux->sig;
		nodoAux->sig = 0;
	}
	tam--;
}

// Otras operaciones
Nat Pila::tamanio() const{
	return tam;
}

// Asignacion
Pila& Pila::operator=(const Pila & aCopiar){
	while(tam > 0){
		desapilar();
	}

	Nodo* nodoAux = aCopiar.prim;
	int indice = 1;
	while(indice <= aCopiar.tamanio()){
		ElemPila elemAApilar = nodoAux->elem;
		apilar(elemAApilar);
		nodoAux = nodoAux->sig;
		indice++;
	}
	return *this;
}

// Muestra la lista en un ostream
// formato de salida: [e_0, e_1, e_2, ...]
// donde e_i es el resultado del "mostrar" del ElemPila i
void Pila::mostrar(ostream& os) const{
	os << "[";
	Nodo* nodoAux = prim;
	int indice = 1;
	while(indice <= tam){//mando al os lo que necesito, luego voy al siguiente nodo y por ultimo avanza el indice
		os << nodoAux->elem;
		if(indice < tam){//solo cuando no estoy en el ultimo nodo imprimo la ','  y muevo nodoAux
			os << ", ";
			nodoAux = nodoAux->sig; 
		}
		indice++;
	}
	os << "]";
}
