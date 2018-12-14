/**********************************
 * FILE NAME: Application.cpp
 *
 * DESCRIPTION: Application layer class function definitions
 **********************************/

#include "Application.h"
#include <memory>

void handler(int sig) {
	void *array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

/**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main(int argc, char *argv[])
{
	//signal(SIGSEGV, handler);

	if ( argc != ARGS_COUNT ) {
		cout<<"Configuration (i.e., *.conf) file File Required"<<endl;
		return FAILURE;
	}

	auto app = std::unique_ptr<Application>{new Application{argv[1]}};
	app->run();
}

/**
 * Constructor of the Application class
 */
Application::Application(const std::string& infile):
  param_{new Params(infile)},
  logger_{new Log(param_.get())},
  emul_net_{new EmulNet(param_.get())}
{
	srand (time(NULL));
	mp1 = (MP1Node **) malloc (param_->en_gpsz_ * sizeof(MP1Node *));

	/*
	 * Init all nodes
	 */
	for (auto i{0}; i < param_->en_gpsz_; ++i ) {

		Member *memberNode = new Member;
		memberNode->inited = false;

		Address *address_of_member_node = new Address();
		// Address join_addr{getjoinaddr()};

		address_of_member_node = (Address *) emul_net_->ENinit(address_of_member_node, param_->port_num_);

		mp1[i] = new MP1Node(memberNode, param_.get(), emul_net_.get(), logger_.get(), address_of_member_node);

		logger_->LOG(&(mp1[i]->getMemberNode()->addr), "APP");

		delete address_of_member_node;
	}
}

/**
 * Destructor
 */
Application::~Application() {
	for (auto i{0}; i < param_-> en_gpsz_; ++i ) {
		delete mp1[i];
	}
	free(mp1);
}

/**
 * FUNCTION NAME: run
 *
 * DESCRIPTION: Main driver function of the Application layer
 */
int Application::run()
{
	srand(time(NULL));

	// As time runs along
	for(param_->global_time_ = 0; param_->global_time_ < TOTAL_RUNNING_TIME; ++param_->global_time_ ) {
		// Run the membership protocol
		mp1Run();
		// Fail some nodes
		fail();
	}

	// Clean up
	emul_net_->ENcleanup();

	for (auto i{0}; i <= param_->en_gpsz_ - 1; ++i) {
		 mp1[i]->finishUpThisNode();
	}

	return SUCCESS;
}

/**
 * FUNCTION NAME: mp1Run
 *
 * DESCRIPTION:	This function performs all the membership protocol functionalities
 */
void Application::mp1Run() {
	// For all the nodes in the system
	for (auto i{0}; i <= param_->en_gpsz_ - 1; ++i) {

		/*
		 * Receive messages from the network and queue them in the membership protocol queue
		 */
		if (param_->getcurrtime() > param_->step_rate_*i && !(mp1[i]->getMemberNode()->bFailed) ) {
			// Receive messages from the network and queue them
			mp1[i]->recvLoop();
		}

	}

	// For all the nodes in the system
	for(auto i{param_->en_gpsz_-1}; i >= 0; --i ) {

		/*
		 * Introduce nodes into the distributed system
		 */
		if( param_->getcurrtime() == (int)(param_->step_rate_*i) ) {
			// introduce the ith node into the system at time STEPRATE*i
			mp1[i]->nodeStart(JOINADDR, param_->port_num_);
			cout<<i<<"-th introduced node is assigned with the address: "<<mp1[i]->getMemberNode()->addr.getAddress() << endl;
			nodeCount += i;
		}

		/*
		 * Handle all the messages in your queue and send heartbeats
		 */
		else if( param_->getcurrtime() > (int)(param_->step_rate_*i) && !(mp1[i]->getMemberNode()->bFailed) ) {
			// handle messages and send heartbeats
			mp1[i]->nodeLoop();
			#ifdef DEBUGLOG
			if ((i == 0) && (param_->global_time_ % 500 == 0)) {
				logger_->LOG(&mp1[i]->getMemberNode()->addr, "@@time=%d", param_->getcurrtime());
			}
			#endif
		}

	}
}

/**
 * FUNCTION NAME: fail
 *
 * DESCRIPTION: This function controls the failure of nodes
 *
 * Note: this is used only by MP1
 */
void Application::fail() {

	// fail half the members at time t=400
	if(param_->dropmsg_ && param_->getcurrtime() == 50 ) {
		param_->dropmsg_ = true;
	}

	int removed{0};
  if (param_->single_failure_ && param_->getcurrtime() == 100) {

		removed = (rand() % param_->en_gpsz_);

		#ifdef DEBUGLOG
		logger_->LOG(&mp1[removed]->getMemberNode()->addr, "Node failed at time=%d", param_->getcurrtime());
		#endif
		mp1[removed]->getMemberNode()->bFailed = true;

	} else if (param_->getcurrtime() == 100 ) {
		removed = rand() % param_->en_gpsz_ / 2;

		for (auto i{removed}; i < removed + param_->en_gpsz_ / 2; i++ ) {

			#ifdef DEBUGLOG
			logger_->LOG(&mp1[i]->getMemberNode()->addr, "Node failed at time = %d", param_->getcurrtime());
			#endif

			mp1[i]->getMemberNode()->bFailed = true;
		}
	}

	if (param_->drop_msg_num_ && param_->getcurrtime() == 300) {
		param_->dropmsg_ = false;
	}

}

/**
 * FUNCTION NAME: getjoinaddr
 *
 * DESCRIPTION: This function returns the address of the coordinator
 */
Address Application::getjoinaddr(void) const {
	//trace.funcEntry("Application::getjoinaddr");
    Address joinaddr;
    joinaddr.init();
    *(int *)(&(joinaddr.addr))=1;
    *(short *)(&(joinaddr.addr[4]))=0;
    //trace.funcExit("Application::getjoinaddr", SUCCESS);
    return joinaddr;
}
