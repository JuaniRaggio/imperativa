#include <stdio.h>

typedef struct piersCDT * piersADT;

/* Crea un sistema de administración de muelles de los puertos de una ciudad */
piersADT newPiers(void);

/* 
 * Agrega el puerto #pierNumber y retorna 1.
 * Falla si el puerto ya existe y retorna 0.
 * Un puerto inicia sin muelles. Se asume un bajo porcentaje de puertos libres.
 */
size_t addPier(piersADT piers, size_t pierNumber);

/* 
 * Agrega el muelle #dockNumber al puerto #pierNumber y retorna 1.
 * Falla si el muelle ya existe en el puerto o si el puerto no existe, y retorna 0.
 * Un muelle inicia sin una embarcación amarrada.
 * Se asume un bajo porcentaje de muelles libres para cada puerto.
 */
size_t addPierDock(piersADT piers, size_t pierNumber, size_t dockNumber);

/* 
 * Amarra una embarcación en el muelle #dockNumber del puerto #pierNumber y retorna 1.
 * Falla si el muelle ya estaba ocupado, si el muelle no existe en el puerto,
 * o si el puerto no existe, y retorna 0.
 */
size_t dockShip(piersADT piers, size_t pierNumber, size_t dockNumber);

/* 
 * Indica si hay una embarcación amarrada en el muelle #dockNumber del puerto #pierNumber.
 * Retorna:
 *   1 si hay una embarcación amarrada
 *   0 si no hay una embarcación amarrada
 *  -1 si el muelle no existe en el puerto o si el puerto no existe
 */
int shipInDock(const piersADT piers, size_t pierNumber, size_t dockNumber);

/* 
 * Indica la cantidad de embarcaciones amarradas en todos los muelles del puerto #pierNumber.
 * Falla si el puerto no existe y retorna -1.
 */
size_t pierShips(const piersADT piers, size_t pierNumber);

/* 
 * Desamarra una embarcación en el muelle #dockNumber del puerto #pierNumber y retorna 1.
 * Falla si el muelle estaba libre, si el muelle no existe en el puerto,
 * o si el puerto no existe, y retorna 0.
 */
size_t undockShip(piersADT piers, size_t pierNumber, size_t dockNumber);

/* Libera los recursos utilizados por el TAD */
void freePiers(piersADT piers);

