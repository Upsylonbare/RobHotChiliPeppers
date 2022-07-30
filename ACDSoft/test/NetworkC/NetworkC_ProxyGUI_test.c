/**
 * Test module for src/NetworkC/Coder
 *
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "../../src/NetworkC/Proxy/NetworkC_ProxyGUI.c"


static int set_up(void **state)
{
    return 0;
}

static int tear_down(void **state) 
{
    return 0;
}

int CheckCommandFromMessageEqual(const LargestIntegralType value, const LargestIntegralType check_value_data)
{
   s_message * actual = (s_message*)value;
   e_command * expected = (e_command*)check_value_data;
   return actual->command == *expected;
}

int CheckCommandFromMessageInequal(const LargestIntegralType value, const LargestIntegralType check_value_data)
{
   s_message * actual = (s_message*)value;
   e_command * expected = (e_command*)check_value_data;
   return actual->command != *expected;
}

static void test_NetworkC_ProxyGUI_ack4Scan()
{
    e_command dtCommandAttendu = C_ACK4SCAN;

    expect_function_call(__wrap_NetworkC_Coder_encode);
    expect_check(__wrap_NetworkC_Coder_encode, myDataToCode, CheckCommandFromMessageEqual, &dtCommandAttendu);
    expect_function_call(__wrap_NetworkC_Postman_askSend);

    NetworkC_ProxyGUI_ack4Scan();
}

static void test_NetworkC_ProxyGUI_ack4SaveCarto()
{
    e_command dtCommandAttendu = C_ACK4SAVECARTO;

    expect_function_call(__wrap_NetworkC_Coder_encode);
    expect_check(__wrap_NetworkC_Coder_encode, myDataToCode, CheckCommandFromMessageEqual, &dtCommandAttendu);
    expect_function_call(__wrap_NetworkC_Postman_askSend);

    NetworkC_ProxyGUI_ack4SaveCarto();
}

static void test_NetworkC_ProxyGUI_not_ack4Scan()
{
    e_command dtCommandAttendu = C_SETCARTO;

    expect_function_call(__wrap_NetworkC_Coder_encode);
    expect_check(__wrap_NetworkC_Coder_encode, myDataToCode, CheckCommandFromMessageInequal, &dtCommandAttendu);
    expect_function_call(__wrap_NetworkC_Postman_askSend);

    NetworkC_ProxyGUI_ack4Scan();
}

static void test_NetworkC_ProxyGUI_not_ack4SaveCarto()
{
    e_command dtCommandAttendu = C_ACKCARTO;

    expect_function_call(__wrap_NetworkC_Coder_encode);
    expect_check(__wrap_NetworkC_Coder_encode, myDataToCode, CheckCommandFromMessageInequal, &dtCommandAttendu);
    expect_function_call(__wrap_NetworkC_Postman_askSend);

    NetworkC_ProxyGUI_ack4SaveCarto();
}

/**
 * Suite de test pour le module.
 *
 * A compléter si besoin est.
 *
 */
static const struct CMUnitTest tests[] = 
{
    cmocka_unit_test(test_NetworkC_ProxyGUI_ack4Scan),
    cmocka_unit_test(test_NetworkC_ProxyGUI_ack4SaveCarto),
    cmocka_unit_test(test_NetworkC_ProxyGUI_not_ack4Scan),
    cmocka_unit_test(test_NetworkC_ProxyGUI_not_ack4SaveCarto)
};

int NetworkC_ProxyGUI_run_tests() 
{
	return cmocka_run_group_tests_name("Test du module ProxyGUI", tests, set_up, tear_down);
}