#include <stdio.h>
#include "rabbitPop.h"





/*##############################################*
*   @brief:  fibbonacci est une fonction qui    *
*            calcule le nombre de couple de     *
*            lapin à chaque étape (mois)        *                              
*                                               *
*   @return: une structure de population de     *
*            couple de lapin                    *                                               *
*###############################################*/



rabbitPop fibonacci(int nb_of_time,rabbitPop population_of_rabbit){

    double temp;

    for (int i = 0 ; i < nb_of_time; i++){

        temp = population_of_rabbit.nb_Rabbit_Enfant;
        population_of_rabbit.nb_Rabbit_Enfant = population_of_rabbit.nb_Rabbit_Adult;
        population_of_rabbit.nb_Rabbit_Adult += temp;

    }

    return population_of_rabbit;

}