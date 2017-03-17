#ifndef ABS_FORMATTER_HPP
#define ABS_FORMATTER_HPP

#include    <iostream>
#include    <xoc/zutils.hpp>
#include    <xoc/edlapi/Datalog.pb.h>
#include    "StdfFormatter/DataPopulator.hpp"
#include    "SummaryFormatter/EventManager.hpp"
#include    "TextFormatter/Formatter.hpp"
#include    "TextFormatter/DataPopulator.hpp"
#include    "StreamBuffer/StreamBuffer.hpp"
#include    "EventProvider.hpp"
#include    "Utility.hpp"

enum FormatterType { FT_STDF, FT_SUMMARY, FT_TEXT , FT_EDLDUMP };

class AbsFormatter
{

public:
    AbsFormatter(){};
    virtual ~AbsFormatter(){};

    virtual void handleEvent(const ::xoc::edlapi::Event& event) = 0;
    virtual void convert(const std::string edlpath, const std::string filepath) = 0;

    virtual void consumeTestProgramStartEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTestEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeParametricTestEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeFuntionalTestEvnet(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeBinEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeVariableChangeEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTestFlowStartEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTestFlowEndEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTestSuiteStartEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTestSuiteEndEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeMeasurementStartEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumePinMapEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeGenericDataEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void consumeTextEvent(::xoc::edlapi::Event& ev) = 0;
    virtual void handleUnknown(::xoc::edlapi::Event& ev) = 0;

    virtual void consumeExecutionStartEvent(::xoc::edlapi::Event &ev) = 0;
    virtual void consumeExecutionEndEvent(::xoc::edlapi::Event &ev) = 0;
    virtual void consumeSetupDefinitionEvent(::xoc::edlapi::Event &ev) = 0;
};

#endif
