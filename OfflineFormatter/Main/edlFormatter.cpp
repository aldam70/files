#include    "edlFormatter.hpp"

using namespace std;
using namespace ::xoc::edlapi;
using namespace ::xoc::exc;
using namespace integration_ext_DatalogFormatter;

void EDLFormatter::convert(const string edlpath, const string filepath)
{
    EventProvider edl(edlpath);

    mOutStream.open(filepath.c_str(), ofstream::out);
    if(!mOutStream)
    {
        char buff[256];
        cout << "ERROR: Failed to access the output file: " << strerror_r(errno, buff, 256) << endl;
        return;
    }

    ::xoc::svc::msgbus::ZMessageBusMessage message;
    while(edl.getMessage(message))
    {
        Event ev(utility::message2Event(message));
        mOutStream << ev.DebugString();
    }

    mOutStream.close();
}

