package src;

/**
 * An AVL Tree class for storing stock data
 * 
 * The AVL tree is a self-balancing binary search tree, it maintains the property that the height of the left and right subtrees of any node differ by at most one
 */
public class AVLTree {
    private class Node {
        Stock stock;
        Node left, right;
        int height;

        Node(Stock stock) {
            this.stock = stock;
            this.height = 1;
        }
    }

    private Node root;

    /**
     * Insert a new stock into the AVL tree, if the stock already exists, update the stock
     * @param stock The stock to insert or update
     */
    public void insert(Stock stock) {
        root = insert(root, stock);
    }

    private Node insert(Node node, Stock stock) {
        if(node == null){
            return new Node(stock);
        }

        // Update the stock if it already exists
        if(stock.getSymbol().compareTo(node.stock.getSymbol()) == 0){
            node.stock = stock;
            return node;
        }

        // Insert the stock
        if(stock.getSymbol().compareTo(node.stock.getSymbol()) > 0){
            node.right = insert(node.right, stock);
        }else{
            node.left = insert(node.left, stock);
        }

        // Update the height of the node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // Balance the tree 
        node = balanceAfterAddition(node, stock);

        return node;
    }

    /**
     * Delete a stock from the AVL tree
     * @param symbol The symbol of the stock to delete
     */
    public void delete(String symbol) {
        root = delete(root, symbol);
    }

    private Node delete(Node node, String symbol) {
        if(node == null){
            return null;
        }

        // Locate the stock to delete
        if(symbol.compareTo(node.stock.getSymbol()) > 0){
            node.right = delete(node.right, symbol);
        }else if(symbol.compareTo(node.stock.getSymbol()) < 0){
            node.left = delete(node.left, symbol);
        }else{
            Node temp;
            // If the node has one child or no child
            if(node.left == null || node.right == null){
                if(node.left == null) temp = node.right;
                else temp = node.left;

                node = temp;
            }
            // If the node has two children, get the inorder successor and replace the node with it
            else{
                temp = getMinNode(node.right);
                node.stock = temp.stock;
                node.right = delete(node.right, temp.stock.getSymbol());
            }
        }

        if(node == null){
            return null;
        }

        // Update the height of the node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // Balance the tree
        node = balanceAfterDeletion(node);
        return node;
    }

    /**
     * Search for a stock in the AVL tree
     * @param symbol The symbol of the stock to search for
     * @return The stock if found, null otherwise
     */
    public Stock search(String symbol) {
        Node result = search(root, symbol);
        return (result != null) ? result.stock : null;
    }

    private Node search(Node node, String symbol) {
        if(node == null){
            return null;
        }
        // Return the node if the stock is found
        if(node.stock.getSymbol().equals(symbol)){
            return root;
        }
        // Search the right subtree if the symbol is greater than the current node's symbol
        if(symbol.compareTo(node.stock.getSymbol()) > 0){
            return search(node.right, symbol);
        }
        // Search the left subtree if the symbol is less than the current node's symbol
        return search(node.left, symbol);
    }

    private int height(Node node){
        if(node == null){
            return 0;
        }
        return node.height;
    }

    // Calculate the balance factor of a node, which is the difference between the height of the left and right subtrees
    private int balanceFactor(Node node){
        if(node == null){
            return 0;
        }
        return height(node.left) - height(node.right);
    }

    // Get the node with the minimum value in the tree
    private Node getMinNode(Node root){
        Node current = root;

        while(current.left != null){
            current = current.left;
        }

        return current;
    }

    private Node balanceAfterAddition(Node root, Stock addedData){
        int bf = balanceFactor(root);

        // Left Left Case
        if(bf > 1 && addedData.getSymbol().compareTo(root.left.stock.getSymbol()) < 0){
            return rightRotate(root);
        }

        // Right Right Case
        if(bf < -1 && addedData.getSymbol().compareTo(root.right.stock.getSymbol()) > 0){
            return leftRotate(root);
        }

        // Left Right Case
        if(bf > 1 && addedData.getSymbol().compareTo(root.left.stock.getSymbol()) > 0){
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }

        // Right Left Case
        if(bf < -1 && addedData.getSymbol().compareTo(root.right.stock.getSymbol()) < 0){
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }

        return root;
    }

    private Node balanceAfterDeletion(Node root){
        int bf = balanceFactor(root);

        // Left Left Case
        if(bf > 1 && balanceFactor(root.left) >= 0){
            return rightRotate(root);
        }

        // Right Right Case
        if(bf < -1 && balanceFactor(root.right) <= 0){
            return leftRotate(root);
        }

        // Left Right Case
        if(bf > 1 && balanceFactor(root.left) < 0){
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }

        // Right Left Case
        if(bf < -1 && balanceFactor(root.right) > 0){
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }

        return root;
    }

    // Rotation methods
    private Node rightRotate(Node toRotate){
        Node newRoot = toRotate.left;

        toRotate.left = newRoot.right;
        newRoot.right = toRotate;

        toRotate.height = 1 + Math.max(height(toRotate.left), height(toRotate.right));
        newRoot.height = 1 + Math.max(height(newRoot.left), height(newRoot.right));

        return newRoot;
    }

    private Node leftRotate(Node toRotate){
        Node newRoot = toRotate.right;

        toRotate.right = newRoot.left;
        newRoot.left = toRotate;

        toRotate.height = 1 + Math.max(height(toRotate.left), height(toRotate.right));
        newRoot.height = 1 + Math.max(height(newRoot.left), height(newRoot.right));

        return newRoot;
    }

    /**
     * Traverse the AVL tree in in-order and print the stocks
     */
    public void inOrderTraversal() {
        inOrderTraversal(root);
    }

    private void inOrderTraversal(Node node) {
        if (node != null) {
            inOrderTraversal(node.left);
            System.out.println(node.stock);
            inOrderTraversal(node.right);
        }
    }

    /**
     * Traverse the AVL tree in pre-order and print the stocks
     */
    public void preOrderTraversal() {
        preOrderTraversal(root);
    }

    private void preOrderTraversal(Node node) {
        if (node != null) {
            System.out.println(node.stock);
            preOrderTraversal(node.left);
            preOrderTraversal(node.right);
        }
    }

    /**
     * Traverse the AVL tree in post-order and print the stocks
     */
    public void postOrderTraversal() {
        postOrderTraversal(root);
    }

    private void postOrderTraversal(Node node) {
        if (node != null) {
            postOrderTraversal(node.left);
            postOrderTraversal(node.right);
            System.out.println(node.stock);
        }
    }
}