package SimRabbitTest;

/**
 * @author Largeron Jean-Baptiste and Elnasory Karam
 * 
 * @description
 *  This class manages the time for simulation because simulation is experiences plonged in the time
 * 
 * 
 */

public class Time {

    private int month =0;
    



    /*-----------------------------Getters / setters ----------------------------- */
    /**
     * 
     * @return the number of month passed
     */
    public int getMonth() {
        return month;
    }






    /**
     * 
     * @return the number of year passed
     */
    public int getYear(){
        return this.month/12;
    }




    /*----------------------------- Methods ----------------------------- */


    /**
     * move forward the time by 1 month
     */
    public void moveForward(){
        this.month +=1;

    }
    





    /**
     * @description
     * reset the time to 0
     */
    public void reset(){
        this.month = 0;
    }
    




    @Override
    public String toString() {
        return String.format("Time passed :%d (%d years)", this.getMonth(), this.getYear());
    };
}
