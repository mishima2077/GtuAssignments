package src;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

/**
 * A class for generating a file with random operations and performing a performance analysis
 */
public class Main {
    public static void main(String[] args) {

        // Generate a file with random operations and perform the operations on the AVL tree
        generateAndOperateFile();

        Scanner scanner = new Scanner(System.in);

        // Perform a performance analysis
        StockDataManager analysisManager = new StockDataManager();

        System.out.println();
        System.out.println("Performance Analysis");
        System.out.println("Suggestion, set the values high for better analysis (e.g. 50, 700) ");
        System.out.println("Enter the number of operations to perform for each data point (don't exceed 100): ");
        int interval = scanner.nextInt();

        if(interval > 100){
            System.out.println("Number of operations cannot exceed 100, setting to 100");
            interval = 100;
        }

        System.out.println("Enter the number of data points to generate(don't exceed 1500): ");
        int count = scanner.nextInt();

        if(count > 1500){
            System.out.println("Number of data points cannot exceed 1500, setting to 1500");
            count = 1500;
        }

        // Perform a simple performance analysis
        performPerformanceAnalysis(analysisManager, interval, count);
    }

    private static StockDataManager generateAndOperateFile(){
        StockDataManager manager = new StockDataManager();
        String filename;
        int operationCount;

        System.out.println("File name to generate (without the extension): ");

        Scanner scanner = new Scanner(System.in);
        filename = scanner.nextLine();
        filename += ".txt"; // Append ".txt" to the filename to create a text file

        System.out.println("Number of operations (max 1000): ");
        operationCount = scanner.nextInt();

        if(operationCount > 1000){
            System.out.println("Number of operations cannot exceed 1000, setting to 1000");
            operationCount = 1000;
        }

        System.out.println("Generating file: " + filename + " with " + operationCount + " operations");

        // Generate a file with random operations
        FileGeneretor fileGeneretor = new FileGeneretor(filename, operationCount);
        fileGeneretor.generateFile();

        // Perform the operations on the AVL tree
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                processCommand(line, manager);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return manager;
    }

    private static void processCommand(String line, StockDataManager manager) {
        String[] tokens = line.split(" ");
        String command = tokens[0];

        switch (command) {
            case "ADD":
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                break;
            case "REMOVE":
                manager.removeStock(tokens[1]);
                break;
            case "SEARCH":
                Stock stock = manager.searchStock(tokens[1]);
                if (stock != null) {
                    System.out.println(stock);
                } else {
                    System.out.println("Stock not found: " + tokens[1]);
                }
                break;
            case "UPDATE":
                manager.updateStock(tokens[1],tokens[2], Double.parseDouble(tokens[3]), Long.parseLong(tokens[4]), Long.parseLong(tokens[5]));
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    private static void performPerformanceAnalysis(StockDataManager manager, int interval,int count) {
        long startTime, endTime, avgTime;
        List<Integer> dataPointsX = new ArrayList<>();
        List<Long> insertionValues = new ArrayList<>();
        List<Long> searchValues = new ArrayList<>();
        List<Long> removalValues = new ArrayList<>();

        String randomSymbol;

        ArrayList<String> addedSymbols = new ArrayList<>();

        // Generate random values for the stock
        double num2 = (Math.random() * 100);
        long num3 = (long) (Math.random() * 1000000);
        long num4 = (long) (Math.random() * 1000000000);

        //Start with 100 data points
        for(int j = 0; j < 100; ++j){
            manager.addOrUpdateStock(generateRandomString(7) , num2,num3,num4);
        }

        // Perform the performance analysis
        for(int i = 0; i < count; ++i){
            num2 = (Math.random() * 100);
            num3 = (long) (Math.random() * 1000000);
            num4 = (long) (Math.random() * 1000000000);

            // Measure time for ADD operation
            avgTime = 0;
            for (int j = 0; j < interval; j++) {
                randomSymbol = generateRandomString(4);

                startTime = System.nanoTime();
                manager.addOrUpdateStock(randomSymbol , num2,num3,num4);
                endTime = System.nanoTime();

                // Store the added symbols for the SEARCH and REMOVE operations
                addedSymbols.add(randomSymbol);

                avgTime += endTime - startTime;
            }
            // Calculate the average time for the ADD operation
            insertionValues.add(avgTime / interval);

            // Measure time for SEARCH operation
            avgTime = 0;
            for (int j = 0; j < interval; j++) {
                randomSymbol = generateRandomString(4);

                startTime = System.nanoTime();
                manager.searchStock(addedSymbols.get(j));
                endTime = System.nanoTime();

                avgTime += endTime - startTime;
            }
            // Calculate the average time for the SEARCH operation
            searchValues.add(avgTime / interval);

            // Measure time for REMOVE operation
            avgTime = 0;
            for (int j = 0; j < interval; j++) {
                startTime = System.nanoTime();
                manager.removeStock(addedSymbols.get(j));
                endTime = System.nanoTime();

                avgTime += endTime - startTime;
            }
            // Calculate the average time for the REMOVE operation
            removalValues.add(avgTime / interval);

            addedSymbols.clear();

            //Increase the size of the AVL tree by interval
            for(int j = 0; j < interval; ++j){
                manager.addOrUpdateStock(generateRandomString(7) , num2,num3,num4);
            }

            dataPointsX.add(i * interval);
        }

        // Print the performance analysis graphs
        GUIVisualization insertionGraph = new GUIVisualization("Insertion Performance Analysis", "scatter", dataPointsX, insertionValues);
        insertionGraph.setVisible(true);

        GUIVisualization searchGraph = new GUIVisualization("Search Performance Analysis", "scatter", dataPointsX, searchValues);
        searchGraph.setVisible(true);

        GUIVisualization removalGraph = new GUIVisualization("Removal Performance Analysis", "scatter", dataPointsX, removalValues);
        removalGraph.setVisible(true);
    }

    /**
     * Generate a random string with a given average length, (lengthAvg ± 3)
     * @param lengthAvg The average length of the string
     * @return The generated random string
     */
    public static String generateRandomString(int lengthAvg) {
        int length = (int) (Math.random() * 3) + lengthAvg;

        Random random = new Random();
        StringBuilder sb = new StringBuilder(length);
    
        for (int i = 0; i < length; i++) {
            // Generate a random uppercase letter
            char randomChar = (char) ('A' + random.nextInt(26));
            sb.append(randomChar);
        }
    
        return sb.toString();
    }
}
