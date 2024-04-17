#pragma once
#include <iostream>
#include <bitset>
#include <string>


//anotacion bitset tiene como msb el ultimo indice y el lsb el 0

struct registro {
    float numero = 0;
    std::bitset<1>signo;
    std::bitset<8>exponente;
    std::bitset<23>significante;
};


std::bitset<23> parteFraccionaria(float);

registro separacion(float);


std::bitset<8> sumaBinaria(std::bitset<8>, std::bitset<8>,bool&,bool&);
std::bitset<23> sumaBinaria(std::bitset<23>, std::bitset<23>, bool&);

std::bitset<23> normalizarRedondear(std::bitset<46>&, std::bitset<8>&);
std::bitset<23> multiplicacionNumerosSinSigno(std::bitset<23>, std::bitset<23>, std::bitset<8>&);

registro multiplicacionPuntoFlotante(registro, registro);