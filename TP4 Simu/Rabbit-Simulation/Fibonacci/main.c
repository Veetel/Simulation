#include <stdio.h>
#include "rabbitPop.h"

#define NB_SIMULATION 100


/*##############################################*
*   @brief : simulation of fibonacci suite      *
*            using one couple of rabbit         *
*                                               *
*###############################################*/


int main (int argc,char* argv){

    rabbitPop rabbit_population;

    rabbit_population.nb_Rabbit_Adult  = 1;
    rabbit_population.nb_Rabbit_Enfant = 0;

    rabbit_population = fibonacci(100,rabbit_population);

    printf("Number of final rabbits: \n adult :% d  children : %d \n",rabbit_population.nb_Rabbit_Adult, rabbit_population.nb_Rabbit_Enfant);

    return 0;


}