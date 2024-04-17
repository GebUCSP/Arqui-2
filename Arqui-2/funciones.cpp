#include "funciones.h"

//creacion del struct registro
std::bitset<23> parteFraccionaria(float f) {
    std::string binary;
    for (int i = 0; i < 23; i++) {
        float nuevof = f * 2;
        f = nuevof - int(nuevof);
        binary += std::to_string(int(nuevof));
    }
    return std::bitset<23>(binary);
}

registro separacion(float num) {
    registro separado;

    uint32_t e = static_cast<uint32_t>(num);
    float f = num - int(e);
    separado.numero = num;
    separado.signo = num < 0;
    separado.exponente = std::bitset<8>(int(e));
    separado.significante = parteFraccionaria(f);

    return separado;
}

//operaciones de apoyo para la multiplicacion
std::bitset<8> sumaBinaria(std::bitset<8> a, std::bitset<8> b) {
    std::string binary;
    int c = 0;

    for (int i = 0; i < 8; i++) {
        int acumulado = a[i] + b[i] + c;
        std::string string;

        if (acumulado == 3) {
            c = 1;
            string = "1";
        }else if (acumulado == 2) {
            c = 1;
            string = "0";
        }else if(acumulado == 1) {
            c = 0;
            string = "1";
        }
        else if(acumulado == 0){
            c = 0;
            string = "0";
        }

        binary = string + binary;
    }

    std::bitset<8>result(binary);

    return result;
}

std::bitset<8> sumaBinaria(std::bitset<8> a, std::bitset<8> b, bool& overflow, bool& underflow) {
    std::string binary;
    underflow = false;
    overflow = false;
    int c = 0;

    for (int i = 0; i < 8; i++) {
        int acumulado = a[i] + b[i] + c;
        std::string string;

        if (acumulado == 3) {
            c = 1;
            string = "1";
        }if (acumulado == 2) {
            c = 1;
            string = "0";
        }if (acumulado == 1) {
            c = 0;
            string = "1";
        }
        else {
            c = 0;
            string = "0";
        }

        binary = string + binary;
    }

    std::bitset<8>result(binary);
    overflow = c;
    for (int i = 7; i > 0; i--) {
        if ((!result[i] && a[i]) || (!result[i] && b[i])) {
            underflow = true;
            break;
        }
    }
    
    return result;
}

std::bitset<23> sumaBinaria(std::bitset<23> a, std::bitset<23> b, bool& overflow) {
    std::string binary;
    int c = 0;

    for (int i = 0; i < 23; i++) {
        int acumulado = a[i] + b[i] + c;
        std::string string;

        if (acumulado == 3) {
            c = 1;
            string = "1";
        }if (acumulado == 2) {
            c = 1;
            string = "0";
        }if (acumulado == 1) {
            c = 0;
            string = "1";
        }
        else {
            c = 0;
            string = "0";
        }

        binary = string + binary;
    }

    std::bitset<23>result(binary);
    overflow = c;
    return result;
}

std::bitset<23> normalizarRedondear(std::bitset<46>& op, std::bitset<8>& exp) {
    int contador = 0;
    for (int i = 22; 0 <= i; i--) {
        if (op[i] != 1) {
            contador++;
        }
        else {
            break;
        }
    }
    op <<= contador;
    exp = sumaBinaria(exp, std::bitset<8>(static_cast<uint32_t>(contador)));

    std::bitset<23> resultado;
    for (int i = 22; 0 <= i; i--) {
        resultado[i] = op[i];
    }

    return resultado;
}

std::bitset<23> multiplicacionNumerosSinSigno(std::bitset<23> M, std::bitset<23> Q, std::bitset<8>&exponente) {
    bool C = 1;
    std::bitset<23>A;
    for (int i = 0; i < 23; i++) {
        if (Q[0] == 1) {
            A = sumaBinaria(A, M, C);
        }

        int temp = A[0];
        A >>= 1;
        A[22] = C;
        Q >>= 1;
        Q[22] = temp;
    }

    std::bitset<46>result;
    for (int i = 0; i < 23; i++) {
        result[i] = A[i];
        result[i + 23] = Q[i];
    }

   
    return normalizarRedondear(result, exponente);
}

//multiplicacion
registro multiplicacionPuntoFlotante(registro a, registro b) {
    registro multiplicacion;
    bool overflow, underflow;

    if (a.numero == 0 || b.numero == 0) {
        return {};
    }

    multiplicacion.signo = !(a.signo == b.signo);
    multiplicacion.exponente = sumaBinaria(sumaBinaria(a.exponente, b.exponente), std::bitset<8>("10000001"),overflow,underflow);
    multiplicacion.significante = multiplicacionNumerosSinSigno(a.significante, b.significante,multiplicacion.exponente);

    if (overflow) {
        std::cout << "Hubo overflow" << std::endl;
        return {};
    }
    else if (underflow) {
        std::cout << "Hubo underflow" << std::endl;
        return {};
    }

    return multiplicacion;
    
}



