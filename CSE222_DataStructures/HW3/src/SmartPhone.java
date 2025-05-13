public class SmartPhone extends GeneralDevice{
    
    public SmartPhone(String name, double price, int quantity){
        super(name, price, quantity);
    }

    /**
     * Returns the category of the device
     * 
     * Complexity: O(1)
     * @return the category
     */
    @Override
    public String getCategory() {
        return "Smart Phone";
    }
}
