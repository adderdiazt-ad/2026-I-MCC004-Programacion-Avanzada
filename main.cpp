#include <iostream>
#include "util.h"
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
    
    // 2 Bernaola Gayoso César Raúl <bernaolacesar@gmail.com>,
    // Multiplicar
    int x1 = 5, y1 = 3;
    int a1 = resta(x1, y1);
    cout << "Michell Alvarez-Cadillo: " << a1 << endl;

    // 2 Bernaola Gayoso César Raúl <bernaolacesar@gmail.com>,
    cout << "Bernaola Gayoso Cesar Raul: " << multiplicacion(x0, y0) << endl;

    // 3 Castro Chaupis, Armando Cristhian <armandocristhiancastrochaupis@gmail.com>,
    // Dividir
    int x3 = 3,y3=2;
    float a3 = dividir(x3,y3);
    cout << "Armando Cristhian Castro Chaupis: " << a3 << endl;

    // 4 Castro Galindo Carlo André <carlocastrogalindo@gmail.com>,
    // Potencia
    
    // 5 Diaz Tapia Adderly Orlando <adderly.diaz.tapia@gmail.com>
    // Raiz cuadrada

    // 6 Díaz Vega Greta Solange <gretadiaz01@gmail.com>
    // Modulo

    // 7 DÍAZ VEGA OLENKA HELENE <olenka.diaz.v@uni.pe>

    // 8 Gallo Lugo Carlos enrique <cgallolugo@gmail.com>

    // 9 Lopez Flores Royer Amed <roamlofl9@gmail.com>

    // 10 Miranda Zarate Jorge Luis <mirandazaratejorge@gmail.com>,

    // 11 Oscar Toledo Guerrero <tgoscar@gmail.com>

    // 12 Quispe Calloapaza, David Saul <quispedavid987@gmail.com>

    // 13 Suarez Maciel Susana Isabel <susana.suarez.maciel@gmail.com>

    // 14 Tellez Heredia Jhon <phyjhon@gmail.com>,

    // 15 Vilca Aguilar Luis Angel <luisangelvilca2@gmail.com>,

    // 16 Vinatea Chávez Camilo Jorge <camo2391@gmail.com>

    // 20 Segura Nuñez Alex Ernesto <alex.segura.nunez@gmail.com>

    // 21 Selis Vasquez Luis Antonio <luisanonioselisvasquez@gmail.com>
    int a1 = 5, b1 = 6; 
    int r0 = (a1*a1 + b1*b1)/(a1 + b1); 
    cout << r0 << endl;
    
    return 0;
}
