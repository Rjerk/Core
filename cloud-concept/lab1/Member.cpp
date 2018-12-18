/**********************************
 * FILE NAME: Member.cpp
 *
 * DESCRIPTION: Definition of all Member related class
 **********************************/

#include "Member.h"

/**
 * Constructor
 */
q_elt::q_elt(void *elt, int size): elt(elt), size(size) {}

/**
 * Copy constructor
 */
Address::Address(const Address &another_address) {
  id_ = another_address.id_;
  port_ = another_address.port_;
}

/**
 * Assignment operator overloading
 */
Address& Address::operator=(const Address& another_address) {
  id_ = another_address.id_;
  port_ = another_address.port_;
	return *this;
}

bool Address::operator==(const Address& another_address) {
  return id_ == another_address.id_ 
      && port_ == another_address.port_;
}

MemberListEntry::MemberListEntry(int id, short port, long heartbeat, long timestamp):
  id_{id}, port_{port}, heartbeat_{heartbeat}, timestamp_{timestamp}
{
}

MemberListEntry::MemberListEntry(int id, short port): id_{id}, port_{port}
{
}

MemberListEntry::MemberListEntry(const MemberListEntry &another_MLE) {
	this->heartbeat_ = another_MLE.heartbeat_;
	this->id_ = another_MLE.id_;
	this->port_ = another_MLE.port_;
	this->timestamp_ = another_MLE.timestamp_;
}

MemberListEntry& MemberListEntry::operator=(const MemberListEntry &another_MLE) {
	MemberListEntry temp(another_MLE);
  std::swap(heartbeat_, temp.heartbeat_);
	std::swap(id_, temp.id_);
	std::swap(port_, temp.port_);
	std::swap(timestamp_, temp.timestamp_);
	return *this;
}

Member::Member(const Member &anotherMember) {
	this->addr_ = anotherMember.addr_;
	this->inited_ = anotherMember.inited_;
	this->in_group_ = anotherMember.in_group_;
	this->failed_ = anotherMember.failed_;
	this->nnb_ = anotherMember.nnb_;
	this->heartbeat_ = anotherMember.heartbeat_;
	this->ping_counter_ = anotherMember.ping_counter_;
	this->timeout_counter_ = anotherMember.timeout_counter_;
	this->member_list_ = anotherMember.member_list_;
	this->my_pos_ = anotherMember.my_pos_;
	this->mp1q = anotherMember.mp1q;
}

Member& Member::operator =(const Member& anotherMember) {
	this->addr_ = anotherMember.addr_;
	this->inited_ = anotherMember.inited_;
	this->in_group_ = anotherMember.in_group_;
	this->failed_ = anotherMember.failed_;
	this->nnb_ = anotherMember.nnb_;
	this->heartbeat_ = anotherMember.heartbeat_;
	this->ping_counter_ = anotherMember.ping_counter_;
	this->timeout_counter_ = anotherMember.timeout_counter_;
	this->member_list_ = anotherMember.member_list_;
	this->my_pos_ = anotherMember.my_pos_;
	this->mp1q = anotherMember.mp1q;
	return *this;
}
