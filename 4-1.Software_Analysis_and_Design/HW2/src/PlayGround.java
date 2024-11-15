import problem1.LogLevel;
import problem1.SimpleLogger;

public class PlayGround {
    /**
     * if you need to simply test your implementation, use the below main function of this class
     */
    public static void main(String[] args){
        SimpleLogger logger = SimpleLogger.getInstance();
        logger.setHandler(System.out);
        logger.log(LogLevel.INFO, "Hello, World!");
        logger.clear();
    }
}
