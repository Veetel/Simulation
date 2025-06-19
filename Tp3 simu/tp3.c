#include <stdio.h>
#include <math.h>
#include <stdlib.h>





/*###############################################################################*
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *                                                                               *
 *###############################################################################*/



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

double norm(double x, double y, double z){
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

 double sphere_Volume(double radius){
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

 int Sphere_Volume_MonteCarlo_Precised(double inPrecision){
    int isInSphere = 0;
    int nbOfGeneratedPoints = 0;
    int x;


    double SphereVolume = (sphere_Volume(1)); 
    double VolumeGenerated  = 1;
    double precisionGotten = 1;
    
    while(  precisionGotten >= inPrecision ){

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
    
        x = VolumeGenerated / inPrecision;
        VolumeGenerated = x *inPrecision;
        
        
        precisionGotten =  fabs(VolumeGenerated - SphereVolume);
        printf(" Volume generated %f \n",VolumeGenerated);
        printf(" précision actuelle :%f \n",precisionGotten);
    }
    
    return nbOfGeneratedPoints;
}


/*############################# Function main ##########################*/


int main(int argc, char * argv[]){

    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);



    printf("Volume Sphere for 1000 points : %lf \n", Sphere_Volume_MonteCarlo(1000));
    // printf("Volume Sphere for 174700 points: %lf \n", Sphere_Volume_MonteCarlo(174700));
    // printf("Volume Sphere for 1 000 000 points : %f \n", Sphere_Volume_MonteCarlo(1000000) );
    // printf("Volume Sphere for 1 000 000 000 points : %f \n", Sphere_Volume_MonteCarlo(1000000000));
    printf("Real Volume Sphere  : %f \n ", sphere_Volume(1));

    printf("%f \n \n", Sphere_Volume_MonteCarlo(529));
    // printf("Number iterations : %d \n ", Sphere_Volume_MonteCarlo_Precised(0.001));
    





    return 0;
}