#include "funciones.h"
#include <iostream>

int main()
{
    float numUno, numDos;   

    std::cout << "Introduzca el primer flotante: ";
    std::cin >> numUno;
    std::cout << "Introduzca el segundo flotante: ";
    std::cin >> numDos;

    registro numUnoReg = separacion(numUno);
    registro numDosReg = separacion(numDos);

    registro multiplicacion = multiplicacionPuntoFlotante(numUnoReg, numDosReg);
    std::cout << multiplicacion.signo << " " << multiplicacion.exponente << " " << multiplicacion.significante;
}
