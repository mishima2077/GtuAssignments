
/**
 * The Device interface represents a generic device.
 * It provides methods to get and set the device's category, name, price, quantity, and a string representation of the device.
 */
public interface Device {
    /**
     * Returns the category of the device.
     *
     * @return the category of the device
     */
    public String getCategory();

    /**
     * Returns the name of the device.
     *
     * @return the name of the device
     */
    public String getName();

    /**
     * Sets the name of the device.
     *
     * @param name the new name of the device
     */
    public void setName(String name);

    /**
     * Returns the price of the device.
     *
     * @return the price of the device
     */
    public double getPrice();

    /**
     * Sets the price of the device.
     *
     * @param price the new price of the device
     */
    public void setPrice(double price);

    /**
     * Returns the quantity of the device.
     *
     * @return the quantity of the device
     */
    public int getQuantity();

    /**
     * Sets the quantity of the device.
     *
     * @param quantity the new quantity of the device
     */
    public void setQuantity(int quantity);

    /**
     * Returns a string representation of the device.
     *
     * @return a string representation of the device
     */
    public String toString();
}