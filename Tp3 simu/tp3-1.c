#include <stdio.h>
#include <math.h>
#include <stdlib.h>





/*#################################################################################*
 *#                  Welcome to my programm for the TP3 of Simulation             #*
 *#                                                                               #*
 *#                                                                               #*
 *#   @author : LARGERON Jean-Baptiste (gH)                                       #*
 *#                                                                               #*
 *#   @brief : Here is a unique document for all the tp, I did that choice        #*
 *#            because the TP is short and I wanted to have all in one to         #*
 *#            simplify the execution (you don't need to download Mersenne-       #*
 *#            Twistter generator with this idea)                                 #*
 *#                                                                               #*
 *#                                                                               #*
 *#            The program is divided in 3 large parts:                           #*
 *#              1) The Mersenne-Twister code (lines: 48 to 176)                  #*
 *#              2) My functions (line :205 to 495)                               #*
 *#              3) The main function (line : 516)                                #*
 *#                                                                               #*
 *#              Please, read the comment blocs and if needed                     #*
 *#                                                                               #*
 *#################################################################################*/



















/*############################## Mersenne-Twister ################################*/

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */




























/*########################### My program ##################################*/


/*-------- Definition of a structure : Point -----------*/

//It helps to manipulate axes

typedef struct {
    double axe_x ;  // axe x
    double axe_y ;  // axe y
    double axe_z ;  // axe z
} Point;

/*-----------------------Function Norm ----------------*/

double norm(const double x,const double y,const double z){
    return ( x*x + y*y +z*z);
}

/*-----------------Volume of a sphere with Monte Carlo---------------*/

/*##########################################################################*
 *                                                                          *
 *  @brief :    Calculate the volume of a sphere with Monte Carlo method    *
 *                                                                          *
 *              inNb_samples is the number of points we want to generate    * 
 *                                                                          *
 *  @param :    number of iterations                                        *
 *  @return:    the volume of a sphere                                      *
 *                                                                          *
 *##########################################################################*/


double Sphere_Volume_MonteCarlo(const unsigned long inNb_Samples){

    int isInSphere = 0; //needed for counting how much points are in the sphere

    for (int i = 0 ; i < inNb_Samples; i++){

        Point rnd_Point;
        rnd_Point.axe_x = genrand_real1();
        rnd_Point.axe_y = genrand_real1();
        rnd_Point.axe_z = genrand_real1();


        //Now we need to check if the point (x,y,z) is inside
        //the sphere
        

        if(norm(rnd_Point.axe_x,rnd_Point.axe_y,rnd_Point.axe_z) < 1){

            isInSphere++;

        }
    }


    return (8.0*  (double)isInSphere / (double) inNb_Samples);


}

/*--------------------------- Volume of a Sphere --------------------------*/

/*##########################################################################*
 *                                                                          *
 *  @brief :    Calculate the volume of a sphere with                       *
 *                                                                          *
 *                                                                          * 
 *                                                                          *
 *  @param :    radius of the sphere                                        *
 *  @return:    the volume of a sphere                                      *
 *                                                                          *
 *##########################################################################*/

 double sphere_Volume(const double radius){
    return (4.0/3.0 * M_PI*radius*radius*radius);

 }
/*-------------------------------------------------------------------------*/

/*##########################################################################*
 *                                                                          *
 *  @brief :    Calculate the volume of a sphere with Monte Carlo method    *
 *                                                                          *
 *              inPrecision is the precision we want                        * 
 *                                                                          *
 *  @param :    number of precision we want                                 *
 *  @return:    the volume of a sphere                                      *
 *                                                                          *
 *##########################################################################*/

 int Sphere_Volume_MonteCarlo_Precised(const double inPrecision){
    int isInSphere = 0;
    int nbOfGeneratedPoints = 0;
    int convertor;


    double SphereVolume = (sphere_Volume(1)); 
    double VolumeGenerated  = 1;
    
    
    convertor = SphereVolume/ inPrecision ;
    SphereVolume = convertor * inPrecision ;
    
      
    while(VolumeGenerated != SphereVolume){

        Point rnd_Point;
        rnd_Point.axe_x = genrand_real1();
        rnd_Point.axe_y = genrand_real1();
        rnd_Point.axe_z = genrand_real1();

        nbOfGeneratedPoints ++;



        //Now we need to check if the point (x,y,z) is inside
        //the sphere
        
        if(norm(rnd_Point.axe_x,rnd_Point.axe_y,rnd_Point.axe_z) < 1){

            isInSphere++;

        }

        VolumeGenerated = (8.0 * (double)isInSphere / (double) nbOfGeneratedPoints);
    
        convertor = VolumeGenerated / inPrecision;
        VolumeGenerated = convertor *inPrecision;
        
    }
    
    return nbOfGeneratedPoints;
}

/*----------------------------- Mean Volume ----------------------------*/

/*##########################################################################*
 *                                                                          *
 *  @brief :    Calculate the mean volume of table of volume                *
 *                                                                          *
 *                                                                          * 
 *                                                                          *
 *  @param :    a tab of volume and his lenght                              *
 *  @return:    the mean of the table                                       *
 *                                                                          *
 *##########################################################################*/

double meanVolume(const double * inTab_of_generated_volume, const int len_of_tab){
    
    double total_value =0;

    for (int i = 0; i < len_of_tab; i++ ){
        total_value += inTab_of_generated_volume[i];

    }


    return (total_value / len_of_tab);

}

/*---------------------------- simSphere_for_mean --------------------------------*/

/*##########################################################################*
 *                                                                          *
 *  @brief :  Simulate the Sphere Volume with Monte Carlo method and stock  *
 *            it in a table to help to compute the mean                     *
 *                                                                          * 
 *            /!\ DON'T FORGET TO FREE YOUR VAR AFTER /!\                   * 
 *                                                                          * 
 *                                                                          *
 *  @param :    number of points you want and number of Iterations in the   *
 *              table                                                       * 
 *                                                                          *
 *  @return:    a table of volumes of spheres generated with Monte carlo    *
 *              method                                                      *
 *                                                                          *
 *##########################################################################*/



double * simSphere_for_mean(const unsigned int inNbPoints, const unsigned int inNbIterations){

    double * result_tab = calloc(inNbIterations, sizeof(double));



    if(result_tab == NULL){

        perror("ALLLOCATION ERROR L:342, result_tab:NULL \n");
        exit(-1);
    }


    for (int i = 0 ; i < inNbIterations ; i++){

        result_tab[i] = Sphere_Volume_MonteCarlo(inNbPoints);

    }


    return (result_tab);
    
}

/*----------------------------- Relative Error ------------------------*/

/*#######################################################################*
 *                                                                       *
 *   @brief : Calculate the relative error between 2 values              *
 *                                                                       *
 *   @param : a value and an analytically expected value                 *
 *                                                                       *
 *   @return: the value of the relative error                            *
 *                                                                       *
 *#######################################################################*/


double relative_error(const double inValue_Approximative,const double inValue_Theor){

    return (fabs((inValue_Theor - inValue_Approximative)/ inValue_Theor));

}


/*------------------------------- Estimation without bias --------------------------------*/


/*#######################################################################*
 *                                                                       *
 *   @brief : Calculate the estimate without bias needed for the         *
 *            confidence interval                                        *
 *                                                                       *
 *   @param : a table of values (like values obtained from our generated *
 *            and his lenght and his mean                                *
 *                                                                       *
 *   @return: the value of the estimate                                  *
 *                                                                       *
 *#######################################################################*/


double estimate_without_bias(const double * inTab_of_values, const int len_of_tab,const double mean_of_tab) {

    double res_out = 0; //It'll be our result

    for (int i = 0; i < len_of_tab; i++){


        res_out = res_out + (inTab_of_values[i] - mean_of_tab)*(inTab_of_values[i]- mean_of_tab);
    }



    res_out = res_out/ (len_of_tab -1);

    return ( res_out);
}


/*----------------------------- Radius Confidence Interval ----------------------------------*/

/*#######################################################################*
 *                                                                       *
 *   @brief : Calculate the confidence Interval                          *
 *                                                                       *
 *                                                                       *
 *   @param : a table of values and is lenght, and the error margin and  *
 *            the mean of the table                                      *
 *            if needed check this URL :                                 *
 *            https://www.supagro.fr/cnam-lr/statnet/tables.htm#student  *
 *                                                                       *
 *                                                                       *
 *   @return: the value of the Radius needed for confidence Interval     *
 *                                                                       *
 *#######################################################################*/



double radius_confidence_interval(const double error_margin, const double * inTab_of_values,const unsigned int len_of_tab, const double mean_of_tab ){
    
    double result_out = 0;
    result_out = estimate_without_bias(inTab_of_values,len_of_tab, mean_of_tab);

    result_out = result_out /len_of_tab;
    result_out = error_margin * sqrt(result_out);

    return result_out;

}





















/*#############################################################################################*
 *##################################                     ######################################*
 *##################################    Function main    ######################################*
 *##################################                     ######################################*
 *#############################################################################################*/


int main(int argc, char * argv[]){

    /*------------------------- Initialisation of Mersenne-Twister ----------------------*/

    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);


    /*----------------------------------------- 1 --------------------------------------*/


    printf("Volume Sphere for 1000 points : %lf \n", Sphere_Volume_MonteCarlo(1000));
    // printf("Volume Sphere for 174700 points: %lf \n", Sphere_Volume_MonteCarlo(174700));
    // printf("Volume Sphere for 1 000 000 points : %f \n", Sphere_Volume_MonteCarlo(1000000) );
    // printf("Volume Sphere for 1 000 000 000 points : %f \n", Sphere_Volume_MonteCarlo(1000000000));
    printf("Real Volume Sphere  : %f \n ", sphere_Volume(1));

    printf("%f \n \n", Sphere_Volume_MonteCarlo(529));
    printf("Number iterations : %d \n ", Sphere_Volume_MonteCarlo_Precised(0.001));
    
    /*----------------------------------------- 2 --------------------------------------*/

    //declaration of variables

    double *thousand;
    double* million;
    // double * billion;

    double thousand_Mean;
    double million_mean;
    // double billion_mean;




    //For 10 Experiences

    //initialization of our tables
    thousand = simSphere_for_mean(1000,10);
    million = simSphere_for_mean(1000000,10);
    // billion = simSphere_for_mean(1000000000,10);


    //calculate the mean of each tables
    thousand_Mean = meanVolume(thousand,10);
    million_mean = meanVolume(million,10);






    double thousand_Error = relative_error(thousand_Mean,sphere_Volume(1));
    double million_Error = relative_error(million_mean,sphere_Volume(1));
    // double billion_Error = relative_error(billion_mean,sphere_Volume(1));

    //print on the terminal
    printf("\n For 10 experiences : \n For 1000 points, the mean is  %lf  \n relative error is : %lf %%\n For 1 000 000 points , the mean is %lf %% \n relative error is : %lf %% \n",thousand_Mean,thousand_Error,million_mean,million_Error);
    

    //For 40 Experiences

    //initialization of our tables
    thousand = simSphere_for_mean(1000,40);
    million = simSphere_for_mean(1000000,40);
    // billion = simSphere_for_mean(1000000000,10);



    //calculate the mean of each tables
    thousand_Mean = meanVolume(thousand,40);
    million_mean = meanVolume(million,40);


    //print on terminal
    printf("\n For 40 experience : \n For 1000 points, the mean is %lf  \n relative error is : %lf %%\n For 1 000 000 points , the mean is %lf %% \n relative error is : %lf %% \n",thousand_Mean,thousand_Error,million_mean,million_Error);


    /*----------------------------------------- 3 --------------------------------------*/

    // alpha = 0.01 -> 1- alpha/2 = 99.5 ==> t = 63.66 for 1, t = 3.1693 for 10,t = 2.7045 for 40 =====>t = 3.2498 for 9 and t =2.7079 for 39 cf supagro.fr  with t(n-1,1-alpha/2)

    // we're doing here for n = 40 but you can use it with 10, just change the parameters and update lines on top as comment

    double estimate = estimate_without_bias(thousand,40,thousand_Mean);



   
    //creation of 
    double thousand_R = radius_confidence_interval(2.7079,thousand,40,thousand_Mean);
    double million_R = radius_confidence_interval(2.7079,million,40,million_mean);
    // double billion_R = confidence_interval(2.7079, billion, 40);


    //declaration and initialisation of tables which contains the confidence interval
    double thousand_cf[2] = {thousand_Mean - thousand_R , thousand_Mean + thousand_R};
    double million_cf[2] ={ million_mean -million_R, million_mean + million_R};




    //print on terminal
    printf("\nFor alpha = 0.01, (the confidence interval is 99%%) : [ %lf, %lf] \n" , thousand_cf[0], thousand_cf[1] );
    printf("\nFor alpha = 0.01, (the confidence interval is 99%%) : [ %lf, %lf] \n\n" , million_cf[0], million_cf[1] );


    //liberation of allocated memory
    free(thousand);
    free(million);
    // free(billion);
    return 0;
}