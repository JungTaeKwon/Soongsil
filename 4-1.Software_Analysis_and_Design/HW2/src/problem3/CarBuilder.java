package problem3;

import problem2.factory.CarPartsFactory;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class CarBuilder implements Builder{
    public CarBuilder(CarPartsFactory factory) {

    }

    @Override
    public Builder addDoors(int numDoors) {
        return null;
    }

    @Override
    public Builder addWheels(int numWheels) {
        return null;
    }

    @Override
    public Builder setRoof() {
        return null;
    }

    @Override
    public Builder setColor(Color color) {
        return null;
    }

    @Override
    public Car getCar() {
        return null;
    }

    @Override
    public void reset() {

    }
}
/**
 * ===============END===============
 */
