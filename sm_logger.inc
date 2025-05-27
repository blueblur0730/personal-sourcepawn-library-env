#if defined _sm_logger_included
 #endinput
#endif
#define _sm_logger_included

#define MAX_LOGGERNAME_LENGTH 64
#define MAX_LOGGER_PREFIX_LENGTH 32
#define MAX_LOG_LINE 512

#define DEFAULT_PATTERN "%F-%T %Z"

enum LoggerType {
    LoggerType_SourcemodLog = 0,
    LoggerType_NewLogFile,
};

enum LogLevel {
    LogLevel_Unknown = -1,
    LogLevel_Trace = 0,
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error,
    LogLevel_Critical,
    LogLevel_Disabled,

    LogLevel_Size = 7,
};

/*
static const char g_sLogLevel[LogLevel_Size][] = {
    "Trace",
    "Debug",
    "Info",
    "Warning",
    "Error",
    "Critical",
    "Disabled"
}
*/
/**
 * Callback for user defined error handler.
 * 
 * @param msg           Error message.
 * @param curTime       The current game time.
 * @param tick          The current game tick.
 * @param mapName       The name of the current map.
 * 
 * @returns             Plugin_Handled will prevent this msg from logged into the file, others otherwise.
*/
typedef LogErrorHandler = function Action (const char[] msg, float curTime, int tick, const char[] mapName);

methodmap UserLogger {
    /**
     * Creates a logger object.
     * 
     * @param sFileName     The file name to log to.
     * @param sPattern      The pattern to log with.
     * @param sLoggerName   The name of the logger.
     * @param lvl           The log level to log at.
     * @param type          The type of logger to create.
     * 
     * @returns             The logger object.
     * @error               Invalid file path.
    */
    public native UserLogger(const char[] sFileName = "", 
                    const char[] sPattern = "", 
                    const char[] sLoggerName, 
                    LogLevel lvl = LogLevel_Info, 
                    LoggerType type = LoggerType_SourcemodLog);

    /**
     * Deletes the logger object, which is its file handle.
     * Must be called to free the file handle.
    */
    public native void deleteThis();

    /**
     * Retrieves the logger name.
    */
    public native void GetName(char[] name, int maxlen);

    /**
     * Sets the logger pattern.
     * If not set, DEFAULT_PATTERN will be used. (see above)
    */
    public native void SetPattern(const char[] parttern);

    /**
     * Retrieves the logger pattern.
    */
    public native void GetPattern(char[] pattern, int maxlen);


    /**
     * Retrieves or set the logger level.
    */
    property LogLevel Level {
        public native get();
        public native set(LogLevel lvl);
    }

    /**
     * Retrieves or set the logger flush level.
    */
    property LogLevel FlushLevel {
        public native get();
        public native set(LogLevel lvl);
    }

    /**
     * Retrieves the logger type.
    */
    property LoggerType Type {
        public native get();
    }

    /**
     * Sets an error handler call back for this logger.
     * Will trigger when >= LogLevel_Error log is called.
    */
    public native void SetErrorHandler(LogErrorHandler handler);

    /**
     * Flushes the logger file.
    */
    public native void Flush();

    /**
     * Checks if the given level is able to be logged.
    */
    public native bool ShouldLog(LogLevel lvl);

    /**
     * Log a message.
     * 
     * @param lvl       Log level enum.
     * @param msg       Log message.
    */
    public native void Log(LogLevel lvl, const char[] msg);
    public native void LogEx(LogLevel lvl, const char[] fmt, any ...);

    public native void Trace(const char[] msg);
    public native void TraceEx(const char[] fmt, any ...);

    public native void Debug(const char[] msg);
    public native void DebugEx(const char[] fmt, any ...);

    public native void Info(const char[] msg);
    public native void InfoEx(const char[] fmt, any ...);

    public native void Warn(const char[] msg);
    public native void WarnEx(const char[] fmt, any ...);

    public native void Error(const char[] msg);
    public native void ErrorEx(const char[] fmt, any ...);

    public native void Critical(const char[] msg);
    public native void CriticalEx(const char[] fmt, any ...);

    public native void AddSink(UserSink sink);

    public native void RemoveSink(UserSink sink);
}

methodmap UserSink {
    property LogLevel Level {
        public native get();
        public native set(LogLevel lvl);
    }

    public native void SetPattern(const char[] pattern);
    public native void GetPattern(char[] pattern, int maxlen);

    public native bool ShouldLog(LogLevel lvl);
    public native void Log(LogLevel lvl, const char[] msg, const char[] sLoggerName);
}

methodmap UserServerConsoleSink < UserSink {
    /**
     * Creates a server console sink object.
     * 
     * @param lvl       The log level to log at.
    */
    public native UserServerConsoleSink(LogLevel lvl);

    public static native UserLogger CreateLogger(const char[] name);
}

methodmap UserClientChatSink < UserSink {
    /**
     * Creates a client chat sink object.
     * 
     * @param lvl       The log level to log at.
     * @param client    The client to log to.
    */
    public native UserClientChatSink(LogLevel lvl, int client = 0);

    property int Client {
        public native get();
        public native set(int client);
    }

    public static native UserLogger CreateLogger(const char[] name);
}

/**
 * Callback for user defined filter handler.
 * The dynamic array length must be equal to MaxClients.
*/
typedef ClientChatFilter = function void (int[] clients);

methodmap UserClientChatAllSink < UserSink {
    /**
     * Creates a client chat all sink object.
     * 
     * @param lvl       The log level to log at.
     * @param filter    The filter to log to. If not set, default filter will be used.
    */
    public native UserClientChatAllSink(LogLevel lvl, ClientChatFilter filter = null);

    property ClientChatFilter Filter {
        public native set(ClientChatFilter filter);
    }

    public static native UserLogger CreateLogger(const char[] name);
}