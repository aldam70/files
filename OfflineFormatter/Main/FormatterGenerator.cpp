#include    "FormatterGenerator.hpp"

AbsFormatter* FormatterGenerator::CreateFromatterByType(FormatterType FT_TYPE)
{
    AbsFormatter* absfm;
    switch (FT_TYPE)
    {
        case FT_STDF:
            absfm = new StdfFormatter();
            break;
        case FT_SUMMARY:
            absfm = new SummaryFormatter();
            break;
        case FT_TEXT:
            absfm = new TextFormatter();
            break;
        case FT_EDLDUMP:
            absfm = new EDLFormatter();
            break;
    }
    return absfm;
}   
