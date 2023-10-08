
namespace timeutil {

    /// Get time in seconds since some arbitrary point in the past
    /// @returns Time, in seconds
    double time_sec();
    
    /// Sleep for some number of seconds
    /// @param Duration, in seconds
    void sleep(double duration);
};
