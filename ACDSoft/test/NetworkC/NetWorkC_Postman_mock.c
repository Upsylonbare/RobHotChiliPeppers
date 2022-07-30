#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"


void __wrap_NetworkC_Postman_sendMsg(char *data, uint8_t size)
{
    function_called();
    check_expected(size);
}

void __wrap_NetworkC_Postman_askSend(uint8_t* datas, uint32_t size)
{
    function_called();
}