public class Person{
    private String Name;
    public String getName(){
        return Name;
    }

    private String Surname;
    public String getSurname(){
        return Surname;
    }

    private String Address;
    public String getAdress(){
        return Address;
    }

    private String Phone;
    public String getPhone(){
        return Phone;
    }

    private int ID;
    public int getID(){
        return ID;
    }

    public Person(String Name, String Surname, String Address, String Phone, int ID){
        this.Name = Name;
        this.Surname = Surname;
        this.Address = Address;
        this.Phone = Phone;
        this.ID = ID;
    }

    public String toString(){
        StringBuilder result = new StringBuilder();
        result.append("Name & Surname : " + Name + " " + Surname + "\n");
        result.append("Address : " + Address + "\n");
        result.append("Phone : " + Phone + "\n");
        result.append("ID : " + ID);
        return result.toString();
    }
}