package problem2.door;

import problem2.CompanyName;
import problem2.Part;

public abstract class Door extends Part {
    public Door(CompanyName companyName){
        super(companyName);
    }

    @Override
    public String toString() {
        return String.format("[%s] Door", companyName);
    }
}
