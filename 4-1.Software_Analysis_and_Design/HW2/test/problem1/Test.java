package problem1;

import java.io.OutputStream;
import java.io.PrintStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.*;

/**
 * DO NOT MODIFY THIS CLASS
 * - Any change will discount your score!!
 */
class Test {
    @org.junit.jupiter.api.Test
    public void test_01(){
        /**
         * Test on implementation of SimpleLogger
         */
        SimpleLogger logger = SimpleLogger.getInstance();
        logger.clear();
        // don't need to print a log message through the standard out (System.out)
        // during this test procedure; thus, its output is suppressed
        logger.setHandler(new PrintStream(OutputStream.nullOutputStream()));

        int numTests = 10;
        for(int i = 0; i < numTests; i++)
            logger.log(LogLevel.INFO, "test");

        // test if the logger correctly preserves the log messages
        assertEquals(numTests, logger.getNumLogs());

        // test if the clear function works correctly
        logger.clear();
        assertEquals(0, logger.getNumLogs());
    }

    @org.junit.jupiter.api.Test
    public void test_02(){
        /**
         * Test on thread-safety of SimpleLogger
         */
        for(int i = 0; i < 1000; i++)
            assertTrue(parallel_run(10));
    }

    public static boolean parallel_run(int numTests){
        /**
         * This function tests if 1) the instance of SimpleLogger is singleton in multi-thread setting, and
         * 2) the logger correctly preserves the occurred log messages (i.e., getNumLogs() should be numTests)
         */
        ExecutorService service = Executors.newCachedThreadPool();

        SimpleLogger logger = SimpleLogger.getInstance();
        logger.clear();
        logger.setHandler(new PrintStream(OutputStream.nullOutputStream()));

        SimpleLogger[] loggers = new SimpleLogger[numTests];
        for(int i = 0; i < numTests; i++){
            final int idx = i;
            service.submit(() -> {
                loggers[idx] = SimpleLogger.getInstance();
                loggers[idx].setHandler(new PrintStream(OutputStream.nullOutputStream()));
                loggers[idx].log(LogLevel.INFO, String.format("This is log from [%s]-th thread", idx));
            });
        }
        service.shutdown();
        try {
            service.awaitTermination(1, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        } finally {
            boolean doesContainAllMessages = logger.getNumLogs() == numTests;
            boolean areAllObjectsSame = true;
            for(SimpleLogger _logger : loggers) // check all references in loggers
                areAllObjectsSame = areAllObjectsSame && (logger == _logger);
            return doesContainAllMessages && areAllObjectsSame;
        }
    }
}