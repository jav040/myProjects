import java.util.Scanner; 
public class q4
{

    public static void main(String[] args)
    {
            
        Scanner input = new Scanner(System.in);
        System.out.println("enter string");
        String testWord = input.nextLine();
        int[] table = getFrequency(testWord);
       // boolean result = isMaxOdd(table);


    }


    static int[] getFrequency(String input)
    {

        int charNum = Character.getNumericValue(c);
        int lowBound = Character.getNumericValue('a');
        int upBound = Character.getNumericValue('z');
		int[] example = new int[upBound - lowBound + 1];
        
		for(char c : input.toCharArray())
        {
         // System.out.println("the lower bound is : " + lowBound);
         // System.out.println("the caps low bound is: " + Character.getNumericValue('A'));
         // System.out.println("the upper bound is : " + upBound);
         // System.out.println("the caps upper bound is: " + Character.getNumericValue('Z'));
        }
		return example;
    }





}
