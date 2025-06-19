package SimRabbitTest;





/**
 * @description 
 * This class is a generator for rabbits. (Final version implements Mersenne Twistter Random generator written by David Beaumont a French developper, 
 * you can find his git here : https://github.com/hagbard 
 * or in this link : https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/VERSIONS/JAVA/java.html )
 */
public class Generator {

    private int age = 0;
    private MTRandom random ;
    private double mortality ;
    
/**
 * @description
 * the constructor for rabbits
 * @important the mortality is a float but it is a percentage, if you set it be careful to 0 <= mortality <= 100
 */
    public Generator(){
        this.age = 0;
        this.random = new MTRandom(true);
        this.mortality =5.46; // /!\ it is a percentage
        //Mortality(year) = 65%
        //Survival(year) = 35%
        //Survival(month) = 0.35 ^ (1/12) --> equivalent of 0.9454
        //Mortality(month) = 1- Survival(month) --->equivalent of 0.0546 = 5.46%
    }
    







/*-------------------------Getters / Setters ----------------------------- */



    /**
     * @description
     * set the age of the rabbit
     * @param age is an integer, represents his age in month , don't be too greedy and don't set it over than 15 years (180 months)
     */

    public void setAge(int age) {
        this.age = age;
        
    }





    /**
     * @description
     * Set the mortality of a rabbit
     * @param mortality is a float for a percent
     * @important if you set it be careful to 0 <= mortality <= 1
     */
    public void setMortality(double mortality) {
        this.mortality = mortality;
    }







    /**
     * @description
     * Use a rabbit instance to set the mortality
     * @param rabbit is an instance of rabbit object
     */

    public void setMortalityAndAge(Rabbit rabbit){
        setAge(rabbit.getAge());
        if(this.age == 15){
            this.age = -1;
        }
        if(this.age >=10*12){
            this.mortality += 10;
        }
        else if(rabbit.getMaturity() == 1){
            this.mortality = 4.56;//see attributes to know how i did this
        }
    }






    /**
     * @description
     * Used to get an random number in [0;100]
     * @return an integer in [0;100]
     */
    public int getRandom() {
        return random.nextInt(100);
    }




    /*--------------------------------- Methods ---------------------------------- */

    /**
     * @description
     * Check if the rabbit dies, if he dies return the rabbit with special argument to be trated in GroupOfRabbit
     * @param rabbit take an instance of rabbit
     * @return return the rabbit
     */
    public Rabbit isDying(Rabbit rabbit){

        setMortalityAndAge(rabbit);

        if (random.nextInt(100) <= mortality){
            rabbit.setAge(-1);
        }

        return rabbit;

    }







    /**
     * @description check if the rabbit is mature, need a object rabbit to change his status here we force the Gaussian to be sure 
     * it s what was required by the guidelines
     * 
     * @param  rabbit rabbit is a Rabbit object used to initiate the age of the rabbit object to generate change the rabbit stats if needed
     * @return rabbit after beeing changed if needed
     */
    public Rabbit isMature(Rabbit rabbit){
        setAge(rabbit.getAge());
        if (this.age == 8  ){

            rabbit.setMaturity(1);

        }
        int p =0;//probabilité
        if(this.age == 5 ||this.age == 7){
            p = 25;
            
        }
        if(this.age == 6 ||this.age == 6){
            p = 50;
            
        }


        if(this.getRandom() < p){
            rabbit.setMaturity(1);
            
        }

        return(rabbit);
    }
    
}