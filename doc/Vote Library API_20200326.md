# Vote Engine API



#### Notation of data type

- `QUANTITY`: String of hex encoded integer value with prefix "0x".
  - Refer to "Hex value encoding" description of Ethereum JSON-RPC API document(https://github.com/ethereum/wiki/wiki/JSON-RPC).
- `DATA`: String of hex encoded byte array data with prefix "0x" and two hex digit per byte.
  - Refer to "Hex value encoding" description of Ethereum JSON-RPC API document(https://github.com/ethereum/wiki/wiki/JSON-RPC).
- `Object`: String data of Json format
- `Array`: Array data of json format
- `string`: Normal C string
- `int`: Normal C integer



## SCT Format

To use SCT, Please check the contents of each SCT format below.

**[ ${Type}, ${Method}, ${Parameter} ]**

* Type - It means Type to be processed among SCT 20/30/40/50/51.

* Method - Method corresponding to SCT Type.

* Parameter - Parameter corresponding to SCT Type.

  

**SCT format example (SCT50/51):** 

| Operation              | SCT Type | SCT  Method | Function Input                                               |
| ---------------------- | -------- | ----------- | ------------------------------------------------------------ |
| Vote Contract Creation | 0x32     | 0x0         | (from, NIL, sctType, sctMethod, [partyName, tokenAddr, owner]) |
| Add Poll Creators      | 0x32     | 0x1         | (from, voteContractAddr, sctType, sctMethod, [pollCreator, ...]) |
| Remove Poll Creators   | 0x32     | 0x2         | (from, voteContractAddr, sctType, sctMethod, [pollCreator, ...]) |
| Poll Creation          | 0x33     | 0x0         | (from, NIL, sctType, sctMethod, [category, agenda, description, owner, startTime, endTime, voteContractAddr]) |
| Stake Tokens           | 0x33     | 0x1         | (from, pollAddr, sctType, sctMethod, [amount])               |
| Withdraw Tokens        | 0x33     | 0x2         | (from, pollAddr, sctType, sctMethod, [amount])               |
| Vote In Poll           | 0x33     | 0x3         | (from, pollAddr, sctType, sctMethod, [decision])             |
| Poll Stop              | 0x33     | 0x4         | (from, pollAddr, sctType, sctMethod, NIL)                    |
| Poll Revocation        | 0x33     | 0x5         | (from, pollAddr, sctType, sctMethod, NIL)                    |



---

## Vote Engine Library

The following libraries are supported.

- [MakeSCT](#MakeSCT)
- [MakeTransaction](#MakeTransaction)
- [SignTransaction](#SignTransaction)
- [UnlockAccount](#UnlockAccount)
- [SendTransaction](#SendTransaction)
- [SendRawTransaction](#SendRawTransaction)
- [GetTransactionStatus](#GetTransactionStatus)
- [GetTransactionReceipt](#GetTransactionReceipt)
- [GetContract](#GetContract)
- [GetVoteContract](#GetVoteContract)
- [GetAvailablePollCreators](#GetAvailablePollCreators)
- [GetPollContract](#GetPollContract)
- [GetPollCreator](#GetPollCreator)
- [GetPollState](#GetPollState)
- [GetVoteResult](#GetVoteResult)
- [CreateTokenContract](#CreateTokenContract)
- [CreateVoteContract](#CreateVoteContract)
- [CreatePollContract](#CreatePollContract)
- [AddPollCreators](#AddPollCreators)
- [RemovePollCreators](#RemovePollCreators)
- [StopPoll](#StopPoll)
- [FinishPoll](#FinishPoll)
- [StartTally](#StartTally)
- [WritePollResults](#WritePollResults)

----

#### MakeSCT

*func MakeSCT(sctTemplate) rlpSctData*

- **Input :** 

  - `sctTemplate`: `Object` - SCT template parameters. For the more detail, refer to SCT document.
    - `type` : `QUANTITY` - SCT type
    - `method` : `QUANTITY` - SCT method
  
    - `params` : `Array` - SCT params
  
  ```
    //example (SCT50 creation)
    sctTemplate : {
        "type" 	 : "0x32",
        "method" : "0x0",
        "params" : ["SymParty", "0xC434A0B1b3dE05615c0d", "0x00000000000000000201"]
    }
  ```
  
- **Output** :

  - `rlpSctData`: `DATA` - RLP encoded SCT

- **Example**

```
MakeSCT({"type":...}) // see above

//output
0xe23280df8853796d50617274798ac434a0b1b3de05615c0d8a00000000000000000201
```



---

#### MakeTransaction

*func MakeTransaction(transactionParams, sctTemplate) transaction*

- **Input  :** 
  
  - `transactionParams`: `Object` - transaction parameters.
  
      - `from`: `DATA`, 10 Bytes - the address the transaction is send from.
      - `to`: `DATA`, 10 Bytes - (optional when creating new contract) the address the transaction is directed to.
      - `gas`: `QUANTITY` - (optional, default: 90000) integer of the gas provided for the transaction execution. It will return unused gas.
      - `gasPrice`: `QUANTITY` - (optional, default: To-Be-Determined) integer of the gasPrice used for each paid gas.
      - `value`: `QUANTITY` - (optional, default: 0) integer of the value sent with this transaction.
      - `type`:`QUANTITY` - (optional, default: 0) type of the transaction(0: original, 1: sct, 2: deposit)
      - `input|data`: `DATA` - (optional) the compiled code of a contract OR the hash of the invoked method signature and encoded Parameters.
      - `nonce`: `QUANTITY` - (optional, default: To-Be-Determined) integer of a nonce. This allows to overwrite your own pending transactions that use the same nonce.
      - `workNodes`: `Array` - (optional, default: 0's gsym node symId that in configration)selected work node's SymID to send this transaction. (min: 1, max: 3)

          ```
          //example
          tansactionParams: {
              "from": "0x00000000000000000201",	//required
              "type": "0x1"
          }
          ```
  
  
  
  - `sctTemplate`: `Object`, SCT template parameters. For the more detail, refer to SCT document
  
      - `type` : `QUANTITY` - SCT type.
      - `method` : `QUANTITY` - SCT method.
      - `params` :  `Array` - SCT params.
  
      ```
      //example (SCT50 creation)
         sctTemplate : {
               "type" 	 : "0x32",
               "method" : "0x0",
               "params" : ["SymParty", "0xC434A0B1b3dE05615c0d", "0x00000000000000000201"]
         }
      ```
  
- **Output : **

  - `transaction`: `Object` - transaction without sign values
    - `from`: `DATA`, 10 Bytes - address of the sender.
    - `gas`: `QUANTITY` - gas provided by the sender.
    - `gasPrice`: `QUANTITY` - gas price provided by the sender in Hug.
    - `hash`: `DATA`, 32 Bytes - hash of the transaction.
    - `input`: `DATA` - the data send along with the transaction.
    - `nonce`: `QUANTITY` - the number of transactions made by the sender prior to this one.
    - `to`: `DATA`, 10 Bytes - address of the receiver. `null` when its a contract creation transaction.
    - `type`:`QUANTITY` - type of the transaction (0: original, 1: sct, 2: deposit)
    - `workNodes`: `Array` - Array of selected work nodes via SymID when sending transactions . (min: 1, max: 3)
    - `value`: `QUANTITY` - value transferred in Hug.
    - `v`: `QUANTITY` - ECDSA recovery id (0x0 due to before signing)
    - `r`: `DATA`, 32 Bytes - ECDSA signature r (0x0 due to before signing)
    - `s`: `DATA`, 32 Bytes - ECDSA signature s (0x0 due to before signing)

- **Example**

```
MakeTransaction({"from":...}, {"type":...}) // see above

//output
{"from":"0x00000000000000000201","nonce":"0x5a","gasPrice":"0x174876e800","gas":"0x7a55f8","to":null,"value":"0x0","input":"0xe23280df8853796d50617274798ac434a0b1b3de05615c0d8a00000000000000000000","type":"0x1","workNodes":["0x00000000000000000201"],"extraData":"0x","v":"0x0","r":"0x0","s":"0x0","hash":"0x57e3d063a8beee2009ec7e23ee6565dd85e0c74d56a4046a31ba0367445d4311"}
```



---

#### SignTransaction

*func SignTransaction(transactionParams) signedTransaction*

- **Input  :** 

  - `transactionParams`: `Object` - **fully formatted transaction** parameters.

      - `from`: `DATA`, 10 Bytes - the address the transaction is send from.

      - `to`: `DATA`, 10 Bytes - (optional, when creating new contract) the address the transaction is directed to.

      - `gas`: `QUANTITY` - integer of the gas provided for the transaction execution. It will return unused gas.

      - `gasPrice`: `QUANTITY` - integer of the gasPrice used for each paid gas.

      - `value`: `QUANTITY` - integer of the value sent with this transaction.

      - `type`:`QUANTITY` - type of the transaction(0: original, 1: sct, 2: deposit)

      - `input|data`: `DATA` - the compiled code of a contract OR the hash of the invoked method signature and encoded Parameters.

      - `nonce`: `QUANTITY` - integer of a nonce. This allows to overwrite your own pending transactions that use the same nonce.

      - `workNodes`: `Array` - selected work node's SymID to send this transaction. (min: 1, max: 3)

        ```
        //example
        transactionParams:{
        	"from":"0x00000000000000000201",
        	"nonce":"0x5a",
        	"gasPrice":"0x174876e800",
        	"gas":"0x7a55f8",
        	"to":null,
        	"value":"0x0",
        "input":"0xe23280df8853796d50617274798ac434a0b1b3de05615c0d8a00000000000000000000",
        	"type":"0x1",
        	"workNodes":["0x00000000000000000201"]
        }
        ```


- **Output : **

  - `signedTransaction`: `Object` - transaction with sign sign values
    - `from`: `DATA`, 10 Bytes - address of the sender.
    - `gas`: `QUANTITY` - gas provided by the sender.
    - `gasPrice`: `QUANTITY` - gas price provided by the sender in Hug.
    - `hash`: `DATA`, 32 Bytes - hash of the transaction.
    - `input`: `DATA` - the data send along with the transaction.
    - `nonce`: `QUANTITY` - the number of transactions made by the sender prior to this one.
    - `to`: `DATA`, 10 Bytes - address of the receiver. `null` when its a contract creation transaction.
    - `type`:`QUANTITY` - type of the transaction (0: original, 1: sct, 2: deposit)
    - `workNodes`: `Array` - Array of selected work nodes via SymID when sending transactions . (min: 1, max: 3)
    - `value`: `QUANTITY` - value transferred in Hug.
    - `v`: `QUANTITY` - ECDSA recovery id
    - `r`: `DATA`, 32 Bytes - ECDSA signature r
    - `s`: `DATA`, 32 Bytes - ECDSA signature s
- **Example**

```
SignTransaction({"from":...}) // see above

//output
{"from":"0x00000000000000000201","nonce":"0x95","gasPrice":"0x174876e800","gas":"0x261d8","to":"0xed38f42357f947d331f3","value":"0x0","input":"0xd11401ce8a000000000000000005018210a0","type":"0x1","workNodes":["0x00000000000000000201"],"extraData":"0x","v":"0x0","r":"0x815e
be5ca01e00bce0b6c3221bc594f048de7ab0d6269b3bdba3b66e6a4faaf6","s":"0x1437e379ecdd12aeff687eafb0f7b61d526f776c51ee13121b82d80325cf9f98","hash":"0xe14739afa6a56c7a1a702e7ccf3214110094cc4daa0836cc3e51f0f51424225b"}
```



---

#### UnlockAccount

*func UnlockAccount(address, passphrase) result* 

- **Input :** 
  - `address`: `DATA` - the address to unlock.
  - `passphrase`: `string` - passphrase of the address.

- **Output :** 
  - `result`: `int` - return `1`  if success to unlock account, otherwise return `-1`
- **Example**
```
UnlockAccount("0x00000000000000000201","pass")

//output
1
```

​    

---

#### SendTransaction

*func SendTransaction(transaction) txHash*

- **Input  :** 

  - `transaction`: `Object` - transaction parameters.

     - `from`: `DATA`, 10 Bytes - the address the transaction is send from.

     - `to`: `DATA`, 10 Bytes - (optional, when creating new contract) the address the transaction is directed to.

     - `gas`: `QUANTITY` - (optional, default: 90000) integer of the gas provided for the transaction execution. It will return unused gas.

     - `gasPrice`: `QUANTITY` - (optional, default: To-Be-Determined) integer of the gasPrice used for each paid gas.

     - `value`: `QUANTITY` - (optional, default: 0) integer of the value sent with this transaction.

     - `type`:`QUANTITY` - (optional, default: 0) type of the transaction(0: original, 1: sct, 2: deposit)

     - `input|data`: `DATA` - (optional) the compiled code of a contract OR the hash of the invoked method signature and encoded Parameters.

     - `nonce`: `QUANTITY` - (optional, default: To-Be-Determined) integer of a nonce. This allows to overwrite your own pending transactions that use the same nonce.

     - `workNodes`: `Array` - (optional, default: 0's gsym node symId that in configration)selected work node's SymID to send this transaction. (min: 1, max: 3)

       ```
       //example
       tansactionParams: {
           "from": "0x00000000000000000201",	//required
           "type": "0x1"
       }
       ```

- **Output : **

  - `txHash`: `DATA` - transaction hash

- **Example**

```
SendTransaction({"from":...}) // see above

//output
0x873269d0152db001610c2a5ad48d110fad1e39fee0bf0c169f0a047073caa639
```



---

#### SendRawTransaction

*func SendRawTransaction(signedTransaction) txHash*

- **Input :** 
  - `signedTransaction`: `Object` - Signed transaction data
* **Output :** 
  * `txHash`: `DATA` - transaction hash

* **Example**

```
SendRawTransaction("0xd46e8dd67c5d32be8d46e8dd67c5d32be8058bb8eb970870f072445675058bb8eb970870f072445675")

//output
0xcd169668b3106405f3faa438e8b07f2a1b8daeb6ce562b7bfd826eb7d8ad9c37
```

  

---

#### GetTransactionStatus

*func GetTransactionStatus(txHash) result*

- **Input :** 
  - `txHash`: `DATA` - the transaction Hash.

* **Output :** 
  * `result`: `int` - transaction status(-1: GetTxFail, 0: Pending, 1: Done)
* **Example**

```
GetTransactionStatus("0x4c3d33216ab949911285bfd3808a1673d42cde46cda293abce22b485f7851fbb")

//output
1
```



---

#### GetTransactionReceipt

*func GetTransactionStatus(txHash) transactionReciept*

- **Input :** 
  - `txHash`: `DATA` - the transaction Hash.

* **Output :** 
  * `transactionReciept`: `Object` - A transaction receipt object, or `null` when no receipt was found:
    - `blockHash`: `DATA`, 32 Bytes - hash of the block where this transaction was in.
    - `blockNumber`: `QUANTITY` - block number where this transaction was in.
    - `contractAddress `: `DATA`, 10 Bytes - The contract address created, if the transaction was a contract creation, otherwise `null`.
    - `cumulativeGasUsed `: `QUANTITY ` - The total amount of gas used when this transaction was executed in the block.
    - `from`: `DATA`, 10 Bytes - address of the sender.
    - `gasUsed `: `QUANTITY ` - The amount of gas used by this specific transaction alone.
    - `logs`: `Array` - Array of log objects, which this transaction generated.
    - `logsBloom`: `DATA`, 256 Bytes - Bloom filter for light clients to quickly retrieve related logs.
    - `status`: `QUANTITY` either `1` (success) or `0` (failure) 
    - `to`: `DATA`, 10 Bytes - address of the receiver. null when it's a contract creation transaction.
    - `transactionHash `: `DATA`, 32 Bytes - hash of the transaction.
    - `transactionIndex`: `QUANTITY` - integer of the transaction's index position in the block.
* **Example**

```
GetTransactionReceipt("0xf2186757e18ccde8f00787ad3c0e225934e6aece291864d205034803dab87b44")

//output
{"blockHash":"0xece6b2cb41121e1c2a681b505c12dce19a067ce3110d7e653f20a263311e5608","blockNumber": "0x1e7","contractAddress": null,"cumulativeGasUsed": "0x6518","from": "0x00000000000000000201","gasUsed": "0x6518","logs": [],"logsBloom":"0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","status": "0x1","to": "0x60d7ad69e0f4abab397c","transactionHash": "0x4f1db0e1aab0d47f9fc7f9cc9ac657bac553f970403787aaf5b1f08b6555be4c","transactionIndex": "0x0"}
```



---

#### GetContractAddress

*func GetContractAddress(txHash) contractAddress*

- **Input :** 
  - `txHash`: `DATA` - transaction Hash.

* **Output :** 
  * `contractAddress`: `DATA` - the contract address

* **Example**

```
GetContractAddress("0x4c3d33216ab949911285bfd3808a1673d42cde46cda293abce22b485f7851fbb")

//output
0xc352691630E387a4C571
```

 

---

#### GetVoteContract

*func GetVoteContract(voteContractAddr) voteContract*

- **Input :** 
  - `voteContractAddr`: `DATA`  - a vote contract address.

- **Output : ** 
  - `voteContract`: `Object` - given SCT50 Vote Contract's Information.
    - `party` : `DATA` -Party Name.
    - `owner` : `DATA`, 10 Bytes - Owner SymId.
    - `creator` : `DATA`, 10 Bytes - Creator SymId.
    - `token` : `DATA`, 10 Bytes - SCT20 Token Address.
    - `pollCreators` : `Array`-  array of registered poll creators.
    - `polls` :`Array` - array of created polls.

- **Example**

```
GetVoteContract("0xDEa0b102C66C71663d64") 

//output
{"party":"SymParty","owner":"0x00000000000000000201","creator":"0x00000000000000000201","token":"0xc352691630e387a4c571","pollCreators":["0x00000000000000000201","0x00000000000000000401"],"polls":["0xbe9487cbff1015a131f5"]}
```



---

#### GetAvailablePollCreators

*func GetAvailablePollCreators(voteContractAddr) pollCreators*

- **Input :** 
  - `voteContractAddr`: `DATA`  - a vote contract address.

- **Output : ** 
  - `pollCreators`: `Array` - array of registered poll creators.

- **Example**

```
GetAvailablePollCreators("0x3af45122285062b07cc9") 

//output
["0x00000000000000000201","0x00000000000000000301"]
```



---
#### GetPollContract

*func GetPollContract(pollContractAddr) pollContract*

- **Input :** 
  - `pollContractAddr`: `DATA`  - a poll  contract address.

- **Output : **
  -  `pollContract`: `Object`  - givens SCT51 poll contract's information.
    - `pollNumber` : `DATA` - poll number.
    - `category` : `DATA` - category for agenda.
    - `agenda` : `DATA` - agenda name.
    - `description` : `DATA` - agenda description.
    - `start` : `QUANTITY` - Start UNIX time.
    - `end` : `QUANTITY` - End UNIX time.
    - `state` : `DATA` - state of the poll (active, inactive, finished)
    - `votingPaper` : `Array` - array of voting paper.
    - `voteResult` : `object` - summary of the poll.
    - `voteContract` : `DATA`, 10 Bytes - related vote contract address.
    - `secretOption` : `DATA` - secret option. (0: public, 1: secret)
    - `stakeOption` : `DATA` - available maximum stake amount. (0: free stake, >= 1: stake limit for each voters can not over this value)
    - `totalVoters` : `QUANTITY` - the number of total voters.
    - `quorum` : `QUANTITY` - minimum rate of participants for the poll.
    - `passRate` : `QUANTITY` - minimum rate of agree for the poll.
    - `owner` : `DATA`, 10 Bytes - owner SymId.
    - `creator` : `DATA`, 10 Bytes - creator SymId.
- **Example**

```
GetPollContract("0x4D8D5B14b4E2eE605c74") 

//output
{"pollNumber":"0x0","category":"0x0","agenda":"Agenda - break time ","description":"Agenda descrition - Let's take a break :)","start":"0x5e74642d","end":"0x5e75b5ad","state":"finished","votingPaper":[{"voter":"0x00000000000000000201","stake":"0x1","decision":"agree"},{"voter":"0x00000000000000000401","stake":"0x1","decision":"disagree"},{"voter":"0x00000000000000000301","stake":"0x1","decision":"disagree"},{"voter":"0x00000000000000000501","stake":"0x0","decision":"agree"}],"voteResult":{"result":"0x3","code":"0x0","agrees":"0x21","disagrees":"0x42","nullities":"0x19","totalvoters":"0x3","votingRate":"0x4b"},"voteContract":"0x60d7ad69e0f4abab397c","secretOption":"public","stakeOption":"0x0","owner":"0x00000000000000000201","creator":"0x00000000000000000201","totalVoters":"0x4","quorum":"0x4","passRate":"0x7"} 
```



---
#### GetPollCreator

*func GetPollCreator(pollContractAddr) pollCreatorAddr*

- **Input :** 
  - `pollContractAddr`: `DATA`, 10 Bytes - a poll contract address.

- **Output : ** 
  - `pollCreatorAddr`: `DATA`, 10 Bytes - the poll creator SymID.

- **Example**

```
GetPollCreator("0x4D8D5B14b4E2eE605c74") 

//output
0x00000000000000000201
```



---
#### GetPollState

*func GetPollState(pollContractAddr) pollState*

- **Input :** 
  - `pollContractAddr`: `DATA` - a poll contract address.

- **Output : ** 
  - `pollState`: `int` - state of the poll(-1: GetPollFail, 0: Inactive, 1: Active, 2: Expired, 3: Approved, 4: Rejected)

- **Example**

```
GetPollState("0x4D8D5B14b4E2eE605c74") 

//output
1
```



---
#### GetVoteResult

*func GetVoteResult(pollContractAddr) voteResult*

- **Input :** 
  - `pollContractAddr`: `DATA` - a poll contract address.

- **Output : ** 
  - `voteResult`: `Object` - voting result of the poll
    - `result` : `QUANTITY` - voting result of the poll(0: unknown, 1: pass, 2: deny, 3: unachieved)
    - `code` : `QUANTITY` - result code for the given poll (future using)
    - `agrees` : `QUANTITY` - total agrees for the given poll.
    - `disagrees` : `QUANTITY` - total disagrees for the given poll.
    - `nullities` : `QUANTITY` - total nullities for the given poll.
    - `totalvoters` : `QUANTITY` - total voters for the given poll.
    - `votingRate` : `QUANTITY` - voting rate for the given poll.

- **Example**

```
GetVoteResult("0x4D8D5B14b4E2eE605c74") 

//output
{"result":"0x3","code":"0x0","agrees":"0x21","disagrees":"0x42","nullities":"0x19","totalvoters":"0x3","votingRate":"0x4b"}
```



---
#### CreateTokenContract

*func CreateTokenContract(sctParams) txHash*

- **Input :** 

  1.  `sctParams`: `Array` - SCT params. For the more detail, refer to SCT document

     ```
     //example
       params = ["SymToken",					// Tocken Name
       			"STK",						// Tocken Symbol
       			"0x56bc75e2d631",			// Tocken TotalSupply
       			"0x00000000000000000201"	// Owner
       			]
     ```

- **Output :** 

  * `txHash`: `DATA` - transaction hash

- **Example**

```
CreateTokenContract(params) //see above

//output
0xed46b6d14e949d371937302f6e80601af9bdc78577dbfdea6cfde97988911160
```



---

#### CreateVoteContract

*func CreateVoteContract(sctParams) txHash*

- **Input :** 

  - `sctParams`: `Array` - SCT params. For the more detail, refer to SCT document

     ```
     //example
       params = ["SymParty",					 // PartyName
       			"0xC434A0B1b3dE05615c0d",	 // SCT20TokenAddress
                 "0x00000000000000000201"	 // OwnerSymId
                 ]
     ```

- **Output :** 

  * `txHash`: `DATA` - transaction hash

- **Example**

```
CreateVoteContract(params) //see above

//output
0x9e025d8292e6a348dada5deff582aa4f2f1b3b85e64a8c5d87babf4c057a18d2
```



---

#### CreatePollContract

*func CreatePollContract(sctParams) txHash*

- **Input :** 

  - `sctParams`: `Array` - SCT params. For the more detail, refer to SCT document

     ```
     //example
       params =[
     		   "0x0",						// Poll number
     		   "0x0",						// Category
                "Agenda1",					// Agenda
                "Agenda1 is about ...",		// Description
                "0x00020000000000020002",	// OwnerSymId
                "0x5e4b36c9",				// Start Unix time
                "0x5e50b509",				// End Unix time
                "0x83c4b863539810ef20f4"		// SCT50 Vote Contract Address
                "0x0",						// Secret option
                "0x1",						// Stake option
                "0x64",						// The number of total stake holders
                "0x64",						// The number of minimum stake holders
                "0x64"   					// The number of minimum stake
                ]
     ```

- **Output :** 

  * `txHash`: `DATA` - transaction hash

- **Example**

```
CreatePollContract(params) //see above

//output
0x6b9bfe410bc156d309c59d20644ba13b1048d79d6eb337f073a0efc923032b73
```



---

#### AddPollCreators

*func AddPollCreators(pollContractAddr, users) txHash*

- **Input :** 
  - `pollContractAddr`: `DATA` - a vote contract address.
  - `users`: `Array` - array of symID which want to make poll creator.
- **Output :** 
  * `txHash`: `DATA` - transaction hash
- **Example**

```
AddPollCreators("0xDEa0b102C66C71663d64",["0x00000000000000000801","0x00000000000000001101"]) 

//output
0x3a646cbc8f7a2e05c6e0dafaa5ea600a93e72925a188706089a1b32d84090235
```



---

#### RemovePollCreators

*func RemovePollCreators(pollContractAddr, users) txHash*

- **Input :** 
  - `pollContractAddr`: `DATA`  - a vote contract address.
  - `users`: `Array` - array of symID which want to remove from poll creator list.
- **Output :** 
  * `txHash`: `DATA` - transaction hash
- **Example**

```
RemovePollCreators("0xDEa0b102C66C71663d64",["0x00000000000000000801","0x00000000000000001101"]) 

//output
0xdaaaab94743134fbfae4f08a2ac3ed651183418dcb8d49c34a64004a9a052593
```



---

#### StopPoll

*func StopPoll(pollContractAddr) txHash*

- **Input :** 
  - `pollContractAddr`: `DATA` - a poll contract address.
- **Output :** 
  * `txHash`: `DATA` - transaction hash
- **Example**

```
StopPoll("0x4D8D5B14b4E2eE605c74") 

//output
0x6b9bfe410bc156d309c59d20644ba13b1048d79d6eb337f073a0efc923032b73
```



---

#### FinishPoll

*func FinishPoll(pollContractAddr) txHash*

- **Input :** 
  - `pollContractAddr`: `DATA` - a poll contract address.
- **Output :** 
  * `txHash`: `DATA` - transaction hash
- **Example**

```
FinishPoll("0x4D8D5B14b4E2eE605c74") 

//output
0xf6b233162cae70c6394fad3fd0c825b29cdfd5ea690eedf12e11cc445187d5a9
```



---

#### StartTally

*func StartTally(pollContractAddr) result* 

- **Input :** 
  - `pollContractAddr`: `DATA` - a poll contract address.
- **Output :** 
  * `result`: `int` - return `1`  if success to tally the poll, otherwise return `-1`
- **Example**

```
StartTally("0x4D8D5B14b4E2eE605c74") 

//output
1
```



---

#### WritePollResults

*func WritePollResults(pollContractAddr, pollResult) txHash*

- **Input :** 

  - `pollContractAddr`: `DATA` - a poll contract address.

  - `pollResult`: `Array` - array of poll results. For the more detail, refer to SCT document (sct51WritePollResults).

    ```
    //example
      pollResult =[
      				"0x1",	// result
                    "0x0",	// result code
                    "0x62",	// agrees
                    "0x2",	// disagrees
                    "0x2",	// nullities
                    "0x64",	// total voters
                    "0x62"	// voting rate(unsigned integer)
                  ]
    ```

- **Output :**

- * `txHash`: `DATA` - transaction hash
- **Example**

```
WritePollResults("0x4D8D5B14b4E2eE605c74",["0x1","0x0","0x62","0x2","0x2","0x64","0x62"]) 

//output
0x4d7b1afa5fcebb97b6c64c6843db944de5178defd58947fe459e4481634972d4
```



---


