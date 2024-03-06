public class Customer extends Person{
    private Order[] Orders;
    
    private int operator_ID;

    public int getOperatorID(){
        return operator_ID;
    }

    public Customer(String Name, String Surname, String Address, String Phone, int ID, int operator_ID){
        super(Name, Surname, Address, Phone, ID);

        this.Orders = null;
        this.operator_ID = operator_ID;
    }

    public void print_customer(){
        System.out.println(super.toString());
        System.out.println("Operator ID : " + operator_ID);
    }

    public void print_orders(){
        if(Orders == null) return;
        for(int i = 0; i < Orders.length; ++i){
            System.out.printf("Order #%d => ",i+1);
            Orders[i].print_order();
            System.out.println();
        }
    }

    public void define_orders(Order[] allOrders){
        int totalOrders = 0;
        int myOrders = 0;
        while(allOrders[totalOrders] != null){
            if(allOrders[totalOrders].getCustomerID() == getID())
                ++myOrders;
            ++totalOrders;
        }
        Orders = new Order[myOrders];
        for(int i = 0, j = 0; i < totalOrders; ++i){
            if(allOrders[i].getCustomerID() == getID()){
                Orders[j] = allOrders[i];
                ++j;
            }
        }
    }
}
