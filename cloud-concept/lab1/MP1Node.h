/**********************************
 * FILE NAME: MP1Node.cpp
 *
 * DESCRIPTION: Membership protocol run by this Node.
 * 				Header file of MP1Node class.
 **********************************/

#ifndef _MP1NODE_H_
#define _MP1NODE_H_

#include "stdincludes.h"
#include "Log.h"
#include "Params.h"
#include "Member.h"
#include "EmulNet.h"
#include "Queue.h"

/**
 * Macros
 */
#define TREMOVE 20
#define TFAIL 5

/*
 * Note: You can change/add any functions in MP1Node.{h,cpp}
 */

/**
 * Message Types
 */
using MsgTypes = enum class MsgTypes {
  JOINREQ,
  JOINREP,
  DUMMYLASTMSGTYPE
};

/**
 * STRUCT NAME: MessageHdr
 *
 * DESCRIPTION: Header and content of a message
 */
using MessageHdr = struct {
	MsgTypes msgType;
};

/**
 * CLASS NAME: MP1Node
 *
 * DESCRIPTION: Class implementing Membership protocol functionalities for failure detection
 */
class MP1Node {
public:
	MP1Node(Member *, Params *, EmulNet *, Log *, Address *);
	Member* getMemberNode() const {
		return member_node_;
	}

	int recvLoop();
	static int enqueueWrapper(void *env, char *buff, int size);
	void nodeStart(char *servaddrstr, short serverport);
	int initThisNode(Address *joinaddr);
	int introduceSelfToGroup(Address *joinAddress);
	int finishUpThisNode();
	void nodeLoop();
	void checkMessages() const;
	bool recvCallBack(void *env, char *data, int size);
	void nodeLoopOps();
	int isNullAddress(Address *addr) const;
	Address getJoinAddress() const;
	void initMemberListTable(Member *memberNode);
	void printAddress(Address *addr) const;
	virtual ~MP1Node();

private:
	EmulNet* emul_net_;
	Log* logger_;
	Params* par_;
	Member* member_node_;
	char NULLADDR[6];
};

#endif /* _MP1NODE_H_ */
