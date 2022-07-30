#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "../../src/NetworkC/Dispatcher/NetworkC_Dispatcher.h"

void __wrap_Geographer_ask4Scan(uint32_t r)
{
    function_called();
    check_expected(r);
}

void __wrap_Geographer_ackCarto()
{
    function_called();
}

void __wrap_Geographer_setCarto(s_carto* theCarto)
{
    function_called();
    check_expected(theCarto);
}