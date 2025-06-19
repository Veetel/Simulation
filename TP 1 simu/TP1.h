#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ITER  1000000
#define MAX(a,b) (a>b)? a:b
#define MIN(a,b) (a<b)? a:b





/*----------------------------------------------------*/
int coin_tossing(){
    int r = rand()%2;
    return (r);
}
/*---------------------------------------------------*/
int roll_dice(){
    return (rand() %6);
}
/*---------------------------------------------------*/

int john_von_neumann(int seed){

    seed = seed*seed;
    seed = seed /100;
    seed = seed%10000;
    return seed;
}
/*-----------------------------------------------*/
int roll_d10(){
    return(rand()%10);
}
/*--------------------------------------- */

int* equidistrib(int n){
    int *tab = calloc(n,(sizeof(int)));
    int iter = ITER;
    if (tab == NULL){
        perror("Allocation Error \n");
        exit (-3);
    }
    if (n == 2){

            for(int j = 0; j< iter ; j++){
                tab[coin_tossing()]++;
            }
        
    }
    if(n == 6){
        for (int i = 0 ; i < iter ; i++){ 
            tab[roll_dice()]++;
        }
    }
    if(n==10){
        for (int i = 0 ; i < iter ; i++){
            tab[roll_d10()]++;
        }
    }
    for(int i = 0 ; i <n ; i++){
        printf("%d \n",tab[i]);
    }

    return tab;
}

/*-----------------------------------------------------*/
int * max_tab(int * tab,int n){
    int max = tab[0];
    int min = tab[0];
    for(int i =0; i < n;i++){
     max = MAX(tab[i],max);   
     min = MIN(tab[i],min);
    }

    printf("%d\n",max);
    return tab;
}
/*-----------------------------------------------------*/
int is_equidistri(int *tab , int n,double range_err , double total_nb){
    for (int i = 0; i < n-1;i++){
        for (int j = i ; j < n-1 ; j++){
            if(i != j){
                if (tab[i] -tab[j] / total_nb >= range_err || tab[i] -tab[j] / total_nb <= (-1)*range_err ){
                    return 0;
                }
         
            }

        }
        
    }
   
    return 1;
}

/*-----------------------------------------------------*/

int linear (int a, int c, int seed, int m){

    return (5*seed +c )%m;

}

int * intRand (int a, int c, int seed, int m, int iter_nb){
    
    int * res = calloc(iter_nb, sizeof(int));
    if(res==NULL){
        perror("ALLOCATION ERROR");
        exit (-1);

    }

    for (int i = 0; i < iter_nb ; i++){
        res[i] = linear(a,c,seed,m);
        seed = res[i];
    }
    return res;
}

/*------------------------------------------------*/

double *floatRand(int a, int c , int seed, int m ,int iter_nb, double diviser){
    int * intRandomised = intRand(a,c,seed,m,iter_nb);
    double * res = calloc(iter_nb,sizeof(double));
    if(res == NULL){
        perror("ALLOCATION ERROR");
        exit(-2);
    }

    for (int i = 0 ; i < iter_nb; i++){

        res[i] = ( (double)intRandomised[i] / diviser);
    }

    return res;
}

/*----------------------------------------------------------*/

int bits_generator(int nb_loop){

    char * binary[] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"}; // les mots binaires possibles

    int bit1,bit2,bit_test = 15; //valeur du bit de départ fixé a 1111
    int Int = 15;

    for(int i = 0  ; i < nb_loop; i++){
        bit1 = Int & 1 ;  //Et avec 1
        bit2 = Int & 2 ; // Et avec 10

        bit_test = bit1 ^ (bit2>>1) ; //on décale bit2 pour aligner avec bit1 
        printf("Bit du Xor: %d \n Valeur : %s \n", bit_test,binary[Int]);
        Int >>= 1;
        printf(" valeur décalée : %s \n", binary[Int]);

        if(bit_test) {
            Int |= 8;
        }   
        printf("Nouvelle valeur: %s \n", binary[Int]);
    
        
    }

    return 0;

}
    