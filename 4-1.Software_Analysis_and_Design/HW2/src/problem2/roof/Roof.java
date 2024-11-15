package problem2.roof;

import problem2.CompanyName;
import problem2.Part;

public abstract class Roof extends Part {
    public Roof(CompanyName companyName) {
        super(companyName);
    }

    @Override
    public String toString() {
        return String.format("[%s] Roof", companyName);
    }
}