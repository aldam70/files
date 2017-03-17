#ifndef TEXT_FORMATTER_HPP
#define TEXT_FORMATTER_HPP

#include    "AbsFormatter.hpp"

class TextFormatter : public AbsFormatter
{
public:

    TextFormatter();
    ~TextFormatter(){};

    void handleEvent(const ::xoc::edlapi::Event& event);
    void convert(const std::string edlpath, const std::string filepath);

    void consumeTestProgramStartEvent(::xoc::edlapi::Event& ev);
    void consumeTestEvent(::xoc::edlapi::Event& ev);
    void consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev);
    void consumeParametricTestEvent(::xoc::edlapi::Event& ev);
    void consumeBinEvent(::xoc::edlapi::Event& ev);
    void consumeVariableChangeEvent(::xoc::edlapi::Event& ev);
    void consumeTestFlowStartEvent(::xoc::edlapi::Event& ev);
    void consumeTestFlowEndEvent(::xoc::edlapi::Event& ev);
    void consumeTestSuiteStartEvent(::xoc::edlapi::Event& ev);
    void consumeTestSuiteEndEvent(::xoc::edlapi::Event& ev);
    void consumeMeasurementStartEvent(::xoc::edlapi::Event& ev);
    void consumePinMapEvent(::xoc::edlapi::Event& ev);
    void consumeGenericDataEvent(::xoc::edlapi::Event& ev);
    void consumeTextEvent(::xoc::edlapi::Event& ev);
    void handleUnknown(::xoc::edlapi::Event& ev);

    void consumeExecutionStartEvent(::xoc::edlapi::Event &ev);
    void consumeExecutionEndEvent(::xoc::edlapi::Event &ev);
    void consumeSetupDefinitionEvent(::xoc::edlapi::Event &ev);

    void splitPath(string filepath, string& path, string& name);

private:
    std::ofstream mOutStream;
    StreamBuffer mStreamBuffer;
    integration_ext_DatalogFormatter::textFormatter::Setting mSetting;
    integration_ext_DatalogFormatter::textFormatter::DataPopulator mDataPopulator;
    integration_ext_DatalogFormatter::textFormatter::Formatter mFormatter;

};

#endif

