// Compile: javac -cp jna-5.5.0.jar VoteExample.java Vote.java
// Run: java -cp .:jna-5.5.0.jar VoteExample

import com.sun.jna.*;
import java.util.*;
import java.lang.Long;

public class Vote {
   public interface GoVote extends Library {
        // // GoSlice class maps to:
        // // C type struct { void *data; GoInt len; GoInt cap; }
        // public class GoSlice extends Structure {
        //     public static class ByValue extends GoSlice implements Structure.ByValue {}
        //     public Pointer data;
        //     public long len;
        //     public long cap;
        //     protected List getFieldOrder(){
        //         return Arrays.asList(new String[]{"data","len","cap"});
        //     }
        // }

        // // GoString class maps to:
        // // C type struct { const char *p; GoInt n; }
        // public class GoString extends Structure {
        //     public static class ByValue extends GoString implements Structure.ByValue {}
        //     public String p;
        //     public long n;
        //     protected List getFieldOrder(){
        //         return Arrays.asList(new String[]{"p","n"});
        //     }
        // }

        // Extern C functions
        public int Init(String owner, String onwerPassword, String filePath);
        public void Close();
        public String MakeSCT(String p0);
        public String MakeTransaction(String p0, String p1);
        public String SignTransaction(String p0);
        public String SignTransactionEx(String p0, String p1, String p2);
        public int UnlockAccount(String p0, String p1);
        public String SendTransaction(String p0);
        public String SendRawTransaction(String p0);
        public int GetTransactionStatus(String p0);
        public String GetTransactionReceipt(String p0);
        public String GetContractAddress(String p0);
        public String GetTokenContract(String p0);
        public String GetVoteContract(String p0);
        public String GetAvailablePollCreators(String p0);
        public String GetPollContract(String p0);
        public String GetPollCreator(String p0);
        public int GetPollState(String p0);
        public String GetVoteResult(String p0);
        public String SetVoteManager(String p0);
        public String CreateTokenContract(String p0);
        public String CreateVoteContract(String p0);
        public String CreatePollContract(String p0);
        public String AddPollCreators(String p0, String p1);
        public String RemovePollCreators(String p0);
        public String StopPoll(String p0);
        public String FinishPoll(String p0);
        public int StartTally(String p0);
        public String WritePollResults(String p0, String p1);
    }
 
    public GoVote vote = (GoVote) Native.loadLibrary("../../lib/vote.so", GoVote.class);

    String config_file;
   
    String owner;
    String owner_keydir;
    String owner_pw;
    String user1;
    String user1_keydir;
    String user1_pw;
    String user2;
    String user2_keydir;
    String user2_pw;
    String user3;
    String user3_keydir;
    String user3_pw;
    String user4;
    String user4_keydir;
    String user4_pw;

    String work_node;
        
    String total_supply;
    String transfer_value;

    public void fullScenario(int option) throws InterruptedException {
        String token_contract_addr = "";
        String vote_contract_addr = "";
        String poll_contract_addr = "";
    
        String input_tx = "";
        String input_sct20_create = "";
        String input_sct20_transfer ="";
        String input_sct50_create = "";
        String input_sct50_addpollcreators = "";
        String input_sct51_create = "";
        String input_sct51_castvote = "";

        String ret_tx = "";
        String ret_signedtx = "";
        String ret_txhash = "";
        //String rlp_sct = "";    
        //String ret_vote_result = "";
        int ret_value = 0;
    
        String vote_contract;
        String poll_contract;

        long poll_start_time = 0;
        long poll_end_time = 0;

        //Setup test user info
        setup(option);

        //0. Initialize
        ret_value = vote.Init(owner, owner_pw, config_file);
        if (ret_value < 1) {
            System.out.printf("Go vote library init fail\n");
            System.exit(0);
        }
    

        //1. Token creation : 투표에 사용될 토큰을 생성합니다. 
        System.out.printf("<START CreateTokenContract\n");
        input_sct20_create = String.format("[\"SymToken\",\"STK\",\"%s\",\"%s\"]", total_supply, owner);
        ret_txhash =  vote.CreateTokenContract(input_sct20_create);
        System.out.printf("<END CreateTokenContract>\n%s\n\n",ret_txhash);
        
        Thread.sleep(10000);

        //Get token contract address
        token_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Token contract address: %s\n\n", token_contract_addr);

        
        //2. Token transfer : 투표에 사용될 토큰을 유저에게 전송합니다. 
        System.out.printf("<START Token transfer>\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, token_contract_addr, work_node);
    
        System.out.printf("<START Token transfer User 1 >\n");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s‬\"]}", user1, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        System.out.printf("<DONE transfer to User 1 >\n\n");
        
        System.out.printf("<START Token transfer User 2 >\n");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user2, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        System.out.printf("<DONE transfer to User 2 >\n\n");
    
        System.out.printf("<START Token transfer User 3 >\n");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user3, transfer_value);     
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        System.out.printf("<DONE transfer to User 3 >\n\n");
        
        System.out.printf("<START Token transfer User 4 >\n");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user4, transfer_value);     
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        System.out.printf("<DONE transfer to User 4 >\n\n");
        
        System.out.printf("<END Token transfer>\n\n");
    

        //3. Vote creation : 투표 컨트랙트(생성된 토큰을 사용할 안건의 모임)를 생성합니다. 
        System.out.printf("<START createVoteContract creation>\n");
        input_sct50_create = String.format("[\"SymParty\",\"%s\",\"%s\"]", token_contract_addr, owner);
        ret_txhash = vote.CreateVoteContract(input_sct50_create);
        System.out.printf("<END createVoteContract>\n%s\n\n",ret_txhash);
                
        Thread.sleep(10000);
        
        vote_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Vote contract address: %s\n\n", vote_contract_addr);
    

        //4. Add poll creator : 생성된 투표컨트랙트에 안건 제안 가능자를 등록합니다. 
        System.out.printf("<START Add poll creators>\n");
        input_sct50_addpollcreators = String.format("[\"%s\", \"%s\"]", owner, user1);
        ret_txhash = vote.AddPollCreators(vote_contract_addr,input_sct50_addpollcreators);
        System.out.printf("<END AddPollCreators>\n%s\n\n",ret_txhash);


        //5. Poll creation : 투표에 안건을 등록합니다.
        poll_start_time = System.currentTimeMillis() / 1000;
        poll_end_time = poll_start_time + 24*60*60;
        //poll_end_time = poll_start_time + 10000;
        System.out.printf("poll start: %d, end: %d\n", poll_start_time, poll_end_time);
    
        System.out.printf("<START CreatePollContract creation>\n");
        input_sct51_create = String.format("[\"0x0\",\"0x0\",\"Agenda - break time \",\"Agenda descrition - Let's take a break :)\",\"%s\",\"0x%x\",\"0x%x\",\"%s\",\"0x0\",\"0x0\",\"0x4\",\"0x4\",\"0x7\"]", owner, poll_start_time, poll_end_time, vote_contract_addr);
        ret_txhash = vote.CreatePollContract(input_sct51_create);
        System.out.printf("<END CreatePollContract>\n%s\n\n",ret_txhash);
       
        Thread.sleep(10000);

        //Get contract address
        poll_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Poll contract address: %s\n\n", poll_contract_addr);
    

        //6. Cast vote : 등록된 안건에 대하여 투표를 합니다. 
        System.out.printf("<START cast vote>\n");
         
        System.out.printf("<START cast vote Owner>\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote, "", "");
        System.out.printf("<DONE cast vote Owner>\n\n");
        
        System.out.printf("<START cast vote User 1 >\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote,user1_keydir,user1_pw);
        System.out.printf("<DONE cast vote User 1 >\n\n");
        
        System.out.printf("<START cast vote User 2 >\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user2, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote,user2_keydir,user2_pw);
        System.out.printf("<DONE cast vote User 2 >\n\n");
        
        System.out.printf("<START cast vote User 3 >\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user3, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote,user3_keydir,user3_pw);
        System.out.printf("<DONE cast vote User 3 >\n\n");
    
        System.out.printf("<END cast vote>\n\n");
    

        //7. Tally vote : 결과를 집계합니다. 
        int ret;
        ret = vote.StartTally(poll_contract_addr);
        Thread.sleep(10000);
        System.out.printf("<END StartTally>\n%d\n\n",ret);
    
        
        //*. 결과의 조회는 아래와 같이 확인할수 있습니다. 
        //Check result
        checkResult(token_contract_addr, vote_contract_addr, poll_contract_addr);
    }

    public void fullScenario2(int option) throws InterruptedException {
        String token_contract_addr = "";
        String vote_contract_addr = "";
        String poll_contract_addr = "";
    
        String input_tx = "";
        String input_sct20_create = "";
        String input_sct20_transfer ="";
        String input_sct50_create = "";
        String input_sct50_addpollcreators = "";
        String input_sct51_create = "";
        String input_sct51_castvote = "";

        String ret_tx = "";
        String ret_signedtx = "";
        String ret_txhash = "";
        String rlp_sct = "";    
        String ret_vote_result = "";
        int ret_value = 0;
    
        String vote_contract;
        String poll_contract;

        long poll_start_time = 0;
        long poll_end_time = 0;
        
        // GoVote vote = (GoVote) Native.loadLibrary("./vote.so", GoVote.class);

        //Setup test user info
        setup(option);

        //Init vote library
        ret_value = vote.Init(owner, owner_pw, config_file);
        if (ret_value < 1) {
            System.out.printf("Go vote library init fail\n");
            System.exit(0);
        }

        //Unlock operator account
        // ret_value = vote.UnlockAccount(owner, owner_pw);
        // if (ret_value < 1) {
        //     System.out.printf("Operator account unlock fail\n");
        //     System.exit(0);
        // }

        //Token creation
        System.out.printf("<START Token creation>\n");
        input_tx = String.format("{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, work_node);
        input_sct20_create = String.format("{\"type\":\"0x14\",\"method\":\"0x0\",\"params\":[\"VToken\",\"VTK\",\"%s\",\"%s\"]}", total_supply, owner);
        //Make sct (test)
        // rlp_sct = vote.MakeSCT(input_sct20_create);
        // System.out.printf("rlp encoded sct: %s\n", rlp_sct);
        ret_txhash = processTx(input_tx, input_sct20_create, "", "");
        System.out.printf("<END Token creation>\n\n");

        Thread.sleep(10000);

        //Get token contract address
        token_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Token contract address: %s\n\n", token_contract_addr);
        
        //Token transfer
        System.out.printf("<START Token transfer>\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, token_contract_addr, work_node);
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user1, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user2, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user3, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        input_sct20_transfer = String.format("{\"type\":\"0x14\",\"method\":\"0x1\",\"params\":[\"%s\",\"%s\"]}", user4, transfer_value);
        ret_txhash = processTx(input_tx, input_sct20_transfer, "", "");
        System.out.printf("<END Token transfer>\n\n");
    
        //Vote creation
        System.out.printf("<START Vote creation>\n");
        input_tx = String.format("{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, work_node);
        input_sct50_create = String.format("{\"type\":\"0x32\",\"method\":\"0x0\",\"params\":[\"SymParty\",\"%s\",\"%s\"]}", token_contract_addr, owner);
        ret_txhash = processTx(input_tx, input_sct50_create, "", "");
        System.out.printf("<END Vote creation>\n\n");
    
        Thread.sleep(10000);

        //Get vote contract address
        vote_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Vote contract address: %s\n\n", vote_contract_addr);

        //Get vote contract info (just check)
        vote_contract = vote.GetVoteContract(vote_contract_addr);
        System.out.printf("Vote contract info: %s\n\n", vote_contract);

        //Add poll creator
        System.out.printf("<START Add poll creators>\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, vote_contract_addr, work_node);
        input_sct50_addpollcreators = String.format("{\"type\":\"0x32\",\"method\":\"0x1\",\"params\":[\"%s\", \"%s\"]}", user1, user2);
        ret_txhash = processTx(input_tx, input_sct50_addpollcreators, "", "");
        System.out.printf("<END Add poll creators>\n\n");

        Thread.sleep(10000);

        //Poll creation
        System.out.printf("<START Poll creation>\n");
        poll_start_time = System.currentTimeMillis() / 1000;
        // poll_end_time = poll_start_time + 24*60*60;
        poll_end_time = poll_start_time + 10000;
        System.out.printf("poll start: %d, end: %d\n", poll_start_time, poll_end_time);
        input_tx = String.format("{\"from\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, work_node);
        input_sct51_create = String.format("{\"type\":\"0x33\",\"method\":\"0x0\",\"params\":[\"0x1\",\"0x1\",\"Agenda1-coffee break\",\"Agenda1 descrition-do you want to have some coffee?\",\"%s\",\"0x%x\",\"0x%x\",\"%s\",\"0x0\",\"0x0\",\"0x4\",\"0x4\",\"0x7\"]}", owner, poll_start_time, poll_end_time, vote_contract_addr);
        ret_txhash = processTx(input_tx, input_sct51_create, user1_keydir, user1_pw);
        System.out.printf("<END Poll creation>\n\n");

        Thread.sleep(10000);

        //Get poll contract address
        poll_contract_addr = vote.GetContractAddress(ret_txhash);
        System.out.printf("Poll contract address: %s\n\n", poll_contract_addr);

        //Get poll contract info (check)
        poll_contract = vote.GetPollContract(poll_contract_addr);
        System.out.printf("Poll contract info: %s\n\n", poll_contract);

        //Cast vote
        System.out.printf("<START cast vote>\n");
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", owner, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote, owner_keydir, owner_pw);
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user1, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote, user1_keydir, user1_pw);
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user2, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x1\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote, user2_keydir, user2_pw);
        input_tx = String.format("{\"from\":\"%s\",\"to\":\"%s\",\"workNodes\":[\"%s\"],\"type\":\"0x1\"}", user3, poll_contract_addr, work_node);
        input_sct51_castvote = String.format("{\"type\":\"0x33\",\"method\":\"0x1\",\"params\":[\"0x1\", \"0x0\"]}");
        ret_txhash = processTx(input_tx, input_sct51_castvote, user3_keydir, user3_pw);
        System.out.printf("<END cast vote>\n\n");

        Thread.sleep(10000);  //wait until poll end

        //Tally vote
        System.out.printf("<START tally vote>\n");
        ret_value = vote.StartTally(poll_contract_addr);
        System.out.printf("Poll contract %s tally vote started: %d\n", poll_contract_addr, ret_value);
        Thread.sleep(10000);   //wait until tally finished
        ret_vote_result = vote.GetVoteResult(poll_contract_addr);
        System.out.printf("Poll contract %s vote result: \n%s\n", poll_contract_addr, ret_vote_result);
        System.out.printf("<END tally vote>\n\n");

        Thread.sleep(10000);

        //Get vote contract info (just check)
        vote_contract = vote.GetVoteContract(vote_contract_addr);
        System.out.printf("Vote contract info: %s\n\n", vote_contract);

        //Get poll contract info (check)
        poll_contract = vote.GetPollContract(poll_contract_addr);
        System.out.printf("Poll contract info: %s\n\n", poll_contract);

        //Check result
        checkResult(token_contract_addr, vote_contract_addr, poll_contract_addr);
    }

    public String processTx(String input_tx, String input_sct, String keydir, String pw) {
        String ret_tx = "";
        String ret_signedtx = "";
        String ret_txhash = "";
    
        System.out.printf(" - MakeTransaction - \n");
        ret_tx = vote.MakeTransaction(input_tx, input_sct);
        System.out.printf(" - SignTransaction - \n");
        if (keydir == "") {
            ret_signedtx = vote.SignTransaction(ret_tx);
        } else {
            ret_signedtx = vote.SignTransactionEx(ret_tx, keydir, pw);
        }
        // ret_signedtx = SignTransactionEx(ret_tx, keydir, pw);
        System.out.printf("return SignTransaction:\n %s\n", ret_signedtx);
        ret_txhash = vote.SendRawTransaction(ret_signedtx);
        System.out.printf("return SendRawTransaction:\n %s\n", ret_txhash);
    
        return ret_txhash;
    }

    public void checkResult(String token_contract_addr, String vote_contract_addr, String poll_contract_addr) {
        String ret_token_info;
        String ret_vote_info;
        String ret_poll_info;
        String ret_available_poll_creators;
        String ret_poll_creater;
        String ret_vote_result;
        int ret_value;
    
        System.out.printf("\ntoken_contract: %s, vote contract: %s, poll contract: %s \n", token_contract_addr, vote_contract_addr, poll_contract_addr);
    
        //get token contract
        System.out.printf("<START GetTokenContract>\n");
        ret_token_info = vote.GetTokenContract(token_contract_addr);
        System.out.printf("<END GetTokenContract>\n%s\n\n",ret_token_info);
    
        //get vote contract
        System.out.printf("<START GetVoteContract>\n");
        ret_vote_info = vote.GetVoteContract(vote_contract_addr);
        System.out.printf("<END GetVoteContract>\n%s\n\n",ret_vote_info);
    
        //get available poll creators
        System.out.printf("<START GetAvailablePollCreators>\n");
        ret_available_poll_creators = vote.GetAvailablePollCreators(vote_contract_addr);
        System.out.printf("<END GetAvailablePollCreators>\n%s\n\n",ret_available_poll_creators);
    
        //get poll contract
        System.out.printf("<START GetPollContract>\n");
        ret_poll_info = vote.GetPollContract(poll_contract_addr);
        System.out.printf("<END GetPollContract>\n%s\n\n",ret_poll_info);
       
        //get poll creator
        System.out.printf("<START GetPollCreator>\n");
        ret_poll_creater = vote.GetPollCreator(poll_contract_addr);
        System.out.printf("<END GetPollCreator>\n%s\n\n",ret_poll_creater);
       
        //get poll state
        System.out.printf("<START GetPollState>\n");
        ret_value = vote.GetPollState(poll_contract_addr);
        System.out.printf("<END GetPollState>\n%d\n\n",ret_value);
       
        //get vote result
        System.out.printf("<START GetVoteResult>\n");
        ret_vote_result = vote.GetVoteResult(poll_contract_addr);
        System.out.printf("<END GetVoteResult>\n%s\n\n",ret_vote_result);
    }
    
    public void setup(int option) {
        if (option == 0) {
            config_file = ".config.json";
       
            owner = "0x00020000000000100002";
            owner_keydir = "keystore/vote_work1";
            owner_pw = "1";
            user1 = "0x00020000000000110002";
            user1_keydir = "keystore/vote_work2";
            user1_pw = "1";
            user2 = "0x00020000000000120002";
            user2_keydir = "keystore/vote_work3";
            user2_pw = "1";
            user3 = "0x00020000000000130002";
            user3_keydir = "keystore/vote_work4";
            user3_pw = "1";
            user4 = "0x00020000000000140002";
            user4_keydir = "keystore/vote_work5";
            user4_pw = "1";
    
            work_node = "0x00020000000000090002";
                
            total_supply = "0x56bc75e2d63100000";
            transfer_value = "0xde0b6b3a7640000";
        } else if (option == 1) {
            config_file = "../../lib/.config.json";
       
            owner = "0x00021000000000080002";
            owner_keydir = "/home/bakcj/test8/node8/keystore/";
            owner_pw = "jj";
            user1 = "0x00021000000000090002";
            user1_keydir = "/home/bakcj/test8/node9/keystore/";
            user1_pw = "jj";
            user2 = "0x00010000000000010002";
            user2_keydir = "/home/bakcj/test8/node10/keystore/";
            user2_pw = "jj";
            user3 = "0x00020000000000010002";
            user3_keydir = "/home/bakcj/test8/node11/keystore/";
            user3_pw = "jj";
            user4 = "0x0002a000000000010002";
            user4_keydir = "/home/bakcj/test8/node12/keystore/";
            user4_pw = "jj";
    
            work_node = "0x00021000000000080002";
                
            total_supply = "0x56bc75e2d63100000";
            transfer_value = "0xde0b6b3a7640000";
        } else if (option == 2) {
            config_file = ".config.json";
            
            owner = "0x00000000000000000201";
            owner_keydir = "keystore/node2";
            owner_pw = "shlee";
            user1 = "0x00000000000000000301";
            user1_keydir ="keystore/node3";
            user1_pw = "shlee";
            user2 = "0x00000000000000000401";
            user2_keydir = "keystore/node4";
            user2_pw = "shlee";
            user3 = "0x00000000000000000501";
            user3_keydir = "keystore/node5";
            user3_pw = "shlee";
            user4 = "0x00000000000000000601";
            user4_keydir = "keystore/node6";
            user4_pw = "shlee";
            
            work_node = "0x00000000000000000201";
            
            total_supply = "0x56bc75e2d63100000";
            transfer_value ="0x10a0";
        } else {
        
        }
    }
    
}
