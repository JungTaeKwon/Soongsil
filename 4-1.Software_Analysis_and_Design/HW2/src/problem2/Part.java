package problem2;

public abstract class Part {
    protected CompanyName companyName;

    public Part(CompanyName companyName) {
        this.companyName = companyName;
    }

    public CompanyName getCompanyName() {
        return companyName;
    }
}

