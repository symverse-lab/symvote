

# SCT50/51 Guide

## SCT APIs Format

The information of the SCT is recorded and operated in the main block and station state through the trans- action.
If `To = null`, SCT Create, when you execute SCT Method, insert `To = $ {SCT Address}` and call Transaction.


* `to` - When `To = null` SCT Create, when executing SCT Method `To = $ {SCT Address}`
* `type` - ` " 0x1 "` // means SCT processing Transcation
* `input(data)` - input (data) - format data for SCT Run or Create

In SCT processing, `input` fomat data has the following format. Invokes the SCT API through a set of Type, method, and Parameter.
Please check the contents of each SCT format below.

**[ ${Type}, ${Method}, ${Parameter} ]**

* Type - It means Type to be processed among SCT 20/30/40/50/51.

* Method - Method corresponding to SCT Type.

* Parameter - Parameter corresponding to SCT Type.

After encoding this SCT data as RLP, add to `input` of transaction.

* `input` = `rlp.encode[ ${Type}, ${Method}, ${Parameter} ]`



## List of SCT50/51 APIs

Contracts APIs based on SCT Type and Method.



| SCT50                                               | SCT51                                           |
| --------------------------------------------------- | ----------------------------------------------- |
| [sct50Create](#sct50Create)                         | [sct51CreatePoll](#sct51CreatePoll)             |
| [sct50AddPollCreators](#sct50AddPollCreators)       | [sct51VoteInPoll](#sct51VoteInPoll)             |
| [sct50RemovePollCreators](#sct50RemovePollCreators) | [sct51UnstakeTokens](#sct51UnstakeTokens)       |
|                                                     | [sct51EmergencyStopPoll](#sct51EmergencyPoll)   |
|                                                     | [sct51FinishPoll](#sct51FinishPoll)             |
|                                                     | [sct51WritePollResults](#sct51WritePollResults) |



## SCT50 - VoteContract

**SCT50 is a template that handles Vote contract. It has following functions:**



### 1. sct50Create

`sct50Create` creates SCT50 Vote Contract. It is needed to use SCT20 token to make. Referring SCT20 token will be standard currency when users stake tokens to poll contract to vote.


* Transaction Parameters:
  
    * **from**:`Address` - sender SymId
    * **to**:`Address` - `none`
    * **input**:`Data` - rlp encoded Data 
        * **Type**:`Data` -  `0x32`
        * **Method**:`Data` -  `0x0`
        * **Parameters**:
            1. **Party Name**:`string` - Digital Party name
            2. **SCT20 Token Address**:`Address` - SCT20 Token Address to use.
            3. **Owner**:`Address` - Owner SymId 


* output:
  
    * Transaction Hash


* validation:

    * `Receipt`.`contractAddress` - sct50 Vote Contract Address:`Address` 
    * `sct_getVoteContract` - checkout sct50 Vote Contract Information



````
[rlp encode input data]
inputdata = rlp.encode(["0x32", "0x0", ["SymParty",   // PartyName
                    "0x7ceb501abaeaef5ff714",       // SCT20TokenAddress
                    "0x00020000000000020002"]])     // OwnerSymId
````



### 2. sct50AddPollCreators

`sct50AddPollCreators` registers given users as a poll creator. Poll creators will be given authority to create SCT51 Poll Contract.

- Transaction Parameters:

  - **from**:`Address` - sender SymId
  - **to**:`Address` - SCT50 Vote Contract Address
  - **input**:`Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x32`
    - **Method*:`Data` -  `0x1`
    - **Parameters**:
      1. **Poll Creators**:`Array[Address]` -  SymId lists to register as poll creator
- output:
  - Transaction Hash
- validation:
  - `sct_getVoteContract` - checkout `pollCreators` index



```js
[rlp encode input data]
inputdata = rlp.encode(["0x32", "0x1", ["0x00020000000000030002", 	// PollCreator
                    "0x00020000000000040002"]])                 	// PollCreator
```



#### 3. sct50RemovePollCreators

`sct50RemovePollCreators` unregisters given users from poll creator. They lost authority to create SCT51 Poll Contract.

- Transaction Parameters:

  - **from**:`Address` - sender SymId
  - **to**:`Address` - SCT50 Vote Contract Address
  - **input**:`Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x32`
    - **Method**:`Data` -  `0x2`
    - **Parameters**:
      1. **Poll Creators**:`(Array[Address])` -  SymId lists to unregister from poll creator
- output:
  - Transaction Hash
- validation:
  - `sct_getVoteContract` - checkout `pollCreators` index



```js
[rlp encode input data]
inputdata = rlp.encode(["0x32", "0x2", ["0x00020000000000030002", 	// PollCreator
                    "0x00020000000000040002"]])                 	// PollCreator
```



## SCT51 - PollContract

### sct51CreatePoll

`sct51CreatePoll` creates SCT51 Poll Contract. Only Poll Creators registered from SCT50 Vote Contract Creator(or Owner) can create. It is needed to use SCT50 Vote Contract to make. Created Poll Contract will handle about voting activity.

* Transaction Parameters:
  - **from**:`Address` - sender SymId
  - **to**:`Address` - `none`
  - **input**:`Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x0`
    - **Parameters**:
      1. **PollNumber**:`Int` -  Poll number
      2. **Category**:`Int` -  Agenda category (it defines `voting rate`, `participation rate`)
      3. **Agenda**:`string` -  Agenda name
      4. **Description**:`string` -  Description about Agenda
      5. **Owner**:`Address` -  Owner of Poll to create
      6. **Start**:`Int` -  Poll start time (`UNIX time stamp`)
      7. **End**:`Int` -  Poll start time (`UNIX time stamp`)
      8. **VoteContract**:`Address` -  SCT50 Vote Contract Address
      9. **SecretOption**:`Int` -  Secret option for the poll [`0`: `public` `1`: `secret`]
      10. **StakeOption**:`Int` -  Stake strict option for each voter to vote poll [`0`: `free stake` `*`: `stake limit for each voter with given amount`]
      11. **TotalVoters**:`Int` -  Allowed total voters for the poll.
      12. **Quorum**:`Int` -  Minimum rate of participants for the poll to pass.
      13. **PassRate**:`Int` -  Minimum rate of agree for the poll to pass.

- output:
  - Transaction Hash
- validation:
  - `Receipt`.`contractAddress` - sct51 Poll Contract Address:`Address`
  - `sct_getVoteContract` - checkout `polls` index
  - `sct_getPollContract` - checkout sct51 Poll Contract Information



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x0", ["0x0",	// Poll number
    				"0x0",						// Category
                    "Agenda1",					// Agenda
                    "Agenda1 is about ...",		// Description
                    "0x00020000000000020002",	// OwnerSymId
                    "0x5e4b36c9",				// Start Unix time
                    "0x5e50b509",				// End Unix time
                    "0x83c4b863539810ef20f4",	// SCT50 Vote Contract Address
                    "0x0",						// Secret option
                    "0x1",						// Stake option
                    "0x64",						// TotalVoters
                    "0x64",						// Quorum
                    "0x64"]])					// PassRate
```



### sct51VoteInPoll

`sct51VoteInPoll` make user vote in poll. It should be preceded staking tokens in poll.

- Transaction Parameters:
  - **from**:`Address` - sender SymId
  - **to**:`Address` - SCT51 Poll Contract Address
  - **input**:`Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x1`
    - **Parameters**:
      1. **Stake**:`Int` -  SCT20 balance to stake for voting in poll contract (weighted vote)
      2. **Decision**:`Int` -  decision about Poll ( `0` - Disagree `1` - Agree)
- output:
  - Transaction Hash
- validation:
  - `sct_getVotingPaper` - checkout voting paper information



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x1", ["0x1",		// Stake
					"0x1"]])						// Decision
```



### sct51UnstakeTokens

`sct51UnstakeTokens` unstakes given amount from the balance that sender staked in Poll Contract. Unstaked balance will return to sender's SCT20 balance.

* Transaction Parameters:

  - **from**:`Address` - sender SymId
  - **to**:`Address` - SCT51 Poll Contract Address
  - **input**:`Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x2`
    - **Parameters**:
      1. **Amount**:`Int` -  SCT20 balance to unstake in poll contract
* output:
  * Transaction Hash
* validation:
  * `sct_getVotingPaper` - checkout voting paper information
  * `sct_getContractAccount` - checkout balance



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x2", ["0x1"]])	// Unstake Amount
```



### sct51EmergencyStopPoll

`sct51EmergencyStopPoll` make poll inactive. Only SCT50 Vote Creator(or owner) can make it. Hence poll state turns to inactive, user can not stake and vote in poll.

* Transaction Parameters:

  - **from** - `Address` - sender SymId
  - **to** - `Address` - SCT51 Poll Contract Address
  - **input** - `Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x3`
      - **Parameters** - `none`
* output:
  * Transaction Hash
* validation:
  * `sct_getPollContract` - checkout `pollState` index



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x3", [])
```



### sct51FinishPoll

`sct51RevokePoll` make poll expired. Only SCT50 Vote Creator can make it. Hence poll state turns to expired, the staked balance from users will be returned to them.

* Transaction Parameters:

  - **from** - `Address` - sender SymId
  - **to** - `Address` - SCT51 Poll Contract Address
  - **input** - `Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x4`
    - **Parameters** -  `none`
* output:
  * Transaction Hash
* validation:
  * `sct_getPollContract` - checkout `pollState` index
  * `sct_getContractAccount` - checkout balance



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x4", [])
```



### sct51WritePollResults

`sct51WritePollResults` write result to the poll contract. Only SCT50 Vote Creator can write it. 

- Transaction Parameters:
  - **from** - `Address` - sender SymId
  - **to** - `Address` - SCT51 Poll Contract Address
  - **input** - `Data` - rlp encoded Data 
    - **Type**:`Data` -  `0x33`
    - **Method**:`Data` -  `0x5`
    - **Parameters** :
      1. **Result**:`Int` -  poll result code
      2. **Code**:`Int` -  extra poll result code
      3. **Agrees**:`Int` -  the number of stake voted as agree for the poll
      4. **Disagrees**:`Int` -  the number of stake voted as disagree for the poll
      5. **Nullities**:`Int` -  the number of stake holders not voted for the poll
      6. **TotalVoters**:`Int` -  the number of stake holders for the poll
      7. **VotingRate**:`Int` -  the rate of holders voted for the poll (unsigned integer value)
- output:
  - Transaction Hash
- validation:
  - `sct_getPollContract` - checkout `pollState` index
  - `sct_getContractAccount` - checkout balance



```js
[rlp encode input data]
inputdata = rlp.encode(["0x33", "0x5", ["0x1",	// result
                                       	"0x0",	// result code
                                       	"0x62",	// agrees
                                       	"0x2",	// disagrees
                                       	"0x2",	// nullities
                                       	"0x64",	// total voters
                                       	"0x62"])// voting rate(unsigned integer)
```





## List of SCT50/51 RPC API

| SCT50                                       | SCT51                                       |
| ------------------------------------------- | ------------------------------------------- |
| [sct_getVoteContract](#sct_getVoteContract) | [sct_getPollContract](#sct_getPollContract) |
|                                             | [sct_getVoteResult](#sct_getVoteResult)     |
|                                             | [sct_getVotingPaper](#sct_getVotingPaper)   |

### 1. sct_getVoteContract

`sct_getVoteContract` returns given SCT50 Vote Contract's Information.



* input:
  1. **VoteContractAddress**:`Address` - SCT50 Vote Contract Address
  2. **BlockNumber**:`Int` - Last block number
* output
  * **party**: `string` - Party Name
  * **owner**: `Address` - Owner SymId
  * **creator** - `Address` - Creator SymId
  * **token**: `Address` - SCT20 Token Address
  * **pollCreators**: `Array[Address]` - registered poll creators list
  * **polls**: `Array[Address]` - created polls list



### 2. sct_getPollContract

`sct_getPollContract` returns givens SCT51 Poll Contract's Information.

 

* input:
  1. **PollContractAddress**:`Address` - SCT51 Poll Contract Address
  2. **BlockNumber**:`Int` - Last block number
* output:
  * **pollNumber** - `Int` - Poll number
  * **category** - `Int` - Category for Agenda
  * **agenda** - `STRING` - Adenda name
  * **description** - `string` - Agenda description
  * **start** - `Int` - Start UNIX time
  * **end** - `Int` - End UNIX time
  * **state** - `String` - Poll State
  * **votingPaper** - `Array[VotingPaper]` - Voting paper lists. `VotingPaper` - {`voter`, `stake`, `votes`, `decision`}
  * **voteResult** - `VoteResult` - Vote result. `VoteResult`: {`result`, `resultCode`, `agrees`, `disagrees`, `totalVoters`, `votingRate`}
  * **voteContract** - `ADDRESS` - SCT50 Vote Contract address.
  * **secretOption** - `STRING` - secret option
  * **stakeOption** - `STRING` - stake option
  * **totalVoters** - `INT` - the number of total voters
  * **quorum** - `INT` - minimum rate of participants for the poll
  * **passRate** - `INT` - minimum rate of agree for the poll
  * **owner** - `ADDRESS` - Owner SymId
  * **creator** - `ADDRESS` - Creator SymId



### 3. sct_getVoteResult

`sct_getVoteResult` returns given SCT51 Poll Contract's vote result.



* input:
  1. **PollContractAddress**:`Address` - SCT51 Poll Contract Address
  2. **BlockNumber**:`Int` - Last block number
* output:
  * **result** - `INT` - final result code for the given poll
  * **code** - `Int` - extra result code for the given poll
  * **agrees** - `Int` - total agrees for the given poll
  * **disagrees** - `Int` - total disagrees for the given poll
  * **nullities** - `Int` - total nullities for the given poll
  * **totalVoters** - `Int` - total voters for the given poll
  * **votingRate** - `Int` - voting rate for the given poll

### 4. sct_getVotingPaper

`sct_getVotingPaper` returns given user's vote information in poll.



* input:
  1. **PollContractAddress**:`Address` - SCT51 Poll Contract Address
  2. **SymId**:`Address` - SymId to request.
  3. **BlockNumber**:`Int` - Last block number
* output:
  * **stake**:`Int` - Staked balance in poll
  * **votes**:`Int` - Used stake for voting
  * **decision**:`STRING` - decision about poll



## SCT50/51 Error codes

| ErrName                     | ErrMsg                                    | ErrCode |
| --------------------------- | ----------------------------------------- | ------- |
| ErrExistPollCreator         | already registered poll creator           | `5000`  |
| ErrNoExistPollCreator       | there are no any poll creators            | `5001`  |
| ErrNoProperStakeBalance     | no proper stake balance                   | `5002`  |
| ErrUnavailablePoll          | check the poll state                      | `5003`  |
| ErrExpiredPoll              | poll alrealy expired                      | `5004`  |
| ErrSctContractPollFormat    | sct contract item format is incorrect     | `5005`  |
| ErrInsufficientContractVote | insufficient stake to vote                | `5006`  |
| ErrInvalidVoting            | can not change voting decision            | `5007`  |
| ErrSctAddPollCreatorsFormat | sct add poll creators format is incorrect | `5008`  |



## SCT51 Poll result codes

| Code  | Message       | Description                                                  |
| ----- | ------------- | ------------------------------------------------------------ |
| `0x0` | `Unknown`     | It may be occurred when the poll is not finished yest        |
| `0x1` | `Approved`    | The poll is finished with approved state.                    |
| `0x2` | `Denied`      | The poll is finished with denied state.                      |
| `0x3` | `Poor Holder` | The poll is finished with lacking number of participants of stake holders. |
| `0x4` | `Poor Stake`  | The poll is finished with lacking number of stakes.          |



## SCT50/51 API Access Authority

| API                     | SCT50 Vote Contract Creator | SCT51 Poll Contract Creator | Voter |
| ----------------------- | --------------------------- | --------------------------- | ----- |
| sct50Create             | O                           | -                           | -     |
| sct50AddPollCreators    | O                           | -                           | -     |
| sct50RemovePollCreators | O                           | -                           | -     |
| sct51CreatePoll         | -                           | O                           | -     |
| sct51VoteInPoll         | O                           | O                           | O     |
| sct51UnstakeTokens      | O                           | O                           | O     |
| sct51EmergencyStopPoll  | O                           | -                           | -     |
| sct51FinishPoll         | O                           | -                           | -     |
| sct51WritePollResults   | O                           | -                           | -     |

