#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "../../src/NetworkC/Coder/NetworkC_Coder.h"

void __wrap_NetworkC_Dispatcher_mainDispatcher(s_log* ptr_myLetterToDispatch)
{
    function_called();
    check_expected(ptr_myLetterToDispatch);
}