public class CorporateCustomer extends Customer{
    private String CompanyName;

    public CorporateCustomer(String Name, String Surname, String Address, String Phone, int ID, int operator_ID, String CompanyName){
        super(Name, Surname, Address, Phone, ID, operator_ID);

        this.CompanyName = CompanyName;
    }

    public void print_customer(){
        super.print_customer();
        System.out.println("Company Name : " + CompanyName);
    }
}
