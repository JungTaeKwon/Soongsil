package problem3;

import problem2.CompanyName;
import problem2.door.Door;
import problem2.roof.Roof;
import problem2.wheel.Wheel;

import java.util.ArrayList;
import java.util.List;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class Car {
    private List<Door> doors;
    private List<Wheel> wheels;
    private List<Roof> roofs;
    private Color color;
    private CompanyName companyName;

    public Car() {
        this.doors = new ArrayList<>();
        this.wheels = new ArrayList<>();
        this.roofs = new ArrayList<>();
        this.color = Color.BLACK;
    }

    public int numWheels() {
        return 0;
    }

    public int numDoors() {
        return 0;
    }

    public int numRoofs() {
        return 0;
    }

    public int getColor() {
        return 0;
    }

    public CompanyName getCompanyName() {
        return null;
    }

    public List<Door> getDoors() {
        return null;
    }

    public List<Wheel> getWheels() {
        return null;
    }

    public Roof getRoof() {
        return null;
    }
}
/**
 * ===============END===============
 */
