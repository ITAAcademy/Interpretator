#pragma once
#include <iostream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

//#include <chrono>

#include "fcgi_config.h"
#include "fcgiapp.h"

using namespace std;

#define THREAD_COUNT 2
#define SOCKET_PATH "127.0.0.1:9002"

static int socketId;
