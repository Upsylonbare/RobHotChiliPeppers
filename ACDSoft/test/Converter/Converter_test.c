/**
 * Module de test du module src/Converter/Converter.c
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"

#include "Converter_rawData.h"
#include "Converter_rawScanExpected.h"

#include "../../src/Geographer/Geographer.h"
#include "../../src/Converter/Converter.c"

s_rawData *Converter_myRawData;
s_rawScan *Converter_myRawScan;
s_rawScan *Converter_myRawScanExpected;

static int retreive_rawData(s_rawData *myArray, int data[RAW_DATA_SIZE]);
static int retreive_rawScan(s_rawScan *myArray, bool data[RAW_SCAN_SIZE][RAW_SCAN_SIZE]);

static int set_up(void **state) {
    Converter_myRawData = (s_rawData *)calloc(1, sizeof(s_rawData));
    Converter_myRawScan = (s_rawScan *)calloc(1, sizeof(s_rawScan));
    Converter_myRawScanExpected = (s_rawScan *)calloc(1, sizeof(s_rawScan));

	return 0;
}

static int tear_down(void **state) {
    if(Converter_myRawScanExpected)
    {
        free(Converter_myRawScanExpected);
    }

    if(Converter_myRawScan)
    {
        free(Converter_myRawScan);
    }

    if(Converter_myRawData)
    {
        free(Converter_myRawData);
    }

	return 0;
}


static void test_Converter_convert2RawScan(void **state)
{
    // Retrieve the raw scan data
    retreive_rawData(Converter_myRawData, Converter_rawData);

    // Retrieve the raw scan data
    retreive_rawScan(Converter_myRawScanExpected, Converter_rawScanExpected);

	Converter_convert2RawScan(Converter_myRawScan, Converter_myRawData);

    // Test rawScanExpectedR3
    assert_memory_equal(Converter_myRawScan, Converter_rawScanExpected, sizeof(s_rawScan));
}


/**
 * @brief resetRawScan test : the scan is reset and every slot in the array is pushed to 1
 * @note Expected behavior : the currentRawScan array filled with random values has all its values pushed to 1
 */
static void test_Converter_resetRawScan(void **state){
	s_rawScan *res_attendu = calloc(1, sizeof(s_rawScan));
	for(int i = 0; i < RAW_SCAN_SIZE; i++){
		for(int j = 0; j < RAW_SCAN_SIZE; j++){
			res_attendu->rawScan_a[i][j] = 1;
		}
	}
	s_rawScan *currentRawScan = calloc(1, sizeof(s_rawScan));
	for(int i = 0; i < RAW_SCAN_SIZE; i++){
		for(int j = 0; j < RAW_SCAN_SIZE; j++){
			currentRawScan->rawScan_a[i][j] = rand();
		}
	}

	Converter_resetRawScan(currentRawScan);

	assert_memory_equal(res_attendu, currentRawScan, sizeof(s_rawScan));
	
	free(res_attendu);
	free(currentRawScan);
}

static int retreive_rawData(s_rawData *myArray, int data[RAW_DATA_SIZE])
{
    for(int i = 0; i < RAW_DATA_SIZE; i++)
    {
        myArray->rawData_a[i] = data[i];
    }
    return 0;
}

static int retreive_rawScan(s_rawScan *myArray, bool data[RAW_SCAN_SIZE][RAW_SCAN_SIZE])
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

static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(test_Converter_resetRawScan),
	cmocka_unit_test(test_Converter_convert2RawScan)
};

/**
 * Lancement de la suite de tests pour le module.
 */
int Converter_run_tests() {
	return cmocka_run_group_tests_name("Test du module Converter", tests, set_up, tear_down);
}