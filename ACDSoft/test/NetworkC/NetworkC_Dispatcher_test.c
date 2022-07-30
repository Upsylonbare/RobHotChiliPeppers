/**
 * Module de test du module pkg/mod1.c
 *
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "../../src/NetworkC/NetworkC.c"
#include "../../src/NetworkC/Postman/NetworkC_Postman.c"

#include "../../src/NetworkC/Dispatcher/NetworkC_Dispatcher.c"

static int set_up(void **state) {
	return 0;
}

static int tear_down(void **state) {
	return 0;
}

static void testNetworkC_Dispatcher_dispatch_ASK4SCAN(void **state)
{
    s_message* dtLog = calloc(1, sizeof(s_message));
    dtLog->command = A_ASK4SCAN;
    dtLog->carto.id = 1;

    expect_function_call(__wrap_Geographer_ask4Scan);
    expect_value(__wrap_Geographer_ask4Scan, r, dtLog->carto.id);

    NetworkC_Dispatcher_dispatch(dtLog);

    free(dtLog);
}

static void testNetworkC_Dispatcher_dispatch_ACKCARTO(void **state)
{
    s_message* dtLog = calloc(1, sizeof(s_message));
    dtLog->command = A_ACKCARTO;

    expect_function_call(__wrap_Geographer_ackCarto);

    NetworkC_Dispatcher_dispatch(dtLog);

    free(dtLog);
}

static void testNetworkC_Dispatcher_dispatch_SETCARTO(void **state)
{
    char dtName[] = "raclette";
    char dtCartoData[] = "CARTODataYoupiyiYoupiya";
    uint32_t dtId = 12;

    s_message* dtLog = calloc(1, sizeof(s_message));
    dtLog->command = A_SETCARTO;
    dtLog->carto.id = dtId;
    memcpy(dtLog->carto.name, &dtName, sizeof(dtName));
    memcpy(dtLog->carto.treatedCarto, &dtCartoData, sizeof(dtCartoData));

    expect_function_call(__wrap_Geographer_setCarto);
    expect_memory(__wrap_Geographer_setCarto, theCarto, &(dtLog->carto), sizeof(s_carto));

    NetworkC_Dispatcher_dispatch(dtLog);

    free(dtLog);

}

static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(testNetworkC_Dispatcher_dispatch_ASK4SCAN),
    cmocka_unit_test(testNetworkC_Dispatcher_dispatch_ACKCARTO),
    cmocka_unit_test(testNetworkC_Dispatcher_dispatch_SETCARTO)
};

int NetworkC_Dispatcher_run_tests(void) 
{
	return cmocka_run_group_tests_name("Test du module Dispatcher", tests, set_up, tear_down);
}