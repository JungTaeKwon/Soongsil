package problem1;

public enum LogLevel {
    TRACE(1), // for finer-grained informational events
    DEBUG(2), // for fine-grained informational events that are most useful to debug an application
    INFO(3), // for informational messages that highlight the progress of the application at coarse-grained level.
    WARN(4), // for potentially harmful situations.
    ERROR(5); // for error events that might still allow the application to continue running

    final int level;

    LogLevel(int level) {
        this.level = level;
    }
}