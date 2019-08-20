all : test

TARGET=unit_test


CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x
LDFLAGS += -shared -Wl,-rpath='$$ORIGIN' -pthread
USE_GTEST_AS_LIB = -DGTEST_LINKED_SHARED_LIBRARY=1


${TARGET} : soundex.h soundex.cpp char-string-util.h char-string-util.cpp unit_test.cpp
	g++ ${CXXFLAGS} ${USE_GTEST_AS_LIB} -o $@ $^ -lgmock_main -lgmock -lgtest

test : ${TARGET}
	./${TARGET}

clean:
	rm -f ${TARGET}

