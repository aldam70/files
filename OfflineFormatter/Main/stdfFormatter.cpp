#include    "stdfFormatter.hpp"

using namespace std;
using namespace ::xoc::edlapi;
using namespace ::xoc::exc;
using namespace integration_ext_DatalogFormatter;

static const string DEFAULT_SETTING = "<datalogFilePath>/tmp</datalogFilePath><datalogFileName>stdf_output</datalogFileName><testText>TEST_TXT</testText><forcedPtr>false</forcedPtr><useUTCTime>false</useUTCTime><enablePatternNameInSTR>false</enablePatternNameInSTR><stdfVersion>V4-2007.1</stdfVersion>";
static const string MSG_DBG_UNKNOWN_EVENT = "Unknown event type. Event id : ";

StdfFormatter::StdfFormatter(): mSetting(DEFAULT_SETTING), mDataPopulator(mOutStream, mSetting)
{
}

void StdfFormatter::convert(const string edlpath, const string filepath)
{
    EventProvider edl(edlpath);

    //this->mDataPopulator.setStdfFilePath(filepath);
    mOutStream.open(filepath.c_str(), ofstream::out);
    if(!mOutStream)
    {
        char buff[256];
        cout << "ERROR: Failed to access the output file: " << strerror_r(errno, buff, 256) << endl;
        return;
    }

    Event ev1;
    mDataPopulator.handleRecord(ev1, Record::FAR_TYPE);
    mDataPopulator.setLogCreateTime(true);

    ::xoc::svc::msgbus::ZMessageBusMessage message;
    while(edl.getMessage(message))
    {
      Event ev(utility::message2Event(message));
      this->handleEvent(ev);
    }

    mDataPopulator.handleSummaryInfo();

    mOutStream.close();
    mDataPopulator.clearDataPopulateInfo();
}

void StdfFormatter::handleEvent(const ::xoc::edlapi::Event& event)
{
    Event ev(event);

    switch ( ev.type() )
    {
        case Event::TEST_PROGRAM_START_EVENT:
            this->consumeTestProgramStartEvent(ev);
            break;
        case Event::EXECUTION_START_EVENT:
            this->consumeExecutionStartEvent(ev);
            break;
        case Event::EXECUTION_END_EVENT:
            this->consumeExecutionEndEvent(ev);
            break;
        case Event::TEST_EVENT:
        case Event::PARAMETRIC_TEST_EVENT:
        case Event::FUNCTIONAL_TEST_EVENT:
        case Event::SCAN_TEST_EVENT:
            this->consumeTestEvent(ev);
            break;
        case Event::BIN_EVENT:
            this->consumeBinEvent(ev);
            break;
        case Event::VARIABLE_CHANGE_EVENT:
            this->consumeVariableChangeEvent(ev);
            break;
        case Event::TEST_FLOW_START_EVENT:
            this->consumeTestFlowStartEvent(ev);
            break;
        case Event::TEST_FLOW_END_EVENT:
            this->consumeTestFlowEndEvent(ev);
            break;
        case Event::TEST_SUITE_START_EVENT:
            this->consumeTestSuiteStartEvent(ev);
            break;
        case Event::TEST_SUITE_END_EVENT:
            this->consumeTestSuiteEndEvent(ev);
            break;
        case Event::MEASUREMENT_START_EVENT:
            this->consumeMeasurementStartEvent(ev);
            break;
        case Event::MEASUREMENT_END_EVENT:
            break;
        case Event::SIGNAL_DEFINITION_EVENT:
            this->consumePinMapEvent(ev);
            break;
        case Event::GENERIC_DATA_EVENT:
            this->consumeGenericDataEvent(ev);
            break;
        case Event::TEXT_EVENT:
            this->consumeTextEvent(ev);
            break;
        case Event::SETUP_DEFINITION_EVENT:
            this->consumeSetupDefinitionEvent(ev);
            break;
        default:
            break;
    }
}

void StdfFormatter::consumeExecutionStartEvent(::xoc::edlapi::Event &ev)
{
    mDataPopulator.procExecutionStart(ev);
}

void StdfFormatter::consumeExecutionEndEvent(::xoc::edlapi::Event &ev)
{
    mDataPopulator.procExecutionEnd(ev);
}

void StdfFormatter::consumeSetupDefinitionEvent(::xoc::edlapi::Event &ev)
{
    mDataPopulator.procPatternSequence(ev);
}

void StdfFormatter::consumeTestProgramStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestProgramStart(ev);
}

void StdfFormatter::consumeTestEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestEvent(ev);
}

void StdfFormatter::consumeParametricTestEvent(::xoc::edlapi::Event& ev)
{
}

void StdfFormatter::consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev)
{
}

void StdfFormatter::consumeBinEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procBinInfo(ev);
}

void StdfFormatter::consumeVariableChangeEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procVariableChange(ev);
}

void StdfFormatter::consumeTestFlowStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestFlowStart(ev);
}

void StdfFormatter::consumeTestFlowEndEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestFlowEnd(ev);
}

void StdfFormatter::consumeTestSuiteStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestSuiteStartEvent(ev);
}

void StdfFormatter::consumeTestSuiteEndEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procTestSuiteEndEvent(ev);
}

void StdfFormatter::consumeMeasurementStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procMeasurementStart(ev);
}

void StdfFormatter::consumePinMapEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procPinMap(ev);
}

void StdfFormatter::consumeGenericDataEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procGdrEvent(ev);
}

void StdfFormatter::consumeTextEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.procDatalogText(ev);
}

void StdfFormatter::handleUnknown (::xoc::edlapi::Event& ev)
{
    cout << MSG_DBG_UNKNOWN_EVENT << (unsigned int)ev.type() << endl;
}

