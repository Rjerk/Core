/**********************************
 * FILE NAME: Params.cpp
 *
 * DESCRIPTION: Definition of Parameter class
 **********************************/

#include "Params.h"

Params::Params(const std::string& config_file)
{
  auto file{::fopen(config_file.data(), "r")};
  if (!file) {
    throw std::runtime_error{ "could not open" + config_file };
  }

	::fscanf(file, "MAX_NNB: %d", &max_neighbors_);
	::fscanf(file, "\nSINGLE_FAILURE: %d", &single_failure_);
	::fscanf(file, "\nDROP_MSG: %d", &drop_msg_num_);
	::fscanf(file, "\nMSG_DROP_PROB: %lf", &msg_drop_prob_);
	::fclose(file);

	for (auto i = 0; i < en_gpsz_; i++ ) {
		all_nodes_joined_ += i;
	}
}

// DESCRIPTION: Return time since start of program, in time units.
// For a 'real' implementation, this return time would be the UTC time.
int Params::getcurrtime() const {
  return global_time_;
}
