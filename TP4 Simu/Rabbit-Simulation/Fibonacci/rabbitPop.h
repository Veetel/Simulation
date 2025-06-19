a#ifndef H_RABBIT_POP
#define H_RABBIT_POP


typedef struct {
    double nb_Rabbit_Adult;
    double nb_Rabbit_Enfant;
}rabbitPop;



rabbitPop fibonacci(int nb_of_time,rabbitPop population_of_rabbit);

#endif