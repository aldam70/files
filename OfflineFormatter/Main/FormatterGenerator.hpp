#ifndef FORMATTER_GENERATOR_HPP
#define FORMATTER_GENERATOR_HPP

#include    "AbsFormatter.hpp"
#include    "stdfFormatter.hpp"
#include    "summaryFormatter.hpp"
#include    "textFormatter.hpp"
#include    "edlFormatter.hpp"

class FormatterGenerator
{
public:
    FormatterGenerator(){}
    ~FormatterGenerator(){}

    static AbsFormatter* CreateFromatterByType(FormatterType FT_TYPE);
};

#endif
