package problem3;

public interface Builder {
    Builder addDoors(int numDoors);
    Builder addWheels(int numWheels);
    Builder setRoof();
    Builder setColor(Color color);
    Car getCar();
    void reset();
}
