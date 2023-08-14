#ifndef DICCHASHCERRADO_H_
#define DICCHASHCERRADO_H_

#include "Lista.h"

#ifndef TAM_TABLA_INI
	#define TAM_TABLA_INI 100
#endif
#ifndef UMBRAL_FC
	#define UMBRAL_FC	  0.75
#endif


namespace aed2 {

template<class S>
class DiccHashCerrado {
public:

	typedef String K;

	DiccHashCerrado();
	~DiccHashCerrado();

	bool 	 Definido(const K& clave) const;
	void 	 Definir(const K& clave, const S& significado);
	S& 		 Significado(const K& clave);
	void 	 Borrar(const K& clave);
	Nat 	 CantClaves() const;

	// solo para test!!
	Lista<K> Claves() const;
	float    factorCarga() const;
	Nat      colisiones() const;

private:

	struct TElem{
			K 	 clave;
			S 	 signif;

			TElem(const K& c, const S& v) : clave(c), signif(v) {}
		};


	Lista<TElem>*   _tabla;
	Nat             _cant_elems;
    Nat             _tam;

	Nat fn_hash (const String& str) const {
		Nat hash = 0;
		int indice = 0;
		while(indice < str.length()){
			hash = hash + charToNat(str[indice]);
			if(hash % 2 == 0){
				hash = hash + 2 * charToNat(str[indice]);
			}
			indice++;
		}
		
		if(longitudDe(hash) >= 3){
			int hasta = longitudDe(hash) / 2;
			indice = 1;
			while(indice < hasta){
				hash = hash / 10;
				indice++;
			}
		}
		
		hash = hash % _tam;
		return hash;
	}

	//aux de fn_hash
	Nat longitudDe(Nat num) const{
		int i = 1;
		while(potDeDiez(i) <= num){
			i++;
		}
		return i;
	}
	
	int potDeDiez(int i) const{
		int indice = 1;
		int res = 1;
		while(indice <= i){
			res = res * 10;
			indice++;
		}
		return res;
	}
	
	Nat charToNat(char c) const {
			return (Nat)(c);
	}
	//aux de fn_hash

	void redimensionarTabla(){
		int nuevoTam = _tam*2;
		Lista<TElem>* nuevaTabla = new Lista<TElem>[nuevoTam];
		
		int indice = 0;
		while(indice < _tam){
			typename Lista<TElem>::Iterador it(_tabla[indice].CrearIt());
			while(it.HaySiguiente()){
				nuevaTabla[fn_hash(it.Siguiente().clave)].AgregarAtras(it.Siguiente());
				it.Avanzar();
			}
			indice++;
		}
		
		Lista<TElem>* viejaTabla = _tabla;
		_tabla = nuevaTabla;
		delete [] viejaTabla;
		_tam = nuevoTam;
	}

};

/********************************************************************************
 * Implementacion
 ********************************************************************************/

template<class S>
DiccHashCerrado<S>::DiccHashCerrado() 
: _cant_elems(0), _tam(TAM_TABLA_INI) 
{
    _tabla = new Lista<TElem>[TAM_TABLA_INI];
}

template<class S>
DiccHashCerrado<S>::~DiccHashCerrado() {
    delete [] _tabla;
}

template<class S>
bool DiccHashCerrado<S>::Definido(const K& clave) const {
	typename Lista<TElem>::const_Iterador itListaQuizasEstaClave(_tabla[fn_hash(clave)].CrearIt());
	bool estaDef = false;
	while(itListaQuizasEstaClave.HaySiguiente() && !estaDef){
		if(itListaQuizasEstaClave.Siguiente().clave == clave){
			estaDef = true;
		}
		itListaQuizasEstaClave.Avanzar();
	}
	return estaDef;
}

template<class S>
void DiccHashCerrado<S>::Definir(const K& clave, const S& significado) {
	if(factorCarga() > UMBRAL_FC)
		redimensionarTabla();

	typename Lista<TElem>::Iterador it(_tabla[fn_hash(clave)].CrearIt());
	bool loEncontre = false;
	while(it.HaySiguiente() && !loEncontre){
		if(it.Siguiente().clave == clave){
			it.EliminarSiguiente();
			TElem redefinicion(clave, significado);
			it.AgregarComoAnterior(redefinicion);
			loEncontre = true;
		}
		if(!loEncontre){
			it.Avanzar();
		}
	}
	
	if(!loEncontre){
		TElem nuevaClaveSig(clave, significado);
		_tabla[fn_hash(clave)].AgregarAtras(nuevaClaveSig);
		_cant_elems++;
	}
}

template<class S>
S& DiccHashCerrado<S>::Significado(const K& clave) {
	typename Lista<TElem>::Iterador it(_tabla[fn_hash(clave)].CrearIt());
	bool loEncontre = false;
	while(it.HaySiguiente() && !loEncontre){
		if(it.Siguiente().clave == clave){
			loEncontre = true;
		}
		if(!loEncontre){
			it.Avanzar();
		}
	}
	return it.Siguiente().signif;
}

template<class S>
void DiccHashCerrado<S>::Borrar(const K& clave) {
	typename Lista<TElem>::Iterador it(_tabla[fn_hash(clave)].CrearIt());
	bool estaBorrado = false;
	while(it.HaySiguiente() && !estaBorrado){
		if(it.Siguiente().clave == clave){
			it.EliminarSiguiente();
			estaBorrado = true;
			_cant_elems--;
		}
		if(!estaBorrado){
			it.Avanzar();
		}
	}
}

template<class S>
Nat DiccHashCerrado<S>::CantClaves() const {
	return _cant_elems;
}

// solo para test!!
template<class S>
Lista<typename DiccHashCerrado<S>::K> DiccHashCerrado<S>::Claves() const {
	Lista<K> ret;
	typename Lista<TElem>::const_Iterador it;

	for(Nat i=0; i < _tam; i++){
        for(it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
            ret.AgregarAtras(it.Siguiente().clave);
	}

	return ret;
}

// solo para test!!
template<class S>
float DiccHashCerrado<S>::factorCarga() const {
	return float(_cant_elems) / _tam;
}

// solo para test!!
template<class S>
Nat DiccHashCerrado<S>::colisiones() const {
	Nat ret = 0;
	for(Nat i = 0; i < _tam; i++){
		if (_tabla[i].Longitud() > 1)
			ret = ret + _tabla[i].Longitud() - 1;
	}

	return ret;
}

} /* namespace aed2 */

#endif /* DICCHASHCERRADO_H_ */
