#ifndef _LOGGER_HPP_INCLUDED
#define _LOGGER_HPP_INCLUDED

#include <stdint.h>
#include <log4cxx/logger.h>

class SignalGuard_ex;
class Logger;

// This macro needs to appear in every cpp file in order to use the macros below.

// Determine the default logger, i.e. the logger used by FMT_DEBUG, FMT_INFO,
// FMT_WARN, FMT_ERROR, FMT_FATAL,
//
// Use this macro, if you need to pass the logger in a method/function
#define FMT_GET_DEFAULT_LOGGER Logger::getLogger()

// Use this macro to trace internal working steps and data. Highest verbosity.
#define FMT_DEBUG(message) { \
  if (FMT_GET_DEFAULT_LOGGER->isDebugEnabled()) {\
  ::log4cxx::StringBuffer __oss; \
  __oss << "\t" << message; \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getDebug(), __oss.str(), \
  __FILE__, __LINE__); }}

// Use this macro to log the completion of a major working step such as completing a service call.
#define FMT_INFO(message) { \
  if (FMT_GET_DEFAULT_LOGGER->isInfoEnabled()) {\
  ::log4cxx::StringBuffer __oss; \
  __oss << "\t" << message; \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getInfo(), __oss.str(), \
  __FILE__, __LINE__); }}

// Use this macro to document an encounter with a suspicious situation
#define FMT_WARN(message) { \
  if (FMT_GET_DEFAULT_LOGGER->isWarnEnabled()) {\
  ::log4cxx::StringBuffer __oss; \
  __oss << "\t" << message; \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getWarn(), __oss.str(), \
  __FILE__, __LINE__); }}

// Use this macro to log an unexpected situation that prevented the intended
// operation to complete. Return to caller or throw an exception.
#define FMT_ERROR(message) { \
  if (FMT_GET_DEFAULT_LOGGER->isErrorEnabled()) {\
  ::log4cxx::StringBuffer __oss; \
  __oss << "\t" << message; \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getError(), __oss.str(), \
  __FILE__, __LINE__); }}

// Do not use this macro in a regular application component.
#define FMT_FATAL(message) { \
  if (FMT_GET_DEFAULT_LOGGER->isErrorEnabled()) {\
  ::log4cxx::StringBuffer __oss; \
  __oss << "\t" << message; \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getFatal(), __oss.str(), \
  __FILE__, __LINE__); }}


// Use this macro to generate the function call stack trace for desired depth.
#define FMT_DEBUG_STACKTRACE(depth) { \
  if (FMT_GET_DEFAULT_LOGGER->isDebugEnabled()) {\
  std::ostringstream __oss; \
  FMT_GET_DEFAULT_LOGGER->generateStackTrace(depth, __oss); \
  SignalGuard_ex __SignalGuard_ex; \
  FMT_GET_DEFAULT_LOGGER->forcedLog(::log4cxx::Level::getDebug(), __oss.str(), \
  __FILE__, __LINE__); }}


class SignalGuard_ex
{
  public:
    SignalGuard_ex();
    ~SignalGuard_ex();

  private:
    sigset_t mPreviousMask;
};

class Logger
{
  public:
    static ::log4cxx::LoggerPtr getLogger();

    /**
     * Prints the function stack trace of given depth.
     *
     * @param stackDepth  Stack trace depth.
     * @param os          String stream where stack trace will be written.
     */
    void generateStackTrace(uint32_t stackDepth, std::ostringstream &os);

  private:
    Logger() {}
    ~Logger() {}
    Logger(const Logger &);
    Logger & operator=(const Logger &);

    static void initLoger();

  private:
    static ::log4cxx::LoggerPtr _LoggerPtr;
};


#endif // _LOGGER_HPP_INCLUDED
