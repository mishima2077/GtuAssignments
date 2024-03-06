public class Order {
    private String product_name;

    private int Count;
    public int getCount(){
        return Count;
    }

    private int total_price;
    public int getTotalPrice(){
        return total_price;
    }

    private int Status;
    public int getStatus(){
        return Status;
    }

    private int customer_ID;
    public int getCustomerID(){
        return customer_ID;
    }

    public Order(String product_name, int Count, int total_price, int Status, int custormer_ID){
        this.product_name = product_name;
        this.Count = Count;
        this.total_price = total_price;
        this.Status = Status;
        this.customer_ID = custormer_ID;
    }

    public void print_order(){
        System.out.printf("Product name: %s - Count: %d - Total Price: %d - Status: %s",product_name,Count,total_price,StatusPrinter(),customer_ID);
    }

    private String StatusPrinter(){
        switch(Status){
            case 0: return "Initialized";
            case 1: return "Processing";
            case 2: return "Completed";
            case 3: return "Cancelled";
            default: return "Error";
        } 
    }
}
