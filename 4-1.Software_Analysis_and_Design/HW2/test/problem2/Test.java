package problem2;

import problem2.door.*;
import problem2.roof.*;
import problem2.wheel.*;
import problem2.factory.*;

import static org.junit.jupiter.api.Assertions.*;

/**
 * DO NOT MODIFY THIS CLASS
 * - Any change will discount your score!!
 */
public class Test {

    @org.junit.jupiter.api.Test
    public void test_03(){
        /**
         * Test on implementation of HyundaiPartsFactory
         */
        CarPartsFactory factory = new HyundaiPartsFactory();
        Door door = factory.createDoor();
        Roof roof = factory.createRoof();
        Wheel wheel = factory.createWheel();

        // their classes should be regarding HYUNDAI
        assertEquals(door.getClass(), HyundaiDoor.class);
        assertEquals(roof.getClass(), HyundaiRoof.class);
        assertEquals(wheel.getClass(), HyundaiWheel.class);

        // their company names should be HYUNDAI
        assertEquals(door.getCompanyName(), CompanyName.HYUNDAI);
        assertEquals(roof.getCompanyName(), CompanyName.HYUNDAI);
        assertEquals(wheel.getCompanyName(), CompanyName.HYUNDAI);
    }

    @org.junit.jupiter.api.Test
    public void test_04() {
        /**
         * Test on implementation of TeslaPartsFactory
         */

        // for the first time you set this project, there will be no classes related to Tesla in problem2 package
        // the below code will do similar to test_01 on Tesla, but it does not depend on the existence on such classes
        assertDoesNotThrow(() -> {
            Class<?> teslaFactoryClass = Class.forName("problem2.factory.TeslaPartsFactory");
            CarPartsFactory factory = (CarPartsFactory) teslaFactoryClass.newInstance();

            Door door = factory.createDoor();
            Roof roof = factory.createRoof();
            Wheel wheel = factory.createWheel();

            // their classes should be regarding TESLA
            assertEquals(door.getClass(), Class.forName("problem2.door.TeslaDoor"));
            assertEquals(roof.getClass(), Class.forName("problem2.roof.TeslaRoof"));
            assertEquals(wheel.getClass(), Class.forName("problem2.wheel.TeslaWheel"));

            // their company names should be TESLA
            assertEquals(door.getCompanyName(), CompanyName.TESLA);
            assertEquals(roof.getCompanyName(), CompanyName.TESLA);
            assertEquals(wheel.getCompanyName(), CompanyName.TESLA);
        });
    }
}
