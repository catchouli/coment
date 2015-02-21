#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"

namespace coment
{
    void setupMemoryLeakDetection()
    {
        atexit([]()
        {
            // Dump output to console
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

            // Dump memory leaks
            if (_CrtDumpMemoryLeaks())
            {
                system("pause");
            }
        });
    }
}