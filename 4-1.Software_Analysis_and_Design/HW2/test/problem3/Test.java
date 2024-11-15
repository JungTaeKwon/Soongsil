package problem3;

import problem2.CompanyName;
import problem2.factory.CarPartsFactory;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;


/**
 * DO NOT MODIFY THIS CLASS
 * - Any change will discount your score!!
 */
public class Test {
    @org.junit.jupiter.api.Test
    public void test_05() {
        /**
         * Test on CarBuilder with HyundaiPartsFactory
         */
        assertDoesNotThrow(() -> {
            Class<?> teslaFactoryClass = Class.forName("problem2.factory.HyundaiPartsFactory");
            CarPartsFactory factory = (CarPartsFactory) teslaFactoryClass.newInstance();

            Builder builder = new CarBuilder(factory);
            Car car = builder.addDoors(4)
                    .addWheels(4)
                    .setRoof()
                    .setColor(Color.BLUE)
                    .getCar();

            assertEquals(car.numDoors(), 4);
            assertEquals(car.numWheels(), 4);
            assertEquals(car.numRoofs(), 1);
            assertEquals(car.getColor(), Color.BLUE);
            assertEquals(car.getCompanyName(), CompanyName.HYUNDAI);

            assertTrue(areAllObjectsDifferent(car.getDoors()));
            assertTrue(areAllObjectsDifferent(car.getWheels()));
        });
    }


    @org.junit.jupiter.api.Test
    public void test_06() {
        /**
         * Test on CarBuilder with TeslaPartsFactory
         */
        assertDoesNotThrow(() -> {
            Class<?> teslaFactoryClass = Class.forName("problem2.factory.TeslaPartsFactory");
            CarPartsFactory factory = (CarPartsFactory) teslaFactoryClass.newInstance();

            Builder builder = new CarBuilder(factory);
            Car car = builder.addDoors(6)
                    .addWheels(6)
                    .setRoof()
                    .getCar();

            assertEquals(car.numDoors(), 6);
            assertEquals(car.numWheels(), 6);
            assertEquals(car.numRoofs(), 1);
            assertEquals(car.getColor(), Color.BLACK);
            assertEquals(car.getCompanyName(), CompanyName.TESLA);

            assertTrue(areAllObjectsDifferent(car.getDoors()));
            assertTrue(areAllObjectsDifferent(car.getWheels()));
        });
    }

    public static <T> boolean areAllObjectsDifferent(List<T> list) {
        /**
         * check if all objects are distinct in the given list
         */
        Set<T> uniqueObjects = new HashSet<>();
        for (T obj : list)
            if (!uniqueObjects.add(obj))
                return false;
        return true;
    }
}
