package problem1;

import java.io.PrintStream;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SimpleLogger {
    private LogLevel logLevel;
    private PrintWriter fileWriter;
    private List<String> logs;

    public void log(LogLevel level, String message) {
        // A log request of level p in a logger with level q is enabled if p >= q.
        // It assumes that levels are ordered. For the standard levels, we have TRACE < DEBUG < INFO < WARN < ERROR
        String log = String.format("[%s] [%s] %s", level, LocalDateTime.now(), message);
        if(level.ordinal() >= logLevel.ordinal()) {
            fileWriter.println(log);
            fileWriter.flush();
        }
        logs.add(log);
    }

    public int getNumLogs(){
        return logs.size();
    }

    public void clear(){
        // clear all previous messages in the list of logs
        logs.clear();
    }

    public void setHandler(PrintStream ps){
        // set output stream
        // if ps = new PrintStream(System.out), fileWriter will print a string into your console
        // if ps = new PrintStream(new FileOutputStream("...")), it will print a string into the target file
        // if ps = new PrintStream(OutputStream.nullOutputStream()), it will print nothing
        fileWriter = new PrintWriter(ps);
    }

    private SimpleLogger(){
        logLevel = LogLevel.INFO;
        logs = Collections.synchronizedList(new ArrayList());
        fileWriter = new PrintWriter(System.out); // default is set to the standard output
    }

    /**
     * ==============BEGIN==============
     * Complete the below code that requires your implementation
     * If necessary, you can make your own methods or classes so that the corresponding tests are passed
     */

    public static SimpleLogger getInstance() {
        return null;
    }

    /**
     * ===============END===============
     */
}

