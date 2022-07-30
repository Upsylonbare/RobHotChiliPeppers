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

#include "../../src/NetworkC/Coder/NetworkC_Coder.c"


static s_message* dtMessageAttendu;
static s_message* dtMessage;
static s_log* dtLogAttendu;
static s_log* dtLog;

/**
 * Test datas ar arbitray
 * 
 */

static int set_up(void **state)
{
    dtMessageAttendu = calloc(1, sizeof(s_message));
    dtMessage = calloc(1, sizeof(s_message));
    dtLogAttendu = calloc(1, sizeof(s_log));
    dtLog = calloc(1, sizeof(s_log));
    return 0;
}

static int tear_down(void **state) 
{
    free(dtMessageAttendu);
    free(dtMessage);
    free(dtLog);
    free(dtLogAttendu);
	return 0;
}

static void clearDt(void)
{
    memset(dtMessageAttendu, 0, sizeof(s_message));
    memset(dtMessage, 0, sizeof(s_message));
    memset(dtLogAttendu, 0, sizeof(s_log));
    memset(dtLog, 0, sizeof(s_log));
}

static void test_NetworkC_Coder_encode_C_SETCARTO()
{
    //Check that an s_message that contains the message setcarto is well encoded.
    e_command dtCommand = C_SETCARTO;
    uint32_t dtId = 28;
    char dtCartoName[] = "monNom";
    char dtCartoDatas[] = "OHFOEIHOHDLKVLMENPHVOHLK";

    //Setup of s_message struct
    dtMessage->command = dtCommand;
    dtMessage->carto.id = dtId;
    memcpy(dtMessage->carto.name, dtCartoName, sizeof(dtCartoName));
    memcpy(dtMessage->carto.treatedCarto, dtCartoDatas, sizeof(dtCartoDatas));

    //Manually setup s_log struct
    dtLogAttendu->command = htonl(dtCommand);
    dtLogAttendu->id = htonl(dtId);
    memcpy(dtLogAttendu->carto, dtCartoDatas, sizeof(dtCartoDatas));
    memcpy(dtLogAttendu->name, dtCartoName, sizeof(dtCartoName));
    dtLogAttendu->size = htonl(\
        sizeof(dtLogAttendu->command) + \
        sizeof(dtLogAttendu->id) + \
        sizeof(dtLogAttendu->name) + \
        sizeof(dtLogAttendu->carto));

    //Encode s_message as a s_log
    NetworkC_Coder_encode(dtMessage, dtLog);

    //Check that the memory is equal
    assert_memory_equal(dtLogAttendu, dtLog, sizeof(s_log));

    clearDt();

}

static void test_NetworkC_Coder_encode_C_ACK4SCAN()
{
    //Check that an s_message that contains the message ack4scan is well encoded.

    //Setup of s_message struct
    dtMessage->command = C_ACK4SCAN;
    
    //Manually setup s_log struct
    dtLogAttendu->command = htonl(C_ACK4SCAN);
    dtLogAttendu->size = htonl(sizeof(uint32_t)*2);

    //Encode s_message as a s_log
    NetworkC_Coder_encode(dtMessage, dtLog);

    //Check that the memory is equal
    assert_memory_equal(dtLog, dtLogAttendu, sizeof(s_log));

    clearDt();

}

static void test_NetworkC_Coder_encode_C_ACKCARTO()
{
    //Check that an s_message that contains the message ackcarto is well encoded.

    //Setup of s_message struct
    dtMessage->command = C_ACKCARTO;
    
    //Manually setup s_log struct
    dtLogAttendu->command = htonl(C_ACKCARTO);
    dtLogAttendu->size = htonl(sizeof(uint32_t)*2);

    //Encode s_message as a s_log
    NetworkC_Coder_encode(dtMessage, dtLog);

    //Check that the memory is equal
    assert_memory_equal(dtLog, dtLogAttendu, sizeof(s_log));

    clearDt();

}

static void test_NetworkC_Coder_encode_C_ACK4SAVECARTO()
{
    //Check that an s_message that contains the message ack4savecarto is well encoded.
    dtMessage->command = C_ACK4SAVECARTO;
    
    //Manually setup s_log struct
    dtLogAttendu->command = htonl(C_ACK4SAVECARTO);
    dtLogAttendu->size = htonl(sizeof(uint32_t)*2);

    //Encode s_message as a s_log
    NetworkC_Coder_encode(dtMessage, dtLog);

    //Check that the memory is equal
    assert_memory_equal(dtLog, dtLogAttendu, sizeof(s_log));

    clearDt();

}

static void test_NetworkC_Coder_decode_A_ASK4SCAN()
{
    //Check that an s_log that contains the message ask4scan is well encoded.
    uint32_t dtSize = 8;
    uint32_t dtCommand = A_ASK4SCAN;

    //Manually setup s_log struct
    dtLog->command = htonl(dtCommand);
    dtLog->size = htonl(dtSize);

    //Setup of waited s_message struct
    dtMessageAttendu->command = dtCommand;

    //Decode s_log as a s_message
    NetworkC_Coder_decode(dtLog, dtMessage);

    //Check that the memory is equal
    assert_memory_equal(dtMessage, dtMessageAttendu, sizeof(s_message));

    clearDt();

}

static void test_NetworkC_Coder_decode_A_ACKCARTO()
{
    //Check that an s_log that contains the message ackcarto is well encoded.
    uint32_t dtSize = 8;
    uint32_t dtCommand = A_ACKCARTO;

    //Manually setup s_log struct
    dtLog->command = htonl(dtCommand);
    dtLog->size = htonl(dtSize);

    //Setup of waited s_message struct
    dtMessageAttendu->command = dtCommand;

    //Decode s_log as a s_message
    NetworkC_Coder_decode(dtLog, dtMessage);

    //Check that the memory is equal
    assert_memory_equal(dtMessage, dtMessageAttendu, sizeof(s_message));

    clearDt();

}

static void test_NetworkC_Coder_decode_A_SETCARTO()
{
    //Check that an s_log that contains the message ask4scan is well encoded.
    uint32_t dtSize = 32;
    uint32_t dtCommand = A_SETCARTO;
    char dtName[] = "YOUPIYOU";
    char dtTreatedCarto[] = "Huuuuuuuuuuuuuuuuuuujj";
    uint32_t dtId = 25;

    //Manually setup s_carto struct for s_log struct
    s_carto* dtCarto = calloc(1, sizeof(s_carto));
    dtCarto->id = dtId;
    memcpy(dtCarto->name, dtName, sizeof(dtName));
    memcpy(dtCarto->treatedCarto, dtTreatedCarto, sizeof(dtTreatedCarto));

    //Manually setup s_log struct
    dtLog->command = htonl(dtCommand);
    dtLog->size = htonl(dtSize);
    memcpy(dtLog->carto, dtTreatedCarto, sizeof(dtTreatedCarto));
    memcpy(dtLog->name, dtName, sizeof(dtName));
    dtLog->id = htonl(dtId);

    //Setup of waited s_message struct
    s_message* dtMessageAttendu = calloc(1, sizeof(s_message));
    dtMessageAttendu->command = dtCommand;
    memcpy(&(dtMessageAttendu->carto), dtCarto, sizeof(s_carto));

    //Decode s_log as a s_message
    NetworkC_Coder_decode(dtLog, dtMessage);

    //Check that the memory is equal
    assert_memory_equal(dtMessage, dtMessageAttendu, sizeof(s_message));

    clearDt();

}

/**
 * Suite de test pour le module.
 *
 * A compléter si besoin est.
 *
 */
static const struct CMUnitTest tests[] = 
{
    cmocka_unit_test(test_NetworkC_Coder_encode_C_ACKCARTO),
    cmocka_unit_test(test_NetworkC_Coder_encode_C_ACK4SAVECARTO),
    cmocka_unit_test(test_NetworkC_Coder_encode_C_ACK4SCAN),
    cmocka_unit_test(test_NetworkC_Coder_encode_C_SETCARTO),
    cmocka_unit_test(test_NetworkC_Coder_decode_A_SETCARTO),
    cmocka_unit_test(test_NetworkC_Coder_decode_A_ASK4SCAN),
    cmocka_unit_test(test_NetworkC_Coder_decode_A_ACKCARTO)
};

/**
 * Lancement de la suite de tests pour le module.
 */
int NetworkC_Coder_run_tests() 
{
	return cmocka_run_group_tests_name("Test du module Coder", tests, set_up, tear_down);
}