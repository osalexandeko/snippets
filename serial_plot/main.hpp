#ifndef MAIN_HPP
#define MAIN_HPP


#include <windows.h>
#include <gl/gl.h>
//#include <GL/glew.h>
#include <gl/glu.h>
#include <cmath>
#include <stdint.h>
#include <iterator> 
#include <map> 
#include <stdlib.h>    
#include <windows.h>
#include <string>
#include <pthread.h>
#include "thread.h"
#include "wqueue.h"
#include "serial.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>



#include "scrnsave.h"  //contains hMainInstance

using namespace std;

#define T_MIN  -1
#define T_MAX  100
#define T_PRECISION 0.1

/*global serial buffer*/
#define  SERIAL_BUFFER_MAX_SIZE  RX_SER_BUF_MAX_SZ			

#endif
