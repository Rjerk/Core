/**********************************
 * FILE NAME: Params.h
 *
 * DESCRIPTION: Header file of Parameter class
 **********************************/

#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "stdincludes.h"
#include "Member.h"

enum class TestType {
  kCreateTest,
  kReadTest,
  kUpdateTest,
  kDeleteTest,
};

/**
 * CLASS NAME: Params
 *
 * DESCRIPTION: Params class describing the test cases
 */
class Params {
public:
  Params() = default;
	explicit Params(const std::string&);

	int getcurrtime() const;

public:
  short port_num_{8001};
  double step_rate_{0.25};     // dictates the rate of insertion
  int max_msg_size_{4000};
	int global_time_{0};
	bool dropmsg_{false};

  int max_neighbors_{10};     // max number of neighbors
  int single_failure_{1};     // single/multi failure
  int drop_msg_num_{1};
  double msg_drop_prob_{0.1}; // message drop probability
  int en_gpsz_{10};           // actual number of peers
  int all_nodes_joined_{55};
};

#endif /* _PARAMS_H_ */
