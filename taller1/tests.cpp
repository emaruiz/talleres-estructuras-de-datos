#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p;
  ASSERT(p.esVacia());
  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar_un_elemento() {
  ElemPila unico_elem;
  unico_elem.id = 1;
  unico_elem.nombre = "unico elemento";
  unico_elem.descripcion = "soy el unico";
  Pila p;
  p.apilar(unico_elem);
  
  ASSERT(!p.esVacia());
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope().id, unico_elem.id);
}

void test_apilar_varios_elementos() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p;

  p.apilar(elem_fondo);
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope().id, elem_fondo.id);

  p.apilar(elem_medio);
  ASSERT_EQ(p.tamanio(), 2);
  ASSERT_EQ(p.tope().id, elem_medio.id);

  p.apilar(elem_tope);
  ASSERT_EQ(p.tamanio(), 3);
  ASSERT_EQ(p.tope().id, elem_tope.id);
}

void test_desapilar_un_elemento() {
  ElemPila unico_elem;
  unico_elem.id = 1;
  unico_elem.nombre = "unico elemento";
  unico_elem.descripcion = "soy el unico";
  Pila p;
  p.apilar(unico_elem);
  p.desapilar();

  ASSERT(p.esVacia());
  ASSERT_EQ(p.tamanio(), 0);
}

void test_desapilar_consecutivamente_varios_elementos() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p;

  p.apilar(elem_fondo);
  p.apilar(elem_medio);
  p.apilar(elem_tope);

  p.desapilar();
  ASSERT_EQ(p.tamanio(), 2);
  ASSERT_EQ(p.tope().id, elem_medio.id);

  p.desapilar();
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope().id, elem_fondo.id);

  p.desapilar();
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());
}

void test_desapilar_alternadamente_varios_elementos() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p;

  p.apilar(elem_fondo);
  p.desapilar();
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());

  p.apilar(elem_medio);
  p.desapilar();
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());

  p.apilar(elem_tope);
  p.desapilar();
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());
}

void test_modificar_referencia_tope() {
  ElemPila unico_elem;
  unico_elem.id = 1;
  unico_elem.nombre = "unico elemento";
  unico_elem.descripcion = "soy el unico";
  Pila p;

  p.apilar(unico_elem);
  p.tope().id = 5;
  ASSERT_EQ(p.tope().id, 5);
}

void test_asignacion_pila_con_elementos_a_pila_vacia() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p_con_elementos;
  p_con_elementos.apilar(elem_fondo);
  p_con_elementos.apilar(elem_medio);
  p_con_elementos.apilar(elem_tope);
  Pila nueva_p;

  nueva_p = p_con_elementos;
  ASSERT_EQ(nueva_p.tamanio(), 3);
  ASSERT_EQ(nueva_p.tope().id, elem_tope.id);
  
  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 2);
  ASSERT_EQ(nueva_p.tope().id, elem_medio.id);
  
  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 1);
  ASSERT_EQ(nueva_p.tope().id, elem_fondo.id);

  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 0);
}

void test_asignacion_pila_vacia_a_pila_con_elementos() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p_vacia;
  Pila nueva_p;
  nueva_p.apilar(elem_fondo);
  nueva_p.apilar(elem_medio);
  nueva_p.apilar(elem_tope);
  
  nueva_p = p_vacia;
  ASSERT_EQ(nueva_p.tamanio(), 0);
}

void test_asignacion_pila_con_elementos_a_otra_pila_con_elementos() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  ElemPila elem_piso;
  elem_piso.id = 10;
  elem_piso.nombre = "elem piso";
  elem_piso.descripcion = "soy elem piso";
  ElemPila elem_techo;
  elem_techo.id = 20;
  elem_techo.nombre = "elem techo";
  elem_techo.descripcion = "soy elem techo";
  Pila p_con_elementos;
  p_con_elementos.apilar(elem_fondo);
  p_con_elementos.apilar(elem_medio);
  p_con_elementos.apilar(elem_tope);
  Pila nueva_p;
  nueva_p.apilar(elem_piso);
  nueva_p.apilar(elem_techo);

  nueva_p = p_con_elementos;
  ASSERT_EQ(nueva_p.tamanio(), 3);
  ASSERT_EQ(nueva_p.tope().id, elem_tope.id);
  
  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 2);
  ASSERT_EQ(nueva_p.tope().id, elem_medio.id);
  
  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 1);
  ASSERT_EQ(nueva_p.tope().id, elem_fondo.id);

  nueva_p.desapilar();
  ASSERT_EQ(nueva_p.tamanio(), 0);
}

void test_pila_se_muestra_con_formato_apropiado() {
  ElemPila elem_fondo;
  elem_fondo.id = 1;
  elem_fondo.nombre = "elem fondo";
  elem_fondo.descripcion = "soy elem fondo";
  ElemPila elem_medio;
  elem_medio.id = 2;
  elem_medio.nombre = "elem medio";
  elem_medio.descripcion = "soy elem medio";
  ElemPila elem_tope;
  elem_tope.id = 3;
  elem_tope.nombre = "elem tope";
  elem_tope.descripcion = "soy elem tope";
  Pila p;
  p.apilar(elem_fondo);
  p.apilar(elem_medio);
  p.apilar(elem_tope);

  ostringstream oss_p;
  oss_p << p;
  string s_p = oss_p.str();

  ostringstream oss_esperado;
  oss_esperado << "[" << elem_fondo << ", " << elem_medio << ", " << elem_tope << "]";
  string s_esperado = oss_esperado.str();

  ASSERT_EQ(s_p, s_esperado);
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar_un_elemento);
  RUN_TEST(test_apilar_varios_elementos);
  RUN_TEST(test_desapilar_un_elemento);
  RUN_TEST(test_desapilar_consecutivamente_varios_elementos);
  RUN_TEST(test_desapilar_alternadamente_varios_elementos);
  RUN_TEST(test_modificar_referencia_tope);
  RUN_TEST(test_asignacion_pila_con_elementos_a_pila_vacia);
  RUN_TEST(test_asignacion_pila_vacia_a_pila_con_elementos);
  RUN_TEST(test_asignacion_pila_con_elementos_a_otra_pila_con_elementos);
  RUN_TEST(test_pila_se_muestra_con_formato_apropiado);
  return 0;
}
