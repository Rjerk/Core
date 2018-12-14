/**********************************
 * FILE NAME: Application.h
 *
 * DESCRIPTION: Header file of all classes pertaining to the Application Layer
 **********************************/

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "stdincludes.h"
#include "MP1Node.h"
#include "Log.h"
#include "Params.h"
#include "Member.h"
#include "EmulNet.h"
#include "Queue.h"
#include <string>
/**
 * global variables
 */

namespace {
  int nodeCount = 0;
  const int ARGS_COUNT = 2;
  const int TOTAL_RUNNING_TIME = 700;
}
/**
 * CLASS NAME: Application
 *
 * DESCRIPTION: Application layer of the distributed system
 */
class Application {
public:
	explicit Application(const std::string&);
	virtual ~Application();

  // suppress copying
  Application(const Application&) = delete;
  Application(Application&&) = delete;

	Address getjoinaddr() const;

	int run();
	void mp1Run();
	void fail();

private:
	// Address for introduction to the group
	// Coordinator Node
  std::unique_ptr<Params> param_;
  std::unique_ptr<Log> logger_;
  std::unique_ptr<EmulNet> emul_net_;

	char JOINADDR[30];
	MP1Node **mp1;
};

#endif /* _APPLICATION_H__ */
