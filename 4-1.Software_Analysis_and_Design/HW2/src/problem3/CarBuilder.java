package problem3;

import problem2.factory.CarPartsFactory;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class CarBuilder implements Builder {

    private final CarPartsFactory builderFactory;
    private Car builderCar;

    public CarBuilder(CarPartsFactory factory) {
        builderFactory = factory;
        builderCar = new Car();
    }

    @Override
    public Builder addDoors(int numDoors) {
        for (int i = 0; i < numDoors; i++) {
            this.builderCar.addDoor(builderFactory.createDoor());
        }
        return this;
    }

    @Override
    public Builder addWheels(int numWheels) {
        for (int i = 0; i < numWheels; i++) {
            this.builderCar.addWheel(builderFactory.createWheel());
        }
        return this;
    }

    @Override
    public Builder setRoof() {
        this.builderCar.setRoof(builderFactory.createRoof());
        return this;
    }

    @Override
    public Builder setColor(Color color) {
        this.builderCar.setColor(color);
        return this;
    }

    @Override
    public Car getCar() {
        return this.builderCar;
    }

    @Override
    public void reset() {
        this.builderCar = new Car();
    }
}
/**
 * ===============END===============
 */
