#include <iostream>
#include <math.h>
#include "util.h"
#include "types.h"
using namespace std;

// Ernesto Cuadros
// g++ -std=c++17 main.cpp util.cpp -o main
int main() {
    
    // 0. Ernesto Cuadros <ecuadros@spc.org.pe>
    T1 x0 = 1, y0 = 2;
    T1 a0 = suma(x0, y0);
    cout << "Ernesto Cuadros-Vargas: " << a0 << endl;

    // 1 Alvarez Cadillo, Michell Adrian <<michell.aac.1106@gmail.com>,
    // Resta

    T1 x1 = 5, y1 = 3;
    T1 a111 = resta(x1, y1);
    cout << "Michell Alvarez-Cadillo: " << a111 << endl;

    // 2 Bernaola Gayoso César Raúl <bernaolacesar@gmail.com>,
    // Multiplicar
    cout << "Bernaola Gayoso Cesar Raul: " << multiplicacion(x0, y0) << endl;

    // 3 Castro Chaupis, Armando Cristhian <armandocristhiancastrochaupis@gmail.com>,
    // Dividir
    T3F x3=5,y3=6;
    T3F a3 = dividir(x3,y3);
    cout << "Armando Castro:" <<a3 <<endl;

    // 4 Castro Galindo Carlo André <carlocastrogalindo@gmail.com>,
    // Potencia
    T1 base = 2, exponente = 3;
    T1 a4 = potencia(base, exponente);
    cout << "Castro Galindo Carlo Andre: " << a4 << endl;
    
    // 5 Diaz Tapia Adderly Orlando <adderly.diaz.tapia@gmail.com>
    // Raiz cuadrada
    T5 x5 = 16.0;
    T5 a5 = raizCuadrada(x5);
    cout << "Diaz Tapia Adderly Orlando: " << a5 << endl;
    // 6 Díaz Vega Greta Solange <gretadiaz01@gmail.com>
    // Modulo

    // 7 DÍAZ VEGA OLENKA HELENE <olenka.diaz.v@uni.pe>
    
    // 8 Gallo Lugo Carlos enrique <cgallolugo@gmail.com>
    T8 n8 = 7;
    T8 f8 = fibo(n8);
    cout << "Carlos Enrique Gallo Lugo: fibonacci(" << n8 << ") = " << f8 << endl;

    // 9 Lopez Flores Royer Amed <roamlofl9@gmail.com>
    // Valor absoluto
    T_ABS x91 = -3.14;
    T_ABS a91 = valor_absoluto(x91);
    cout << "Lopez Flores Royer Amed: " << a91 << endl;

    // 10 Miranda Zarate Jorge Luis <mirandazaratejorge@gmail.com>,
    unsigned int u0 = 10;
    cout << "Demo Miranda Zarate Jorge: " << u0 << "! = " << factorial(u0) << endl;

    // 11 Oscar Toledo Guerrero <tgoscar@gmail.com>

    // 12 Quispe Calloapaza, David Saul <quispedavid987@gmail.com>
    T12 a1 = 5., b1 = 6.;
    T12 p0 = Promedio(a1, b1);
    cout << "David Quispe: " << p0 << endl;

    // 13 Suarez Maciel Susana Isabel <susana.suarez.maciel@gmail.com>
    int x13 = 8;
    int result = cuadrado(x13);
    cout << "Suarez Maciel Susana Isabel: El cuadrado de: " << x13 << " es " << result << endl;
    
    // 14 Tellez Heredia Jhon <phyjhon@gmail.com>,
    T14 a14 = 1, b14 = 2;
    F14 c14 = porcentaje(a14, b14);
    cout << "porcentaje: " << c14 << endl;
    // 15 Vilca Aguilar Luis Angel <luisangelvilca2@gmail.com>,
    // Factorial
    T1 n = 6;
    T1 res = fact(n);
    cout << "Luis Vilca: " << res << endl;

    // 16 Vinatea Chávez Camilo Jorge <camo2391@gmail.com>
    T16 x16 = 3.14, y16 = 2.71;
    T16 z16 = mult(x16, y16);
    cout << "Camilo Vinatea: " << z16 << endl;
    // 20 Segura Nuñez Alex Ernesto <alex.segura.nunez@gmail.com>

    // 21 Selis Vasquez Luis Antonio <luisanonioselisvasquez@gmail.com>
    T1 a21 = 5, b21 = 6; 
    T1 r21 = (a21*a21 + b21*b21)/(a21 + b21); 
    cout << "Selis Vasquez Luis Antonio: " << r21 << endl;
    
    return 0;
}
