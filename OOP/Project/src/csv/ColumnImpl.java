package csv;

import java.util.*;

class ColumnImpl implements Column{
    List<String> col = new ArrayList<>();
    private String type = "String";
    private int maxsize = 4;
    void setType(String str){ this.type = str; }
    String getType() { return this.type; }

    ColumnImpl(){}
    ColumnImpl(String[] data) {
        col = new ArrayList<>(data.length);
        for (int i = 0; i < data.length; i++) {
            try {
                if (data[i].equals(""))
                    data[i] = null;
            }
            catch(NullPointerException e)
            {
                continue;
            }
            if (data[i] != null) {
                if (data[i].charAt(0) == '\"') {
                    data[i] = data[i].substring(0);
                }
                if (data[i].charAt(data[i].length() - 1) == '\"') {
                    data[i] = data[i].substring(1, data[i].length() - 1);
                }
                data[i] = data[i].replace("\"\"", "\"");
            }
        }
        int max = 4;
        for (int i = 0; i < data.length; i++) {
            col.add(data[i]);
            if(data[i] == null)
                continue;
            if(max < data[i].length())
                max = data[i].length();
        }

        this.maxsize = max;
    }
    int getMaxsize() { return this.maxsize; }
    void setMaxsize()
    {
        boolean flag = false;
        int max = 4;
        for(int i = 0 ; i < col.size() ; i++)
        {
            try {
                if (this.col.get(i).length() > max) {
                    max = this.col.get(i).length();
                    flag = true;
                }
            }
            catch(NullPointerException e)
            {
                continue;
            }
        }
        if(flag) {
            this.maxsize = max;
        }
        else return;
    }
    void setMaxsize(int n)
    {
        this.maxsize = n;
    }


    @Override
    public String getHeader() {
        return this.col.get(0);
    }

    @Override
    public String getValue(int index) { return col.get(index);
    }

    @Override
    public <T extends Number> T getValue(int index, Class<T> t) {
        return t.cast(Integer.parseInt(this.col.get(index+1)));

    }

    @Override
    public void setValue(int index, String value) {
        this.col.set(index, value);
    }

    @Override
    public <T extends Number> void setValue(int index, T value) {
        this.col.set(index, String.valueOf(value));
    }

    @Override
    public int count() {return col.size()-1;}

    @Override
    public void print() {

    }

    @Override
    public boolean isNumericColumn() {
        for(int i = 1 ; i < col.size() ; i++)
        {
            if(col.get(i) == null)
                continue;
            try{
                Integer.parseInt(col.get(i));
                this.type = "int";
                continue;
            }
            catch(NumberFormatException e)
            {
                try {
                    Double.parseDouble(col.get(i));
                    this.type = "double";
                }
                catch(NumberFormatException ex)
                {
                    return false;
                }
            }

        }
        return true;
    }

    @Override
    public long getNullCount() {
        int cnt = 0;
        for (int i = 1; i < col.size(); i++) {
            if (col.get(i) == null) {
                cnt++;
            }
        }
        return cnt;
    }

    @Override
    public long getNumericCount() {
        int cnt = 0;
        for(int i = 1 ; i < col.size() ; i++)
        {
            if(col.get(i) == null)
                continue;
            try{
                Integer.parseInt(col.get(i));
                cnt++;
            }
            catch(NumberFormatException e)
            {
                try {
                    Double.parseDouble(col.get(i));
                    cnt++;
                }
                catch(NumberFormatException ex)
                {
                    continue;
                }
            }
        }
        return cnt;
    }

    @Override
    public double getNumericMin() {
        if(this.type == "String")
            throw  new NumberFormatException();
        double result;
        int t = 1;
        while(true) {
            if (col.get(t) != null) {
                result = Double.parseDouble(col.get(t));
                break;
            }
            else t++;
        }
        for(int i = t ; i < col.size() ; i++)
        {
            if(col.get(i)==null)
                continue;
            try {
                if (i == 1)
                    result = Double.parseDouble(col.get(i));
                if (result > Double.parseDouble(col.get(i)))
                    result = Double.parseDouble(col.get(i));
            }
            catch(NumberFormatException e)
            {
                continue;
            }
        }
        return result;
    }

    @Override
    public double getNumericMax() {

        if(this.type == "String")
            throw  new NumberFormatException();

        double result;
        int t = 1;
        while(true) {
            if (col.get(t) != null) {
                result = Double.parseDouble(col.get(t));
                break;
            }
            else t++;
        }
        for(int i = t ; i < col.size() ; i++)
        {
            if(col.get(i)==null)
                continue;
            try {
                if (i == 1)
                    result = Double.parseDouble(col.get(i));
                if (result < Double.parseDouble(col.get(i)))
                    result = Double.parseDouble(col.get(i));
            }
            catch(NumberFormatException e)
            {
                continue;
            }
        }
        return result;
    }

    @Override
    public double getMean() {
        double average = 0;
        double cnt = 0;
        isNumericColumn();
        if(this.type == "String")
            throw new NumberFormatException();
        for(int i = 1 ; i < col.size() ; i++)
        {
            if(col.get(i)==null)
                continue;
            average += Double.parseDouble(col.get(i));
            cnt++;
        }
        return average/cnt;
    }

    @Override
    public double getStd(){
        if(this.type == "String")
            throw  new NumberFormatException();
        double mean = this.getMean();
        double sum = 0;
        for(int i = 1 ; i < col.size() ; i++)
        {
            if(col.get(i)==null)
                continue;
            sum += Math.pow((Double.parseDouble(col.get(i)) - mean) , 2);
        }
        sum = sum / (col.size()-getNullCount()-2);
        return Math.sqrt(sum);
    }

    @Override
    public double getQ1() {
        if(this.type == "String")
            throw new NumberFormatException();
        List<Double> temp = new ArrayList<>();

        for(int i = 1 ; i < this.col.size() ; i++) {
            if (this.col.get(i) != null) {
                try {
                    temp.add(Double.parseDouble(this.col.get(i)));
                } catch (NumberFormatException e) {
                    continue;
                }
            }
            else continue;
        }

        temp.sort(null);

        double div = (temp.size()-1)*0.25;
        if(div-(int)div != 0)
        {
            if(div-(int)div > 0.5)
            {
                return (temp.get((int) div) * (1 - (div-(int)div)) + temp.get((int)div+1 ) * (div-(int)div))/2.0;
            }
            else if(div-(int)div < 0.5)
            {
                return (temp.get( (int)div ) * (1-(div-(int)div)) + temp.get( (int)div+1) * (div-(int)div));
            }
            else
            {
                return temp.get((int) div) * 0.5 + temp.get((int)div + 1) * 0.5;
            }
        }
        else {
            return temp.get((int)div);
        }
    }


    @Override
    public double getMedian() {
        if(this.type == "String")
            throw new NumberFormatException();
        List<Double> temp = new ArrayList<>();

        for(int i = 1 ; i < this.col.size() ; i++) {
            if (this.col.get(i) != null) {
                try {
                    temp.add(Double.parseDouble(this.col.get(i)));
                } catch (NumberFormatException e) {
                    continue;
                }
            }
            else continue;
        }

        temp.sort(null);
        if(temp.size() % 2 == 0)
            return (temp.get(temp.size()/2)+temp.get(temp.size()/2+1))/2.0;
        else return temp.get(temp.size()/2);
    }

    @Override
    public double getQ3() {
        if(this.type == "String")
            throw new NumberFormatException();
        List<Double> temp = new ArrayList<>();

        for(int i = 1 ; i < this.col.size() ; i++) {
            if (this.col.get(i) != null) {
                try {
                    temp.add(Double.parseDouble(this.col.get(i)));
                } catch (NumberFormatException e) {
                    continue;
                }
            }
            else continue;
        }

        temp.sort(null);

        double div = (temp.size()-1)*0.75;
        if(div-(int)div != 0)
        {
            if((div - (int)div) == 0.5 )
            {
                return temp.get((int) div) * 0.5 + temp.get((int)div + 1) * 0.5;
            }
            else
            {
                return (temp.get( (int)div ) * (1-(div-(int)div)) + temp.get( (int)div+1) * (div-(int)div));
            }
        }
        else {
            return temp.get((int)div);
        }
    }

    @Override
    public boolean fillNullWithMean() {
        return false;
    }

    @Override
    public boolean fillNullWithZero() {
        return false;
    }

    @Override
    public boolean standardize() {
        return false;
    }

    @Override
    public boolean normalize() {
        return false;
    }

    @Override
    public boolean factorize() {
        return false;
    }
}
