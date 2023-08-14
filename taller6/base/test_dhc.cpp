#include <iostream>
#include <fstream>
#include "DiccHashCerrado.hpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_claves_dicc_vacio() {
	DiccHashCerrado<int> dh;
	ASSERT_EQ(dh.CantClaves(), 0);
}

void test_Definir_uno() {
	DiccHashCerrado<int> dhi;
	dhi.Definir("juanca", 40);
	ASSERT(dhi.Definido("juanca"));
	ASSERT_EQ(dhi.Significado("juanca"), 40);
	ASSERT_EQ(dhi.CantClaves(), 1);
}

void test_Definir_uno_y_repetidos() {
	DiccHashCerrado<int> dhi;
	dhi.Definir("juanca", 40);
	dhi.Definir("juanca", 50);
	dhi.Definir("juanca", 60);
	ASSERT(dhi.Definido("juanca"));
	ASSERT_EQ(dhi.Significado("juanca"), 60);
	ASSERT_EQ(dhi.CantClaves(), 1);
}

void test_Definir_varios() {
	DiccHashCerrado<int> dhi;
	dhi.Definir("juanca", 20);
	dhi.Definir("fer", 40);
	dhi.Definir("nico", 60);
	ASSERT(dhi.Definido("juanca"));
	ASSERT(dhi.Definido("fer"));
	ASSERT(dhi.Definido("nico"));
	ASSERT_EQ(dhi.Significado("juanca"), 20);
	ASSERT_EQ(dhi.Significado("fer"), 40);
	ASSERT_EQ(dhi.Significado("nico"), 60);
	ASSERT_EQ(dhi.CantClaves(), 3);
}

void test_Definir_varios_y_repetidos() {
	DiccHashCerrado<int> dhi;
	dhi.Definir("juanca", 20);
	dhi.Definir("fer", 40);
	dhi.Definir("nico", 60);

	dhi.Definir("juanca", 200);
	dhi.Definir("fer", 400);
	dhi.Definir("nico", 600);
	ASSERT(dhi.Definido("juanca"));
	ASSERT(dhi.Definido("fer"));
	ASSERT(dhi.Definido("nico"));
	ASSERT_EQ(dhi.Significado("juanca"), 200);
	ASSERT_EQ(dhi.Significado("fer"), 400);
	ASSERT_EQ(dhi.Significado("nico"), 600);
	ASSERT_EQ(dhi.CantClaves(), 3);
}

void test_Definir_String_vacio() {
	DiccHashCerrado<int> dhi;
	dhi.Definir("", 10);
	ASSERT(dhi.Definido(""));
	ASSERT_EQ(dhi.Significado(""), 10);
	ASSERT_EQ(dhi.CantClaves(), 1);
}


void test_Borrar_uno() {
	DiccHashCerrado<string> dhs;
	dhs.Definir("casa", "hogar");
	dhs.Definir("hola", "saludo");

	dhs.Borrar("casa");
	ASSERT(!dhs.Definido("casa"));
	ASSERT(dhs.Definido("hola"));
	ASSERT_EQ(dhs.Significado("hola"), "saludo");
	ASSERT_EQ(dhs.CantClaves(), 1);
}

void test_Borrar_varios() {
	DiccHashCerrado<string> dhs;
	dhs.Definir("auto", "transporte");
	dhs.Definir("perro", "animal");
	dhs.Definir("manzana", "fruta");
	dhs.Definir("taza", "utenzillo de cocina");
	dhs.Definir("ruido", "sonido no agradable");

	dhs.Borrar("auto");
	dhs.Borrar("manzana");
	dhs.Borrar("ruido");
	ASSERT(!dhs.Definido("auto"));
	ASSERT(!dhs.Definido("manzana"));
	ASSERT(!dhs.Definido("ruido"));
	ASSERT(dhs.Definido("perro"));
	ASSERT(dhs.Definido("taza"));
	ASSERT_EQ(dhs.Significado("perro"), "animal");
	ASSERT_EQ(dhs.Significado("taza"), "utenzillo de cocina");
	ASSERT_EQ(dhs.CantClaves(), 2);
}

void test_modificar_referencia_Significado() {
	DiccHashCerrado<string> dhs;
	dhs.Definir("juanca", "alguien");
	dhs.Significado("juanca")[0] = 'o';
	ASSERT_EQ(dhs.Significado("juanca"), "olguien");
}

void test_claves() {
	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();
	ASSERT(dhi.CantClaves() == 0);

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);
	claves = dhi.Claves();
	ASSERT(dhi.CantClaves() == 2);
	
	dhi.Definir("moncho",56);
	claves = dhi.Claves();
	ASSERT(dhi.CantClaves() == 2);

	dhi.Borrar("juanca");
	claves = dhi.Claves();
	ASSERT(dhi.CantClaves() == 1);

	dhi.Borrar("moncho");
	claves = dhi.Claves();
	ASSERT(dhi.CantClaves() == 0);
}

void test_redimensionado() {
	DiccHashCerrado<int> dhi;
	std::string archnom = "../data/uniforme.txt";
	
	int val = 0;
	string str;
	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str) && archin.good()){
		dhi.Definir(str, val);
		val++;
		if (val == 100) break;
	}
	archin.close();
	ASSERT_EQ(dhi.CantClaves(), 100);
	ASSERT(dhi.factorCarga() <= 0.75);
}

void test_colisiones_uniforme() {
	DiccHashCerrado<int> dh;
	std::string archnom = "../data/uniforme.txt";
	
	int val = 0;
	string str;
	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin, str) && archin.good()){
		dh.Definir(str, val);
		val++;
		if (val == 50) break;
	}
	archin.close();
	ASSERT_EQ(dh.CantClaves(), val);
	ASSERT(dh.colisiones() < 20);
}

void test_colisiones_gauss() {
	DiccHashCerrado<int> dh;
	std::string archnom = "../data/gauss.txt";
	
	int val = 0;
	string str;
	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin, str) && archin.good()){
		dh.Definir(str, val);
		val++;
		if (val == 50) break;
	}
	archin.close();
	ASSERT_EQ(dh.CantClaves(), val);
	ASSERT(dh.colisiones() < 30);
}

void test_colisiones_libretas() {
	DiccHashCerrado<int> dh;
	std::string archnom = "../data/libretas.txt";
	
	int val = 0;
	string str;
	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin, str) && archin.good()){
		dh.Definir(str, val);
		val++;
		if (val == 50) break;
	}
	archin.close();
	ASSERT_EQ(dh.CantClaves(), val);
	ASSERT(dh.colisiones() < 26);
}

int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_Definir_uno);
	RUN_TEST(test_Definir_uno_y_repetidos);
	RUN_TEST(test_Definir_varios);
	RUN_TEST(test_Definir_varios_y_repetidos);
	RUN_TEST(test_Definir_String_vacio);
	RUN_TEST(test_Borrar_uno);
	RUN_TEST(test_Borrar_varios);
	RUN_TEST(test_modificar_referencia_Significado);
	RUN_TEST(test_claves);
	RUN_TEST(test_redimensionado);
	RUN_TEST(test_colisiones_uniforme);
	RUN_TEST(test_colisiones_gauss);
	RUN_TEST(test_colisiones_libretas);
	return 0;
}
