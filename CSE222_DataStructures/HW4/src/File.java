/**
 * File class that extends FileSystemElement
 * Represents a file in the file system
 */
public class File extends FileSystemElement{
    /**
     * Constructor for the file.
     * @param name name of the file.
     * @param parent parent of the file.
     */
    public File(String name, FileSystemElement parent) {
        super(name, parent);
    }
    
    @Override
    public void print(String prefix) {
        System.out.println(prefix + getName());
    }
}
