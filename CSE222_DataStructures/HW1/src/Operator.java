public class Operator extends Person{
    private int Wage;

    private Customer[] Customers;

    public Operator(String Name, String Surname, String Address, String Phone, int ID, int Wage){
        super(Name, Surname, Address, Phone, ID);

        this.Wage = Wage;
        this.Customers = null;
    }

    public void print_operator(){
        System.out.println(super.toString());
        System.out.println("Wage : " + Wage);
    }

    public void print_customers(){
        if(Customers == null) return;
        if(Customers.length == 0){
            System.out.println("This operator doesn't have any customers.");
            System.out.println("----------------------------");
        }

        for(int i = 0; i < Customers.length; ++i){
            System.out.printf("Customer #%d ",i+1);
            if(Customers[i] instanceof RetailCustomer){
                System.out.println("(a reatail customer)");
            }
            else{
                System.out.println("(a corporate customer)");
            }
            Customers[i].print_customer();
            Customers[i].print_orders();
            System.out.println("---------------------------- ");
        }
    }

    public void define_customers(Customer[] allCustomers){
        int totalCustomers = 0;
        int myCustomers = 0;
        while(allCustomers[totalCustomers] != null){
            if(allCustomers[totalCustomers].getOperatorID() == getID())
                ++myCustomers;
            ++totalCustomers;
        }

        Customers = new Customer[myCustomers];
        for(int i = 0, j = 0; i < totalCustomers; ++i){
            if(allCustomers[i].getOperatorID() == getID()){
                Customers[j] = allCustomers[i];
                ++j;
            }
        }
    }
}
