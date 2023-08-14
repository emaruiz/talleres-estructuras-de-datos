#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"

void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
}

void test_definir_uno() {
	DiccString<int> d;
	d.Definir("casa", 40);
	ASSERT(d.Definido("casa"));
	ASSERT_EQ(d.Obtener("casa"), 40);
	ASSERT_EQ(d.Claves().cardinal(), 1);
}

void test_definir_uno_y_repetidos() {
	DiccString<int> d;
	d.Definir("casa", 30);
	d.Definir("casa", 50);
	d.Definir("casa", 70);
	ASSERT(d.Definido("casa"));
	ASSERT_EQ(d.Obtener("casa"), 70);
	ASSERT_EQ(d.Claves().cardinal(), 1);
}

void test_definir_varios_sin_prefijo_en_comun() {
	DiccString<int> d;
	d.Definir("ciruela", 20);
	d.Definir("manzana", 50);
	d.Definir("tomate", 80);
	
	ASSERT(d.Definido("ciruela"));
	ASSERT(d.Definido("manzana"));
	ASSERT(d.Definido("tomate"));
	ASSERT_EQ(d.Obtener("ciruela"), 20);
	ASSERT_EQ(d.Obtener("manzana"), 50);
	ASSERT_EQ(d.Obtener("tomate"), 80);
	ASSERT_EQ(d.Claves().cardinal(), 3);
}

void test_definir_varios_con_prefijo_en_comun() {
	DiccString<int> d;
	d.Definir("biologia", 30);
	d.Definir("bolsa", 50);
	d.Definir("biomedicina", 70);
	d.Definir("biologias", 90);

	ASSERT(d.Definido("biologia"));
	ASSERT(d.Definido("bolsa"));
	ASSERT(d.Definido("biomedicina"));
	ASSERT(d.Definido("biologias"));
	ASSERT_EQ(d.Obtener("biologia"), 30);
	ASSERT_EQ(d.Obtener("bolsa"), 50);
	ASSERT_EQ(d.Obtener("biomedicina"), 70);
	ASSERT_EQ(d.Obtener("biologias"), 90);
	ASSERT_EQ(d.Claves().cardinal(), 4);
}

void test_definir_varios() {
	DiccString<int> d;
	d.Definir("biomecanica", 20);
	d.Definir("biometria", 25);
	d.Definir("bioinformatica", 30);
	d.Definir("bioinsumos", 35);
	d.Definir("bio", 5);
	d.Definir("geografia", 50);
	d.Definir("anatomia", 10);

	ASSERT(d.Definido("biomecanica"));
	ASSERT(d.Definido("biometria"));
	ASSERT(d.Definido("bioinformatica"));
	ASSERT(d.Definido("bioinsumos"));
	ASSERT(d.Definido("bio"));
	ASSERT(d.Definido("geografia"));
	ASSERT(d.Definido("anatomia"));
	ASSERT_EQ(d.Obtener("biomecanica"), 20);
	ASSERT_EQ(d.Obtener("biometria"), 25);
	ASSERT_EQ(d.Obtener("bioinformatica"), 30);
	ASSERT_EQ(d.Obtener("bioinsumos"), 35);
	ASSERT_EQ(d.Obtener("bio"), 5);
	ASSERT_EQ(d.Obtener("geografia"), 50);
	ASSERT_EQ(d.Obtener("anatomia"), 10);
	ASSERT_EQ(d.Claves().cardinal(), 7);
}

void test_definir_varios_y_repetidos() {
	DiccString<int> d;
	d.Definir("hipertension", 40);
	d.Definir("hipertrofia", 50);
	d.Definir("hiperinflacion", 60);
	d.Definir("dado", 10);
	d.Definir("llave", 90);

	d.Definir("hipertension", 400);
	d.Definir("hipertension", 4000);
	d.Definir("hiperinflacion", 600);
	d.Definir("hiperinflacion", 6000);
	d.Definir("llave", 900);
	d.Definir("llave", 9000);

	ASSERT(d.Definido("hipertension"));
	ASSERT(d.Definido("hipertrofia"));
	ASSERT(d.Definido("hiperinflacion"));
	ASSERT(d.Definido("dado"));
	ASSERT(d.Definido("llave"));
	ASSERT_EQ(d.Obtener("hipertension"), 4000);
	ASSERT_EQ(d.Obtener("hipertrofia"), 50);
	ASSERT_EQ(d.Obtener("hiperinflacion"), 6000);
	ASSERT_EQ(d.Obtener("dado"), 10);
	ASSERT_EQ(d.Obtener("llave"), 9000);
	ASSERT_EQ(d.Claves().cardinal(), 5);
}

void test_definir_string_vacio() {
	DiccString<int> d;
	d.Definir("", 15);
	ASSERT(d.Definido(""));
	ASSERT_EQ(d.Obtener(""), 15);
	ASSERT_EQ(d.Claves().cardinal(), 1);
}

void test_definir_string_vacio_y_repetidos() {
	DiccString<int> d;
	d.Definir("", 15);
	d.Definir("", 25);
	d.Definir("", 35);

	ASSERT(d.Definido(""));
	ASSERT_EQ(d.Obtener(""), 35);
	ASSERT_EQ(d.Claves().cardinal(), 1);
}

void test_borrar_unica_clave() {
	DiccString<int> d;
	d.Definir("hola", 42);

 	d.Borrar("hola");
	ASSERT(!d.Definido("hola"));
	ASSERT_EQ(d.Claves().cardinal(), 0);
}
void test_borrar_una_clave_con_prefijo_en_comun() {
	DiccString<int> d;
	d.Definir("casas", 29);
	d.Definir("caserio", 26);

	d.Borrar("caserio");
	ASSERT(d.Definido("casas"));
	ASSERT(!d.Definido("caserio"));
	ASSERT_EQ(d.Claves().cardinal(), 1);
}

void test_borrar_una_clave_que_es_prefijo() {
	DiccString<int> d;
	d.Definir("cas", 40);
	d.Definir("casas", 29);
	d.Definir("caserio", 26);

	d.Borrar("cas");
	ASSERT(!d.Definido("cas"));
	ASSERT(d.Definido("casas"));
	ASSERT(d.Definido("caserio"));
	ASSERT_EQ(d.Claves().cardinal(), 2);
}

void test_borrar_claves() {
	string clave_tronco = "biologiamarina";
	string clave_prefijo = "bio";
	string otra_clave_prefijo = "biologia";
	string clave_con_prefijo_en_comun = "biografia";
	string otra_clave_con_prefijo_en_comun = "bolsa";
	string clave_sin_prefijo_en_comun = "geologia";
	DiccString<int> d;
	d.Definir(clave_tronco, 100);
	d.Definir(clave_prefijo, 50);
	d.Definir(otra_clave_prefijo, 55);
	d.Definir(clave_con_prefijo_en_comun, 70);
	d.Definir(otra_clave_con_prefijo_en_comun, 75);
	d.Definir(clave_sin_prefijo_en_comun, 200);

	d.Borrar(clave_prefijo);
	d.Borrar(otra_clave_prefijo);
	d.Borrar(clave_con_prefijo_en_comun);
	d.Borrar(otra_clave_con_prefijo_en_comun);
	d.Borrar(clave_tronco);
	d.Borrar(clave_sin_prefijo_en_comun);
	ASSERT(!d.Definido(clave_prefijo));
	ASSERT(!d.Definido(otra_clave_prefijo));
	ASSERT(!d.Definido(clave_con_prefijo_en_comun));
	ASSERT(!d.Definido(otra_clave_con_prefijo_en_comun));
	ASSERT(!d.Definido(clave_tronco));
	ASSERT(!d.Definido(clave_sin_prefijo_en_comun));
	ASSERT_EQ(d.Claves().cardinal(), 0);
}

void test_borrar_string_vacio() {
	DiccString<int> d;
	d.Definir("", 42);

 	d.Borrar("");
	ASSERT(!d.Definido(""));
	ASSERT_EQ(d.Claves().cardinal(), 0);
}

void test_borrar_string_vacio_luego_clave() {
	DiccString<int> d;
	d.Definir("", 10);
	d.Definir("hola", 20);
	
	d.Borrar("");
	d.Borrar("hola");
	ASSERT(!d.Definido(""));
	ASSERT(!d.Definido("hola"));
	ASSERT_EQ(d.Claves().cardinal(), 0);
}

void test_constructor_copia_diccionario_unica_clave() {
	DiccString<int> d;
	d.Definir("hola", 42);
	DiccString<int> copia(d);
	ASSERT(copia.Definido("hola"));
	ASSERT_EQ(copia.Obtener("hola"), 42);
	ASSERT_EQ(copia.Claves().cardinal(), 1);
}

void test_constructor_copia_diccionario_una_clave_en_comun() {
	DiccString<int> d;
	d.Definir("bioinformatica", 30);
	d.Definir("bioinsumos", 35);
	d.Definir("bio", 5);
	d.Definir("bolsa", 20);
	DiccString<int> copia(d);
	ASSERT(copia.Definido("bioinformatica"));
	ASSERT(copia.Definido("bioinsumos"));
	ASSERT(copia.Definido("bio"));
	ASSERT(copia.Definido("bolsa"));
	ASSERT_EQ(copia.Obtener("bioinformatica"), 30);
	ASSERT_EQ(copia.Obtener("bioinsumos"), 35);
	ASSERT_EQ(copia.Obtener("bio"), 5);
	ASSERT_EQ(copia.Obtener("bolsa"), 20);
	ASSERT_EQ(copia.Claves().cardinal(), 4);
}

void test_constructor_copia_diccionario_varias_claves_en_comun() {
	DiccString<int> d;
	d.Definir("c", 10);
	d.Definir("ca", 20);
	d.Definir("cas", 30);
	d.Definir("casa", 40);
	d.Definir("casas", 50);
	d.Definir("birome", 110);
	d.Definir("biomecanica", 120);
	d.Definir("biomedico", 130);
	d.Definir("biomedicina", 140);
	d.Definir("super", 210);
	d.Definir("superpoblacion", 220);
	d.Definir("superposicion", 230);
	d.Definir("superheroe", 240);
	d.Definir("superheroina", 250);

	ASSERT_EQ(d.Obtener("c"), 10);
	ASSERT_EQ(d.Obtener("ca"), 20);
	ASSERT_EQ(d.Obtener("cas"), 30);
	ASSERT_EQ(d.Obtener("casa"), 40);
	ASSERT_EQ(d.Obtener("casas"), 50);
	ASSERT_EQ(d.Obtener("birome"), 110);
	ASSERT_EQ(d.Obtener("biomecanica"), 120);
	ASSERT_EQ(d.Obtener("biomedico"), 130);
	ASSERT_EQ(d.Obtener("biomedicina"), 140);
	ASSERT_EQ(d.Obtener("super"), 210);
	ASSERT_EQ(d.Obtener("superpoblacion"), 220);
	ASSERT_EQ(d.Obtener("superposicion"), 230);
	ASSERT_EQ(d.Obtener("superheroe"), 240);
	ASSERT_EQ(d.Obtener("superheroina"), 250);
	ASSERT_EQ(d.Claves().cardinal(), 14);
}

void test_constructor_copia_diccionario_y_se_modifica() {
	DiccString<int> d;
	d.Definir("bioinformatica", 30);
	d.Definir("bioinsumos", 35);
	d.Definir("bio", 5);
	
	DiccString<int> copia(d);
	copia.Borrar("bioinformatica");
	ASSERT(!copia.Definido("bioinformatica"));
	ASSERT(copia.Definido("bioinsumos"));
	ASSERT(copia.Definido("bio"));
	ASSERT_EQ(copia.Obtener("bioinsumos"), 35);
	ASSERT_EQ(copia.Obtener("bio"), 5);
	ASSERT_EQ(copia.Claves().cardinal(), 2);
}

void test_obtener_referencia_simple_entero() {
	DiccString<int> d;
	d.Definir("hola", 42);
	d.Obtener("hola") = 52;
	ASSERT_EQ(d.Obtener("hola"), 52);
}

void test_obtener_referencia_simple_string() {
	DiccString<string> d;
	d.Definir("casa", "canstruccion");
	d.Obtener("casa")[1] = 'o';
	ASSERT_EQ(d.Obtener("casa"), "construccion");
}

void test_obtener_referencia_compleja_entero() {
	DiccString< DiccString<int> > d;
	d.Definir("submarino", DiccString<int>());
	d.Definir("subrayar", DiccString<int>());
	d.Definir("subte", DiccString<int>());

	d.Obtener("submarino").Definir("agua", 20);
	d.Obtener("submarino").Definir("pez", 30);
	d.Obtener("subte").Definir("tunel", 1000);

	ASSERT(d.Definido("submarino"));
	ASSERT(d.Obtener("submarino").Definido("agua"));
	ASSERT(d.Obtener("submarino").Definido("pez"));
	ASSERT_EQ(d.Obtener("submarino").Obtener("agua"), 20);
	ASSERT_EQ(d.Obtener("submarino").Obtener("pez"), 30);
	ASSERT_EQ(d.Obtener("submarino").Claves().cardinal(), 2);
	
	ASSERT(d.Definido("subrayar"));
	ASSERT_EQ(d.Obtener("subrayar").Claves().cardinal(), 0);

	ASSERT(d.Definido("subte"));
	ASSERT(d.Obtener("subte").Definido("tunel"));
	ASSERT_EQ(d.Obtener("subte").Obtener("tunel"), 1000);
	ASSERT_EQ(d.Obtener("subte").Claves().cardinal(), 1);

	ASSERT_EQ(d.Claves().cardinal(), 3);
}

void test_obtener_referencia_compleja_string() {
	DiccString<string> d_una_clave;
	d_una_clave.Definir("hola", "saludos");
	DiccString<string> d_claves_intermedias;
	d_claves_intermedias.Definir("casa", "palabra completa");
	d_claves_intermedias.Definir("cas", "palabra incompleta");
	d_claves_intermedias.Definir("ca", "otra palabra incompleta");
	DiccString<string> d_claves_prefijo_comun;
	d_claves_prefijo_comun.Definir("biologia", "ciencia");
	d_claves_prefijo_comun.Definir("biografia", "historia de alguien");
	d_claves_prefijo_comun.Definir("bolsa", "envoltura");

	DiccString< DiccString<string> > d;
	d.Definir("unica", d_una_clave);
	d.Definir("intermedia", d_claves_intermedias);
	d.Definir("prefijo", d_claves_prefijo_comun);

	d.Obtener("intermedia").Borrar("cas");
	d.Obtener("prefijo").Borrar("biografia");

	ASSERT(d.Definido("unica"));
	ASSERT(d.Obtener("unica").Definido("hola"));
	ASSERT_EQ(d.Obtener("unica").Obtener("hola"), "saludos");

	ASSERT(d.Definido("intermedia"));
	ASSERT(d.Obtener("intermedia").Definido("casa"));
	ASSERT(!d.Obtener("intermedia").Definido("cas"));
	ASSERT(d.Obtener("intermedia").Definido("ca"));
	ASSERT_EQ(d.Obtener("intermedia").Obtener("casa"), "palabra completa");
	ASSERT_EQ(d.Obtener("intermedia").Obtener("ca"), "otra palabra incompleta");
	ASSERT_EQ(d.Obtener("intermedia").Claves().cardinal(), 2);
	
	ASSERT(d.Definido("prefijo"));
	ASSERT(d.Obtener("prefijo").Definido("biologia"));
	ASSERT(!d.Obtener("prefijo").Definido("biografia"));
	ASSERT(d.Obtener("prefijo").Definido("bolsa"));
	ASSERT_EQ(d.Obtener("prefijo").Obtener("biologia"), "ciencia");
	ASSERT_EQ(d.Obtener("prefijo").Obtener("bolsa"), "envoltura");
	ASSERT_EQ(d.Obtener("prefijo").Claves().cardinal(), 2);

	ASSERT_EQ(d.Claves().cardinal(), 3);
}

int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_definir_uno);
	RUN_TEST(test_definir_uno_y_repetidos);
	RUN_TEST(test_definir_varios_sin_prefijo_en_comun);
	RUN_TEST(test_definir_varios_con_prefijo_en_comun);
	RUN_TEST(test_definir_varios);
	RUN_TEST(test_definir_varios_y_repetidos);
	RUN_TEST(test_definir_string_vacio);
	RUN_TEST(test_definir_string_vacio_y_repetidos);
	RUN_TEST(test_borrar_unica_clave);
	RUN_TEST(test_borrar_una_clave_con_prefijo_en_comun);
	RUN_TEST(test_borrar_una_clave_que_es_prefijo);
	RUN_TEST(test_borrar_claves);
	RUN_TEST(test_borrar_string_vacio);
	RUN_TEST(test_borrar_string_vacio_luego_clave);
	RUN_TEST(test_constructor_copia_diccionario_unica_clave);
	RUN_TEST(test_constructor_copia_diccionario_una_clave_en_comun);
	RUN_TEST(test_constructor_copia_diccionario_varias_claves_en_comun);
	RUN_TEST(test_constructor_copia_diccionario_y_se_modifica);
	RUN_TEST(test_obtener_referencia_simple_entero);
	RUN_TEST(test_obtener_referencia_simple_string);
	RUN_TEST(test_obtener_referencia_compleja_entero);
	RUN_TEST(test_obtener_referencia_compleja_string);
	return 0;
}