package GtuContainer;
import java.util.Iterator;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
/**
 * A class to test the JavaContainer implementations.
 */
public class ContainerTestClass{
    /**
     * @param args
     */
    public static void main(String args[]) {
        PrintWriter writer = null;
        PrintWriter writer2 = null;
        try{
            JavaVector<String> myVec = new JavaVector<String>();
            JavaVector<Integer> myVec2 = new JavaVector<Integer>(3);
            myVec.add("Hello");
            myVec.add("Second");
            myVec.add("Mehmet");
            myVec2.add(3);
            myVec2.add(6);
            myVec2.add(61);
            myVec2.add(61);
            System.out.printf("Size of the first vector: %d\nSize of the second vector: %d\n\n",myVec.size(),myVec2.size());
            
            System.out.println("Contents of first and second JavaVector: ");
            var itV1 = myVec.getIterator();
            while(itV1.hasNext())
                System.out.printf("%s ",itV1.next());
            System.out.println();
            System.out.println(myVec2.toString());
            System.out.println();

            if(myVec.equals(myVec2))
                System.out.println("Vectors are equal.\n");
            else
                System.out.println("Vectors are not equal.\n");

            myVec.remove("Hello");
            myVec2.remove(6);
            System.out.printf("Contents of first and second JavaVector:\n%s\n%s\n\n",myVec.toString(),myVec2.toString());

            JavaSet<String> mySet = new JavaSet<String>();
            JavaSet<String> mySet2 = new JavaSet<String>();
            mySet.add("me");
            mySet.add("Hello");
            mySet.add("GTU");
            mySet2.add("me");
            mySet2.add("Hello");
            mySet2.add("GTU");
            mySet2.add("GTU");

            System.out.println("Contents of first and second JavaSet: ");
            var itS1 = mySet.getIterator();
            while(itS1.hasNext())
                System.out.printf("%s ",itS1.next());
            System.out.println();
            System.out.println(mySet2.toString());
            System.out.println();

            if(mySet.equals(mySet2))
                System.out.println("Sets are equal.\n");
            else
                System.out.println("Sets are not equal.\n");

            mySet.remove("me");
            mySet2.remove("Hello");
            System.out.printf("Contents of first and second JavaSet:\n%s\n%s\n\n",mySet.toString(),mySet2.toString());

            if(mySet.equals(mySet2))
                System.out.println("Sets are equal.\n");
            else
                System.out.println("Sets are not equal.\n");

            System.out.println("Printing the first JavaSet to JavaSet1.txt and JavaSet2 to JavaSet2.txt.");

            writer = new PrintWriter(new FileWriter("JavaSet1.txt"));
            writer2 = new PrintWriter(new FileWriter("JavaSet2.txt"));
            writer.print(mySet);
            writer2.print(mySet2);

        } catch(IOException e){
            e.printStackTrace();
        } catch(Exception e){
            System.out.println(e.getMessage());
            e.printStackTrace();
        }finally{
            if(writer != null)
                writer.close();
            if(writer2 != null)
                writer2.close();
        }
    }
}