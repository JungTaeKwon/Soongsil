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

    public Car(CompanyName companyName) {
        this.doors = new ArrayList<>();
        this.wheels = new ArrayList<>();
        this.roofs = new ArrayList<>();
        this.color = Color.BLACK;
        this.companyName = companyName;
    }

    public int numWheels() {
        return this.wheels.size();
    }

    public int numDoors() {
        return this.doors.size();
    }

    public int numRoofs() {
        return this.roofs.size();
    }

    public Color getColor() {
        return this.color;
    }

    public void addDoor(Door door) {
        this.doors.add(door);
    }

    public void addWheel(Wheel wheel) {
        this.wheels.add(wheel);
    }

    public void setRoof(Roof roof) {
        this.roofs.add(roof);
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public CompanyName getCompanyName() {
        return this.companyName;
    }

    public List<Door> getDoors() {
        return this.doors;
    }

    public List<Wheel> getWheels() {
        return this.wheels;
    }

    public Roof getRoof() {
        return this.roofs.getFirst();
    }
}
/**
 * ===============END===============
 */
