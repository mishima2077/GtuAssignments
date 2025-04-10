package src;

/**
 * A class for managing stock data with AVL Tree
 */
public class StockDataManager {
    private AVLTree avlTree;

    public StockDataManager() {
        avlTree = new AVLTree();
    }

    /**
     * Print the tree in inorder traversal
     */
    public void printTree(){
        avlTree.inOrderTraversal();
    }

    //Write javadoc comments

    /**
     * Add or update a stock, if the stock already exists, update the stock details
     * @param symbol stock symbol
     * @param price stock price
     * @param volume stock volume
     * @param marketCap stock market capitalization
     */
    public void addOrUpdateStock(String symbol, double price, long volume, long marketCap) {
        Stock existingStock = avlTree.search(symbol);
        if (existingStock != null) {
            existingStock.setPrice(price);
            existingStock.setVolume(volume);
            existingStock.setMarketCap(marketCap);
        } else {
            Stock newStock = new Stock(symbol, price, volume, marketCap);
            avlTree.insert(newStock);
        }
    }

    /**
     * Remove a stock
     * @param symbol stock to be removed
     */
    public void removeStock(String symbol) {
        avlTree.delete(symbol);
    }

    /**
     * Search a stock by symbol, return the stock if found, otherwise return null
     * @param symbol stock symbol
     * @return stock if found, otherwise null
     */
    public Stock searchStock(String symbol) {
        return avlTree.search(symbol);
    }

    /**
     * Update stock details
     * @param symbol stock to be updated
     * @param newSymbol new stock symbol
     * @param newPrice new stock price
     * @param newVolume new stock volume
     * @param newMarketCap new stock market capitalization
     */
    public void updateStock(String symbol, String newSymbol, double newPrice, long newVolume, long newMarketCap) {
        Stock stock = avlTree.search(symbol);
        if (stock != null) {
            stock.setSymbol(newSymbol);
            stock.setPrice(newPrice);
            stock.setVolume(newVolume);
            stock.setMarketCap(newMarketCap);
        }
    }
}
