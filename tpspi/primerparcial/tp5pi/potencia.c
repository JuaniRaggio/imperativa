double potencia(double base, int exponente) {
    if(exponente % 2 == 0 && base < 0)
        return -1;
    else if(exponente < 0){
        exponente *= -1;
        base = 1/base;
    } else if(exponente == 0)
        return 1;

    while(exponente > 0){
        base *= base;
        --exponente;
    }
    return base;
}

