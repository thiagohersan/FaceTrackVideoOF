# add custom variables to this file

# Paths

ifndef OPENCV_PATH
    OPENCV_PATH=/usr/local
endif

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

ifndef OF_ROOT
    OF_ROOT=../../..
endif


# Flags
INCLUDES=-I$(OPENCV_PATH)/include -Iinclude/
LIBRARIES=-L$(OPENCV_PATH)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS = 

# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

USER_LDFLAGS = 


# use this to add system libraries for example:
# USER_LIBS = -lpango
 
USER_LIBS =


# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -Os


EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj,.git"
