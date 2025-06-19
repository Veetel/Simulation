package SimRabbit;

public class Time {

    private int time ; // months passed

    /*------ Constructor -------- */

    /**
     * @description it is the default constructor of Time Object
     */
    public Time()
    {
        this.time = 0;
    }

    /*---------------- Getters ---------- */
    /**
     * @description it is the getter to know what time it is
     * @return which time we are at this moment in this Object
     */
    public int time()
    {
        return this.time ; 
    }

    /**
     * @description Increments the time (+1 month) 
     * @return void
     */
    public void step()
    {
        this.time++;
    }


}
