import java.util.LinkedList;
import java.util.ArrayList;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Inventory class to manage the devices in the inventory
 * 
 * The inventory contains devices of the following categories:
 * - Headphone
 * - Keyboard
 * - Laptop
 * - Smart Phone
 * - TV
 */
public class Inventory {
    private LinkedList<ArrayList<Device>> theData;

    /**
     * Categories that are allowed in the inventory
     */
    private static final String[] Categories = {"Headphone","Keyboard","Laptop","Smart Phone","TV"};

    /**
     * Checks if the given category is valid
     * 
     * Complexity: O(5) = O(1) (since the number of categories is fixed)
     * @param element the category to check
     * @return the index of the category if it is valid, -1 otherwise
     */
    private static int checkCategory(String element){
        for(int i = 0; i < Categories.length; ++i)
            if(Categories[i].equals(element))
                return i;

        return -1;
    }

    /**
     * Constructs an Inventory object
     * 
     * Complexity: O(5) = O(1) (since the number of categories is fixed)
     */
    public Inventory(){
        theData = new LinkedList<ArrayList<Device>>();
        ArrayList<Device> Node;
        for(int i = 0; i < Categories.length; ++i){
            Node = new ArrayList<Device>();
            theData.add(Node);
        }

        // Adding some initial devices
        addDevice("Headphone", "Sony WH-1000XM4", 349.99, 10);
        addDevice("Keyboard", "Razer BlackWidow Elite", 129.99, 5);
        addDevice("Laptop", "Apple MacBook Pro", 1299.99, 3);
        addDevice("Smart Phone", "Apple iPhone 12", 799.99, 7);
        addDevice("TV", "Samsung Q90T", 1499.99, 2);        
        addDevice("Headphone", "Sony WH-1000XM3", 249.99, 5);
        addDevice("Keyboard", "Logitech G Pro X", 149.99, 3);
        addDevice("Laptop", "Dell XPS 13", 999.99, 4);
        addDevice("Smart Phone", "Samsung Galaxy S21", 999.99, 6);
        addDevice("TV", "LG CX", 1999.99, 1);
    }

    /**
     * Adds a new device to the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: 5(category check) + n(device name check) + 1(adding the new device to end of the array)
     *           = O(n + 6) = O(n)
     * 
     * @param categoryName the category of the device
     * @param deviceName the name of the device
     * @param price the price of the device
     * @param quantity the quantity of the device
     * @return true if the device is added successfully, false otherwise
     */
    public boolean addDevice(String categoryName, String deviceName, double price, int quantity){
        int index = checkCategory(categoryName);

        if(index == -1){
            System.out.println("Invalid Category");
            return false;
        }

        ArrayList<Device> temp = theData.get(index);
        if(findDeviceByName(deviceName) != null){
            System.out.println("Device Already Exists");
            return false;
        }

        try{
            switch(index){
                case 0:
                    temp.add(new Headphone(deviceName, price, quantity));
                    break;
                case 1:
                    temp.add(new Keyboard(deviceName, price, quantity));
                    break;
                case 2:
                    temp.add(new Laptop(deviceName, price, quantity));
                    break;
                case 3:
                    temp.add(new SmartPhone(deviceName, price, quantity));
                    break;
                case 4:
                    temp.add(new TV(deviceName, price, quantity));
                    break;
            }
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
            return false;
        }catch(Exception e){
            System.out.println("Invalid Input");
            return false;
        }

        return true;
    }

    /**
     * Removes a device from the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: n(device name check) + n(removing the device from the array)
     *          = O(2n) = O(n)
     * @param deviceName
     * @return
     */
    public Device removeDevice(String deviceName){
        Device res = null;

        for(ArrayList<Device> i : theData){
            for(Device j : i){
                if(j.getName().equals(deviceName)){
                    res = j;
                    i.remove(j);
                    break;
                }
            }
        }

        return res;
    }

    /**
     * Updates the details of a device
     * 
     * (n is the number of devices in the inventory)
     * Complexity: n(device name check) + 1(updating the device details)
     *          = O(n + 1) = O(n)
     * 
     * @param deviceName Name of the device to update
     * @param price New price of the device
     * @param quantity New quantity of the device
     * @return true if the device is updated successfully, false otherwise
     */
    public boolean updateDevice(String deviceName, double price, int quantity){
        Device temp = findDeviceByName(deviceName);

        if(temp == null){
            System.out.println("Device Not Found");
            return false;
        }

        try{
            temp.setPrice(price);
            temp.setQuantity(quantity);
        } catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
            return false;
        }

        return true;
    }

    /**
     * Lists all the devices in the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: O(n)
     */
    public void listDevices(){
        System.out.println("\nDevices in Inventory:");

        int count = 1;
        for(ArrayList<Device> i : theData){
            for(Device j : i){
                System.out.print(count++);
                System.out.println(". " + j);
            }
        }
        System.out.println();
    }

    /**
     * Finds the cheapest device in the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: O(n)
     * 
     * @return the cheapest device
     */
    public Device findCheapest(){
        Device temp = null;
        double min = Double.MAX_VALUE;
        
        for(ArrayList<Device> i : theData){
            for(Device j : i){
                if(j.getPrice() < min){
                    min = j.getPrice();
                    temp = j;
                }
            }
        }

        return temp;
    }

    /**
     * Sorts the devices in the inventory by price
     * 
     * (n is the number of devices in the inventory)
     * Complexity: n(adding all devices to a single list) + n*logn(sorting the list) + n(printing the list)
     *            = O(n*logn + 2n) = O(n*logn)
     */
    public void sortByPrice(){
        ArrayList<Device> allLists = new ArrayList<Device>();
        for(ArrayList<Device> i : theData){
            for(Device j : i){
                allLists.add(j);
            }
        }

        allLists.sort(null);
        System.out.println("Devices Sorted by Price:");
        for(int i = 0; i < allLists.size(); ++i){
            System.out.print(i+1);
            System.out.println(". " + allLists.get(i));
        }
    }

    /**
     * Calculates the total value of the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: O(n)
     * 
     * @return the total value of the inventory
     */
    public double totalInventoryValue(){
        double total = 0.0;
        for(ArrayList<Device> i : theData){
            for(Device j : i){
                total += j.getPrice() * j.getQuantity();
            }
        }

        return total;
    }

    /**
     * Restocks a device in the inventory
     * 
     * (n is the number of devices in the inventory)
     * Complexity: n(device name check) + 1(restocking the device)
     *          = O(n + 1) = O(n)
     * 
     * @param deviceName Name of the device to restock
     * @param quantity Quantity to restock
     * @param add true if the quantity is to be added, false if it is to be subtracted
     * @return true if the device is restocked successfully, false otherwise
     */
    public boolean restockDevice(String deviceName, int quantity, boolean add){
        Device temp = findDeviceByName(deviceName);

        if(temp == null){
            System.out.println("Device Not Found");
            return false;
        }

        try{
            if(add)
                temp.setQuantity(temp.getQuantity() + quantity);
            else
                temp.setQuantity(temp.getQuantity() - quantity);
            
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
            return false;
        }catch(Exception e){
            System.out.println("Invalid Input");
            return false;
        }

        return true;
    }

    /**
     * Exports the inventory report to a file
     * 
     * (n is the number of devices in the inventory)
     * Complexity: O(n)
     */
    public void exportInventoryReport(){
        try {
            FileWriter writer = new FileWriter("export.txt");
            writer.write("Arasaka Corporation Inventory Report\n");
            writer.write("Generated on: ");
            writer.write(java.time.LocalDate.now().toString() + "\n\n");

            writer.write("----------------------------------------\n");
            writer.write("| No. | Category | Name | Price | Quantity |\n");
            writer.write("----------------------------------------\n");

            int count = 1;
            for(ArrayList<Device> i : theData){
                for(Device j : i){
                    writer.write("| " + count + " | " + j.getCategory() + " | " + j.getName() + " | " + j.getPrice() + " | " + j.getQuantity() + " |\n");
                    count++;
                }
            }

            writer.write("----------------------------------------\n");

            writer.write("Summary:\n");
            writer.write("-Total Devices: " + (count-1) + "\n");
            writer.write("-Total Inventory Value: " + totalInventoryValue() + "\n");

            writer.close();
            System.out.println("Inventory report exported successfully.");
        } catch (IOException e) {
            System.out.println("Error exporting inventory report: " + e.getMessage());
        }
    }

    /**
     * Finds a device by name
     * 
     * (n is the number of devices in the inventory)
     * Complexity: O(n)
     * 
     * @param name Name of the device to find
     * @return the device if found, null otherwise
     */
    private Device findDeviceByName(String name){
        for(ArrayList<Device> i : theData){
            for(Device j : i){
                if(j.getName().equals(name))
                    return j;
            }
        }

        return null;
    }
    
    /**
     * Prints the menu for the inventory management system
     * 
     * Complexity: O(1)
     */
    public void printMenu(){
        System.out.println("\nPlease select an option:");
        System.out.println("1. Add a new device");
        System.out.println("2. Remove a device");
        System.out.println("3. Update device details");
        System.out.println("4. List all devices");
        System.out.println("5. Find the cheapest device");
        System.out.println("6. Sort devices by price");
        System.out.println("7. Calculate total inventory value");
        System.out.println("8. Restock a device");
        System.out.println("9. Export inventory report");
        System.out.println("0. Exit\n");
    }
}
