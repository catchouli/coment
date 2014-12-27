#pragma once

/*
*   This file is included in files which wish to export or import to or from a DLL.
*   To use it, simply #include the file and include COMENT_API in your prototypes.
*   When compiling a dll, COMENT_COMPILE_DLL should be defined
*/
#ifdef _MSC_VER
#   ifdef COMENT_COMPILE_DLL
#       define COMENT_API __declspec(dllexport)
#   else
#       define COMENT_API __declspec(dllimport)
#   endif
#else
#   define COMENT_API
#endif