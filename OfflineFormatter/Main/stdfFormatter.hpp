#ifndef STDF_FORMATTER_HPP
#define STDF_FORMATTER_HPP

#include    "AbsFormatter.hpp"

class StdfFormatter : public AbsFormatter
{
public:

    StdfFormatter();
    ~StdfFormatter(){};

    void handleEvent(const ::xoc::edlapi::Event& event);
    void convert(const std::string edlpath, const std::string filepath);

    void consumeTestProgramStartEvent(::xoc::edlapi::Event& ev);
    void consumeTestEvent(::xoc::edlapi::Event& ev);
    void consumeParametricTestEvent(::xoc::edlapi::Event& ev);
    void consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev);
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

private:
    std::ofstream mOutStream;
    integration_ext_DatalogFormatter::stdfFormatter::Setting mSetting;
    integration_ext_DatalogFormatter::stdfFormatter::DataPopulator mDataPopulator;

};

#endif
