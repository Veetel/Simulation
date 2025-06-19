package SimRabbitTest;

public class Rabbit {
    
    private int age;
    private int maturity;
    private int nbOfLitter;

    public Rabbit(int a,int matur){
        this.age = a;
        this.maturity = matur;
    }


    public Rabbit(){
        this.age =0;
        this.maturity = 0 ;
        this.nbOfLitter = 0;
    }




/*----------------------- Getters / Setters ----------------------------*/


    /**
     * get the number of litters a female rabbit did in 1 year (starting from the first litter)
     * @return nbOfLitter is the number of Litter a female rabbit did in 1 year
     */
    public int getNbOfLitter() {
        return nbOfLitter;
    }


    /**
     * method to set the number of litters a rabbit did
     * @param nbOfLitter is a int need to set the nbOfLitter
     */
    public void setNbOfLitter(int nbOfLitter) {
        this.nbOfLitter = nbOfLitter;
    }


    /**
     * increase the number of litter a rabbit females did
     */
    public void increaseNbOfLitter(){
        this.nbOfLitter += 1;
    }

    /**
     * set the age of the rabbit
     * @param age is the age you want to set
     */
    public void setAge(int age) {
        this.age = age;
    }

    public void beOlder(){
        this.age += 1;
    }
    /**
     * Set the maturity
     * @param maturity is 0 if non mature else 1
     */
    public void setMaturity(int maturity) {
        this.maturity = maturity;
    }

    /**
     * 
     * @return age is the age of the rabbit
     */
    public int getAge() {
        return age;
    }
    /**
     * method used to know the maturity of a rabbit
     * @return maturity =1 if mature else 0
     */
    public int getMaturity() {
        return maturity;
    }

    


    






/*--------------------------- Methods -------------------------------------------- */

    /**
     * use the random generator of the object rabbit to check if the rabbit is mature and
     * if it is true, set the maturity to 1
     * @param rabbit is an instance of rabbit
     */
    public void verrifyMaturity(Generator rabbit){

        if (this.age == 9  ){
            this.maturity = 1;


        }
        int p =0;
        if(this.age == 5 ||this.age == 8){
            p = 25;
            
        }
        if(this.age == 6 ||this.age == 7){
            p = 50;
            
        }


        if(rabbit.getRandom() < p){
            this.maturity = 1;
        }
    }



    public boolean isFemale(Generator generator){
        return(generator.getRandom()%2 == 1 );
    }
}
