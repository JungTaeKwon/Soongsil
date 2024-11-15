package problem2.factory;

import problem2.CompanyName;
import problem2.door.Door;
import problem2.door.TeslaDoor;
import problem2.roof.Roof;
import problem2.roof.TeslaRoof;
import problem2.wheel.TeslaWheel;
import problem2.wheel.Wheel;

import static problem2.CompanyName.TESLA;

public class TeslaPartsFactory implements CarPartsFactory {
    private final CompanyName companyName;

    public TeslaPartsFactory() {
        this.companyName = TESLA;
    }

    @Override
    public Door createDoor() {
        return new TeslaDoor(getCompanyName());
    }

    @Override
    public Wheel createWheel() {
        return new TeslaWheel(getCompanyName());
    }

    @Override
    public Roof createRoof() {
        return new TeslaRoof(getCompanyName());
    }

    @Override
    public CompanyName getCompanyName() {
        return this.companyName;
    }
}
