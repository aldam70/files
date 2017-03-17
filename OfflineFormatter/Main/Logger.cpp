#include "Logger.hpp"

#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/consoleappender.h>
//#include <log4cxx/rollingfileappender.h>
//#include <log4cxx/logmanager.h>
#include <execinfo.h>
#include <csignal>
#include <unistd.h>

namespace
{
  pthread_mutex_t instanceMutex = PTHREAD_MUTEX_INITIALIZER;
}

::log4cxx::LoggerPtr Logger::_LoggerPtr(0);

::log4cxx::LoggerPtr Logger::getLogger()
{
  pthread_mutex_lock(&instanceMutex);

  if (_LoggerPtr == 0)
  {
    initLoger();
    _LoggerPtr = ::log4cxx::Logger::getLogger(::log4cxx::String(""));
  }

  pthread_mutex_unlock(&instanceMutex);

  return _LoggerPtr;
}


void Logger::initLoger()
{
  std::string property;
  if(getenv("HOME") != NULL) property = getenv("HOME");
  property += "/textFormatterLogger.conf";
  if (access(property.c_str(), R_OK) == 0)
  {
    ::log4cxx::PropertyConfigurator::configure(property);
  }
  else
  {
    using namespace log4cxx;
    using namespace log4cxx::helpers;
    //PatternLayoutPtr layout(new PatternLayout("%d{ABSOLUTE} %5p %c %l %t %m%n"));
    //helpers::ObjectPtrT<RollingFileAppender> appender(new RollingFileAppender(layout, "/tmp/textformatter.log", true));
    //appender->setName("R");
    //appender->setMaxFileSize("100MB");
    //appender->setMaxBackupIndex(9);
    PatternLayoutPtr layout(new PatternLayout("ERROR: %m%n"));
    helpers::ObjectPtrT<ConsoleAppender > appender(new ConsoleAppender (layout));

    //Pool pool;                                              // unaviable for log4cxx_0.9.7
    //appender->activateOptions(pool);
    log4cxx::Logger::getRootLogger()->addAppender(appender);
    //LogManager::getLoggerRepository()->setConfigured(true); //unaviable for log4cxx_0.9.7
    log4cxx::Logger::getRootLogger()->setLevel(Level::getError());
  }
}

void Logger::generateStackTrace(uint32_t stackDepth, std::ostringstream &os)
{
  #define MAX_STACK_DEPTH 256
  void *stackPointers[MAX_STACK_DEPTH];
  uint32_t stackSize = MAX_STACK_DEPTH;
  if ( (0 < stackDepth) && (stackDepth < MAX_STACK_DEPTH) )
  {
    stackSize = stackDepth;
  }
  stackSize = ::backtrace (stackPointers, stackSize);

  char **stackStrings;
  stackStrings = ::backtrace_symbols (stackPointers, stackSize);  
  if(NULL == stackStrings)
  {
    os << "Unable to print stack trace" << std::endl;
  }
  else
  {
    os << "*** Begin stack trace ***" << std::endl;
    for (uint32_t depth = 0; depth < stackSize; depth++)
    {
      os << "stack[" << depth << "]: " << stackStrings[depth] << std::endl;
    }
    ::free(stackStrings);  
    os << "*** End stack trace ***";
  }
}

SignalGuard_ex::SignalGuard_ex()
{
  sigset_t mask;
  sigfillset(&mask);

  // block all signals on current thread and save the previous mask.
  pthread_sigmask(SIG_BLOCK, &mask, &mPreviousMask);
}

SignalGuard_ex::~SignalGuard_ex()
{
  int s = pthread_sigmask(SIG_SETMASK, &mPreviousMask, NULL);
  if (s != 0) perror("roll back signal mask error.");
}
