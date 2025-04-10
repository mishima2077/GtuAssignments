package src;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * A class for generating a file with random operations
 * 
 * The file will contain a specified number of operations, each operation will be one of the following:
 * - ADD: Add a new stock to the AVL tree
 * - REMOVE: Remove a stock from the AVL tree
 * - SEARCH: Search for a stock in the AVL tree
 * - UPDATE: Update a stock in the AVL tree
 */
public class FileGeneretor {
    private String fileName;
    private int operationCount;

    public FileGeneretor(String fileName, int operationCount) {
        this.fileName = fileName;
        this.operationCount = operationCount;
    }

    /**
     * Generate a file with random operations
     */
    public void generateFile() {
        try {
            FileWriter fileWriter = new FileWriter(fileName);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            ArrayList<String> addedSymbols = new ArrayList<>();

            for (int i = 0; i < operationCount; i++) {
                int operation = (int) (Math.random() * 6);

                // Randomly select an operation:
                // 0, 1, 2: ADD
                // 3: REMOVE
                // 4: SEARCH
                // 5, 6: UPDATE
                switch (operation) {
                    case 0:
                    case 1:
                    case 2:
                        String randomString = generateRandomSymbol();
                        printWriter.println("ADD " + generateRandomStock(randomString));
                        addedSymbols.add(randomString);
                        break;
                    case 3:
                        // Remove a random stock if there are any added stocks
                        if (addedSymbols.size() > 0) {
                            int index = (int) (Math.random() * addedSymbols.size());
                            printWriter.println("REMOVE " + addedSymbols.get(index));
                            addedSymbols.remove(index);
                        } else {
                            printWriter.println("REMOVE " + generateRandomSymbol());
                        }
                        break;
                    case 4:
                        // Search for a random stock if there are no added stocks
                        if (addedSymbols.size() == 0){
                            printWriter.println("SEARCH " + generateRandomSymbol());
                        } else {
                            printWriter.println("SEARCH " + addedSymbols.get((int) (Math.random() * addedSymbols.size())));
                        }
                        break;
                    case 5:
                    case 6:
                        // Update a random stock if there are any added stocks
                        if(addedSymbols.size() > 0){
                            printWriter.println("UPDATE " + addedSymbols.get((int) (Math.random() * addedSymbols.size())) + " " + generateRandomStock(generateRandomSymbol()));
                        }else{
                            printWriter.println("UPDATE " + generateRandomSymbol() + " " + generateRandomStock(generateRandomSymbol()));
                        }
                        break;
                }
            }

            printWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Generate a random stock with a random symbol
    private String generateRandomStock(String ranSymbol) {
        double num2 = (Math.random() * 100);
        long num3 = (long) (Math.random() * 1000000);
        long num4 = (long) (Math.random() * 1000000000);

        return ranSymbol + " " + num2 + " " + num3 + " " + num4;
    }

    // Generate a random symbol
    private String generateRandomSymbol() {
        return Main.generateRandomString(4);
    }
}
