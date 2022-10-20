
#include "ATMHeader.h"
#include "ScreenHeader.h"


int main()
{
    session ss;
    Bank a(ss);
    cm ccm;

    session* s = &ss; cm* cmb = &ccm;

    start_screen src(s, cmb);
    while(true)
    {
        src.read_card(); 
        while (src.is_on)
        {
            src.work();
            
        }       
        a.addSessionsHistory(ss);
        ss.clear();
        src.is_on = true;
    }
    cout << ""; 
}
