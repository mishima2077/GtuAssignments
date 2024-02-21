package GtuContainer;
import java.util.Iterator;

/**
 * Represents a generic container in Java.
 *
 * @param <T> the type of elements held in the container.
 */
public interface JavaContainer<T>{

    /**
     * Adds an element to the container.
     *
     * @param element the element to be added.
     */
    void add(T element);

    /**
     * Removes an element from the container.
     *
     * @param element the element to be removed.
     */
    void remove(T element);

    /**
     * Returns the size of the container.
     *
     * @return the size of the container.
     */
    int size();

    /**
     * Returns an iterator over the elements in the container.
     *
     * @return an iterator over the elements in the container.
     */
    Iterator<T> getIterator();
    
}