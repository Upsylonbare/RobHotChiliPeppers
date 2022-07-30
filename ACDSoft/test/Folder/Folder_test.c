#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "../../libs/cmocka-x86_64/include/cmocka.h"
#include "../../src/Folder/Folder.c"
#include "../../src/Folder/libbmp.c"

static int set_up(void **state) {
	return 0;
}

static int tear_down(void **state) {
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------TEST FOLDER_DELETEOLDESTCARTO-----------------------------------------


/**
 * @brief 1st deleteOldestCarto test : good conditions test = good filenames
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : 1-raw.bmp and 1-cuisine.bmp deleted
 * @author Marin BONSERGENT
 */
void firstTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char *oldest_carto_raw = "cartos/1-raw.bmp";
    file = fopen(oldest_carto_raw, "w");
    fclose(file);

    char *oldest_carto_treated = "cartos/1-cuisine.bmp";
    file = fopen(oldest_carto_treated, "w");
    fclose(file);

    char *recent_carto_raw = "cartos/2-raw.bmp";
    file = fopen(recent_carto_raw, "w");
    fclose(file);

    char *recent_carto_treated = "cartos/2-salon.bmp";
    file = fopen(recent_carto_treated, "w");
    fclose(file);

    // end of building environment for test

    Folder_deleteOldestCarto();

    if (access(oldest_carto_raw, F_OK) != 0 && access(oldest_carto_treated, F_OK) != 0 && access(recent_carto_raw, F_OK) == 0 && access(recent_carto_treated, F_OK) == 0)  {
        // SUCCESS FILES DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        success = 1;
    } 
    else
    {
        // FAIL FILES NOT DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        remove(oldest_carto_raw);
        remove(oldest_carto_treated);
        success = -1;
    }
    assert_int_equal(success, 1);
}

/**
 * @brief 2nd deleteOldestCarto test : Cartos directory has cartos and other files not starting with a digit
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : oldest cartos are deleted -> 1-raw.bmp and 1-cuisine.bmp
 * @author Marin BONSERGENT
 */
void secondTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char *oldest_carto_raw = "cartos/1-raw.bmp";
    file = fopen(oldest_carto_raw, "w");
    fclose(file);

    char *oldest_carto_treated = "cartos/1-cuisine.bmp";
    file = fopen(oldest_carto_treated, "w");
    fclose(file);

    char *recent_carto_raw = "cartos/2-raw.bmp";
    file = fopen(recent_carto_raw, "w");
    fclose(file);

    char *recent_carto_treated = "cartos/2-salon.bmp";
    file = fopen(recent_carto_treated, "w");
    fclose(file);

    char * file_other = "cartos/file_other.txt";
    file = fopen(file_other, "w");
    fclose(file);

    char *other_file = "cartos/other_file.txt";
    file = fopen(other_file, "w");
    fclose(file);

    // end of building environment for test

    Folder_deleteOldestCarto();

    if (access(oldest_carto_raw, F_OK) != 0 && access(oldest_carto_treated, F_OK) != 0 && access(recent_carto_raw, F_OK) == 0 && access(recent_carto_treated, F_OK) == 0 && access(file_other, F_OK) == 0 && access(other_file, F_OK) == 0)  {
        // SUCCESS FILES DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        remove(file_other);
        remove(other_file);
        success = 1;
    } 
    else
    {
        // FAIL FILES NOT DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        remove(oldest_carto_raw);
        remove(oldest_carto_treated);
        remove(file_other);
        remove(other_file);
        success = -1;
    }
    assert_int_equal(success, 1);
}

/**
 * @brief 3rd deleteOldestCarto test : No cartos saved, directory is empty.
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : no carto deleted
 * @author Marin BONSERGENT
 */
void thirdTest_deleteOldestCarto(void **state)
{
    // end of building environment for test

    Folder_deleteOldestCarto();
    // If next line can be reached (no crash), then it is a success
    int success = 1;
    assert_int_equal(success, 1);
}

/**
 * @brief 4th deleteOldestCarto test : only 1 carto saved, impossible case
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : 1-raw.bmp carto deleted
 * @author Marin BONSERGENT
 */
void fourthTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char *test_carto = "cartos/1-raw.bmp";
    file = fopen(test_carto, "w");
    fclose(file);
    // end of building environment for test

    
    Folder_deleteOldestCarto();

    if (access(test_carto, F_OK) != 0) {
        // SUCCESS FILE DELETED
        success = 1;
    } 
    else
    {
        // FAIL FILE NOT DELETED
        remove(test_carto);
        success = -1;
    }
    
    assert_int_equal(success, 1);
}

/**
 * @brief 5th deleteOldestCarto test : 2 cartos saved
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : 1-raw.bmp and 1-cuisine.bmp deleted
 * @author Marin BONSERGENT
 */
void fifthTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char oldest_carto_raw[] = "cartos/1-raw.bmp";
    file = fopen(oldest_carto_raw, "w");
    fclose(file);
    
    char *oldest_carto_treated = "cartos/1-cuisine.bmp";
    file = fopen(oldest_carto_treated, "w");
    fclose(file);
    
    // end of building environment for test

    Folder_deleteOldestCarto();
    
    if (access(oldest_carto_raw, F_OK) != 0 && access(oldest_carto_treated, F_OK) != 0) {
        // SUCCESS FILES DELETED
        success = 1;
    } 
    else
    {
        // FAIL FILES NOT DELETED
        remove(oldest_carto_raw);
        remove(oldest_carto_treated);
        success = -1;
    }
    assert_int_equal(success, 1);
}

/**
 * @brief 6th deleteOldestCarto test : 4 cartos : 2 with an unit bigger than the ten of the 2 others 
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : 2-raw.bmp and 2-salon.bmp deleted
 * @author Marin BONSERGENT
 */
void sixthTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char *oldest_carto_raw = "cartos/2-raw.bmp";
    file = fopen(oldest_carto_raw, "w");
    fclose(file);

    char *oldest_carto_treated = "cartos/2-salon.bmp";
    file = fopen(oldest_carto_treated, "w");
    fclose(file);

    char *recent_carto_raw = "cartos/10-raw.bmp";
    file = fopen(recent_carto_raw, "w");
    fclose(file);

    char *recent_carto_treated = "cartos/10-chambre.bmp";
    file = fopen(recent_carto_treated, "w");
    fclose(file);

    // end of building environment for test

    Folder_deleteOldestCarto();

    if (access(oldest_carto_raw, F_OK) != 0 && access(oldest_carto_treated, F_OK) != 0 && access(recent_carto_raw, F_OK) == 0 && access(recent_carto_treated, F_OK) == 0)  {
        // SUCCESS FILES DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        success = 1;
    } 
    else
    {
        // FAIL FILES NOT DELETED
        remove(recent_carto_raw);
        remove(recent_carto_treated);
        remove(oldest_carto_raw);
        remove(oldest_carto_treated);
        success = -1;
    }
    assert_int_equal(success, 1);
}

/**
 * @brief 7th deleteOldestCarto test : Cartos directory has cartos and other files starting with a digit
 * @return 0 if test is successful, -1 otherwise
 * @note Expected behavior : oldest cartos are deleted -> 1-raw.bmp and 1-cuisine.bmp
 * @note FAIL : algorithm just look if first char is a digit
 * @author Marin BONSERGENT
 */
void seventhTest_deleteOldestCarto(void **state)
{
    int success = 0;
    FILE *file;

    char *oldest_carto_raw = "cartos/9-raw.bmp";
    file = fopen(oldest_carto_raw, "w");
    fclose(file);

    char *oldest_carto_treated = "cartos/9-cuisine.bmp";
    file = fopen(oldest_carto_treated, "w");
    fclose(file);

    char * file_other = "cartos/3file_other.txt";
    file = fopen(file_other, "w");
    fclose(file);

    char *other_file = "cartos/4other_file.txt";
    file = fopen(other_file, "w");
    fclose(file);

    // end of building environment for test

    Folder_deleteOldestCarto();

    if (access(oldest_carto_raw, F_OK) != 0 && access(oldest_carto_treated, F_OK) != 0 && access(file_other, F_OK) == 0 && access(other_file, F_OK) == 0)  {
        // SUCCESS FILES DELETED
        remove(file_other);
        remove(other_file);
        success = 1;
    } 
    else
    {
        // FAIL FILES NOT DELETED
        remove(oldest_carto_raw);
        remove(oldest_carto_treated);
        remove(file_other);
        remove(other_file);
        success = -1;
    }
    assert_int_equal(success, 1);
}


// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------TEST FOLDER_BUILDFILENAME-----------------------------------------

/**
 * @brief test of the buildFilename function of Folder
 * Create a temporary carto with id at 0 and build the filename using Folder_buildFilename function
 * Compare the filename rawCartoPath generate with the filename expected res_attendu.
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_buildFilename_temporary(void **state){
	char * res_attendu = "/tmp/0-raw_tmp.bmp";
    s_carto * myCarto = malloc (sizeof(s_carto));
    myCarto->id = 0;
    char * rawCartoPath = malloc (sizeof (char) * 45);
    Folder_buildFilename(myCarto,TEMPORARY,rawCartoPath);

	assert_string_equal(res_attendu, rawCartoPath);

    free(myCarto);
    free(rawCartoPath);
}

/**
 * @brief test of the buildFilename function of Folder
 * Create a definitive threated carto with id at 0 and no name and build the filename using Folder_buildFilename function
 * Compare the filename rawCartoPath generate with the filename expected res_attendu.
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_buildFilename_definitive_treated_without_name(void **state){
	char * res_attendu = "cartos/0-.bmp";;
    s_carto * myCarto2 = malloc (sizeof(s_carto));
    myCarto2->id = 0;
    strncpy(myCarto2->name, "", sizeof(myCarto2->name));

    char * rawCartoPath = malloc (sizeof (char) * 45);
    Folder_buildFilename(myCarto2,DEFINITIVE_TREATED,rawCartoPath);

	assert_string_equal(res_attendu, rawCartoPath);
    free(myCarto2);

    free(rawCartoPath);
}

/**
 * @brief test of the buildFilename function of Folder
 * Create a definitive threated carto with id at 0 and build the filename using Folder_buildFilename function
 * Compare the filename rawCartoPath generate with the filename expected res_attendu.
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_buildFilename_definitive_treated(void **state){
	char * res_attendu = "cartos/0-test_treated.bmp";;
    s_carto * myCarto = malloc (sizeof(s_carto));
    myCarto->id = 0;
    strncpy(myCarto->name, "test_treated", sizeof(myCarto->name));

    char * rawCartoPath = malloc (sizeof (char) * 45);
    Folder_buildFilename(myCarto,DEFINITIVE_TREATED,rawCartoPath);

	assert_string_equal(res_attendu, rawCartoPath);
    free(myCarto);

    free(rawCartoPath);
}

/**
 * @brief test of the buildFilename function of Folder
 * Create a definitive raw carto with id at 0 and build the filename using Folder_buildFilename function
 * Compare the filename rawCartoPath generate with the filename expected res_attendu.
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_buildFilename_definitive_raw(void **state){
	char * res_attendu = "cartos/0-raw.bmp";;
    s_carto * myCarto = malloc (sizeof(s_carto));
    myCarto->id = 0;

    char * rawCartoPath = malloc (sizeof (char) * 45);
    Folder_buildFilename(myCarto,DEFINITIVE_RAW,rawCartoPath);

	assert_string_equal(res_attendu, rawCartoPath);
    free(myCarto);

    free(rawCartoPath);
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------TEST FOLDER_GETNEWID-----------------------------------------

/**
 * @brief test of the getNewId function of Folder
 * Get the id by default and verify if it is equal to 1
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_getNewId_by_default(void **state){
	int res_attendu = 1;

    int res = Folder_getNewId();

	assert_int_equal(res_attendu, res);
}

/**
 * @brief test of the getNewId function of Folder
 * Create a file with a carto path with an id at 1 and create a carto using the Folder_createNewCarto function wich use Folder_getNewId function
 * Verify if the function getNewId detect the id 1 in the path of the file and increment it to 2 to return the new id of the new carto. 
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_getNewId_with_1_carto(void **state){

    FILE *file;

    char *carto_raw = "cartos/1-raw.bmp";
    file = fopen(carto_raw, "w");
    fclose(file);

	int res_attendu = 2;
    s_carto * myCarto2 = Folder_createNewCarto();

    int res = myCarto2->id;
	assert_int_equal(res_attendu, res);
    free(myCarto2);
    remove(carto_raw);
}

/**
 * @brief test of the getNewId function of Folder
 * Create 2 files with a carto path with an id at 1 and an other with an id at 10 and create a carto using the Folder_createNewCarto function wich use Folder_getNewId function
 * Verify if the function getNewId detect the biggest id of the 2 files, wich is 10, and increment it to 11 to return the new id of the new carto. 
 * Return Ok if success, fail if test fail
 * @author Jean-Théophane Deschard
 */
static void test_Folder_getNewId_with_2_carto(void **state){

    FILE *file;

    char *carto_raw = "cartos/1-raw.bmp";
    file = fopen(carto_raw, "w");
    fclose(file);

    char *carto_raw2 = "cartos/10-raw.bmp";
    file = fopen(carto_raw2, "w");
    fclose(file);

	int res_attendu = 11;
    s_carto * myCarto2 = Folder_createNewCarto();

    int res = myCarto2->id;
	assert_int_equal(res_attendu, res);
    free(myCarto2);
    remove(carto_raw);
    remove(carto_raw2);
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------TEST FOLDER_GETNUMBEROFCARTOSSAVED-----------------------------------------


/**
 * @brief 1st test : good conditions : only 2 cartos saved
 * @note Expected behavior : return 2
 * @author Marin BONSERGENT
 */
void firstTest_getNumberOfCartosSaved(void **state)
{
    FILE *file;

    char *first_carto = "cartos/1-raw.bmp";
    file = fopen(first_carto, "w");
    fclose(file);
    
    char *second_carto = "cartos/1-cuisine.bmp";
    file = fopen(second_carto, "w");
    fclose(file);
    
    // end of building environment for test

    int res = Folder_getNumberOfCartosSaved();
    
    assert_int_equal(res, 2);

    remove(first_carto);
    remove(second_carto);

}

/**
 * @brief 2nd test : no carto saved
 * @note Expected behavior : return 0
 * @author Marin BONSERGENT
 */
void secondTest_getNumberOfCartosSaved(void **state)
{    
    // end of building environment for test

    int res = Folder_getNumberOfCartosSaved();
    
    assert_int_equal(res, 0);
}

/**
 * @brief 3rd test : no cartos saved, just random files without digit first
 * @note Expected behavior : return 0
 * @author Marin BONSERGENT
 */
void thirdTest_getNumberOfCartosSaved(void **state)
{
    FILE *file;

    char *first_random = "cartos/other_file.txt";
    file = fopen(first_random, "w");
    fclose(file);
    
    char *second_random = "cartos/file_other.txt";
    file = fopen(second_random, "w");
    fclose(file);
    
    // end of building environment for test

    int res = Folder_getNumberOfCartosSaved();
    
    assert_int_equal(res, 0);

    remove(first_random);
    remove(second_random);

}

/**
 * @brief 4rd test : 1 carto saved with one random files without digit first
 * @note Expected behavior : return 1
 * @author Marin BONSERGENT
 */
void fourdTest_getNumberOfCartosSaved(void **state)
{
    FILE *file;

    char *first_carto = "cartos/1-raw.bmp";
    file = fopen(first_carto, "w");
    fclose(file);
    
    char *second_random = "cartos/file_other.txt";
    file = fopen(second_random, "w");
    fclose(file);
    
    // end of building environment for test

    int res = Folder_getNumberOfCartosSaved();
    
    assert_int_equal(res, 1);

    remove(first_carto);
    remove(second_random);

}

/**
 * @brief 5th test : 1 carto saved with one random files with digit first
 * @note Expected behavior : return 1
 * @note FAIL because algorithm just look if the first character is a digit
 * @author Marin BONSERGENT
 */
void fifthTest_getNumberOfCartosSaved(void **state)
{
    FILE *file;

    char *first_carto = "cartos/1-raw.bmp";
    file = fopen(first_carto, "w");
    fclose(file);
    
    char *second_random = "cartos/49file_other.txt";
    file = fopen(second_random, "w");
    fclose(file);
    
    // end of building environment for test

    int res = Folder_getNumberOfCartosSaved();

    remove(first_carto);
    remove(second_random);
    assert_int_equal(res, 1);

}

static const struct CMUnitTest tests[] = 
{
    cmocka_unit_test(firstTest_deleteOldestCarto),
    cmocka_unit_test(secondTest_deleteOldestCarto),
    cmocka_unit_test(thirdTest_deleteOldestCarto),
    cmocka_unit_test(fourthTest_deleteOldestCarto),
    cmocka_unit_test(fifthTest_deleteOldestCarto),
    cmocka_unit_test(sixthTest_deleteOldestCarto),
    cmocka_unit_test(seventhTest_deleteOldestCarto),
    cmocka_unit_test(test_Folder_buildFilename_temporary),
    cmocka_unit_test(test_Folder_buildFilename_definitive_treated),
    cmocka_unit_test(test_Folder_buildFilename_definitive_treated_without_name),
    cmocka_unit_test(test_Folder_buildFilename_definitive_raw),
    cmocka_unit_test(test_Folder_getNewId_by_default),
    cmocka_unit_test(test_Folder_getNewId_with_1_carto),
    cmocka_unit_test(test_Folder_getNewId_with_2_carto),
    cmocka_unit_test(firstTest_getNumberOfCartosSaved),
    cmocka_unit_test(secondTest_getNumberOfCartosSaved),
    cmocka_unit_test(thirdTest_getNumberOfCartosSaved),
    cmocka_unit_test(fourdTest_getNumberOfCartosSaved),
    cmocka_unit_test(fifthTest_getNumberOfCartosSaved),

};


int Folder_run_tests()
{
    return cmocka_run_group_tests_name("Test de Folder", tests, set_up, tear_down);
}