#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

template<typename T>
std::string to_s(const T& m) {
 	std::ostringstream os;
	os << m;
	return os.str();
}

void test_vacia() {
	Conjunto<int> c;
	ASSERT_EQ(c.cardinal(), 0);
}

void test_insertar_uno() {
	Conjunto<int> c;
	c.insertar(42);
	ASSERT(c.pertenece(42));
	ASSERT_EQ(c.cardinal(), 1);
}

void test_insertar_uno_y_repetidos() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(42);
	c.insertar(42);
	c.insertar(42);
	ASSERT(c.pertenece(42));
	ASSERT_EQ(c.cardinal(), 1);
}

void test_insertar_varios_desbalanceado_der() {
	Conjunto<int> c;
	c.insertar(1);
	c.insertar(5);
	c.insertar(10);
	c.insertar(3);
	ASSERT(c.pertenece(1));
	ASSERT(c.pertenece(5));
	ASSERT(c.pertenece(10));
	ASSERT(c.pertenece(3));
	ASSERT_EQ(c.cardinal(), 4);
}

void test_insertar_varios_desbalanceado_izq() {
	Conjunto<int> c;
	c.insertar(10);
	c.insertar(5);
	c.insertar(1);
	c.insertar(7);
	ASSERT(c.pertenece(1));
	ASSERT(c.pertenece(5));
	ASSERT(c.pertenece(10));
	ASSERT(c.pertenece(7));
	ASSERT_EQ(c.cardinal(), 4);
}

void test_insertar_varios_y_repetidos() {
	Conjunto<int> c;
	c.insertar(20);
	c.insertar(10);
	c.insertar(5);
	c.insertar(15);
	c.insertar(30);
	c.insertar(25);
	c.insertar(35);

	c.insertar(10);
	c.insertar(30);
	c.insertar(5);
	c.insertar(35);
	ASSERT(c.pertenece(20));
	ASSERT(c.pertenece(10));
	ASSERT(c.pertenece(5));
	ASSERT(c.pertenece(15));
	ASSERT(c.pertenece(30));
	ASSERT(c.pertenece(25));
	ASSERT(c.pertenece(35));
	ASSERT_EQ(c.cardinal(), 7);
}

void test_remover_elemento_hoja() {
 	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);

	c.remover(-460);
	bool pertenencia;
	pertenencia = c.pertenece(42) && c.pertenece(44) 
				&& c.pertenece(104) && c.pertenece(450)
				&& c.pertenece(-46) && !c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );
	ASSERT_EQ(c.cardinal(), 7);
}

void test_remover_elemento_interno_con_un_hijo() {
	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);

	c.remover(104);
	bool pertenencia;
	pertenencia = c.pertenece(42) && c.pertenece(44)
				&& !c.pertenece(104) && c.pertenece(450)
				&& c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );
	ASSERT_EQ(c.cardinal(), 7);
}

void test_remover_elemento_interno_con_dos_hijos() {
	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);

	c.remover(44);
	bool pertenencia;
	pertenencia = c.pertenece(42) && !c.pertenece(44)
				&& c.pertenece(104) && c.pertenece(450)
				&& c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );
	ASSERT_EQ(c.cardinal(), 7);
}

void test_remover_elementos() {
	Conjunto<int> c;
	c.insertar(50);
	c.insertar(10);
	c.insertar(90);
	c.insertar(5);
	c.insertar(40);
	c.insertar(80);
	c.insertar(95);
	c.insertar(20);
	c.insertar(45);
	c.insertar(60);
	c.insertar(85);
	c.insertar(15);
	c.insertar(30);
	c.insertar(75);
	c.insertar(25);
	c.insertar(35);
	c.insertar(70);

	int elemento_con_dos_hijos = 40;
	int otro_elemento_con_dos_hijos = 35; 
	c.remover(elemento_con_dos_hijos);
	c.remover(otro_elemento_con_dos_hijos);

	int elemento_hoja = 85;
	int elemento_con_hijo = 60;
	int otro_elemento_con_hijo = 75;
	int otro_elemento_hoja = 70;
	c.remover(elemento_hoja);
	c.remover(elemento_con_hijo);
	c.remover(otro_elemento_con_hijo);
	c.remover(otro_elemento_hoja);

	bool pertenencia;
	pertenencia = c.pertenece(50) && c.pertenece(10)
				&& c.pertenece(90) && c.pertenece(5)
				&& !c.pertenece(elemento_con_dos_hijos)
				&& c.pertenece(80) && c.pertenece(95)
				&& c.pertenece(20) && c.pertenece(45)
				&& !c.pertenece(elemento_con_hijo)
				&& !c.pertenece(elemento_hoja)
				&& c.pertenece(15) && c.pertenece(30)
				&& !c.pertenece(otro_elemento_con_hijo)
				&& c.pertenece(25)
				&& !c.pertenece(otro_elemento_con_dos_hijos)
				&& !c.pertenece(otro_elemento_hoja);
 	ASSERT( pertenencia );
	ASSERT_EQ(c.cardinal(), 11);
}

void test_remover_mismo_elemento_varias_veces() {
	Conjunto<int> c;
	c.insertar(20);
	c.insertar(10);
	c.insertar(15);
	c.insertar(30);

	c.remover(20);
	c.remover(20);
	c.remover(20);

	ASSERT(c.pertenece(10));
	ASSERT(c.pertenece(15));
	ASSERT(c.pertenece(30));
	ASSERT(!c.pertenece(20));
	ASSERT(c.cardinal());
}

void test_remover_mismos_elementos_varias_veces() {
	Conjunto<int> c;
	c.insertar(20);
	c.insertar(10);
	c.insertar(15);
	c.insertar(30);
	c.insertar(5);

	int elemento_con_dos_hijos = 10;
	int elemento_con_hijo = 5;
	int elemento_hoja = 30;
	c.remover(elemento_hoja);
	c.remover(elemento_con_dos_hijos);
	c.remover(elemento_con_hijo);

	c.remover(elemento_hoja);
	c.remover(elemento_con_dos_hijos);
	c.remover(elemento_con_hijo);

	ASSERT(c.pertenece(20));
	ASSERT(c.pertenece(15));
	ASSERT(!c.pertenece(elemento_hoja));
	ASSERT(!c.pertenece(elemento_con_dos_hijos));
	ASSERT(!c.pertenece(elemento_con_hijo));
	ASSERT_EQ(c.cardinal(), 2);
}

void test_maximo_en_conjunto_unico_elemento() {
	Conjunto<int> c;
	c.insertar(10);
 	ASSERT_EQ(c.maximo(), 10);
}

void test_maximo_en_conjunto_varios_elementos_a_izq() {
	Conjunto<int> c;
	c.insertar(30);
	c.insertar(15);
	c.insertar(20);
	c.insertar(10);
	c.insertar(12);
	c.insertar(5);
	ASSERT_EQ(c.maximo(), 30);
}

void test_maximo_en_conjunto_varios_elementos_a_der() {
	Conjunto<int> c;
	c.insertar(5);
	c.insertar(12);
	c.insertar(10);
	c.insertar(20);
	c.insertar(15);
	c.insertar(30);
	ASSERT_EQ(c.maximo(), 30);
}

void test_minimo_en_conjunto_unico_elemento() {
	Conjunto<int> c;
	c.insertar(10);
 	ASSERT_EQ(c.minimo(), 10);
}

void test_minimo_en_conjunto_varios_elementos_a_izq() {
	Conjunto<int> c;
	c.insertar(30);
	c.insertar(15);
	c.insertar(20);
	c.insertar(10);
	c.insertar(12);
	c.insertar(5);
	ASSERT_EQ(c.minimo(), 5);
}

void test_minimo_en_conjunto_varios_elementos_a_der() {
	Conjunto<int> c;
	c.insertar(5);
	c.insertar(12);
	c.insertar(10);
	c.insertar(20);
	c.insertar(15);
	c.insertar(30);
	ASSERT_EQ(c.minimo(), 5);
}

void test_conjunto_desbalanceado_se_muestra_con_formato_apropiado() {
	Conjunto<int> c;
	c.insertar(10);
	c.insertar(5);
	c.insertar(1);
	c.insertar(7);
	ASSERT_EQ(to_s(c), "{1, 5, 7, 10}");
}

void test_conjunto_completo_se_muestra_con_formato_apropiado() {
	Conjunto<int> c;
	c.insertar(20);
	c.insertar(10);
	c.insertar(30);
	c.insertar(5);
	c.insertar(15);
	c.insertar(25);
	c.insertar(35);
	ASSERT_EQ(to_s(c), "{5, 10, 15, 20, 25, 30, 35}");
}

void test_conjunto_grande_y_no_completo_se_muestra_con_formato_apropiado() {
	Conjunto<int> c;
	c.insertar(20);
	c.insertar(10);
	c.insertar(30);
	c.insertar(5);
	c.insertar(15);
	c.insertar(25);
	c.insertar(35);
	c.insertar(7);
	c.insertar(13);
	c.insertar(23);
	c.insertar(37);
	ASSERT_EQ(to_s(c), "{5, 7, 10, 13, 15, 20, 23, 25, 30, 35, 37}");
}

void test_insertar_otro_tipo() {
	Conjunto<string> c;
	c.insertar("hola");
	c.insertar("arbol");
	c.insertar("manzana");
	c.insertar("perro");

	ASSERT(c.pertenece("hola"));
	ASSERT(c.pertenece("arbol"));
	ASSERT(c.pertenece("manzana"));
	ASSERT(c.pertenece("perro"));
	ASSERT_EQ(c.cardinal(), 4);
}

void test_remover_otro_tipo() {
	Conjunto<string> c;
	c.insertar("diente");
	c.insertar("bicho");
	c.insertar("elefante");
	c.insertar("arbol");
	c.insertar("casa");
	c.insertar("foca");

	string elemento_hoja = "foca";
	string elemento_con_hijo = "elefante";
	string elemento_con_dos_hijos = "bicho";
	c.remover(elemento_con_hijo);
	c.remover(elemento_hoja);
	c.remover(elemento_con_dos_hijos);

	bool pertenencia;
	pertenencia = c.pertenece("diente") 
				&& c.pertenece("arbol")
				&& c.pertenece("casa") 
				&& !c.pertenece(elemento_hoja)
				&& !c.pertenece(elemento_con_hijo) 
				&& !c.pertenece(elemento_con_dos_hijos);
 	ASSERT( pertenencia );
	ASSERT_EQ(c.cardinal(), 3);
}

void test_minimo_otro_tipo() {
	Conjunto<string> c;
	c.insertar("diente");
	c.insertar("bicho");
	c.insertar("foca");
	c.insertar("arbol");
	c.insertar("casa");
	c.insertar("elefante");
	c.insertar("grulla");

	ASSERT_EQ(c.minimo(), "arbol");
}

void test_maximo_otro_tipo() {
	Conjunto<string> c;
	c.insertar("diente");
	c.insertar("bicho");
	c.insertar("foca");
	c.insertar("arbol");
	c.insertar("casa");
	c.insertar("elefante");
	c.insertar("grulla");

	ASSERT_EQ(c.maximo(), "grulla");
}

void test_mostrar_otro_tipo() {
	Conjunto<string> c;
	c.insertar("diente");
	c.insertar("bicho");
	c.insertar("foca");
	c.insertar("arbol");
	c.insertar("casa");
	c.insertar("elefante");
	c.insertar("grulla");

	ASSERT_EQ(to_s(c), "{arbol, bicho, casa, diente, elefante, foca, grulla}");
}

int main() {
	RUN_TEST(test_vacia);
	RUN_TEST(test_insertar_uno);
	RUN_TEST(test_insertar_uno_y_repetidos);
	RUN_TEST(test_insertar_varios_desbalanceado_der);
	RUN_TEST(test_insertar_varios_desbalanceado_izq);
	RUN_TEST(test_insertar_varios_y_repetidos);
	RUN_TEST(test_remover_elemento_hoja);
	RUN_TEST(test_remover_elemento_interno_con_un_hijo);
	RUN_TEST(test_remover_elemento_interno_con_dos_hijos);
	RUN_TEST(test_remover_elementos);
	RUN_TEST(test_remover_mismo_elemento_varias_veces);
	RUN_TEST(test_remover_mismos_elementos_varias_veces);
	RUN_TEST(test_maximo_en_conjunto_unico_elemento);
	RUN_TEST(test_maximo_en_conjunto_varios_elementos_a_izq);
	RUN_TEST(test_maximo_en_conjunto_varios_elementos_a_der);
	RUN_TEST(test_minimo_en_conjunto_unico_elemento);
	RUN_TEST(test_minimo_en_conjunto_varios_elementos_a_izq);
	RUN_TEST(test_minimo_en_conjunto_varios_elementos_a_der);
	RUN_TEST(test_conjunto_desbalanceado_se_muestra_con_formato_apropiado);
	RUN_TEST(test_conjunto_completo_se_muestra_con_formato_apropiado);
	RUN_TEST(test_conjunto_grande_y_no_completo_se_muestra_con_formato_apropiado);
	RUN_TEST(test_insertar_otro_tipo);
	RUN_TEST(test_remover_otro_tipo);
	RUN_TEST(test_minimo_otro_tipo);
	RUN_TEST(test_maximo_otro_tipo);
	RUN_TEST(test_mostrar_otro_tipo);
	return 0;
}
