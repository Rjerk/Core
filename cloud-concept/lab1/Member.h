/**********************************
 * FILE NAME: Member.h
 *
 * DESCRIPTION: Definition of all Member related class
 **********************************/

#ifndef MEMBER_H_
#define MEMBER_H_

#include "stdincludes.h"

/**
 * CLASS NAME: q_elt
 *
 * DESCRIPTION: Entry in the queue
 */
class q_elt {
public:
	void *elt;
	int size;
	q_elt(void *elt, int size);
};

/**
 * CLASS NAME: Address
 *
 * DESCRIPTION: Class representing the address of a single node
 */
class Address {
public:
  int id_;
  int port_;
	Address() = default;
	// Copy constructor
	Address(const Address &);
	 // Overloaded = operator
	Address& operator=(const Address &);
	bool operator==(const Address &);

	explicit Address(std::string address) {
		size_t pos = address.find(":");

		id_ = stoi(address.substr(0, pos));
		port_ = stoi (address.substr(pos + 1, address.size()-pos-1));
	}

  std::string getAddress() {
		return std::to_string(id_) + ":" + std::to_string(port_);
	}

	void init() {
    id_ = 0;
    port_ = 0;
	}
};

/**
 * CLASS NAME: MemberListEntry
 *
 * DESCRIPTION: Entry in the membership list
 */
class MemberListEntry {
public:
	int id_;
	short port_;
	long heartbeat_;
	long timestamp_;

	MemberListEntry() = default;
	explicit MemberListEntry(const MemberListEntry &);

	MemberListEntry(int id, short port, long heartbeat, long timestamp);
	MemberListEntry(int id, short port);

	MemberListEntry& operator=(const MemberListEntry &);

	int getid() const { return id_; }
	short getport() const { return port_; }
	long getheartbeat() const { return heartbeat_; }
	long gettimestamp() const { return timestamp_; }

	void setid(int id) { id_ = id; }
	void setport(short port) { port_ = port; }
	void setheartbeat(long hearbeat) { heartbeat_ = hearbeat; }
	void settimestamp(long timestamp) { timestamp_ = timestamp; }
};

/**
 * CLASS NAME: Member
 *
 * DESCRIPTION: Class representing a member in the distributed system
 */
// Declaration and definition here
class Member {
public:
	// This member's Address
	Address addr_;
	// boolean indicating if this member is up
	bool inited_{false};
	// boolean indicating if this member is in the group
	bool in_group_{false};
	// boolean indicating if this member has failed
	bool failed_{false};
	// number of my neighbors
	int nnb_{0};
	// the node's own heartbeat
	long heartbeat_{0};
	// counter for next ping
	int ping_counter_{0};
	// counter for ping timeout
	int timeout_counter_{0};
	// Membership table
  std::vector<MemberListEntry> member_list_;
	// My position in the membership table
  std::vector<MemberListEntry>::iterator my_pos_;

	// Queue for failure detection messages
  std::queue<q_elt> mp1q;
	/**
	 * Constructor
	 */
  Member() = default;

	Member(const Member &);
	Member& operator=(const Member &);

	virtual ~Member() {}
};

#endif /* MEMBER_H_ */
