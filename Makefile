all : test

TARGET=soundex-test


CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x
LDFLAGS += -shared -Wl,-rpath='$$ORIGIN' -pthread
USE_GTEST_AS_LIB = -DGTEST_LINKED_SHARED_LIBRARY=1


${TARGET} : soundex-test.cpp
	g++ ${CXXFLAGS} ${USE_GTEST_AS_LIB} -o $@ $^ -lgmock_main -lgmock -lgtest

test : soundex-test
	./${TARGET}

clean:
	rm -f ${TARGET}

