/**
 * Module de test du module src/Merger/Merger.c
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "Merger_myRawScanMerged.h"
#include "Merger_myRawScan.h"
#include "Merger_rawScanExpectedR0.h"
#include "Merger_rawScanExpectedR1.h"
#include "Merger_rawScanExpectedR2.h"
#include "Merger_rawScanExpectedR3.h"
#include "Merger_rawScanExpectedR4.h"

#include "../../src/Config/util.h"
#include "../../src/Geographer/Geographer.h"
#include "../../src/Merger/Merger.c"

#define PATH_LIDAR_DATA "test/Merger/position_gtk.txt"

s_rawScan *Merger_myRawScan;
s_rawScan *Merger_myRawScanMerged;
s_rawScan *Merger_rawScanExpected;

static int retreive_data(s_rawScan *myArray, bool data[RAW_SCAN_SIZE][RAW_SCAN_SIZE]);
void printColor(s_rawScan *myArray);

static int set_up(void **state)
{
    Merger_myRawScan = (s_rawScan *)calloc(1, sizeof(s_rawScan));
    Merger_myRawScanMerged = (s_rawScan *)calloc(1, sizeof(s_rawScan));
    Merger_rawScanExpected = (s_rawScan *)calloc(1, sizeof(s_rawScan));

    return 0;
}

static int tear_down(void **state)
{
    if(Merger_rawScanExpected)
    {
        free(Merger_rawScanExpected);
    }

    if(Merger_myRawScanMerged)
    {
        free(Merger_myRawScanMerged);
    }

    if(Merger_myRawScan)
    {
        free(Merger_myRawScan);
    }

    return 0;
}

static void test_Merger_merge_R0(void **state)
{
    // Retrieve the raw scan data
    retreive_data(Merger_myRawScan, Merger_rawScan);

    // Retrieve the raw scan merged data
    retreive_data(Merger_myRawScanMerged, Merger_rawScanMerged);

    // Retrieve the expected raw scan data
    retreive_data(Merger_rawScanExpected, Merger_rawScanExpectedR0);
    
    Merger_merge(Merger_myRawScanMerged, Merger_myRawScan, R0);

    //printColor(myRawScan);
    //printColor(myRawScanMerged);

    // Test rawScanExpectedR0
    assert_memory_equal(Merger_myRawScanMerged, Merger_rawScanExpected, sizeof(s_rawScan));
}

static void test_Merger_merge_R1(void **state)
{
    // Retrieve the raw scan data
    retreive_data(Merger_myRawScan, Merger_rawScan);

    // Retrieve the raw scan merged data
    retreive_data(Merger_myRawScanMerged, Merger_rawScanMerged);

    // Retrieve the expected raw scan data
    retreive_data(Merger_rawScanExpected, Merger_rawScanExpectedR1);
    
    Merger_merge(Merger_myRawScanMerged, Merger_myRawScan, R1);

    // Test rawScanExpectedR1
    assert_memory_equal(Merger_myRawScanMerged, Merger_rawScanExpected, sizeof(s_rawScan));
}

static void test_Merger_merge_R2(void **state)
{
    // Retrieve the raw scan data
    retreive_data(Merger_myRawScan, Merger_rawScan);

    // Retrieve the raw scan merged data
    retreive_data(Merger_myRawScanMerged, Merger_rawScanMerged);

    // Retrieve the expected raw scan data
    retreive_data(Merger_rawScanExpected, Merger_rawScanExpectedR2);
    
    Merger_merge(Merger_myRawScanMerged, Merger_myRawScan, R2);

    // Test rawScanExpectedR2
    assert_memory_equal(Merger_myRawScanMerged, Merger_rawScanExpected, sizeof(s_rawScan));
}

static void test_Merger_merge_R3(void **state)
{
    // Retrieve the raw scan data
    retreive_data(Merger_myRawScan, Merger_rawScan);

    // Retrieve the raw scan merged data
    retreive_data(Merger_myRawScanMerged, Merger_rawScanMerged);

    // Retrieve the expected raw scan data
    retreive_data(Merger_rawScanExpected, Merger_rawScanExpectedR3);
    
    Merger_merge(Merger_myRawScanMerged, Merger_myRawScan, R3);

    // Test rawScanExpectedR3
    assert_memory_equal(Merger_myRawScanMerged, Merger_rawScanExpected, sizeof(s_rawScan));
}

static void test_Merger_merge_R4(void **state)
{
    // Retrieve the raw scan data
    retreive_data(Merger_myRawScan, Merger_rawScan);

    // Retrieve the raw scan merged data
    retreive_data(Merger_myRawScanMerged, Merger_rawScanMerged);

    // Retrieve the expected raw scan data
    retreive_data(Merger_rawScanExpected, Merger_rawScanExpectedR4);
    
    Merger_merge(Merger_myRawScanMerged, Merger_myRawScan, R4);

    // Test rawScanExpectedR4
    assert_memory_equal(Merger_myRawScanMerged, Merger_rawScanExpected, sizeof(s_rawScan));
}

static int retreive_data(s_rawScan *myArray, bool data[RAW_SCAN_SIZE][RAW_SCAN_SIZE])
{
    for(int i = 0; i < RAW_SCAN_SIZE; i++)
    {
        for(int j = 0; j < RAW_SCAN_SIZE; j++)
        {
            myArray->rawScan_a[i][j] = data[i][j];
        }
    }
    return 0;
}

void printColor(s_rawScan *myArray)
{
    for(int i = 0; i < RAW_SCAN_SIZE; i++)
    {
        for(int j = 0; j < RAW_SCAN_SIZE; j++)
        {
            if(myArray->rawScan_a[i][j] == 0)
			{
				printf(RED"%d", myArray->rawScan_a[i][j]);
			}
			else
			{
				printf(WHITE"%d", myArray->rawScan_a[i][j]);
			}
        }
        printf("\n");
    }
}

static const struct CMUnitTest tests[] =
{
    cmocka_unit_test(test_Merger_merge_R0),
    cmocka_unit_test(test_Merger_merge_R1),
    cmocka_unit_test(test_Merger_merge_R2),
    cmocka_unit_test(test_Merger_merge_R3),
    cmocka_unit_test(test_Merger_merge_R4)
};

/**
 * Lancement de la suite de tests pour le module.
 */
int Merger_run_tests()
{
    return cmocka_run_group_tests_name("Test du module Merger", tests, set_up, tear_down);
}
