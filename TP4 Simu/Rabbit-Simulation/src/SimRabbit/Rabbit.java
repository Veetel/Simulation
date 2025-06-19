package SimRabbit;

import java.util.ArrayList;
import java.util.Random; 

enum Sex 
{
    MALE,
    FEMALE;
}

public class Rabbit 
{   
    private int age ; // Maybe it's better to make it a calculated field
    
    // Constants
    private final Sex sex ;
    private final int InstantOfBirth;
    private final Coordonates coordonatesOfBirth;
    
    private final int hashID ;

    private int morbidity ;

    private final Random random ;

    private boolean mature ;

    private Coordonates actualCoordonates ;

    // --------------------------- Constructor ---------------------------

    /**
     * @description it is the default constructor for Rabbit Object
     * 
     * @param inCoordonatesOfBirth is the coordonates where the rabbit spawn
     * @param inInstantOfBirth is the date of birth (in months)
     * @param random is an object needed to randomized the simulation
     * 
     */

    public Rabbit(Coordonates inCoordonatesOfBirth, int inInstantOfBirth, Random random )
    {
        this.age = 0 ;
        this.mature = false ;

        this.InstantOfBirth = inInstantOfBirth ;
        this.coordonatesOfBirth = inCoordonatesOfBirth ;

        this.random = random ;

        this.sex =  random.nextInt(2) == 0 ? Sex.MALE : Sex.FEMALE ;
        this.hashID = this.hashCode() ;
    }

    /**
     * @description redifine hashCode to have an identifier for all rabbits
     * @return int : the "value" of the identifier of the rabbit
     */
    // Hasher redifinition
    @Override
    public int hashCode()
    {
        final int prime = 31 ;
        int result = 1 ;
        result = prime * result + age ;

        // result = prime * result + ((sex == null) ? 0 : this.sex.hashCode()) ;

        result = prime * result + InstantOfBirth ;
        result = prime * result + ((coordonatesOfBirth == null) ? 0 : this.coordonatesOfBirth.hashCode()) ;

        return result ;
    }
    
    // --------------------------- Getters ---------------------------
    /**
     * @description used to know the rabbit's coordonates
     * @return Coordonates: is a coordonates  x/y needed to know where the rabbit is on a 2D map
     */
    public Coordonates actualCoordonates()
    {
        return this.actualCoordonates ;
    }
    
    public int morbidity ()
    {
        return this.morbidity ;
    }

    public int age()
    {
        return this.age;
    }

    public boolean isAlive()
    {
        return this.age != -1 ;
    }
    
    public Sex sex()
    {
        return this.sex ;
    }

    /**
     * @description Get the instant of birth of the rabbit
     * @return 
     */
    public int instantOfBirth()
    {
        return this.InstantOfBirth ;
    }

    /**
     * @description Get the coordonates of birth of the rabbit
     * @return
     */
    public Coordonates coordonatesOfBirth()
    {
        return this.coordonatesOfBirth;
    }
    
    public int hashID()
    {
        return this.hashID ;
    }

    // --------------------------- Behaviar Getters ---------------------------

    /**
     * @descrition validate if the rabbit is adult
     * 
     * @return boolean : true if the rabbit is adult, else return false
     */
    public boolean mature () 
    {   
        if ( this.age() > 5 && this.age() < 8)
        {
            if (random.nextInt(1) % 2 == 0 )
            {
                this.mature = true ;
            }
        } 
        else if ( this.age() == 8 )
        {
            this.mature = true ;
        }

        return this.mature ;
    }

    // --------------------------- Behaviar Methodes ---------------------------

    /**
     * @description kill a rabbit. His age becomes -1 significate it's dead.
     * @param void
     * @return void
     */
    public void kill()
    {
        // Delete the object
        this.age = -1 ;
    } 
   
    /**
     * @description update the age of the rabbit. He get older (+1 month)
     * @param void
     * @return void
     */

    public void update()
    {
        this.age ++ ;

        if (this.mature())
        {
            // if mature then look for a mate to 
        }

        // if 15 years old -> die bitch
        if (this.age() / 12 >= 15) 
        {
            this.kill();
        }
    }

    /**
     * @description look for a partener in a list of rabbits
     * @param ArrayList<Rabbit> rabbits, the rabbit list to look for a partener in 
     * @return the index of the rabbit or -1 if not found
     */
    public int lookForPartener (ArrayList<Rabbit> rabbits)
    {
        // Look for a mate
        for (int i = 0; i < rabbits.size(); i++)
        {
            if ( rabbits.get(i).mature() && !rabbits.get(i).equals(this) )
            {
                return i ;
            }
        }
        return -1 ;
    }

}
