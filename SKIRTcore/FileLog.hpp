/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef FILELOG_HPP
#define FILELOG_HPP

#include <mutex>
#include <QFile>
#include <QTextStream>
#include "Log.hpp"
#include "MemoryLogger.hpp"

////////////////////////////////////////////////////////////////////

/** FileLog inherits from Log and implements thread-safe logging to a file. The file has a fixed
    name <tt>prefix_log.txt</tt> and is placed in the output filepath provided by the FilePaths
    instance attached to the simulation hierarchy at setup time. The log text is written in UTF-8
    encoding. All functions in this class are re-entrant; the output() function is thread-safe. */
class FileLog : public Log, public MemoryLogger
{
    Q_OBJECT

    //============= Construction - Setup - Destruction =============

public:
    /** The default constructor does nothing; the log file is opened during setup. */
    FileLog();

    /** The destructor closes the log file, if it is open. */
    ~FileLog();

    /** Setter for the _limit attribute. */
    void setLimit(double value);

    /** This function writes a log message stating the amount of memory acquired or released during
        a resize operation of an Array instance. */
    void memory(size_t oldsize, size_t newsize, void *ptr);

protected:
    /** This function constructs the filename and opens the log file, overwriting any existing file
        with the same name. */
    virtual void setupSelfBefore();

    /** This function provides the implementation of opening the file, called by setupSelfBefore().
        With multiple processes and when not in verbose mode, this function can be called later on
        when a warning or error is encountered on one of the processes. */
    void open();

    //======================== Other Functions =======================

protected:
    /** This function outputs a message to the file. It overrides the pure virtual function in the
        base class. This function is thread-safe.*/
    void output(QString message, Level level);

    //======================== Data Members ========================

private:
    std::mutex _mutex;   // mutex to guard the input/output operations
    QFile _file;
    QTextStream _out;
    double _limit;      // the lower limit for memory (de)allocation logging
};

////////////////////////////////////////////////////////////////////

#endif // FILELOG_HPP
