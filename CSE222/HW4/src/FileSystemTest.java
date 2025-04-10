import java.util.Scanner;

/**
 * Test class for the FileSystem class.
 * Allows the user to interact with the file system.
 */
public class FileSystemTest {
    private static FileSystem fs = new FileSystem();

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int option = 0;
        while(option != 9){
            printMenu();
            option = scanner.nextInt();
            scanner.nextLine();
            switch(option){
                case 1:
                    changeDirectory();
                    break;
                case 2:
                    listDirectoryContents();
                    break;
                case 3:
                    createSystemElement();
                    break;
                case 4:
                    deleteSystemElement();
                    break;
                case 5:
                    moveSystemElement();
                    break;
                case 6:
                    searchSystemElement();
                    break;
                case 7:
                    printDirectoryTree();
                    break;
                case 8:
                    sortContentsByDate();
                    break;
                case 9:
                    System.out.println("Exiting program");
                    break;
                default:
                    System.out.println("Invalid option");
            }
        }
    }

    /**
     * Prints the menu for the file system management program.
     */
    private static void printMenu(){
        System.out.println("\n===== File System Management Menu =====");
        System.out.println("1. Change directory");
        System.out.println("2. List directory contents");
        System.out.println("3. Create file/directory");
        System.out.println("4. Delete file/directory");
        System.out.println("5. Move file/directory");
        System.out.println("6. Search file/directory");
        System.out.println("7. Print directory tree");
        System.out.println("8. Sort contents by date created");
        System.out.println("9. Exit\n");
        System.out.print("Please select an option: ");
    }

    /**
     * Changes the current directory in the file system.
     */
    private static void changeDirectory(){
        System.out.println("Current path: " + fs.getCurrentPath());
        System.out.print("Enter new directory path: ");
        String name = scanner.nextLine();
        if(fs.changeDir(name)){
            System.out.println("Directory changed to: " + fs.getCurrentPath());
        } else{
            System.out.println("Directory not found");
        }
    }

    /**
     * Lists the contents of the current directory.
     */
    private static void listDirectoryContents(){
        System.out.println("Listing contents of: " + fs.getCurrentPath());
        fs.listCurrentDir("");
    }

    /**
     * Creates a new file or directory in the file system.
     */
    private static void createSystemElement(){
        System.out.println("Current path: " + fs.getCurrentPath());
        System.out.print("Enter the name of the element: ");
        String name = scanner.nextLine();
        System.out.print("Enter the type of the element (f/d): ");
        char type = scanner.nextLine().charAt(0);

        if(!fs.addElement(name, type))
            System.out.println("Invalid input, element couldn't be added to the system");
    }

    /**
     * Deletes a file or directory from the file system.
     */
    private static void deleteSystemElement(){
        System.out.println("Current path: " + fs.getCurrentPath());
        System.out.print("Enter the name of the element: ");
        String name = scanner.nextLine();
        if(fs.removeElement(name)){
            System.out.println("Element deleted");
        } else{
            System.out.println("Element not found");
        }
    }

    /**
     * Moves a file or directory to a new path in the file system.
     */
    private static void moveSystemElement(){
        System.out.println("Current path: " + fs.getCurrentPath());
        System.out.print("Enter the name of the element: ");
        String name = scanner.nextLine();
        System.out.print("Enter the path to move the element to: ");
        String path = scanner.nextLine();
        if(fs.moveElement(name, path)){
            System.out.println("Element moved");
        } else{
            System.out.println("Element not found or path not found");
        }
    }

    /**
     * Searches for a file or directory in the file system.
     */
    private static void searchSystemElement(){
        System.out.print("Enter the name of the element: ");
        String name = scanner.nextLine();
        System.out.println("Searching from root...");
        FileSystemElement element = fs.searchElement(name);
        if(element != null){
            System.out.println("Found: " + FileSystem.getPathOfElement(element));
        } else{
            System.out.println("Element not found");
        }
    }

    /**
     * Prints the directory tree starting from the root directory.
     */
    private static void printDirectoryTree(){
        System.out.println("Path to current dir from root:");
        fs.printDirectoryTree();
    }

    /**
     * Sorts the contents of the current directory by date created.
     */
    private static void sortContentsByDate(){
        System.out.println("Contents of " + fs.getCurrentPath() + " sorted by date created");
        fs.sortCurrentDir();
    }
}
