import java.util.Scanner;

public class CustomerTrackingSystem{
    public static void main(String args[]){
        Order[] Orders = new Order[100];
        Customer[] Customers = new Customer[100];
        Operator[] Operators = new Operator[100];

        //Initializing the arrays with contents from txt file
        FileReader.InitializeArrays(Orders, Customers, Operators);
        
        Scanner scanner = new Scanner(System.in);
        try{
            System.out.println("Please enter your ID... ");
            int searchID = scanner.nextInt();
            int customerCount = 0,operatorCount = 0;

            int foundID = 0;
            while(Customers[customerCount]!=null){
                if(Customers[customerCount].getID() == searchID){
                    System.out.println("*** Customer Screen ***");
                    Customers[customerCount].print_customer();
                    Customers[customerCount].print_orders();
                    foundID = 1;
                    break;
                }
                ++customerCount;
            } if(foundID == 0) {
            while(Operators[operatorCount] != null){
                if(Operators[operatorCount].getID() == searchID){
                    System.out.println("*** Operator Screen ***");
                    System.out.println("---------------------------- ");
                    Operators[operatorCount].print_operator();
                    System.out.println("---------------------------- ");
                    Operators[operatorCount].print_customers();
                    foundID = 1;
                    break;
                }
                ++operatorCount;
            }
            }

            if(foundID == 0) System.out.println("No Customer/Operator was found with ID " + searchID + ". Please try again.");
        } catch(Exception e){
            System.out.println("Not a valid input, terminating the program");
        }
        scanner.close();
    }
}
