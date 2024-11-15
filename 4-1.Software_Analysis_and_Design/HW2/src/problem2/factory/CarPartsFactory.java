package problem2.factory;

import problem2.CompanyName;
import problem2.Part;
import problem2.door.Door;
import problem2.roof.Roof;
import problem2.wheel.Wheel;

public interface CarPartsFactory {
    Door createDoor();
    Wheel createWheel();
    Roof createRoof();
    CompanyName getCompanyName();
}
