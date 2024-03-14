package csv;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.function.Predicate;

import static java.lang.Integer.parseInt;

class TableImple implements Table {
    List<ColumnImpl> col = new ArrayList<>();
    File file;

    TableImple() {
    }

    TableImple(File file){
        try {
            this.file = file;
            String[][] temp = null;
            BufferedReader r = new BufferedReader(new FileReader(file));
            String line;

            int k = 0;
            while ((line = r.readLine()) != null) {
                String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                if (k == 0) {
                    temp = new String[(int) Files.lines(Path.of(file.getPath())).count()][arr.length];
                    col = new ArrayList<>(arr.length);
                }
                for (int i = 0; i < arr.length; i++) {
                    temp[k][i] = arr[i];
                }
                k++;
            }
            for (int i = 0; i < temp[i].length; i++) {
                String[] arr = new String[(int) Files.lines(Path.of(file.getPath())).count()];
                for (int j = 0; j < temp.length; j++)
                    arr[j] = temp[j][i];
                col.add(new ColumnImpl(arr));
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    TableImple(File file, int n, boolean flag){
        if (flag == true) {
            this.file = file;
            String[][] temp = null;
            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;

                int k = 0;
                while (k < n) {
                    line = r.readLine();
                    String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                    if (k == 0) {
                        temp = new String[n][arr.length];
                        col = new ArrayList<ColumnImpl>(arr.length);

                    }
                    for (int i = 0; i < arr.length; i++) {
                        temp[k][i] = arr[i];
                    }
                    k++;
                }
                for (int i = 0; i < temp[1].length; i++) {
                    String[] arr = new String[n];
                    for (int j = 0; j < temp.length; j++)
                        arr[j] = temp[j][i];
                    col.add(new ColumnImpl(arr));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else if (flag == false) {
            this.file = file;
            String[][] temp = null;
            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;

                String first = r.readLine();
                for (int i = 1; i < (int) Files.lines(Path.of(file.getPath())).count() - n + 1; i++)
                    r.readLine();
                int k = 0;
                while (k < n) {
                    if (k == 0)
                        line = first;
                    else
                        line = r.readLine();
                    String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                    if (k == 0) {
                        temp = new String[n][arr.length];
                        col = new ArrayList<>(arr.length);
                    }
                    for (int i = 0; i < arr.length; i++) {
                        temp[k][i] = arr[i];
                    }
                    k++;
                }
                for (int i = 0; i < temp[1].length; i++) {
                    String[] arr = new String[n];
                    for (int j = 0; j < temp.length; j++) {
                        arr[j] = temp[j][i];
                    }
                    col.add(new ColumnImpl(arr));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    TableImple(File file, int begin, int end, boolean flag) {
        if (flag) {
            this.file = file;
            String[][] temp = null;
            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;

                for (int i = 0; i < begin; i++)
                    r.readLine();
                int k = 0;
                while (k < end) {
                    line = r.readLine();
                    String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                    if (k == 0) {
                        temp = new String[end - begin][arr.length];
                        col = new ArrayList<>(arr.length);
                    }
                    for (int i = 0; i < arr.length; i++) {
                        temp[k][i] = arr[i];
                    }
                    k++;
                }
                for (int i = 0; i < temp[1].length; i++) {
                    String[] arr = new String[end - begin];
                    for (int j = 0; j < temp.length; j++)
                        arr[j] = temp[j][i];
                    col.add(new ColumnImpl(arr));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            this.file = file;
            String[][] temp = null;

            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;

                int k = 0;
                while ((line = r.readLine()) != null) {
                    try {
                        String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                        if (k == 0) {
                            temp = new String[(int) Files.lines(Path.of(file.getPath())).count()][arr.length];
                            col = new ArrayList<>(arr.length);
                        }
                        for (int i = 0; i < arr.length; i++) {
                            temp[k][i] = arr[i];
                        }
                        k++;
                    } catch (IOException e) {
                        e.printStackTrace();
                        continue;
                    }
                }
                int cnt = 0;
                for (int i = 0; i < temp[i].length; i++) {
                    String[] arr = new String[(int) Files.lines(Path.of(file.getPath())).count()];
                    for (int j = 0; j < temp.length; j++)
                        arr[j] = temp[j][i];
                    if (cnt >= begin && cnt < end)
                        col.add(new ColumnImpl(arr));
                    cnt++;
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    TableImple(File file, boolean flag, int... ind)  {
        if (flag) {
            this.file = file;
            String[][] temp = null;
            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line = null;
                String first = r.readLine();
                int k = 0;
                line = first;
                String[] array = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                temp = new String[ind.length + 1][array.length];
                col = new ArrayList<ColumnImpl>(array.length);
                for (int j = 0; j < array.length; j++) {
                    temp[k][j] = array[j];
                }
                k++;
                boolean flag2 = false;
                for (int i : ind) {
                    if (flag2) r = new BufferedReader(new FileReader(file));
                    while (true) {
                        flag2 = true;
                        line = r.readLine();
                        String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                        if (Integer.toString(i + 1).equals(arr[0])) {
                            for (int j = 0; j < arr.length; j++) {
                                temp[k][j] = arr[j];
                            }
                            k++;
                            break;
                        }
                    }
                }
                for (int i = 0; i < temp[1].length; i++) {
                    String[] arr = new String[ind.length + 1];
                    for (int j = 0; j < temp.length; j++)
                        arr[j] = temp[j][i];
                    col.add(new ColumnImpl(arr));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            this.file = file;
            String[][] temp = null;
            try {
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;

                int k = 0;
                while ((line = r.readLine()) != null) {
                    String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                    if (k == 0) {
                        temp = new String[(int) Files.lines(Path.of(file.getPath())).count()][arr.length];
                        col = new ArrayList<ColumnImpl>(arr.length);
                    }
                    for (int i = 0; i < arr.length; i++) {
                        temp[k][i] = arr[i];
                    }
                    k++;
                }
                int cnt = 0;
                for (int d : ind) {
                    cnt = 0;
                    for (int i = 0; i < temp[i].length; i++) {
                        String[] arr = new String[(int) Files.lines(Path.of(file.getPath())).count()];
                        for (int j = 0; j < temp.length; j++)
                            arr[j] = temp[j][i];
                        if (d == cnt)
                            col.add(new ColumnImpl(arr));
                        cnt++;
                    }
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    TableImple(Table table) {
        for (int i = 0; i < table.getColumnCount(); i++) {
            this.col.add((ColumnImpl) table.getColumn(i));
        }
    }

    private String getLongestIndexName()
    {
        String result = this.col.get(0).getValue(0);
        for(int i = 0 ; i < this.col.size() ; i++)
        {
            if(this.col.get(i).getValue(0).length() > result.length())
            {
                result = this.col.get(i).getValue(0);
            }
        }
        return result;
    }

    Table selectOneRow(TableImple table, int ind)
    {
        TableImple temp = new TableImple();
        String[][] arr = new String[2][table.col.size()];
        for(int i = 0 ; i < table.col.size() ; i++)
        {
            arr[0][i] = table.col.get(i).getValue(0);
        }

        for(int i = 0 ; i < table.col.size() ; i++)
        {
            arr[1][i] = table.col.get(i).getValue(ind+1);
        }
        for(int i = 0 ; i < table.col.size() ; i++)
        {
            String[] arr2 = new String[2];
            for(int j = 0 ; j < arr2.length ; j++)
            {
                arr2[j] = arr[j][i];
            }
            temp.col.add(new ColumnImpl(arr2));
        }
        return temp;
    }

    private int stringCompare(String str1, String str2) {

        int l1 = str1.length();
        int l2 = str2.length();
        int lmin = Math.min(l1, l2);

        for (int i = 0; i < lmin; i++) {
            int str1_ch = (int) str1.charAt(i);
            int str2_ch = (int) str2.charAt(i);

            if (str1_ch != str2_ch) {
                return str1_ch - str2_ch;
            }
        }

        if (l1 != l2) {
            return l1 - l2;
        } else {
            return 0;
        }
    }

    @Override
    public String toString() {
        System.out.println("<csv.Table" + "@" + Integer.toHexString(hashCode()) + ">");
        System.out.println(col.get(0).count() + " entries, 0 to " + (col.get(0).count() - 1));
        System.out.println("Data columns (total " + col.size() + " columns):");
        System.out.printf("%2s | %10s |Non-Null Count | Dtype", "#", "Column");
        System.out.println();
        String[] check = new String[12];

        for (int i = 0; i < 12; i++) {
            try {
                for (int k = 1; k < (int) Files.lines(Path.of(file.getPath())).count(); k++) {
                    if (col.get(i).getValue(k) == null)
                        continue;
                    try {
                        parseInt(col.get(i).getValue(k));
                        check[i] = "int";
                        continue;
                    } catch (NumberFormatException e) {
                        try {
                            Double.parseDouble(col.get(i).getValue(k));
                            check[i] = "double";
                            break;
                        } catch (NumberFormatException ex) {
                            check[i] = "String";
                            break;
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        for (int i = 0; i < col.size(); i++) {
            System.out.printf("%2d" + " |" + "%11s" + " |  " + (col.get(i).count() - col.get(i).getNullCount()) + " non-null | " + check[i], i, col.get(i).getValue(0));
            System.out.println();
        }
        int[] arr = new int[3];
        for (int i = 0; i < check.length; i++) {
            if (check[i].equals("double")) {
                arr[0]++;
            } else if (check[i].equals("int")) {
                arr[1]++;
            } else arr[2]++;
        }

        String result = "dtypes : double(" + arr[0] + "), int(" + arr[1] + "), String(" + arr[2] + ")\n";
        return result;
    }

    @Override
    public void print() {

        for (int k = 0; k < col.size(); k++) {
            try {
                System.out.printf(String.format("%" + col.get(k).getMaxsize() + "s", col.get(k).getValue(0)) + " | ");
            } catch (UnknownFormatConversionException e) {
                String s = col.get(k).getValue(1);
                s = s.replace("%", "%%");
                System.out.printf(String.format("  %" + col.get(k).getMaxsize() + "s", s + " | "));
            }
        }
        System.out.println("\b");

        for(int i = 1; i < (this.col.get(0)).col.size(); i++) {
            for(int k = 0; k < this.col.size(); ++k) {
                if (this.col.get(k).getValue(i) == null) {
                    System.out.printf(String.format("%" + col.get(k).getMaxsize() + "s", col.get(k).getValue(i)) + " | ");
                }
                else {
                    this.col.get(k).isNumericColumn();
                    if (this.col.get(k).getType() == "String" || this.col.get(k).getType() == "int") {
                        try {
                            System.out.printf(String.format("%" + col.get(k).getMaxsize() + "s", col.get(k).getValue(i)) + " | ");
                        } catch (UnknownFormatConversionException e) {
                            String s = this.col.get(k).getValue(i);
                            s = s.replace("%", "%%");
                            System.out.printf(String.format("  %" + ((ColumnImpl)this.col.get(k)).getMaxsize() + "s", s + " | "));
                        }
                    }
                    else {
                        try {
                            if(Double.parseDouble(this.col.get(k).getValue(i)) - (int)Double.parseDouble(this.col.get(k).getValue(i))==0)
                            {
                                System.out.printf(String.format("%" + col.get(k).getMaxsize() + "s", col.get(k).getValue(i)) + " | ");
                            }
                            else
                                System.out.printf(String.format("%" + col.get(k).getMaxsize() + "s", Math.round(Double.parseDouble(this.col.get(k).getValue(i)) * 1000000.0) / 1000000.0) + " | ");
                        }
                        catch (UnknownFormatConversionException e) {
                            String s = this.col.get(k).getValue(i);
                            s = s.replace("%", "%%");
                            System.out.printf(String.format("  %" + this.col.get(k).getMaxsize() + "s", s + " | "));
                        }
                    }
                }
            }
            System.out.println("\b");
        }

    }

    @Override
    public Table getStats() {
        TableImple temp = new TableImple();
        String[] arrr = {" ", "count", "mean", "std", "min", "25%", "50%", "75%", "max"};
        temp.col.add(new ColumnImpl(arrr));

        for (int i = 0; i < col.size(); i++) {
            try {
                col.get(i).isNumericColumn();

                String[] arr = new String[9];
                arr[0] = this.col.get(i).getValue(0);
                arr[1] = Long.toString(this.col.get(i).count() - this.col.get(i).getNullCount());
                arr[2] = Double.toString(this.col.get(i).getMean());
                arr[3] = Double.toString(this.col.get(i).getStd());
                arr[4] = Double.toString(this.col.get(i).getNumericMin());
                arr[5] = Double.toString(this.col.get(i).getQ1());
                arr[6] = Double.toString(this.col.get(i).getMedian());
                arr[7] = Double.toString(this.col.get(i).getQ3());
                arr[8] = Double.toString(this.col.get(i).getNumericMax());
                temp.col.add(new ColumnImpl(arr));
            } catch (NumberFormatException e) {

                boolean flag = false;
                for (int j = 1; j < this.col.get(0).count(); j++) {
                    try {
                        Double.parseDouble(col.get(i).getValue(j));
                        flag = true;
                    } catch (NumberFormatException ex) {
                        col.get(i).setValue(j, (String) null);
                        continue;
                    } catch (NullPointerException ex) {
                        continue;
                    }
                }

                if (flag) {

                    try {
                        col.get(i).isNumericColumn();
                        col.get(i).setType("double");
                        String[] arr = new String[9];
                        arr[0] = this.col.get(i).getValue(0);
                        arr[1] = Long.toString(this.col.get(i).count() - this.col.get(i).getNullCount());
                        arr[2] = Double.toString(this.col.get(i).getMean());
                        arr[3] = Double.toString(this.col.get(i).getStd());
                        arr[4] = Double.toString(this.col.get(i).getNumericMin());
                        arr[5] = Double.toString(this.col.get(i).getQ1());
                        arr[6] = Double.toString(this.col.get(i).getMedian());
                        arr[7] = Double.toString(this.col.get(i).getQ3());
                        arr[8] = Double.toString(this.col.get(i).getNumericMax());
                        temp.col.add(new ColumnImpl(arr));

                    } catch (NumberFormatException ex) {
                        continue;
                    }

                }


            }
        }
        System.out.println();

        for(int j = 0 ; j < temp.col.size() ; j++)
        {
            try {
                if (temp.col.get(j).getValue(0).equals(" ") == false && temp.col.get(j).getValue(0) != null) {
                    try {
                        int size = String.valueOf((Math.round(Double.parseDouble(temp.col.get(j).getValue(1)) * 1000000) / 1000000.0)).length();
                        for (int t = 1; t < temp.col.get(j).count(); t++) {
                            String.valueOf((Math.round(Double.parseDouble(temp.col.get(j).getValue(t)) * 1000000) / 1000000.0));
                            if (size < String.valueOf((Math.round(Double.parseDouble(temp.col.get(j).getValue(t)) * 1000000) / 1000000.0)).length()) {
                                size = String.valueOf((Math.round(Double.parseDouble(temp.col.get(j).getValue(t)) * 1000000) / 1000000.0)).length();
                            } else {
                                continue;
                            }
                        }
                        temp.col.get(j).setMaxsize(size);
                    } catch (NumberFormatException e) {
                        continue;
                    }
                } else {
                    continue;
                }
            }
            catch(NullPointerException e)
            {
                continue;
            }
        }
        for(int i = 1 ; i < temp.col.size() ; i++) {
            if (temp.col.get(i).getMaxsize() < temp.col.get(i).getValue(0).length()) {
                temp.col.get(i).setMaxsize(temp.col.get(i).getValue(0).length());
            }
        }

        return temp;
    }

    @Override
    public Table head()  {
        TableImple temp = new TableImple(file, 6, true);
        return temp;
    }

    @Override
    public Table head(int lineCount) {
        TableImple temp = new TableImple(file, lineCount + 1, true);
        return temp;
    }

    @Override
    public Table tail(){
        TableImple temp = new TableImple(file, 6, false);
        return temp;
    }

    @Override
    public Table tail(int lineCount) {
        TableImple temp = new TableImple(file, lineCount + 1, false);
        return temp;
    }

    @Override
    public Table selectRows(int beginIndex, int endIndex) {
        TableImple temp = new TableImple(file, beginIndex, endIndex + 1, true);
        return temp;
    }

    @Override
    public Table selectRowsAt(int... indices) {
        if(indices.length == 1)
        {
            return selectOneRow(this, indices[0]);
        }
        TableImple temp = new TableImple(file, true, indices);
        return temp;
    }

    @Override
    public Table selectColumns(int beginIndex, int endIndex) {
        TableImple temp = new TableImple(file, beginIndex, endIndex, false);
        return temp;
    }

    @Override
    public Table selectColumnsAt(int... indices) {
        TableImple temp = new TableImple(file, false, indices);
        return temp;
    }

    @Override
    public <T> Table selectRowsBy(String columnName, Predicate<T> predicate){
        List<String> save = new ArrayList<>();
        save.add("0");
        for(int i = 0 ; i < this.col.size() ; i++) {
            if (this.col.get(i).getValue(0).equals(columnName)) {
                for (int j = 1; j < this.col.get(i).count(); j++) {
                    try {
                        if (predicate.test((T) this.col.get(i).getValue(j))) {
                            save.add(String.valueOf(j));
                        }
                    }
                    catch (ClassCastException e) {
                        try {
                            Double d = Double.parseDouble(this.col.get(i).getValue(j));
                            if(predicate.test((T) d)){
                                save.add(String.valueOf(j));
                            }
                        }
                        catch(NumberFormatException ex)
                        {
                            continue;
                        }
                        catch(ClassCastException ex)
                        {
                            try {

                                Integer a = Integer.parseInt(this.col.get(i).getValue(j));
                                if (predicate.test((T) a)) {
                                    save.add(String.valueOf(j));
                                }
                            }
                            catch(NumberFormatException exc)
                            {
                                Integer a = (int)Double.parseDouble(this.col.get(i).getValue(j));
                                if (predicate.test((T) a)) {
                                    save.add(String.valueOf(j));
                                }
                            }
                        }
                    }
                    catch(NullPointerException e)
                    {
                        continue;
                    }
                }
            }
        }

        TableImple table = new TableImple();
        for(int i = 0 ; i < this.col.size() ; i++)
            table.col.add(new ColumnImpl());
        for(int i = 0 ; i < this.col.size() ; i++)
        {
            List<String> arr = new ArrayList<>(save.size());
            for(int j = 0 ; j < save.size() ; j++)
            {
                arr.add(this.col.get(i).getValue(parseInt(save.get(j))));
            }

            for(int j = 0 ; j < arr.size() ; j++)
                table.col.get(i).col.add(arr.get(j));
            table.col.get(i).setMaxsize();
        }

        return table;
    }

    @Override
    public Table sort(int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
        if (isAscending) {
            for (int n = 1; n < this.col.get(1).count(); n++) {
                for (int i = n + 1; i < this.col.get(1).count() + 1; i++) {
                    try {
                        if (isNullFirst) {
                            try {
                                if (this.col.get(byIndexOfColumn).getValue(n) == null || Double.parseDouble(this.col.get(byIndexOfColumn).getValue(n)) > Double.parseDouble(this.col.get(byIndexOfColumn).getValue(i))) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            } catch (NumberFormatException e) {
                                if ((this.col.get(byIndexOfColumn).getValue(n) == null) || stringCompare(this.col.get(byIndexOfColumn).getValue(n), this.col.get(byIndexOfColumn).getValue(i)) == 1 ? true : false) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            }
                        } else {
                            try {
                                if (this.col.get(byIndexOfColumn).getValue(n) == null || Double.parseDouble(this.col.get(byIndexOfColumn).getValue(n)) > Double.parseDouble(this.col.get(byIndexOfColumn).getValue(i))) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            } catch (NumberFormatException e) {
                                if ((this.col.get(byIndexOfColumn).getValue(n) == null) || stringCompare(this.col.get(byIndexOfColumn).getValue(n), this.col.get(byIndexOfColumn).getValue(i)) == 1 ? true : false) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            }
                        }

                    } catch (NumberFormatException e) {
                        continue;
                    } catch (NullPointerException ex) {
                        continue;
                    }
                }
            }
        } else {
            for (int n = 1; n < this.col.get(1).count(); n++) {
                for (int i = n + 1; i < this.col.get(1).count() + 1; i++) {
                    try {
                        if (isNullFirst) {
                            try {
                                if (this.col.get(byIndexOfColumn).getValue(i) == null || Double.parseDouble(this.col.get(byIndexOfColumn).getValue(n)) < Double.parseDouble(this.col.get(byIndexOfColumn).getValue(i))) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);

                                    }
                                }
                            } catch (NumberFormatException e) {
                                if ((this.col.get(byIndexOfColumn).getValue(n) == null) || stringCompare(this.col.get(byIndexOfColumn).getValue(n), this.col.get(byIndexOfColumn).getValue(i)) == -1 ? true : false) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            }
                        } else {
                            try {
                                if (this.col.get(byIndexOfColumn).getValue(n) == null || Double.parseDouble(this.col.get(byIndexOfColumn).getValue(n)) < Double.parseDouble(this.col.get(byIndexOfColumn).getValue(i))) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            } catch (NumberFormatException e) {
                                if ((this.col.get(byIndexOfColumn).getValue(n) == null) || stringCompare(this.col.get(byIndexOfColumn).getValue(n), this.col.get(byIndexOfColumn).getValue(i)) == 1 ? false : true) {
                                    String[] arr = new String[col.size()];
                                    for (int j = 0; j < col.size(); j++) {
                                        arr[j] = this.col.get(j).getValue(n);
                                    }

                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(n, this.col.get(j).getValue(i));
                                    }
                                    for (int j = 0; j < col.size(); j++) {
                                        this.col.get(j).setValue(i, arr[j]);
                                    }
                                }
                            }
                        }

                    } catch (NumberFormatException e) {
                        continue;
                    } catch (NullPointerException ex) {
                        continue;
                    }
                }
            }
        }
        return this;
    }

    @Override
    public Table shuffle(){
        TableImple temp = new TableImple(file);
        while (true) {
            try {
                Collections.shuffle(this.col.get(0).col);
                for (int i = 0; i < this.col.size(); i++) {
                    for (int j = 1; j < this.col.get(0).count() + 1; j++) {
                        this.col.get(i).col.set(parseInt(this.col.get(0).getValue(j)), temp.getColumn(i).getValue(j));
                    }
                }
                this.col.get(0).setValue(0, temp.col.get(0).getValue(0));
                break;
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return this;
    }

    @Override
    public int getRowCount() {
        return this.col.get(0).count();
    }

    @Override
    public int getColumnCount() {
        return this.col.size();
    }

    @Override
    public Column getColumn(int index) {
        return this.col.get(index);
    }

    @Override
    public Column getColumn(String name) {
        for(int i = 0 ; i < this.col.size() ; i++)
        {
            if(this.col.get(i).getValue(0).equals(name)) {
                return this.col.get(i);
            }
            else continue;
        }
        return null;
    }

    @Override
    public boolean fillNullWithMean() {
        boolean result = false;
        double mean;

        for (int i = 0; i < this.col.size(); i++){
            this.col.get(i).isNumericColumn();
            if(this.col.get(i).getType() == "String")
            {
                continue;
            }
            try {
                mean = Math.round(this.col.get(i).getMean() * 1000000) / 1000000.0;
                for (int j = 1; j < this.col.get(i).count(); j++) {
                    if (this.col.get(i).getValue(j) == null) {
                        result = true;
                        this.col.get(i).setValue(j, String.valueOf(mean));
                    }
                }
                this.col.get(i).setMaxsize();
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return result;
    }

    @Override
    public boolean fillNullWithZero() {
        boolean result = false;
        for (int i = 0; i < this.col.size(); i++) {
            this.col.get(i).isNumericColumn();
            if(this.col.get(i).getType() == "String")
            {
                continue;
            }
            try {
                for (int j = 1; j < this.col.get(i).count(); j++) {
                    if (this.col.get(i).getValue(j) == null) {
                        result = true;
                        this.col.get(i).setValue(j, "0");
                    }
                }
                this.col.get(i).setMaxsize();
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return result;
    }

    @Override
    public boolean standardize() {
        boolean flag = false;
        double mean;
        double std;

        for (int i = 0; i < this.col.size(); i++) {
            this.col.get(i).isNumericColumn();
            if(this.col.get(i).getType() != "String")
            {this.col.get(i).setMaxsize(getLongestIndexName().length());}
            try {
                mean = this.col.get(i).getMean();
                std = this.col.get(i).getStd();
                for (int j = 1; j < this.col.get(i).count() + 1; j++) {
                    this.col.get(i).isNumericColumn();
                    try {
                        this.col.get(i).setValue(j, String.valueOf(((Double.parseDouble(this.col.get(i).getValue(j)) - mean) / std)));
                        flag = true;
                    } catch (NullPointerException ex) {
                        continue;
                    }
                }
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return flag;
    }

    @Override
    public boolean normalize() {
        boolean flag = false;
        for (int i = 0; i < this.col.size(); i++) {
            try {
                this.col.get(i).isNumericColumn();
                if(this.col.get(i).getType() != "String")
                {this.col.get(i).setMaxsize(getLongestIndexName().length());}
                double max = this.col.get(i).getNumericMax();
                double min = this.col.get(i).getNumericMin();
                for (int j = 1; j < this.col.get(i).count() + 1; j++) {
                    try {
                        this.col.get(i).setValue(j, (Double.parseDouble(this.col.get(i).getValue(j)) - min) / (max - min));
                        flag = true;
                    } catch (NullPointerException ex) {
                        continue;
                    }
                }
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return flag;
    }

    @Override
    public boolean factorize() {
        boolean flag = false;

        for (int i = 0; i < this.col.size(); i++) {
            List<String> checkArray = new ArrayList<>();
            int cnt = 1;
            while (true) {
                if (this.col.get(i).getValue(cnt) != null) {
                    checkArray.add(this.col.get(i).getValue(cnt));
                    break;
                }
                else {
                    cnt++;
                    continue;
                }
            }
            for (int j = 2; j < this.col.get(i).count(); j++) {
                boolean check = true;
                try{
                    for (int k = 0; k < checkArray.size(); k++) {
                        if (this.col.get(i).getValue(j).equals(checkArray.get(k)))
                            check = false;
                        else
                            continue;
                    }
                    if(check)
                        checkArray.add(this.col.get(i).getValue(j));
                }
                catch(NullPointerException e)
                {
                    continue;
                }
            }
            if (checkArray.size() > 2)
                continue;
            else {
                flag = true;
                String s1 = this.col.get(i).getValue(1);
                if(this.col.get(i).getValue(1).equals("0"))
                {
                    continue;
                }
                for (int j = 2; j < this.col.get(i).count()+1; j++) {
                    if(this.col.get(i).getValue(j) == null){
                        continue;
                    }
                    else {
                        if (s1.equals(this.col.get(i).getValue(j))) {
                            this.col.get(i).setValue(j, "1");
                        } else {
                            this.col.get(i).setValue(j, "0");
                        }
                    }
                }
            }
            this.col.get(i).setValue(1,"1");
            this.col.get(i).setMaxsize();
            this.col.get(i).setType("int");
            this.col.get(i).isNumericColumn();
        }

        return flag;
    }
}