// debug.h

#pragma once


//#ifdef _DEBUG
//#define REPORT(str) {_CrtDbgReport(_CRT_WARN, NULL, NULL, NULL, (str)); LOGOUT_1(str);}
//#else
//#define REPORT
//#endif

//#ifdef _DEBUG
#define TRACE(fmt, ...) g_console->print(fmt, __VA_ARGS__);
//#else
//#define TRACE
//#endif



// generates an error if an invalid class name passed
#ifdef _DEBUG
#define _CLS(name) (sizeof(name), name::this_type)
#else
#define _CLS(name) (name::this_type)
#endif


#define ASSERT_TYPE(pointer, type) _ASSERT(NULL != dynamic_cast<type*>(pointer))

///////////////////////////////////////////////////////////////////////////////
// end of file
