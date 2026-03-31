#include <iostream>
#include "util.h"

#include <math.h> //
using namespace std;

// Ernesto Cuadros
// g++ -std=c++17 main.cpp util.cpp -o main
int main() {

    // 0. Ernesto Cuadros <ecuadros@spc.org.pe>
    int x0 = 1, y0 = 2;
    int a0 = suma(x0, y0);
    cout << "Ernesto Cuadros-Vargas: " << a0 << endl;

    // 1 Alvarez Cadillo, Michell Adrian <<michell.aac.1106@gmail.com>,
    // Resta

    int x1 = 5, y1 = 3;
    int a1 = resta(x1, y1);
    cout << "Michell Alvarez-Cadillo: " << a1 << endl;
        
    // 2 Bernaola Gayoso César Raúl <bernaolacesar@gmail.com>,
    // Multiplicar

    // 3 Castro Chaupis, Armando Cristhian <armandocristhiancastrochaupis@gmail.com>,
    // Dividir

    // 4 Castro Galindo Carlo André <carlocastrogalindo@gmail.com>,
    // Potencia
    int base = 2, exponente = 3;
    int a4 = potencia(base, exponente);
    cout << "Castro Galindo Carlo André: " << a4 << endl;
    
    // 5 Diaz Tapia Adderly Orlando <adderly.diaz.tapia@gmail.com>
    // Raiz cuadrada
    double x5 = 16.0;
    double a5 = raizCuadrada(x5);
    cout << "Diaz Tapia Adderly Orlando: " << a5 << endl;
    // 6 Díaz Vega Greta Solange <gretadiaz01@gmail.com>
    // Modulo

    // 7 DÍAZ VEGA OLENKA HELENE <olenka.diaz.v@uni.pe>
    
    // 8 Gallo Lugo Carlos enrique <cgallolugo@gmail.com>

    // 9 Lopez Flores Royer Amed <roamlofl9@gmail.com>
    // Valor absoluto
    cout << endl;
    double x91 = -3.14;
    double a91 = valor_absoluto(x91);
    cout << "Lopez Flores Royer Amed: " << a91 << endl;
    double x92 = 2.71;
    double a92 = valor_absoluto(x92);
    cout << "Lopez Flores Royer Amed: " << a92 << endl;
    cout<<endl;
    // 10 Miranda Zarate Jorge Luis <mirandazaratejorge@gmail.com>,
    unsigned int u0 = 10;
    cout << "Demo Miranda Zarate Jorge: " << u0 << "! = " << factorial(u0) << endl;

    // 11 Oscar Toledo Guerrero <tgoscar@gmail.com>

    // 12 Quispe Calloapaza, David Saul <quispedavid987@gmail.com>
    double a1 = 5., b1 = 6.;
    double p0 = Promedio(a1, b1);
    cout << "David Quispe: " << p0 << endl;


    // 13 Suarez Maciel Susana Isabel <susana.suarez.maciel@gmail.com>
    int x13 = 8;
    int result = cuadrado(x13);

    cout << "Suarez Maciel Susana Isabel: El cuadrado de: " << x13 << " es " << result << endl;
    
    // 14 Tellez Heredia Jhon <phyjhon@gmail.com>,
    int a14 = 1, b14 = 2;
    float c14 = porcentaje(a14, b14);
    cout << "porcentaje: " << c14 << endl;
    // 15 Vilca Aguilar Luis Angel <luisangelvilca2@gmail.com>,
    // Factorial
    int n = 6;
    int res = fact(n);
    cout << "Luis Vilca: " << res << endl;

    // 16 Vinatea Chávez Camilo Jorge <camo2391@gmail.com>
    float x16 = 3.14, y16 = 2.71;
    float z16 = mult(x16, y16);
    cout << "Camilo Vinatea: " << z16 << endl;
    // 20 Segura Nuñez Alex Ernesto <alex.segura.nunez@gmail.com>

    // 21 Selis Vasquez Luis Antonio <luisanonioselisvasquez@gmail.com>
    int a1 = 5, b1 = 6; 
    int r0 = (a1*a1 + b1*b1)/(a1 + b1); 
    cout << "Luis A. Selis: "<< r0 << endl;
    return 0;
}
