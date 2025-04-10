import java.util.Scanner;


public class InventoryTest {
    public static void main(String[] args) {
        Inventory inventory = new Inventory();
        Scanner scanner = new Scanner(System.in);
        int choice;

        System.out.println("Welcome to the Arasaka Corporation Inventory Management System!");
        
        do{
            try{
                inventory.printMenu();
                System.out.print("Enter your choice: ");
                choice = scanner.nextInt();
                scanner.nextLine();  
            }catch(Exception e){
                scanner.nextLine();
                choice = -1;
            }        

            switch(choice){
                case 1:
                    addDevice(inventory, scanner);
                    break;
                case 2:
                    removeDevice(inventory, scanner);
                    break;
                case 3:
                    updateDevice(inventory, scanner);
                    break;
                case 4:
                    inventory.listDevices();
                    break;
                case 5:
                    System.out.println("Cheapest Device: " + inventory.findCheapest());
                    break;
                case 6:
                    inventory.sortByPrice();
                    break;
                case 7:
                    System.out.println("Total Inventory Value: " + inventory.totalInventoryValue());
                    break;
                case 8:
                    restockDevice(inventory, scanner);
                    break;
                case 9:
                    inventory.exportInventoryReport();
                    break;
                case 0:
                    System.out.println("Exiting Inventory Management System...");
                    break;
                default:
                    System.out.println("Invalid Choice");
            }
        }while(choice != 0);

        scanner.close();
    }

    private static void addDevice(Inventory inventory, Scanner scanner){
        try{
            System.out.print("Enter the category of the device: ");
            String category = scanner.nextLine();
            System.out.print("Enter the name of the device: ");
            String name = scanner.nextLine();
            System.out.print("Enter the price of the device: ");
            double price = scanner.nextDouble();
            System.out.print("Enter the quantity of the device: ");
            int quantity = scanner.nextInt();

            scanner.nextLine();

            inventory.addDevice(category, name, price, quantity);
        }catch(Exception e){
            System.out.println("Invalid Input");
            scanner.nextLine();
            return;
        }
    }

    private static void removeDevice(Inventory inventory, Scanner scanner){
        try{
            System.out.print("Enter the name of the device to remove: ");
            String removeName = scanner.nextLine();
            if(inventory.removeDevice(removeName) == null)
                System.out.println("Device Not Found");
            else 
                System.out.println(removeName + " removed from inventory");
        }catch(Exception e){
            System.out.println("Invalid Input");
            scanner.nextLine();
            return;
        }
    }

    private static void updateDevice(Inventory inventory, Scanner scanner){
        try{
            System.out.print("Enter the name of the device to update: ");
            String updateName = scanner.nextLine();
            System.out.print("Enter the new price of the device: ");
            double newPrice = scanner.nextDouble();
            System.out.print("Enter the new quantity of the device: ");
            int newQuantity = scanner.nextInt();
            scanner.nextLine();

            if(inventory.updateDevice(updateName, newPrice, newQuantity))
                System.out.println(updateName + " details updated: " +"Price: " + newPrice + ", Quantity: " + newQuantity);
        }catch(Exception e){
            System.out.println("Invalid Input");
            scanner.nextLine();
            return;
        }
    }

    private static void restockDevice(Inventory inventory, Scanner scanner){
        try{
            System.out.print("Enter the name of the device to restock: ");
            String restockName = scanner.nextLine();
            System.out.print("Do you want to add or remove stock? (Add/Remove): ");
            String restockChoice = scanner.nextLine();
            boolean addOrRemove;
            if(restockChoice.equals("Add")){
                addOrRemove = true;
                System.out.print("Enter the quantity to add: ");
            }
            else if(restockChoice.equals("Remove")){
                addOrRemove = false;
                System.out.print("Enter the quantity to remove: ");
            }
            else{
                System.out.println("Invalid Choice");
                return;
            }

            int restockQuantity = scanner.nextInt();

            inventory.restockDevice(restockName, restockQuantity, addOrRemove);
        }catch(Exception e){
            System.out.println("Invalid Input");
            scanner.nextLine();
            return;
        }
    }
}
