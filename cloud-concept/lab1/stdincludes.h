/**********************************
 * FILE NAME: stdincludes.h
 *
 * DESCRIPTION: standard header file
 **********************************/

#ifndef _STDINCLUDES_H_
#define _STDINCLUDES_H_

/*
 * Macros
 */
namespace {
  const int RING_SIZE {512};
  const int FAILURE {-1};
  const int SUCCESS {0};
}
/*
 * Standard Header files
 */
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <execinfo.h>
#include <signal.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
#include <fstream>

#define STDCLLBKARGS (void *env, char *data, int size)
#define STDCLLBKRET	void
#define DEBUGLOG 1
		
#endif	/* _STDINCLUDES_H_ */
