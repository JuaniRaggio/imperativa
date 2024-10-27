#define ENT_HORAS 7
#define ENT_MINUTOS 30

// La siguiente funcion es la que nos paso el enunciado
// El problema que tiene esta funcion es que si llega justo en la hora previa o menor a la propuesta, pero los minutos son mayores a los propuestos,
// el programa va a tomar como que llego tarde
int 
llegaTemprano (const int hora, const int minutos)
{
	return (hora <= ENT_HORA && minutos <= ENT_MINUTOS);
}

// La funcion corregida:
int llegaTempCorrecta(const int hora, const int minutos){
    return ((hora < ENT_HORA) || (hora == ENT_HORA && minutos <= ENT_MINUTOS));
}

