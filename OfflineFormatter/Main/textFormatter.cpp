#include    <boost/lexical_cast.hpp>
#include    "textFormatter.hpp"

using namespace std;
using namespace ::xoc::edlapi;
using namespace ::xoc::exc;
using namespace integration_ext_DatalogFormatter;
using ::rtl::OUString;

const std::string DEFAULT_SETTING = "<testNumberWidth>10</testNumberWidth><testNameWidth>48</testNameWidth><pinNameWidth>20</pinNameWidth><vectorLableWidth>18</vectorLableWidth><ffcWidth>15</ffcWidth><ffvWidth>17</ffvWidth><lowWidth>11</lowWidth><unitWidth>4</unitWidth><lowRelationWidth>2</lowRelationWidth><valueWidth>11</valueWidth><valueUnitWidth>4</valueUnitWidth><highRelationWidth>2</highRelationWidth><highWidth>11</highWidth><outputFileRolling>true</outputFileRolling><outputFileSize>600M</outputFileSize><removePinnameFromTestname>true</removePinnameFromTestname><removeLoopcountFromTestname>true</removeLoopcountFromTestname><printPASS>true</printPASS><formatExpressions>true</formatExpressions><showPinColumn>true</showPinColumn><datalogFilePath>/tmp</datalogFilePath><datalogFileName>text_output</datalogFileName>";
static const string MSG_DBG_UNKNOWN_EVENT = "Unknown event type. Event id : ";

TextFormatter::TextFormatter():mSetting(DEFAULT_SETTING), mDataPopulator(), mFormatter(mOutStream, mSetting, mDataPopulator.dataModel(), mStreamBuffer)
{
}

void TextFormatter::splitPath(string filepath, string& path, string& name)
{
    int index = filepath.find_last_of("/");
    path = filepath.substr(0, index);
    name = filepath.substr(index+1);
}

void TextFormatter::convert(const string edlpath, const string filepath)
{
    EventProvider edl(edlpath);

    try
    {
        mOutStream.open(filepath.c_str(), ofstream::out);
        if(!mOutStream)
        {
            char buff[256];
            cout << "ERROR: Failed to access the output file: " << strerror_r(errno, buff, 256) << endl;
            return;
        }

    }
    catch(xml_schema::exception& e)
    {
        ZParameterException exception ;
        exception.Message = xoc::toOu(e.what());
        throw(exception);
    }

    ::xoc::svc::msgbus::ZMessageBusMessage message;
    while(edl.getMessage(message))
    {
        try
        {
            this->handleEvent(utility::message2Event(message));
        }
        catch(const boost::bad_lexical_cast& ex)
        {
            ZIllegalContent exception;
            exception.Message = xoc::toOu(ex.what());
            throw(exception);
        }
    }

    mOutStream.close();
    mFormatter.resetInfo();
}

void TextFormatter::handleEvent(const ::xoc::edlapi::Event& event)
{
    Event ev(event);

    switch ( ev.type() )
    {
        case Event::TEST_PROGRAM_START_EVENT:
            break;
        case Event::TEST_EVENT:
            break;
        case Event::PARAMETRIC_TEST_EVENT:
            this->consumeParametricTestEvent(ev);
            break;
        case Event::FUNCTIONAL_TEST_EVENT:
            this->consumeFuntionalTestEvnet(ev);
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
            break;
        case Event::GENERIC_DATA_EVENT:
            break;
        case Event::TEXT_EVENT:
            break;
        default:
            break;
    }
}

void TextFormatter::consumeExecutionStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.setExecutionStart(true);
    mDataPopulator.processExecutonStartEvent(ev);
    mFormatter.resetHistTestType();
    mFormatter.writeHead();
    mFormatter.writeWaferID();
}

void TextFormatter::consumeExecutionEndEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.setExecutionStart(false);
}

void TextFormatter::consumeSetupDefinitionEvent(::xoc::edlapi::Event &ev)
{

}

void TextFormatter::consumeTestProgramStartEvent(::xoc::edlapi::Event& ev)
{
}

void TextFormatter::consumeTestEvent(::xoc::edlapi::Event& ev)
{
}

void TextFormatter::consumeParametricTestEvent(::xoc::edlapi::Event& ev)
{
    if(! mDataPopulator.isTestFlowStarted())
        return;
    const TestEvent& testEvent = ev.GetExtension(TestEvent::type);
    if(testEvent.result_size() > 0)
    {
        for(int i = 0; i < testEvent.result_size(); i++)
        {
            mDataPopulator.setCurrentSiteId(testEvent.result(i).site());
            mDataPopulator.processTestEvent(ev, i, textFormatter::TestResult::PARAMETRIC);
        }
    }
}

void TextFormatter::consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev)
{
    if(! mDataPopulator.isTestFlowStarted())
        return;
    const TestEvent& testEvent = ev.GetExtension(TestEvent::type);
    if(testEvent.result_size() > 0)
    {
        for(int i = 0; i < testEvent.result_size(); i++)
        {
            mDataPopulator.setCurrentSiteId(testEvent.result(i).site());
            mDataPopulator.processTestEvent(ev, i, textFormatter::TestResult::FUNCTIONAL);
        }
    }
}

void TextFormatter::consumeBinEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.processBinEvent(ev);
    mFormatter.writeBin();
}

void TextFormatter::consumeVariableChangeEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.processVariableChangeEvent(ev);
}

void TextFormatter::consumeTestFlowStartEvent(::xoc::edlapi::Event& ev)
{
    mDataPopulator.processTestFlowStartEvent(ev);
    mFormatter.writeTestHeader();
}

void TextFormatter::consumeTestFlowEndEvent(::xoc::edlapi::Event& ev)
{
    if(mDataPopulator.isTestFlowStarted())
    {
        //mDataPopulator.processTestFlowEndEvent(ev);
        //mFormatter.writeTestFlowEnd();
        mFormatter.setWriteBinFlag(false);
        mFormatter.writeTestTailer();
    }
}

void TextFormatter::consumeTestSuiteStartEvent(::xoc::edlapi::Event& ev)
{
    if(mDataPopulator.isTestFlowStarted())
    {
        mDataPopulator.processTestSuiteStartEvent(ev);
    }
}

void TextFormatter::consumeTestSuiteEndEvent(::xoc::edlapi::Event& ev)
{
    if(mDataPopulator.isTestFlowStarted())
    {
        mDataPopulator.processTestSuiteEndEvent(ev);
        if(!mDataPopulator.isTestSuiteEndWritten())
        {
            mFormatter.writeTestSuite();
            mFormatter.writeTest();
        }

        //mFormatter.writeTestSuiteEnd();
        mDataPopulator.setTestSuiteEndWritten(true);
    }
}

void TextFormatter::consumeMeasurementStartEvent(::xoc::edlapi::Event& ev)
{
    if (mDataPopulator.isTestFlowStarted())
    {
        //mDataPopulator.processMeasurementStartEvent(ev);
        //mFormatter.writeMeasurementStart();
    }
}

void TextFormatter::consumePinMapEvent(::xoc::edlapi::Event& ev)
{
}

void TextFormatter::consumeGenericDataEvent(::xoc::edlapi::Event& ev)
{
}

void TextFormatter::consumeTextEvent(::xoc::edlapi::Event& ev)
{
}

void TextFormatter::handleUnknown (::xoc::edlapi::Event& ev)
{
    cout << MSG_DBG_UNKNOWN_EVENT << (unsigned int)ev.type() << endl;
}

