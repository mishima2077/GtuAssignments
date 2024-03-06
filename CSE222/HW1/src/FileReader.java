import java.io.File;
import java.util.Scanner;

//A class to read the content.txt file and initialize the arrays
public class FileReader{
    private static String fileName = "src/content.txt";

    //This function reads the content.txt file and initializes the arrays with the contents
    public static void InitializeArrays(Order[] Orders, Customer[] Customers, Operator[] Operators){
        try{
            File Contents = new File(fileName);
            Scanner scanner = new Scanner(Contents);
            int order_count = 0, customer_count = 0, operator_count = 0;

            String CurrentLine;
            String[] LineSeperated;

            while(scanner.hasNextLine()){
                CurrentLine = scanner.nextLine();
                LineSeperated = CurrentLine.split(";",-1);

                switch(LineSeperated[0]){
                    case "order":
                        if(OrderReader(Orders, order_count, LineSeperated) == 1)
                            ++order_count;
                        break;
                    case "retail_customer":
                    case "corporate_customer":
                        if(CustomerReader(Customers, customer_count, LineSeperated) == 1)
                            ++customer_count;
                        break;
                    case "operator":
                        if(OperatorReader(Operators, operator_count, Customers, customer_count, LineSeperated) == 1)
                            ++operator_count;
                        break;
                    default:
                }
            }

            //Initializing the Customers and Orders arrays
            for(int i = 0; i < customer_count; ++i)
                Customers[i].define_orders(Orders);
            for(int i = 0; i < operator_count; ++i)
                Operators[i].define_customers(Customers);

            scanner.close();
        } catch(Exception e) {
            System.out.println("Couldn't open the file");
        }
    }

    //All of the reader functions below returns 1 if the line is readed correctly, 0 if there was an exception
    //I could have used boolean, but the homework pdf prevented me from using it
    private static int OrderReader(Order[] Orders, int arrSize, String[] Vals){
        try{
            if (Vals.length != 6)
                throw new Exception("Element count is invalid");
            if (Vals[1].length() < 1)
                throw new Exception("String size less then 1");

            String product_name = Vals[1];
            int count = Integer.parseInt(Vals[2]), total_price = Integer.parseInt(Vals[3]);
            int status = Integer.parseInt(Vals[4]), customer_id = Integer.parseInt(Vals[5]);
            if(count < 1 || total_price < 1 || customer_id < 1)
                throw new Exception("Integers can't be negative");
            if(status < 0 || status > 3)
                throw new Exception("Invalid status value");

            Orders[arrSize] = new Order(product_name, count, total_price, status, customer_id);
            return 1;
        } catch(Exception e) {
            return 0;
        }
    }

    private static int CustomerReader(Customer[] Customers, int arrSize, String[] Vals){
        try{
            String customer_type;
            if(Vals[0].equals("retail_customer")) customer_type = "r";
            else customer_type = "c";
            if((customer_type.equals("r") && Vals.length != 7)||(customer_type.equals("c") && Vals.length != 8))
                throw new Exception("Element count is invalid");
            if(Vals[1].length() < 1 || Vals[2].length() < 1 || Vals[3].length() < 1 || Vals[4].length() < 1 || (customer_type.equals("c") && Vals[7].length() < 1))
                throw new Exception("String size less then 1");

            String name = Vals[1], surname = Vals[2], address = Vals[3], phone = Vals[4];

            int ID = Integer.parseInt(Vals[5]);
            if(ID < 1) throw new Exception("ID can't be negative");
            if(idExists(Customers, arrSize, ID) == 1) throw new Exception("ID already exists");

            int operator_ID = Integer.parseInt(Vals[6]);
            if(operator_ID < 1) throw new Exception("ID can't be negative");

            if(customer_type.equals("r"))
                Customers[arrSize] = new RetailCustomer(name, surname, address, phone, ID, operator_ID);
            else{
                String company_name = Vals[7];
                Customers[arrSize] = new CorporateCustomer(name, surname, address, phone, ID, operator_ID, company_name);
            }
            return 1;
        } catch(Exception e) {
            return 0;
        }
    }

    private static int OperatorReader(Operator[] Operators, int operatorSize, Customer[] Customers, int customerSize, String[] Vals){
        try{
            if(Vals.length != 7)
                throw new Exception("Element count is invalid");
            if(Vals[1].length() < 1 || Vals[2].length() < 1 || Vals[3].length() < 1 || Vals[4].length() < 1)
                throw new Exception("String size less then 1");

            String name = Vals[1], surname = Vals[2], address = Vals[3], phone = Vals[4];
        
            int ID = Integer.parseInt(Vals[5]);
            if(ID < 1) throw new Exception("ID can't be negative");
            if(idExists(Operators, operatorSize, ID) == 1 || idExists(Customers, customerSize, ID) == 1) 
                throw new Exception("ID already exists");


            int wage = Integer.parseInt(Vals[6]);
            if(wage < 1) throw new Exception("Wage can't be negative");

            Operators[operatorSize] = new Operator(name, surname, address, phone, ID, wage);
            return 1;
        } catch(Exception e) {
            return 0;
        }
    }

    //This function checks if the ID exists in the array
    private static int idExists(Person[] arr, int arrSize, int ID){
        for(int i = 0; i < arrSize; ++i)
            if(arr[i].getID() == ID)
                return 1;
        return 0;
    }
}
