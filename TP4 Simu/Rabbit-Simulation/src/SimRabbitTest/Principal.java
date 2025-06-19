package SimRabbitTest;

import java.util.ArrayList;

/**
 * This class is used to execute the program
 */
public class Principal {


    public static final int SIMULATION_COUNT = 40;
    public static final int TIME_OF_A_SIM = 20;

    /**
     * 
     * @param list a list of int
     * @return the mean of the list in parameters
     */
    public static double mean(ArrayList<Integer> list){
        double result = 0;
        for(Integer e : list){
            result = result + e;
        }

        return ( double) result / (double)list.size();
    }


    /**
     * 

     * @description : Calculate the estimate without bias needed for the   
     *                confidence interval                                      
     * @param list a list of integer
     * @param mean_of_list the mean of the list in parameter                                             
     * @param : a table of values (like values obtained from our generated 
     *            and his lenght and his mean                                
     *                                                                       
     *   @return: the value of the estimate  
     */
    public static double estimateWithoutBias(ArrayList<Integer> list, double mean_of_list) {

        double res_out = 0; //It'll be our result
    
        for (int i = 0; i < list.size(); i++){
    
    
            res_out = res_out + (list.get(i) - mean_of_list)*(list.get(i)- mean_of_list);
        }
    
    
    
        res_out = res_out/ (double)(list.size() -1);
    
        return ( res_out);
    }


    /**
     * 
     *   @brief : Calculate the confidence Interval                          
     *                                                                       
     *                                                                       
     *   @param : 
     *            a table of values and is lenght, and the error margin and  
     *            the mean of the table                                      
     *            if needed check this URL :                                 
     *            https://www.supagro.fr/cnam-lr/statnet/tables.htm#student  
     *                                                                       
     *                                                                       
     *   @return: the value of the Radius needed for confidence Interval  
     */
    public static double radiusConfidenceInterval( double error_margin, ArrayList<Integer> list, double mean_of_list ){
    
        double result_out = 0;
        result_out = estimateWithoutBias(list, mean_of_list);
    
        result_out = result_out /(double)list.size();
        result_out = error_margin * Math.sqrt(result_out);
    
        return result_out;
    
    }







    

/*#############################################################################################*
 *##################################                     ######################################*
 *##################################    Function main    ######################################*
 *##################################                     ######################################*
 *#############################################################################################*/


    public static void main(String[] args) {
        

        /*--------- Initialisation ---------- */

        Time time = new Time();
        ArrayList<Integer> numbersDeadInAllSimulations = new ArrayList<Integer>();
        ArrayList<Integer> numbersAliveInAllSimulations = new ArrayList<Integer>();
        


        /*--------- 1st simulation ---------- */

        for(int i = 0 ; i < SIMULATION_COUNT; i++){
            GroupOfRabbit groupOfRabbit = new GroupOfRabbit();

            while(time.getYear() != TIME_OF_A_SIM){

                groupOfRabbit.beOlders();
                groupOfRabbit.checkIsDying(time);
                groupOfRabbit.removeDead();
                groupOfRabbit.reproduction();
    
    
                time.moveForward();
                
                System.out.println("------------------------------------------");
                System.out.println("Simulation number "+i+" :");
                System.out.println(groupOfRabbit);
                System.out.println(time);
    
                
            }
            numbersDeadInAllSimulations.add(groupOfRabbit.getNumbersDead());
            numbersAliveInAllSimulations.add(groupOfRabbit.getNumberAlive());
            time.reset();
            groupOfRabbit.reset();
            

        }

        /*---------2nd calculate the mean of the experiences ---------- */

        double nbMeanDeads = mean(numbersDeadInAllSimulations);
        double nbMeanAlive = mean(numbersAliveInAllSimulations);

        double estimateNbAlive = estimateWithoutBias(numbersAliveInAllSimulations,nbMeanAlive);
        double estimateNbDead = estimateWithoutBias(numbersDeadInAllSimulations,nbMeanDeads);

        double radAlive = radiusConfidenceInterval(2.7079,numbersAliveInAllSimulations,nbMeanAlive);
        double radDead = radiusConfidenceInterval(2.7079,numbersDeadInAllSimulations, nbMeanDeads);

        double[] borderAlive={nbMeanAlive - radAlive , nbMeanAlive + radAlive};
        double[] borderDead = {nbMeanDeads - radDead , nbMeanDeads + radAlive};

        System.out.println("------------------------------------------");
        System.out.println("------------------------------------------");
        System.out.println("Rabbits alive mean :" + nbMeanAlive);
        System.out.println("Rabbits dead mean : "+ nbMeanDeads);
        
        /*---------3rd calculate the confidence interval for 99% ---------- */
        
        //print the confidence interval but in scientific notation
        System.out.println("Rabbits Alive : For alpha = 0.01, (the confidence interval is 99%%) : [" + borderAlive[0] + ";" + borderAlive[1]+ "]"); 
        System.out.println("Rabbits Dead : For alpha = 0.01, (the confidence interval is 99%%) : [" + borderDead[0] + ";" + borderDead[1]+ "]");
        System.out.println("------------------------------------------");
        




    }
}