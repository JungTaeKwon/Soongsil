package problem4;

import problem2.factory.CarPartsFactory;
import problem3.Builder;
import problem3.Car;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class CheckingBuilderProxyDecorator extends BaseBuilderProxyDecorator {
    public CheckingBuilderProxyDecorator(Builder builder) {
        super(builder);
    }

    public CheckingBuilderProxyDecorator(CarPartsFactory factory) {
        super(factory);
    }

    @Override
    public Car getCar() {
        Car car = super.getCar();
        if (car == null || !isValidCar(car)) {
            return null;
        }
        return car;
    }

    private boolean isValidCar(Car car) {
        return isValidDoorCount(car.numDoors())
                && isValidWheelCount(car.numWheels())
                && isValidRoofCount(car.numRoofs());
    }

    private boolean isValidDoorCount(int doorCount) {
        return doorCount >= 4 && doorCount <= 6;
    }

    private boolean isValidWheelCount(int wheelCount) {
        return wheelCount >= 2 && wheelCount <= 10 && wheelCount % 2 == 0;
    }

    private boolean isValidRoofCount(int roofCount) {
        return roofCount == 1;
    }
}
/**
 * ===============END===============
 */
