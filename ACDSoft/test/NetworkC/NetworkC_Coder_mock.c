#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "../../src/NetworkC/Coder/NetworkC_Coder.h"

void __wrap_NetworkC_Coder_encode(s_message* myDataToCode, s_log* myLog)
{
    function_called();
    check_expected(myDataToCode);
    //check_expected(myLog);
}