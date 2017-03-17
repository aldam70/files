#include    <boost/lexical_cast.hpp>
#include    "summaryFormatter.hpp"

using namespace std;
using namespace ::xoc::edlapi;
using namespace ::xoc::exc;
using namespace integration_ext_DatalogFormatter;
using ::rtl::OUString;

static const string MSG_DBG_UNKNOWN_EVENT = "Unknown event type. Event id : ";

SummaryFormatter::SummaryFormatter()
{
}

void SummaryFormatter::splitPath(string filepath, string& path, string& name)
{
    int index = filepath.find_last_of("/");
    path = filepath.substr(0, index);
    name = filepath.substr(index+1);
}

void SummaryFormatter::convert(const string edlpath, const string filepath)
{
    EventProvider edl(edlpath);

    /* test file access */
    ofstream outStream;
    outStream.open(filepath.c_str(), ofstream::out);
    if(!outStream)
    {
        char buff[256];
        cout << "ERROR: Failed to access the output file: " << strerror_r(errno, buff, 256) << endl;
        return;
    }
    outStream.close();

    string strPath, strName;
    splitPath(filepath, strPath, strName);

    mEventManager.setSetting(xoc::toOu("datalogFilePath"), xoc::toOu(strPath));
    mEventManager.setSetting(xoc::toOu("datalogFileName"), xoc::toOu(strName));

    ::xoc::svc::msgbus::ZMessageBusMessage message;
    while(edl.getMessage(message))
    {
        try
        {
            this->handleEvent(utility::message2Event(message));
        }
        catch (const boost::bad_lexical_cast& ex)
        {
            ZIllegalContent exception;
            exception.Message = xoc::toOu(ex.what());
            throw(exception);
        }
   }

    mEventManager.generateSummaryFile();
}

void SummaryFormatter::handleEvent(const ::xoc::edlapi::Event& event)
{
    Event ev(event);

    switch ( ev.type() )
    {
        case Event::TEST_PROGRAM_START_EVENT:
            break;
        case Event::TEST_EVENT:
        case Event::PARAMETRIC_TEST_EVENT:
        case Event::FUNCTIONAL_TEST_EVENT:
            this->consumeTestEvent(ev);
            break;
        case Event::SCAN_TEST_EVENT:
            break;
        case Event::BIN_EVENT:
            this->consumeBinEvent(ev);
            break;
        case Event::VARIABLE_CHANGE_EVENT:
            this->consumeVariableChangeEvent(ev);
            break;
        case Event::EXECUTION_START_EVENT:
            this->consumeExecutionStartEvent(ev);
            break;
        case Event::EXECUTION_END_EVENT:
            this->consumeExecutionEndEvent(ev);
            break;
        case Event::TEST_FLOW_START_EVENT:
            //this->consumeTestFlowStartEvent(ev);
            break;
        case Event::TEST_FLOW_END_EVENT:
            //this->consumeTestFlowEndEvent(ev);
            break;
        case Event::TEST_SUITE_START_EVENT:
            break;
        case Event::TEST_SUITE_END_EVENT:
            break;
        case Event::MEASUREMENT_START_EVENT:
            break;
        case Event::MEASUREMENT_END_EVENT:
            break;
        case Event::SIGNAL_DEFINITION_EVENT:
            break;
        case Event::GENERIC_DATA_EVENT:
            break;
        case Event::TEXT_EVENT:
            break;
        default:
            break;
    }
}

void SummaryFormatter::consumeExecutionStartEvent(::xoc::edlapi::Event &ev)
{
    mEventManager.handleExecutionStartEvent(ev);
}

void SummaryFormatter::consumeExecutionEndEvent(::xoc::edlapi::Event &ev)
{
    mEventManager.handleExecutionEndEvent(ev);
}

void SummaryFormatter::consumeSetupDefinitionEvent(::xoc::edlapi::Event &ev)
{

}

void SummaryFormatter::consumeTestProgramStartEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeTestEvent(::xoc::edlapi::Event& ev)
{
    mEventManager.handleTestEvent(ev);
}

void SummaryFormatter::consumeParametricTestEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeBinEvent(::xoc::edlapi::Event& ev)
{
    mEventManager.handleBinEvent(ev);
}

void SummaryFormatter::consumeVariableChangeEvent(::xoc::edlapi::Event& ev)
{
    mEventManager.handleVariableChangeEvent(ev);
}

void SummaryFormatter::consumeTestFlowStartEvent(::xoc::edlapi::Event& ev)
{
    mEventManager.handleTestFlowStartEvent(ev);
}

void SummaryFormatter::consumeTestFlowEndEvent(::xoc::edlapi::Event& ev)
{
    mEventManager.handleTestFlowEndEvent(ev);
}

void SummaryFormatter::consumeTestSuiteStartEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeTestSuiteEndEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeMeasurementStartEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumePinMapEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeGenericDataEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::consumeTextEvent(::xoc::edlapi::Event& ev)
{
}

void SummaryFormatter::handleUnknown (::xoc::edlapi::Event& ev)
{
    cout << MSG_DBG_UNKNOWN_EVENT << (unsigned int)ev.type() << endl;
}

