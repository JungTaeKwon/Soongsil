package problem4;

import problem2.factory.CarPartsFactory;
import problem3.Builder;
import problem3.Car;
import problem3.CarBuilder;
import problem3.Color;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class BaseBuilderProxyDecorator implements Builder {
    private Builder builder;

    public BaseBuilderProxyDecorator(Builder builder) {
        this.builder = builder;
    }

    public BaseBuilderProxyDecorator(CarPartsFactory factory) {
        this.builder = new CarBuilder(factory);
    }

    @Override
    public Builder addDoors(int numDoors) {
        builder.addDoors(numDoors);
        return this;
    }

    @Override
    public Builder addWheels(int numWheels) {
        builder.addWheels(numWheels);
        return this;
    }

    @Override
    public Builder setRoof() {
        builder.setRoof();
        return this;
    }

    @Override
    public Builder setColor(Color color) {
        builder.setColor(color);
        return this;
    }

    @Override
    public Car getCar() {
        return builder.getCar();
    }

    @Override
    public void reset() {
        builder.reset();
    }
}
/**
 * ===============END===============
 */
