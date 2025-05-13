/**
 * GeneralDevice is an abstract class that implements the Device interface and Comparable interface
 * It provides methods to get and set the device's name, price, quantity, and a string representation of the device.
 * It also provides a compareTo method to compare the price of two devices.
 */
public abstract class GeneralDevice implements Device , Comparable<GeneralDevice>{
    public GeneralDevice(String name, double price, int quantity){
        setName(name);
        setPrice(price);
        setQuantity(quantity);
    }

    private String Name;

    /** 
     * Returns the name of the device
     * 
     * Complexity: O(1)
     * @return the Name
     */
    @Override
    public String getName() {
        return Name;
    }

    /**
     * Sets the name of the device
     * 
     * Complexity: O(1)
     * @param name the Name to set
     */
    @Override
    public void setName(String name) {
        if(name == null || name == "")
            throw new IllegalArgumentException("Invalid Name");

        Name = name;
    }

    private double Price;

    /**
     * Returns the price of the device
     * 
     * Complexity: O(1)
     * @return the Price
     */
    @Override
    public double getPrice() {
        return Price;
    }

    /**
     * Sets the price of the device
     * 
     * Complexity: O(1)
     * @param price the Price to set
     */
    @Override
    public void setPrice(double price) {
        if(price <= 0.0)
            throw new IllegalArgumentException("Invalid Price");

        Price = price;
    }

    private int Quantity;

    /**
     * Returns the quantity of the device
     * 
     * Complexity: O(1)
     * @return the Quantity
     */
    @Override
    public int getQuantity() {
        return Quantity;
    }

    /**
     * Sets the quantity of the device
     * 
     * Complexity: O(1)
     * @param quantity the Quantity to set
     */
    @Override
    public void setQuantity(int quantity) {
        if(quantity <= 0)
            throw new IllegalArgumentException("Illegal Quantity");

        Quantity = quantity;
    }

    /**
     * Returns the category of the device
     * 
     * Complexity: O(1)
     * @return the category
     */
    @Override
    public String toString(){
        return "Category: " + getCategory() + ", " + "Name: " + getName() + ", Price: " + getPrice() + ", Quantity: " + getQuantity();
    }

    /**
     * Compares the price of two devices
     * 
     * Complexity: O(1)
     * @param o the device to compare
     * @return the result of the comparison
     */
    @Override
    public int compareTo(GeneralDevice o) {
        return Double.compare(getPrice(), o.getPrice());
    }
}