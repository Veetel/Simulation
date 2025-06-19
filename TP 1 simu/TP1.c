#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>//librairie scientific opensource
#include "TP1.h"
#define ITER2  100
#define MAX(a,b) (a>b)? a:b
#define MIN(a,b) (a<b)? a:b


/*------------------------------------------------------*/

int main (int argc, char* argv[]){
    
    int seed =1234;
    seed =john_von_neumann(seed);
    printf("Seed= %d  \n ",seed);

    int * res =intRand(5,1,5,16,32);
    double * res2 = floatRand(5,1,5,16,32,16);
    int *qualited_LCG = intRand(137,187,0,256,258);

    int N = 1234;
/*---------------------Von Neumann------------------ */
    for (unsigned int i = 0; i < 100; i ++){
        N = john_von_neumann(N);
        printf("%d  \n " ,N);
    }
/*---------------------Lancement de piece------------------ */


    for(int i = 0 ; i < ITER2 ;i++){
        int coin= coin_tossing();
        printf("coin = %d \n ", coin);
    }


    max_tab(equidistrib(10),10);

/*---------------------intRand------------------ */
    printf(" \n\n intRand : \n ");


    for(int i = 0; i < 32; i ++){
        printf("%d,",res[i]);
    }


/*---------------------floatRand------------------ */

    printf(" \n\n floatRand : \n ");
    for(int i = 0; i < 32; i ++){
        printf("%.4f,",res2[i]);
    }

/*---------------------LCG de "qualité" cyclique sur 256 nombres------------------ */
    printf(" \n\n LCG de Qualité \n ");

    for(int i = 0 ; i < 258; i++){
        printf("%d ", qualited_LCG[i]);
    }





/*--------------------bits_generator------------------------*/






    bits_generator(20);

    free(res);
    free(res2);
  
    return 0;
}
/*------------------------------------------------------*/













