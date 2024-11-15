package problem2.factory;

import problem2.CompanyName;
import problem2.door.Door;
import problem2.door.HyundaiDoor;
import problem2.roof.HyundaiRoof;
import problem2.roof.Roof;
import problem2.wheel.HyundaiWheel;
import problem2.wheel.Wheel;

import static problem2.CompanyName.HYUNDAI;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class HyundaiPartsFactory implements CarPartsFactory {
    private final CompanyName companyName;

    public HyundaiPartsFactory() {
        this.companyName = HYUNDAI;
    }

    public CompanyName getCompanyName() {
        return companyName;
    }

    @Override
    public Door createDoor() {
        return new HyundaiDoor(companyName);
    }

    @Override
    public Wheel createWheel() {
        return new HyundaiWheel(companyName);
    }

    @Override
    public Roof createRoof() {
        return new HyundaiRoof(companyName);
    }
}
/**
 * ===============END===============
 */
