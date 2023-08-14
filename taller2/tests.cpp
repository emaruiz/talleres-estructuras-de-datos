#include "Pila.h"
#include "mini_test.h"
#include "TiposBasicos.h"

// para compilar:
//   $ g++ -g tests.cpp -o tests
// para ejecutar con valgrind:
//   $ valgrind --leak-check=full -v ./tests

// ========================================================================== //

template<typename T>
std::string to_s(const T& m) {
 	std::ostringstream os;
	os << m;
	return os.str();
}

// ========================================================================== //

/**
 * Esto es una clase sin operador asignación. Sirve para testear
 * que estén utilizando el constructor por copia al asignar los elementos
 * de la colección.
 */
class Punto
{
  public:

    Punto(aed2::Nat x, aed2::Nat y)
      : x_(x), y_(y)
    {}

    Punto(const Punto& otro)
      : x_(otro.x_), y_(otro.y_)
    {}

    friend std::ostream& operator << (std::ostream& os, const Punto& punto);

  private:

    aed2::Nat x_, y_;

    Punto& operator = (const Punto&);
};

std::ostream& operator << (std::ostream& os, const Punto& punto)
{
  return os << "(" << punto.x_ << "," << punto.y_ << ")";
}

// ========================================================================== //

void test_vacia()
{
  Pila<aed2::Nat> p;
  ASSERT(p.esVacia());
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(to_s(p), "[]");
}

void test_apilar_uno()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT(!p.esVacia());
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(to_s(p), "[1]");
}

void test_apilar_varios()
{
  Pila<Punto> p;
  
  int indice = 1;
  while(indice <= 5){
    Punto puntoAux(0, indice);
    p.apilar(puntoAux);
    indice++;
  }
  
  ASSERT_EQ(p.tamanio(), 5);
  ASSERT_EQ(to_s(p), "[(0,5), (0,4), (0,3), (0,2), (0,1)]");
}

void test_modificar_referencia_tope()
{
  Pila<aed2::Nat> p;
  
  p.apilar(80);
  p.apilar(120);
  p.apilar(50);
  p.apilar(17);
  
  p.tope() = 20;
  
  ASSERT_EQ(p.tamanio(), 4);
  ASSERT_EQ(p.tope(), 20);
  ASSERT_EQ(to_s(p), "[20, 50, 120, 80]");
}

void test_desapilar_uno()
{
  Pila<aed2::Nat> p;
  
  aed2::Nat indice = 5;
  while(indice > 0){
    p.apilar(indice);
    indice--;
  }
  
  p.desapilar();
  
  ASSERT_EQ(p.tamanio(), 4);
  ASSERT_EQ(to_s(p), "[2, 3, 4, 5]");
}

void test_desapilar_varios()
{
  Pila<aed2::Nat> p;
  
  aed2::Nat indice = 5;
  while(indice > 0){
    p.apilar(indice);
    indice--;
  }
  
  while(indice < 5){
    p.desapilar();
    indice++;
  }

  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(to_s(p), "[]");
}

void test_constructor_copia_una_pila()
{
  Pila<Punto> p1;
  
  Punto MiPunto(1, 0);
  p1.apilar(MiPunto);
  
  Punto MiPunto2(17, 9);
  p1.apilar(MiPunto2);
  
  Pila<Punto> p2(p1);
  
  ASSERT_EQ(p2.tamanio(), 2);
  ASSERT_EQ(to_s(p2), "[(17,9), (1,0)]");
}

void test_constructor_copia_una_pila_y_se_modifica() 
{
  Pila<Punto> p1;
  
  Punto MiPunto(1, 0);
  p1.apilar(MiPunto);
  
  Punto MiPunto2(17, 9);
  p1.apilar(MiPunto2);
  
  Pila<Punto> p2(p1);
  p2.desapilar();
  
  ASSERT_EQ(p2.tamanio(), 1);
  ASSERT_EQ(to_s(p2), "[(1,0)]");
}

void test_asignacion_de_pila_con_elementos_a_pila_vacia()
{
  Pila<aed2::Nat> p1;
  
  p1.apilar(80);
  p1.apilar(90);
  p1.apilar(12);
  p1.apilar(5);
  
  Pila<aed2::Nat> p2;
  p2 = p1;
  
  ASSERT_EQ(p2.tamanio(), 4);
  ASSERT_EQ(to_s(p2), "[5, 12, 90, 80]");
}

void test_asignacion_de_pila_con_elementos_a_otra_pila_con_elementos()
{
  Pila<aed2::Nat> p1;
  
  p1.apilar(80);
  p1.apilar(90);
  p1.apilar(12);
  p1.apilar(5);
  
  Pila<aed2::Nat> p2;

  p2.apilar(5);
  p2.apilar(6);

  p2 = p1;
  
  ASSERT_EQ(p2.tamanio(), 4);
  ASSERT_EQ(to_s(p2), "[5, 12, 90, 80]");
}

void test_asignacion_de_pila_a_otra_pila_y_se_modifica_la_ultima() 
{
  Pila<aed2::Nat> p1;
  
  p1.apilar(80);
  p1.apilar(90);
  p1.apilar(12);
  p1.apilar(5);
  
  Pila<aed2::Nat> p2;

  p2.apilar(5);
  p2.apilar(6);

  p2 = p1;

  p2.desapilar();
  
  ASSERT_EQ(p2.tamanio(), 3);
  ASSERT_EQ(to_s(p2), "[12, 90, 80]");
}

void test_copiar_sin_usar_asignacion_cuando_apilo()
{
  Pila<Punto> pp;

  pp.apilar(Punto(1, 0));

  ASSERT_EQ(to_s(pp), "[(1,0)]");

  pp.apilar(Punto(3, 2));

  ASSERT_EQ(to_s(pp), "[(3,2), (1,0)]");
}

void test_apilar_pilas()
{
  Pila<Pila<aed2::Nat> > pp;

  {
    Pila<aed2::Nat> p;
    p.apilar(1);
    p.apilar(2);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 1);
  ASSERT_EQ(to_s(pp), "[[2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(3);
    p.apilar(4);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 2);
  ASSERT_EQ(to_s(pp), "[[4, 3], [2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(5);
    p.apilar(6);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 3);
  ASSERT_EQ(to_s(pp), "[[6, 5], [4, 3], [2, 1]]");
}

void test_asignacion_de_pila_de_pilas_a_nueva_pila_de_pilas()
{
  Pila<Pila<Punto> > pp;

  {
    Pila<Punto> p;
    
    Punto MiPunto(1, 0);
    p.apilar(MiPunto);
    
    Punto MiPunto2(2, 0);
    p.apilar(MiPunto2);

    pp.apilar(p);
  }
  
  ASSERT_EQ(pp.tamanio(), 1);
  ASSERT_EQ(to_s(pp), "[[(2,0), (1,0)]]");
  
  {
    Pila<Punto> p;
    
    Punto MiPunto(5, 17);
    p.apilar(MiPunto);

    pp.apilar(p);
  }
  
  ASSERT_EQ(pp.tamanio(), 2);
  ASSERT_EQ(to_s(pp), "[[(5,17)], [(2,0), (1,0)]]");
  
  Pila<Pila<Punto> > pp1;
  pp1 = pp;
  ASSERT_EQ(pp1.tamanio(), 2);
  ASSERT_EQ(to_s(pp1), "[[(5,17)], [(2,0), (1,0)]]");
}

int main()
{
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar_uno);
  RUN_TEST(test_apilar_varios);
  RUN_TEST(test_modificar_referencia_tope);
  RUN_TEST(test_desapilar_uno);
  RUN_TEST(test_desapilar_varios);
  RUN_TEST(test_constructor_copia_una_pila);
  RUN_TEST(test_constructor_copia_una_pila_y_se_modifica);
  RUN_TEST(test_asignacion_de_pila_con_elementos_a_pila_vacia);
  RUN_TEST(test_asignacion_de_pila_con_elementos_a_otra_pila_con_elementos);
  RUN_TEST(test_asignacion_de_pila_a_otra_pila_y_se_modifica_la_ultima);
  RUN_TEST(test_copiar_sin_usar_asignacion_cuando_apilo);
  RUN_TEST(test_apilar_pilas);
  RUN_TEST(test_asignacion_de_pila_de_pilas_a_nueva_pila_de_pilas);
  return 0;
}
