package SimRabbit;

/**
 * 
 * @author Largeron Jean-Baptiste and Elnasory Karam
 * 
 * @description 
 * The Cezeau class is meant to be a world that hostes the simulation having the notion of time 
 */

import java.util.ArrayList;
import java.util.LinkedList;

public class Cezeaux
{
    // Statistics

    private double numberAlive;
    private double numberDead;
    private double numberBirth;

    // Time counter

    private final Time time ;

    // Space 

    private LinkedList<Rabbit> MaleRabbits ; 
    private LinkedList<Rabbit> FemaleRabbits ;

    private int foodCount ; 

    // Random generator

    private final MTRandom random ;

    /*-------------------------------- Constructor ---------------------------------- */

    /**
     * @description default constructor
     * @return   initialize a instance
     */
    public Cezeaux(MTRandom random)
    {
        this.numberBirth = 0 ;
        this.numberDead = 0 ;

        this.time = new Time() ;

        this.MaleRabbits = new LinkedList<Rabbit>();
        this.FemaleRabbits = new LinkedList<Rabbit>();

        this.foodCount = 0 ;

        this.numberAlive = MaleRabbits.size() + FemaleRabbits.size();

        this.random = random ;

        for (int i = 0 ; i < 10 ; i++)
        {
            Rabbit newRabbit = new Rabbit(new Coordonates(0, 0), this.time.time(), this.random);
            this.MaleRabbits.add(newRabbit);
        }
    }

    /**
     * @description          The method initialize an instance of Cezeaux from a list of rabbits
     * @param  listOfRabbits is a list of rabbits instances. 
     * @return               return an instance of Ceseaux
     */
    public Cezeaux(ArrayList<Rabbit> listOfRabbits)
    {
        this.random = new MTRandom();

        this.MaleRabbits = new LinkedList<Rabbit>();
        this.FemaleRabbits = new LinkedList<Rabbit>();

        this.foodCount = 0 ;

        for (int i = 0 ; i < listOfRabbits.size() ; i++)
        {
            if(listOfRabbits.get(i).sex() == Sex.MALE)
            {
                this.MaleRabbits.add(listOfRabbits.get(i));
            }
            else
            {
                this.FemaleRabbits.add(listOfRabbits.get(i));
            }
        }

        this.numberBirth = 0;
        this.numberDead = 0;

        this.time = new Time() ;
        this.numberAlive = FemaleRabbits.size() + MaleRabbits.size();
    }

    /*-------------------------------- Getter/Setter ---------------------------------- */

    /**
     * @description Get numbers months passed
     * @return      return number of months passed
     */
    public int getNumberMonth()
    {
        return this.time.time() ;
    }

    /**
     * @description get how many rabbits died since the start of the simulation
     * @return      return the number of rabbits dead
     */
    public double getNumberDead()
    {
        return this.numberDead;
    }

    /**
     * @description get how many rabbits were born since the start of the simulation
     * @return      return the number of rabbits born
     */
    public double getNumberBirth()
    {
        return this.numberBirth;
    }

    /**
     * @description get the number of rabbits
     * @return      return the number of rabbits alive
     */
    public double getNumberAlive()
    {
        return this.numberAlive;
    }


    /**
     * @description Get the food count
     * @return      return food count
     */
    public int foodCount ()
    {
        return this.foodCount ;
    }


    /**
     * @description   add a Rabbit object to the Cezeaux world
     * @param  rabbit is the rabbit to add
     */

    public void addRabbit (Rabbit rabbit)
    {
        if(rabbit.sex() == Sex.MALE)
        {
            this.MaleRabbits.add(rabbit);
        }
        else
        {
            this.FemaleRabbits.add(rabbit);
        }
    }

    /*-------------------------------- Methods ------------------------------------ */

    @Override
    public String toString() 
    {   
        StringBuilder str = new StringBuilder();

        str.append("Number of months passed: " + this.time.time() + "\n");
        str.append("Number of rabbits alive: " + this.numberAlive + "\n");
        str.append("Number of birth since simulation started : " + this.numberBirth + "\n");
        str.append("Number of rabbits dead: " + this.numberDead + "\n");

        return str.toString();
    }

    /**
     * @description move the Cezeau world forward in time (1 month)
     */
    public void update()
    {
        this.time.step() ;

        // generer de nouveaux lapins et les stocker dans le tableau
        for (int i = 0 ; i < this.FemaleRabbits.size() ; i++)
        {
            if(this.FemaleRabbits.get(i).mature() == true)
            {
                int rabbitIndex = this.FemaleRabbits.get(i).lookForPartener(this.MaleRabbits);

                if(rabbitIndex != -1)
                {   
                    Rabbit newRabbit = new Rabbit(this.FemaleRabbits.get(i).actualCoordonates(),  this.time.time(), this.random);
                    
                    if(newRabbit.sex() == Sex.FEMALE)
                    {
                        this.FemaleRabbits.add(newRabbit);
                    }
                    else
                    {
                        this.MaleRabbits.add(newRabbit);
                    }

                    this.numberBirth ++ ;
                }
            }
        }

        // pour chaque lapin faire update()

        for (int i = 0 ; i < this.MaleRabbits.size() ; i++)
        {   
            if(this.MaleRabbits.get(i).age() == -1)
            {
                this.MaleRabbits.remove(i);
                this.numberDead ++ ;
            }
            else 
            {
                this.MaleRabbits.get(i).update();
            }
        }

        for (int i = 0 ; i < this.FemaleRabbits.size() ; i++)
        {   
            if(this.FemaleRabbits.get(i).age() == -1)
            {
                this.FemaleRabbits.remove(i);
                this.numberDead ++ ;
            }
            else 
            {
                this.FemaleRabbits.get(i).update();
            }
        }

        if (this.foodCount() < (this.FemaleRabbits.size() + this.MaleRabbits.size()))
        {
            // Determine how many rabbits to kill
            int numToKill = this.FemaleRabbits.size() + this.MaleRabbits.size() ;

            // Randomly chose rabbits to kill because of famine
            for ( int i = 0 ; i < numToKill ; i +=2 )
            {
                // Choose a random rabbit to kill
                int choice = (int) ( this.random.nextInt(0, 1) * (this.FemaleRabbits.size()) )  ;
                this.FemaleRabbits.get(choice).kill(); ;

                choice = (int) ( this.random.nextInt(0, 1) * (this.MaleRabbits.size()) )  ;
                this.MaleRabbits.get(choice).kill() ;
            }

        } 
        else 
        {
            // Remove the food 
            this.foodCount -= this.FemaleRabbits.size() + this.MaleRabbits.size() ;
        }

        // update the statistics about alive rabbits
        this.numberAlive = this.FemaleRabbits.size() + this.MaleRabbits.size() ;

        // readd some food for the next iteration 
        this.foodCount = (int) (( this.MaleRabbits.size() + this.FemaleRabbits.size() ) * 0.9) + this.random.nextInt() ;
    }

    /**
     * @description update move forward the time of a number of months in parameter
     * @param  numberMonths is the number of months you want to move forward
     */
    public void simulate( int numberMonths )
    {
        for(int i = 0; i < numberMonths; i++)
        {
            update();
        }
    }
    
    public static void main (String[] args)
    {   
        MTRandom random = new MTRandom();

        Cezeaux world = new Cezeaux(random);

        for (int i = 0 ; i < 10 ; i++)
        {
            world.addRabbit(new Rabbit(new Coordonates(0, 0), 0, random));
        }
        
        System.out.println(world.toString());

        world.simulate(12 * 20);
        System.out.println(world.toString());
    }
}