package SimRabbit;

public class Coordonates {
    private final int x_axes;
    private final int y_axes;

    //TODO : implement a space limit notion and move function

    /*--------------------------- getters ----------------------------------------- */  

    /**
     * @description it is the getter of the x axes
     * @return the value in x axes
     */
    public int x() 
    {
        return this.x_axes;
    }

    /**
     * @description it is the getter of the y axes
     * @return the value in y axes
     */
    public int y()
    {
        return this.y_axes;
    }

    /**
     * @descritption it is the constructor of Coordonates Object
     * @param inXAxes is the X axes value
     * @param inYAxes is the Y axes value
     * 
     */
    public Coordonates(int inXAxes, int inYAxes)
    {   
        this.x_axes = inXAxes;
        this.y_axes = inYAxes;
    }

    /*----------------------- Overrided Method ------------------------------- */
    @Override
    public String toString()
    {
        return String.format("({}, {})", this.x(), this.y());
    }

    @Override
    public int hashCode() 
    {
        // A good practice is to use a prime number as a multiplier
        int prime = 31;
        int result = 1;
        result = prime * result + this.x();
        result = prime * result + this.y();
        return result;
    }

    @Override
    public boolean equals(Object obj) 
    {
        if (this == obj) 
        {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) 
        {
            return false;
        }
        Coordonates other = (Coordonates) obj;

        return this.x() == other.x() && this.y() == other.y();
    }
}
