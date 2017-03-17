#include    <com/sun/star/uno/Exception.hpp>
#include    "FormatterGenerator.hpp"
#include    "AbsFormatter.hpp"
#include    "Logger.hpp"

using namespace std;

static string sInputFile = "";
static string sOutputFile = "";
static string sOptString = "";
static FormatterType sFormatterType = FT_STDF;

static void Usage (char *progname);
static bool analyzeArguments(int argc, char* argv[]);
static bool fileAccess(const string filepath);
static bool checkFormatterOpt(const string opt);
static void generateOutputFile();

static bool analyzeArguments(int argc, char* argv[])
{
    if(argc < 2 || argc > 4)
    {
        return false;
    }
    switch( argc )
    {
        case 2:
            sInputFile = argv[1];
            break;
        case 3:
            if(argv[1][0] == '-')
            {
                sOptString = argv[1];
                sInputFile = argv[2];
            }
            else
            {
                sInputFile = argv[1];
                sOutputFile = argv[2];
            }
            break;
        case 4:
            sOptString = argv[1];
            sInputFile = argv[2];
            sOutputFile = argv[3];
            break;
        default :
            break;
    }

    return checkFormatterOpt(sOptString) && fileAccess(sInputFile);
}

static void generateOutputFile()
{
    char* pszTemp = get_current_dir_name();
    if("" == sOutputFile)
    {
        sOutputFile = pszTemp;
        sOutputFile += "/temp";
        switch(sFormatterType)
        {
            case FT_STDF:
                sOutputFile += ".stdf";
                break;
            case FT_TEXT:
                sOutputFile += ".txt";
                break;
            case FT_SUMMARY:
                sOutputFile += ".sum";
                break;
            case FT_EDLDUMP:
                sOutputFile += ".edldump";
                break;
            default:
                break;
        }
    }
    else if(string::npos == sOutputFile.find("/"))
    {
        string szTemp = sOutputFile;
        sOutputFile = pszTemp;
        sOutputFile += "/";
        sOutputFile += szTemp;
    }
    free(pszTemp);
}

static bool checkFormatterOpt(const string opt)
{
    if( opt == "" )
    {
        sFormatterType = FT_STDF;
    }
    else if( opt == "-s" )
    {
        sFormatterType = FT_SUMMARY;
    }
    else if( opt == "-t" )
    {
        sFormatterType = FT_TEXT;
    }
    else if( opt == "-e" )
    {
        sFormatterType = FT_EDLDUMP;
    }
    else
    {
        return false;
    }
    return true;
}

static bool fileAccess(const string filepath)
{
    if( 0 == access(filepath.c_str(), F_OK | R_OK) )
    {
        return true;
    }
    return false;
}

static void Usage (char *progname)
{
    cout << endl;
    cout << " Usage: " << progname << " [-s|-t|-e] <EDL_FILE>" << " [OUTPUT_FILE]" << endl;
    cout << "   [-s|-t|-e]     ----  The type of formatter, default is STDF formatter:\r\n\t\t\t\
        -s to use SUMMARY formatter.\r\n\t\t\t\
        -t to use TEXT formatter.\r\n\t\t\t\
        -e to dump a ASCII edl file." << endl;
    cout << "   <EDL_FILE>     ----  The name of the EDL file." << endl;
    cout << "   [OUTPUT_FILE]  ----  The name of the file, default name is \"temp\"." << endl;
    cout << endl;
}

int main(int argc, char* argv[])
{
    if(analyzeArguments(argc, argv) == false)
    {
        Usage(argv[0]);
        return EXIT_FAILURE;
    }

    generateOutputFile();
    Logger::getLogger();    /* dummy logger instance */
    AbsFormatter* fm = FormatterGenerator::CreateFromatterByType(sFormatterType);

    try
    {
        cout << "\nWill convert EDL file:\n\t" << sInputFile << "\nto file:\n\t" << sOutputFile << endl << endl;
        fm->convert(sInputFile, sOutputFile);
    }
    catch (const ::com::sun::star::uno::Exception & e)
    {
        cout << "Failure to convert file. Detail information:" << e.Message << endl;
        delete fm;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        cout << "Failure to convert file." << endl;
        delete fm;
        return EXIT_FAILURE;
    }
    delete fm;
    return EXIT_SUCCESS;
}

