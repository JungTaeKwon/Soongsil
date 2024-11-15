package problem2.wheel;

import problem2.CompanyName;
import problem2.Part;

public abstract class Wheel extends Part{
    public Wheel(CompanyName factoryName) {
        super(factoryName);
    }

    @Override
    public String toString() {
        return String.format("[%s] Wheel", companyName);
    }
}
