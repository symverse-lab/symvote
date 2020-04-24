// Vote example in C
// Build C with vote lib: gcc -o cvote ./main.c ../../lib/vote.so -I ../../lib
// Run: ./cvote

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <inttypes.h>
#include <time.h>
#include "vote.h"

#define TEST 0
#define TEST_OPTION 0

void fullScenario();
void fullScenario2();
void checkResult(char *token_contract_addr, char *vote_contract_addr, char *poll_contract_addr);
char *processTx(char *input_tx, char *input_sct, char *keydir, char *pw);
char *createTockenContract(char *owner,char *owner_pw,char *config_file);
char *createVoteContract(char *owner,char *owner_pw,char *config_file,char *token);
char *createPollContract(char *owner,char *owner_pw,char *config_file,char *vote);
void addPollCreators(char *owner,char *owner_pw,char *config_file, char *vote);
void tallyVote(char *owner,char *owner_pw,char *config_file,char *poll);
void searchContract(char *owner,char *owner_pw,char *config_file, char *vote,  char *poll);
void removePollCreators(char *owner,char *owner_pw,char *config_file,char *vote);
void stopPoll(char *owner,char *owner_pw,char *config_file,char *poll);
void finishPoll(char *owner,char *owner_pw,char *config_file,char *poll);
void writePollResults(char *owner,char *owner_pw,char *config_file,char *poll);
void cast(char *owner, char *owner_pw, char *config_file,char* poll);

#if TEST_OPTION == 0
    //configuration
    char *config_file = ".config.json";
    //owner
    char *owner = "0x00020000000000100002"; //서버
    char *owner_keydir = "keystore/vote_work1";  //서버
    char *owner_pw = "1";                   //서버
    //users, for test
    char *user1 = "0x00020000000000110002";
    char *user1_keydir = "keystore/vote_work2";
    char *user1_pw = "1";
    char *user2 = "0x00020000000000120002";
    char *user2_keydir ="keystore/vote_work3";
    char *user2_pw = "1";
    char *user3 = "0x00020000000000130002";
    char *user3_keydir = "keystore/vote_work4";
    char *user3_pw = "1";
    char *user4 = "0x00020000000000140002";
    char *user4_keydir = "keystore/vote_work5";
    char *user4_pw = "1";
    //work node
    char *work_node = "0x00020000000000090002";
    //setup token
    char *total_supply = "0x56bc75e2d63100000";
    char *transfer_value ="0x10a0";

#elif TEST_OPTION == 1
    char *config_file = "../../lib/.config1.json";
    //owner
    char *owner = "0x00021000000000080002";
    char *owner_keydir = "/home/bakcj/test8/node8/keystore/";
    char *owner_pw = "jj";
    //users, for test
    char *user1 = "0x00021000000000090002";
    char *user1_keydir = "/home/bakcj/test8/node9/keystore/";
    char *user1_pw = "jj";
    char *user2 = "0x00010000000000010002";
    char *user2_keydir = "/home/bakcj/test8/node10/keystore/";
    char *user2_pw = "jj";
    char *user3 = "0x00020000000000010002";
    char *user3_keydir = "/home/bakcj/test8/node11/keystore/";
    char *user3_pw = "jj";
    char *user4 = "0x0002a000000000010002";
    char *user4_keydir = "/home/bakcj/test8/node12/keystore/";
    char *user4_pw = "jj";
    //work node
    char *work_node = "0x00021000000000080002";
    //setup token
    char *total_supply = "0x56bc75e2d63100000";
    char *transfer_value = "0xde0b6b3a7640000";
#elif TEST_OPTION == 2
    //configuration
    char *config_file = ".config1.json";
    //owner
    char *owner = "0x00000000000000000201"; //서버
    char *owner_keydir = "keystore1/node2";  //서버
    char *owner_pw = "shlee";               //서버
    //users, for test
    char *user1 = "0x00000000000000000301"; //서버
    char *user1_keydir = "keystore1/node3";  //서버
    char *user1_pw = "shlee";               //서버
    char *user2 = "0x00000000000000000401";
    char *user2_keydir ="keystore1/node4";
    char *user2_pw = "shlee";
    char *user3 = "0x00000000000000000501";
    char *user3_keydir = "keystore1/node5";
    char *user3_pw = "shlee";
    char *user4 = "0x00000000000000000601";
    char *user4_keydir = "keystore1/node6";
    char *user4_pw = "shlee";
    //work node
    char *work_node = "0x00000000000000000201";
    //setup token
    char *total_supply = "0x56bc75e2d63100000";
    char *transfer_value ="0x10a0";
#else
//
#endif

int main() {
    printf("Using vote lib from C:\n");
    printf("start main() ==============================================================================\n");

#if TEST == 0
   fullScenario(); 
#elif TEST == 1
   fullScenario2();
#else   //unit test
     char *config_file = ".config.json";
     char *owner = "0x00000000000000000201"; //서버
     char *owner_keydir = "keystore/node2";  //서버
     char *owner_pw = "shlee";               //서버
     
     char *tocken ="0xcEA57432B8be00e7B14E" ; 
     char *vote ="0x60D7Ad69E0F4abAB397c" ;
     char *poll ="0xbE9487cBfF1015a131f5" ;
     int ret_value;
     char *ret_txhash;
    //0. Initialize
    ret_value = Init(owner, owner_pw, config_file);
    if (ret_value < 1) {
        printf("Go vote library init fail\n");
        exit(0);
    }


    //createVote();

    ////////////////////////////////////////
    
    //searchContract(owner,owner_pw,config_file,vote, poll);
    ////////////////////////////////////////
    //removePollCreators(owner,owner_pw,config_file,vote);
    //stopPoll(owner,owner_pw,config_file,poll);
    //finishPoll(owner,owner_pw,config_file,poll);
    //writePollResults(owner,owner_pw,config_file,poll);
    //createTockenContract(owner,owner_pw,config_file); 
    //createVoteContract(owner,owner_pw,config_file, tocken);
    //addPollCreators(owner,owner_pw,config_file,vote);
    //createPollContract(owner,owner_pw,config_file,vote);
    //

    //cast(owner,owner_pw,config_file,poll);
#endif
    printf("end main() ==============================================================================\n");
}

void fullScenario(){
    char input_tx[256];
    char input_sct20_create[256];
    char input_sct20_transfer[256];
    char input_sct50_create[256];
    char input_sct50_addpollcreators[256];
    char input_sct51_create[256];
    char input_sct51_castvote[256];

    char *token_contract_addr;
    char *vote_contract_addr;
    char *poll_contract_addr;

    char *ret_tx;
    char *ret_signedtx;
    char *ret_txhash;
    int ret_value;

    time_t poll_start_time;
    time_t poll_end_time;


    //0. Initialize
    ret_value = Init(owner, owner_pw, config_file);
    if (ret_value < 1) {
        printf("Go vote library init fail\n");
        exit(0);
    }

    //1. Token creation : 투표에 사용될 토큰을 생성합니다. 
    printf("<START CreateTokenContract\n");
    sprintf(input_sct20_create, "[\"SymToken\",\"STK\",\"%s\",\"%s\"]", total_supply, owner);
    ret_txhash =  CreateTokenContract(input_sct20_create);
    printf("<END CreateTokenContract>\n%s\n\n",ret_txhash);
    
    sleep(10);

    //Get token contract address
    token_contract_addr = GetContractAddress(ret_txhash);
    printf("Token contract address: %s\n\n", token_contract_addr);
   
     
    //2. Token transfer : 투표에 사용될 토큰을 유저에게 전송합니다. 
    printf("<START Token transfer>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, token_contract_addr, work_node);

    printf("<START Token transfer User 1 >\n");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s‬\"]}", user1, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    printf("<DONE transfer to User 1 >\n\n");
    
    printf("<START Token transfer User 2 >\n");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user2, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    printf("<DONE transfer to User 2 >\n\n");

    printf("<START Token transfer User 3 >\n");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user3, transfer_value);     
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    printf("<DONE transfer to User 3 >\n\n");
    
    printf("<START Token transfer User 4 >\n");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user4, transfer_value);     
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    printf("<DONE transfer to User 4 >\n\n");
    
    printf("<END Token transfer>\n\n");
    

    //3. Vote creation : 투표 컨트랙트(생성된 토큰을 사용할 안건의 모임)를 생성합니다. 
    printf("<START createVoteContract creation>\n");
    sprintf(input_sct50_create, "[\"SymParty\",\"%s\",\"%s\"]", token_contract_addr, owner);
    ret_txhash = CreateVoteContract(input_sct50_create);
    printf("<END createVoteContract>\n%s\n\n",ret_txhash);
    
    
    sleep(10);


    vote_contract_addr = GetContractAddress(ret_txhash);
    printf("Vote contract address: %s\n\n", vote_contract_addr);

    //4. Add poll creator : 생성된 투표컨트랙트에 안건 제안 가능자를 등록합니다. 
    printf("<START Add poll creators>\n");
    sprintf(input_sct50_addpollcreators,"[\"%s\", \"%s\"]", owner, user1);
    ret_txhash = AddPollCreators(vote_contract_addr,input_sct50_addpollcreators);
    printf("<END AddPollCreators>\n%s\n\n",ret_txhash);


    //5. Poll creation : 투표에 안건을 등록합니다. 
    poll_start_time = time(NULL);
    poll_end_time = poll_start_time + 24*60*60;
    printf("poll start: %ld, end: %ld\n", poll_start_time, poll_end_time);

    printf("<START CreatePollContract creation>\n");
    sprintf(input_sct51_create, "[\"0x0\",\"0x0\",\"Agenda - break time \",\"Agenda descrition - Let's take a break :)\",\"%s\",\"0x%lx\",\"0x%lx\",\"%s\",\"0x0\",\"0x1\",\"0x5\",\"0x4\",\"0x7\"]", owner, poll_start_time, poll_end_time, vote_contract_addr);
    ret_txhash = CreatePollContract(input_sct51_create);
    printf("<END CreatePollContract>\n%s\n\n",ret_txhash);
   
    sleep(10);
    //Get contract address
    poll_contract_addr = GetContractAddress(ret_txhash);
    printf("Poll contract address: %s\n\n", poll_contract_addr);

    //6. Cast vote : 등록된 안건에 대하여 투표를 합니다. 
    printf("<START cast vote>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, owner_keydir, owner_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user1_keydir, user1_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user2, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user2_keydir, user2_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user3, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user3_keydir, user3_pw);

    printf("<END cast vote>\n\n");
    sleep(20);
    //7. Tally vote : 결과를 집계합니다. 
    int ret;
    ret = StartTally(poll_contract_addr);
    sleep(10);
    printf("<END StartTally>\n%d\n\n",ret);

    //*. 결과의 조회는 아래와 같이 확인할수 있습니다. 
    //Check result
    checkResult(token_contract_addr, vote_contract_addr, poll_contract_addr);
}

void fullScenario2() {
    char input_tx[256];
    char input_sct20_create[256];
    char input_sct20_transfer[256];
    char input_sct50_create[256];
    char input_sct50_addpollcreators[256];
    char input_sct51_create[256];
    char input_sct51_castvote[256];

    char *token_contract_addr;
    char *vote_contract_addr;
    char *poll_contract_addr;

    char *ret_tx;
    char *ret_signedtx;
    char *ret_txhash;
    char *ret_vote_result;
    int ret_value;

    time_t poll_start_time;
    time_t poll_end_time;

    //Initialize
    ret_value = Init(owner, owner_pw, config_file);
    if (ret_value < 1) {
        printf("Go vote library init fail\n");
        exit(0);
    }

    //Unlock operator account
    // ret_value = UnlockAccount(owner, owner_pw);
    // if (ret_value < 1) {
    //     printf("Operator account unlock fail\n");
    //     exit(0);
    // }

    //Token creation
    printf("<START Token creation>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, work_node);
    sprintf(input_sct20_create, "{\"type\":\"0x14\",\"method\":\"0x0\",\"params\":[\"VToken\",\"VTK\",\"%s\",\"%s\"]}", total_supply, owner);
    ret_txhash = processTx(input_tx, input_sct20_create, "", "");
    printf("<END Token creation>\n\n");

    sleep(10);

    //Get token contract address
    token_contract_addr = GetContractAddress(ret_txhash);
    printf("Token contract address: %s\n\n", token_contract_addr);

    //Token transfer
    printf("<START Token transfer>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, token_contract_addr, work_node);
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user1, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user2, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user3, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    sprintf(input_sct20_transfer, "{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user4, transfer_value);
    ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
    printf("<END Token transfer>\n\n");

    //Vote creation
    printf("<START Vote creation>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, work_node);
    sprintf(input_sct50_create, "{\"type\":\"0x32\",\"method\":\"0x0\",\"params\":[\"SymParty\",\"%s\",\"%s\"]}", token_contract_addr, owner);
    ret_txhash = processTx(input_tx, input_sct50_create, "", "");
    printf("<END Vote creation>\n\n");

    sleep(10);

    //Get vote contract address
    vote_contract_addr = GetContractAddress(ret_txhash);
    printf("Vote contract address: %s\n\n", vote_contract_addr);

    //Get vote contract info (just check)
    char *vote_contract;
    vote_contract = GetVoteContract(vote_contract_addr);
    printf("Vote contract info: %s\n\n", vote_contract);

    //Add poll creator
    printf("<START Add poll creators>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, vote_contract_addr, work_node);
    sprintf(input_sct50_addpollcreators, "{\"type\":\"0x32\",\"method\":\"0x1\",\"params\":[\"%s\", \"%s\"]}", user1, user2);
    ret_txhash = processTx(input_tx, input_sct50_addpollcreators, "", "");
    printf("<END Add poll creators>\n\n");

    sleep(10);

    //Poll creation
    printf("<START Poll creation>\n");
    poll_start_time = time(NULL);
    // poll_end_time = poll_start_time + 24*60*60;
    poll_end_time = poll_start_time + 100;
    printf("poll start: %ld, end: %ld\n", poll_start_time, poll_end_time);
    sprintf(input_tx, "{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, work_node);
    sprintf(input_sct51_create, "{\"type\":\"0x33\",\"method\":\"0x0\",\"params\":[\"0x1\",\"0x1\",\"Agenda1-coffee break\",\"Agenda1 descrition-do you want to have some coffee?\",\"%s\",\"0x%lx\",\"0x%lx\",\"%s\",\"0x0\",\"0x0\",\"0x4\",\"0x4\",\"0x7\"]}", owner, poll_start_time, poll_end_time, vote_contract_addr);
    ret_txhash = processTx(input_tx, input_sct51_create, user1_keydir, user1_pw);
    printf("<END Poll creation>\n\n");

    sleep(10);

    //Get poll contract address
    poll_contract_addr = GetContractAddress(ret_txhash);
    printf("Poll contract address: %s\n\n", poll_contract_addr);

    //Get poll contract info (just check)
    char *poll_contract;
    poll_contract = GetPollContract(poll_contract_addr);
    printf("Poll contract info: %s\n\n", poll_contract);

    //Cast vote
    printf("<START cast vote>\n");
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, owner_keydir, owner_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user1_keydir, user1_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user2, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user2_keydir, user2_pw);
    sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user3, poll_contract_addr, work_node);
    sprintf(input_sct51_castvote, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
    ret_txhash = processTx(input_tx, input_sct51_castvote, user3_keydir, user3_pw);
    printf("<END cast vote>\n\n");

    sleep(20);  //wait until poll end

    //Tally vote
    printf("<START tally vote>\n");
    ret_value = StartTally(poll_contract_addr);
    printf("Poll contract %s tally vote started: %d\n", poll_contract_addr, ret_value);
    sleep(10);   //wait until tally finished
    ret_vote_result = GetVoteResult(poll_contract_addr);
    printf("Poll contract %s vote result: \n%s\n", poll_contract_addr, ret_vote_result);
    printf("<END tally vote>\n\n");

    sleep(10);

    //Get vote contract info (just check)
    vote_contract = GetVoteContract(vote_contract_addr);
    printf("Vote contract info: %s\n\n", vote_contract);

    //Get poll contract info (just check)
    poll_contract = GetPollContract(poll_contract_addr);
    printf("Poll contract info: %s\n\n", poll_contract);

    //Check result
    checkResult(token_contract_addr, vote_contract_addr, poll_contract_addr);
}

char *processTx(char *input_tx, char *input_sct, char *keydir, char *pw) {
    char *ret_tx;
    char *ret_signedtx;
    char *ret_txhash;

    ret_tx = MakeTransaction(input_tx, input_sct);

    if (keydir == "") {
        ret_signedtx = SignTransaction(ret_tx);
    } else {
        ret_signedtx = SignTransactionEx(ret_tx, keydir, pw);
    }
    ret_txhash = SendRawTransaction(ret_signedtx);
    printf("return SendRawTransaction:\n %s\n", ret_txhash);

    return ret_txhash;
}

void checkResult(char *token_contract_addr, char *vote_contract_addr, char *poll_contract_addr) {
    char *ret_token_info;
    char *ret_vote_info;
    char *ret_poll_info;
    char *ret_available_poll_creators;
    char *ret_poll_creater;
    char *ret_vote_result;
    int ret_value;

    printf("<Check Result>");
    printf("\ntoken_contract: %s, vote contract: %s, poll contract: %s \n", token_contract_addr, vote_contract_addr, poll_contract_addr);

    //get token contract
    printf("<START GetTokenContract>\n");
    ret_token_info = GetTokenContract(token_contract_addr);
    printf("<END GetTokenContract>\n%s\n\n",ret_token_info);

    //get vote contract
    printf("<START GetVoteContract>\n");
    ret_vote_info = GetVoteContract(vote_contract_addr);
    printf("<END GetVoteContract>\n%s\n\n",ret_vote_info);

    //get available poll creators
    printf("<START GetAvailablePollCreators>\n");
    ret_available_poll_creators = GetAvailablePollCreators(vote_contract_addr);
    printf("<END GetAvailablePollCreators>\n%s\n\n",ret_available_poll_creators);

    //get poll contract
    printf("<START GetPollContract>\n");
    ret_poll_info = GetPollContract(poll_contract_addr);
    printf("<END GetPollContract>\n%s\n\n",ret_poll_info);
   
    //get poll creator
    printf("<START GetPollCreator>\n");
    ret_poll_creater = GetPollCreator(poll_contract_addr);
    printf("<END GetPollCreator>\n%s\n\n",ret_poll_creater);
   
    //get poll state
    printf("<START GetPollState>\n");
    ret_value = GetPollState(poll_contract_addr);
    printf("<END GetPollState>\n%d\n\n",ret_value);
   
    //get vote result
    printf("<START GetVoteResult>\n");
    ret_vote_result = GetVoteResult(poll_contract_addr);
    printf("<END GetVoteResult>\n%s\n\n",ret_vote_result);
}

/////////////////////////////////////////////////////////////
//사용 예
/////////////////////////////////////////////////////////////

char* createTockenContract(char *owner,char *owner_pw,char *config_file){

    char *total_supply = "0x56bc75e2d631";
    char *contract_addr;
    printf("<START CreateTokenContract creation>\n");
    char input_sct[256];
    sprintf(input_sct, "[\"SymToken\",\"STK\",\"%s\",\"%s\"]", total_supply, owner);
    char *ret;
    ret = CreateTokenContract(input_sct);
    printf("<END CreateTokenContract>\n%s\n\n",ret);
    
    sleep(4);
    //Get contract address
    contract_addr = GetContractAddress(ret);
    printf("Token contract address: %s\n\n", contract_addr);
    return contract_addr;
}


char* createVoteContract(char *owner,char *owner_pw,char *config_file,char *token){
   
    printf("<START createVoteContract creation>\n");
    char input_sct[256];
    sprintf(input_sct, "[\"SymParty\",\"%s\",\"%s\"]", token, owner);
    char *ret;
    ret = CreateVoteContract(input_sct);
    printf("<END createVoteContract>\n%s\n\n",ret);
    
    sleep(4);
   
    char *contract_addr;
    //Get contract address
    contract_addr = GetContractAddress(ret);
    printf("Vote contract address: %s\n\n", contract_addr);
    return contract_addr;
}

char* createPollContract(char *owner,char *owner_pw,char *config_file,char *vote){
  
    time_t poll_start_time;
    time_t poll_end_time;
  
    poll_start_time = time(NULL);
    poll_end_time = poll_start_time + 24*60*60;
    printf("poll start: %ld, end: %ld\n", poll_start_time, poll_end_time);


    printf("<START CreatePollContract creation>\n");
    char input_sct[256];
    sprintf(input_sct, "[\"0x0\",\"0x0\",\"Agenda - break time \",\"Agenda descrition - Let's take a break :)\",\"%s\",\"0x%lx\",\"0x%lx\",\"%s\",\"0x0\",\"0x0\",\"0x4\",\"0x4\",\"0x7\"]", owner, poll_start_time, poll_end_time, vote);
    char *ret;
    ret = CreatePollContract(input_sct);
    printf("<END CreatePollContract>\n%s\n\n",ret);
   
    sleep(4);
    //Get contract address
    char *contract_addr;
    contract_addr = GetContractAddress(ret);
    printf("Poll contract address: %s\n\n", contract_addr);
    return contract_addr;
}

void addPollCreators(char *owner,char *owner_pw,char *config_file,char *vote){
  
    printf("<START Add poll creators>\n");
    char *input_sct50_addpollcreators = "[\"0x0000000000000000201\", \"0x0000000000000000401\"]";
    char *ret_vote_info;
    ret_vote_info = AddPollCreators(vote,input_sct50_addpollcreators);
    printf("<END AddPollCreators>\n%s\n\n",ret_vote_info);
  
}

void tallyVote(char *owner,char *owner_pw,char *config_file,char *poll){
    int ret;
    ret = StartTally(poll);
    sleep(5);
    printf("<END StartTally>\n%d\n\n",ret);
}


void searchContract(char *owner,char *owner_pw,char *config_file, char *vote,  char *poll){
    char *ret_vote_info;
    char *ret_poll_creater;
    char *ret_poll_info;
    int ret_value;

      printf("<START GetVoteContract>\n");
      ret_vote_info = GetVoteContract(vote);
      printf("<END GetVoteContract>\n%s\n\n",ret_vote_info);

      printf("<START GetAvailablePollCreators>\n");
      ret_poll_creater = GetAvailablePollCreators(vote);
      printf("<END GetAvailablePollCreators>\n%s\n\n",ret_poll_creater);

     printf("<START  GetPollContract>\n");
     ret_poll_info = GetPollContract(poll);
     printf("<END GetPollContract>\n%s\n\n",ret_poll_info);
   
     printf("<START  GetPollCreator>\n");
     ret_poll_info = GetPollCreator(poll);
     printf("<END GetPollCreator>\n%s\n\n",ret_poll_info);
   
     printf("<START  GetPollState>\n");
     ret_value = GetPollState(poll);
     printf("<END GetPollState>\n%d\n\n",ret_value);
   
     printf("<START  GetVoteResult>\n");
     ret_poll_info = GetVoteResult(poll);
     printf("<END GetVoteResult>\n%s\n\n",ret_poll_info);
}

void removePollCreators(char *owner,char *owner_pw,char *config_file,char *vote){
    char *input_sct50_removepollcreators = "[\"0x00000000000000000301\", \"0x0000000000000000701\"]";
    char *ret_vote_info;
    ret_vote_info = RemovePollCreators(vote,input_sct50_removepollcreators);
    printf("<END RemovePollCreators>\n%s\n\n",ret_vote_info);
  
}

void stopPoll(char *owner,char *owner_pw,char *config_file,char *poll){
   
    char *ret;
    ret = StopPoll(poll);
    printf("<END stopPoll>\n%s\n\n",ret);
 }

void finishPoll(char *owner,char *owner_pw,char *config_file,char *poll){
 
    char *ret;
    ret = FinishPoll(poll);
    printf("<END FinishPoll>\n%s\n\n",ret);
 }

void writePollResults(char *owner,char *owner_pw,char *config_file,char *poll){
    char *input_sct = "[\"0x7\", \"0x77\",\"0x777\", \"0x7777\", \"0x77777\", \"0x7337\", \"0x7227\"]";
    char *ret;
    ret = WritePollResults(poll,input_sct);
    printf("<END WritePollResults>\n%s\n\n",ret);
}

void cast(char *owner,char *owner_pw,char *config_file,char* poll){

    char *user = "0x00000000000000000201";
    char *user_keydir = "/mnt/d/symNet/node2/keystore/";
    char *user_pw = "shlee";

    char input_tx[1000];
    char input_sct[1000];
    char *ret_txhash;
     //Cast vote
     printf("<START cast vote>\n");
     
     printf("<START cast vote Owner>\n");
     sprintf(input_tx, "{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"0x00000000000000000201\"],\"type\":\"0x1\"}",user, poll);
     sprintf(input_sct, "{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
     //ret_txhash = processTx(input_tx, input_sct, "", "");
     ret_txhash = processTx(input_tx, input_sct, user_keydir, user_pw);
    printf("<DONE cast vote Owner>\n\n");
}
