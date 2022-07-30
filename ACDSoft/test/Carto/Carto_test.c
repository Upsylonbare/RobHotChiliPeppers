
// /**
//  * Module de test du module src/Carto/Carto.c
//  */
// #include <stdarg.h>
// #include <stddef.h>
// #include <setjmp.h>
// #include "../../lib/cmocka-x86_64/include/cmocka.h"


// //#include "../../src/Carto/Carto.c"

// static int set_up(void **state) {
// 	return 0;
// }

// static int tear_down(void **state) {
// 	return 0;
// }

// static void test_Carto_buildFilename_without_name(void **state){
// 	char * res_attendu = "../../cartos/0-.txt";
//     static s_carto* currentCarto;
//     currentCarto = Carto_new();

//     char * res = Carto_buildFilename(currentCarto);
// 	assert_string_equal(res_attendu, res);
// }

// static void test_Carto_buildFilename_with_name(void **state){
// 	char * res_attendu = "../../cartos/0-test.txt";
//     static s_carto* currentCarto;
//     currentCarto = Carto_new();
// 	Carto_setNameCarto(currentCarto, "test");

//     char * res = Carto_buildFilename(currentCarto);
// 	assert_string_equal(res_attendu, res);
// }

// static void test_Carto_buildFilename_with_too_long_name(void **state){
// 	char * res_attendu = "../../cartos/0-TooLongNameForTe.txt";
//     static s_carto* currentCarto;
//     currentCarto = Carto_new();
// 	Carto_setNameCarto(currentCarto, "TooLongNameForTestingPurpose");

//     char * res = Carto_buildFilename(currentCarto);
// 	assert_string_equal(res_attendu, res);
// }

// static void test_Carto_buildFilename_with_wrong_character(void **state){
// 	char * res_attendu = "../../cartos/0-Characteré.txt";
//     static s_carto* currentCarto;
//     currentCarto = Carto_new();
// 	Carto_setNameCarto(currentCarto, "Characteré");

//     char * res = Carto_buildFilename(currentCarto);
// 	assert_string_equal(res_attendu, res);
// }

// static const struct CMUnitTest tests[] = 
// {
// 	cmocka_unit_test(test_Carto_buildFilename_without_name),
// 	cmocka_unit_test(test_Carto_buildFilename_with_name),
// 	cmocka_unit_test(test_Carto_buildFilename_with_too_long_name),
// 	cmocka_unit_test(test_Carto_buildFilename_with_wrong_character)

// };


// /**
//  * Lancement de la suite de tests pour le module.
//  */
// int carto_run_tests() {
// 	return cmocka_run_group_tests_name("Test du module Carto", tests, set_up, tear_down);
// }
