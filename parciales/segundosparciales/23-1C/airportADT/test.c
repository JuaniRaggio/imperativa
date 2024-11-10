#include "airportADT.h"
#include <assert.h>
#include <string.h>
#include <strings.h>

int main(void) {
  // Crea un sistema sin pistas
  airportADT airportAdt = newAirport();
  // Agrega la pista con el id 5
  assert(addRunway(airportAdt, 5) == 1);
  assert(addRunway(airportAdt, 0) == 2);
  // Falla porque ya existe una pista con el id 5
  assert(addRunway(airportAdt, 5) == -1);
  // Falla porque no es válida la pista cero
  assert(addRunway(airportAdt, 0) == -1);
  // Agrega al final de la pista de id 5 al avión de matrícula AR01 y será
  // el primero en despegar
  char auxPrime[20] = "AR01";
  assert(addPlaneToRunway(airportAdt, 5, auxPrime) == 1);
  // Agrega al final de la pista de id 5 al avión de matrícula AC91 y será
  // el segundo en despegar
  strcpy(auxPrime, "AC91");
  assert(addPlaneToRunway(airportAdt, 5, auxPrime) == 2);
  strcpy(auxPrime, "AC92");
  assert(addPlaneToRunway(airportAdt, 5, auxPrime) == 3);

  // Obtiene los aviones por despegar de la pista de id 5 en orden inverso al
  // orden de despegue
  char ** aux = pendingFlights(airportAdt, 5);
  assert(!strcmp(aux[0], "AC92"));
  assert(!strcmp(aux[1], "AC91"));
  assert(!strcmp(aux[2], "AR01"));
  assert(!strcmp(aux[3], ""));
  free(aux);
  // Despega el primer avión de la pista de id 5
  assert(!strcmp(takeOff(airportAdt, 5), "AR01"));
  assert(!strcmp(takeOff(airportAdt, 5), "AC91"));
  assert(!strcmp(takeOff(airportAdt, 5), "AC92"));
  // Ya no quedan aviones por despegar en la pista de id 5
  assert(takeOff(airportAdt, 5) == NULL);
  // No existe la pista 3
  assert(takeOff(airportAdt, 3) == NULL);
  // No se puede agregar un avión a una pista que no existe
  assert(addPlaneToRunway(airportAdt, 3, "FL91") == -1);
  // No se puede agregar un avión a una pista que no existe
  assert(pendingFlights(airportAdt, 3) == NULL);
  freeAirport(airportAdt);
  puts("Despegue exitoso!");
  return 0;
}
