## SymVote library

### Introduction

Symvote is a go library for handling SCT vote contract(SCT50/51). The library performs the following roles.

- Make SCT transaction for voting.
- Send a transaction for voting to Symverse blockchain node.
- Look up the several information about voting.
- Automatically tally vote and send the result data with transaction to blockchain.
- Manage vote manager account.

##### Contracts

Symverse voting system contains the 3 types of contracts such as SCT50(vote), SCT51(poll), and SCT20/21(token). SCT50 is the contract to manage vote service, and SCT51 is the contract to manage each poll. SCT20/21 is a Token contract for user vote rights.

SCT50 contract can have several SCT51 contract. Therefore, after creating SCT50 contract, it should be created SCT51 contract. Vote service provider(SCT50 owner) can register poll creators in SCT50 contract. The poll creators registered in SCT50 contract can only create SCT51 contract when they want to make a poll contract.

##### Token

The vote contract is using Token(SCT20 or SCT21) for vote rights, and the Tokens of users are staked in the poll when they try to vote in poll. Therefore SCT50 owner should create Token contract first before creating SCT50 contract.

Token can also be used to weighted vote.

In case of non-weighted vote, the poll creator should select the `StakeOption` of SCT51 to **'1'** when creating SCT51 contract. And user should select the `Stake` option of VoteInPoll API as **'1'** when voting in poll.

In case of weighted vote, `StakeOption` of SCT51 should be selected as **'0'** or more than **'2'**. The option **'0'** is free weight(unlimited staking) vote, and the option more than '2' limited weight vote. User can vote in poll with staking Token less than this value.



### Objects

- vote.so: library binary

- vote.h: library C header

- .config.json: configuration file for operation

  ```
  {
      "chainId":1,		//chain id of blockchain
      "owner": {			//vote manager account information
          "symId": "0x00021111111111110002",
          "keydir": "/home/user/vote-server/keystore/"
      },
      "nodes": [{			//work node information for access to blockchain
          "symId":"0x0002222222222220002",
          "host": "127.0.0.1",
          "httpPort": "8008",
          "wsPort": "8018"
      },{
          "symId":"0x00023333333333330002",
          "host": "127.0.0.1",
          "httpPort": "8009",
          "wsPort": "8019"
      }]
  }
  ```



### How to use

- Setup
  1. Initialize library
  2. Unlock vote manager account (option)
  3. Create token contract (SCT20)
  4. Allocate token to users
  5. Create vote contract (SCT50)
  6. Add poll creators

- Send transaction and check status
  1. Make transaction
  2. Sign transaction (by user)
  3. Send transaction
  4. Check transaction status and receipt

- Poll creation (by poll creator only)
  1. Get vote contract
  2. Make and sign poll contract transaction (SCT51)
  3. Send transaction
  4. Check transaction status and receipt

- Vote in poll (by user)
  1. Check poll status
  2. Make and sign voting transaction (SCT51)
  3. Send transaction
  4. Check transaction status and receipt

- Tally vote
  1. Check poll status
  2. Start tally when poll is expired
  3. Check poll status
  4. Get vote result



### APIs

Refer SymVote API document.



### Example

##### C

- build

  ```
  > cd /.../go-symverse/cmd/symvote/example/c/
  > make
  ```

- run

  ```
  > cd /.../go-symverse/cmd/symvote/example/c/
  > ./cvote
  ```

##### Java

- build

  ```
  > cd /.../go-symverse/cmd/symvote/example/java/
  > javac -cp jna-5.5.0.jar VoteExample.java Vote.java
  ```

- run

  ```
  > cd /.../go-symverse/cmd/symvote/example/java/
  > java -cp .:jna-5.5.0.jar VoteExample
  ```



### Reference

##### Calling Go Functions from Other Languages using C Shared Libraries

- https://github.com/vladimirvivien/go-cshared-examples

##### SCT50/51 functions

- Refer SCT50/51 Guide.

