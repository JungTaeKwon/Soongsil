package problem4;

import problem2.factory.CarPartsFactory;
import problem3.Builder;
import problem3.Car;
import problem3.Color;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class BaseBuilderProxyDecorator implements Builder {
    private Builder builder;

    public BaseBuilderProxyDecorator(Builder builder) {

    }

    public BaseBuilderProxyDecorator(CarPartsFactory factory){

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
