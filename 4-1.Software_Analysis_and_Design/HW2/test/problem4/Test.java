package problem4;

import problem1.SimpleLogger;
import problem2.factory.CarPartsFactory;
import problem2.factory.HyundaiPartsFactory;
import problem3.Builder;
import problem3.Car;
import problem3.CarBuilder;
import problem3.Color;

import java.io.OutputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;

/**
 * DO NOT MODIFY THIS CLASS
 * - Any change will discount your score!!
 */
public class Test {
    @org.junit.jupiter.api.Test
    public void test_07() {
        /**
         * Test on Proxy of CarBuilder that checks if the created car is valid
         */
        CarPartsFactory factory = new HyundaiPartsFactory();
        Builder builder = new CheckingBuilderProxyDecorator(factory);
        Car invalidCar = builder.addDoors(1).addWheels(10).setRoof().getCar();
        builder.reset();
        Car validCar = builder.addDoors(4).addWheels(4).setRoof().getCar();

        assertNull(invalidCar); // it should be null object
        assertNotNull(validCar);  // it shouldn't be null object
    }

    @org.junit.jupiter.api.Test
    public void test_08() {
        /**
         * Test on Proxy of CarBuilder that puts logs after the car is created
         */
        SimpleLogger logger = SimpleLogger.getInstance();
        logger.setHandler(new PrintStream(OutputStream.nullOutputStream()));
        logger.clear();

        CarPartsFactory factory = new HyundaiPartsFactory();
        Builder builder = new LoggingBuilderProxyDecorator(factory, logger);
        Car car = builder.addDoors(1)
                .addWheels(10)
                .setColor(Color.BLUE)
                .getCar();

        assertNotNull(car); // it shouldn't be null although it's invalid
        assertEquals(1, logger.getNumLogs()); // one log message should be saved
    }

    @org.junit.jupiter.api.Test
    public void test_09() {
        /**
         * Test on Proxy decorators (default + logger + checker)
         */

        boolean loggerEnabled = true;
        boolean checkerEnabled = true;

        SimpleLogger logger = SimpleLogger.getInstance();
        logger.setHandler(new PrintStream(OutputStream.nullOutputStream()));
        logger.clear();

        Builder builder = new CarBuilder(new HyundaiPartsFactory());

        if(loggerEnabled)
            builder = new LoggingBuilderProxyDecorator(builder, logger);

        if(checkerEnabled)
            builder = new CheckingBuilderProxyDecorator(builder);

        Car invalidCar = builder.addDoors(1).getCar();
        builder.reset();

        Car validCar = builder.addDoors(4).addWheels(4).setRoof().getCar();

        assertNull(invalidCar); // it should be null object
        assertNotNull(validCar); // it shouldn't be null object
        assertEquals(2, logger.getNumLogs()); // two log messages should be saved
    }

    @org.junit.jupiter.api.Test
    public void test_10() {
        /**
         * Test on Proxy decorators (default + checker)
         */

        boolean loggerEnabled = false;
        boolean checkerEnabled = true;

        SimpleLogger logger = SimpleLogger.getInstance();
        logger.setHandler(new PrintStream(OutputStream.nullOutputStream()));
        logger.clear();

        Builder builder = new CarBuilder(new HyundaiPartsFactory());

        if(loggerEnabled)
            builder = new LoggingBuilderProxyDecorator(builder, logger);

        if(checkerEnabled)
            builder = new CheckingBuilderProxyDecorator(builder);

        Car invalidCar = builder.addDoors(1).getCar();
        builder.reset();

        Car validCar = builder.addDoors(4).addWheels(4).setRoof().getCar();

        assertNull(invalidCar); // it should be null object
        assertNotNull(validCar); // it shouldn't be null object
        assertEquals(0, logger.getNumLogs()); // no log messages
    }
}