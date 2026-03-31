#include <cmath>
#include <iostream>
#include "util.h"


// 0. Ernesto Cuadros <ecuadros@spc.org.pe>
T1 suma(T1 x, T1 y) {
    return x + y;
}

// 1 Alvarez Cadillo, Michell Adrian <<michell.aac.1106@gmail.com>,

// 2 Bernaola Gayoso César Raúl <bernaolacesar@gmail.com>,

// 3 Castro Chaupis, Armando Cristhian <armandocristhiancastrochaupis@gmail.com>,

// 4 Castro Galindo Carlo André <carlocastrogalindo@gmail.com>,
int potencia(int base, int exponente) {
    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado *= base;
    }
    return resultado;
}

// 5 Diaz Tapia Adderly Orlando <adderly.diaz.tapia@gmail.com>
double raizCuadrada(double x) {
    if (x < 0) {
     std::cout << "Error: No se puede calcular la raíz cuadrada de un número negativo." << std::endl;
     return -1; 
    }
    return sqrt(x);
}
// 6 Díaz Vega Greta Solange <gretadiaz01@gmail.com>

// 7 DÍAZ VEGA OLENKA HELENE <olenka.diaz.v@uni.pe>

// 8 Gallo Lugo Carlos enrique <cgallolugo@gmail.com>

// 9 Lopez Flores Royer Amed <roamlofl9@gmail.com>
// abs
double valor_absoluto(double x) {
    return (x < 0) ? -x : x; 
}
// 10 Miranda Zarate Jorge Luis <mirandazaratejorge@gmail.com>,
U1 factorial(U1 number){
    U1 result = 1;
    for(int i=number; i > 0; i--){
        result *= i;
    }
    return result;
}

// 11 Oscar Toledo Guerrero <tgoscar@gmail.com>

// 12 Quispe Calloapaza, David Saul <quispedavid987@gmail.com>
double Promedio(double x0, double y0) {
    return (x0 + y0) / 2.;
}

// 13 Suarez Maciel Susana Isabel <susana.suarez.maciel@gmail.com>
    int cuadrado(int x13){
        return x13 * x13;
    }

// 14 Tellez Heredia Jhon <phyjhon@gmail.com>,
float porcentaje(int a14, int b14) {
    return ((a14 + b14)/b14)*100;
}
// 15 Vilca Aguilar Luis Angel <luisangelvilca2@gmail.com>,
int fact(int n) {
    int resultado = 1;
    for (int i = 1; i <= n; i++){
        resultado = resultado * i;
    }
    return resultado;
}

// 16 Vinatea Chávez Camilo Jorge <camo2391@gmail.com>
T16 mult(T16 x, T16 y) {
    return x*y;
}

// 20 Segura Nuñez Alex Ernesto <alex.segura.nunez@gmail.com>

// 21 Selis Vasquez Luis Antonio <luisanonioselisvasquez@gmail.com>
