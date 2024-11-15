package problem2.factory;

import problem2.CompanyName;
import problem2.door.Door;
import problem2.roof.Roof;
import problem2.wheel.Wheel;

/**
 * ==============BEGIN==============
 * Complete the below code that requires your implementation
 * If necessary, you can make your own methods or classes so that the corresponding tests are passed
 */
public class HyundaiPartsFactory implements CarPartsFactory {
    CompanyName companyName;

    public HyundaiPartsFactory() {
        this.companyName = CompanyName.HYUNDAI;
    }

    public CompanyName getCompanyName() {
        return companyName;
    }

    @Override
    public Door createDoor() {
        return null;
    }

    @Override
    public Wheel createWheel() {
        return null;
    }

    @Override
    public Roof createRoof() {
        return null;
    }
}
/**
 * ===============END===============
 */
