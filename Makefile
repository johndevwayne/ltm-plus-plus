#  
# LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
#

# 		make TOMMATH_DIR=<path> libBigNum.a
# to create the c++ library. TOMMATH_DIR should be set to the directory containing the
# original tommath files. Example:
# make TOMMATH_DIR=~/src/libtommath-0.42.0
#

CLASS_OBJS=BigNum.o add_ops.o mul_ops.o io_ops.o serial_ops.o gcd_ops.o
TEST_OBJS=BigNum_test.o
TEST_PROG=BigNum_test
#TOMMATH_DIR=.
LIBTOMMATH=libtommath.a
LIBTOMMATH_PATH=$(TOMMATH_DIR)/$(LIBTOMMATH)
LIBRARY=libBigNum.a
CXXFLAGS=-Wall -fmessage-length=0 -I$(TOMMATH_DIR)

ifeq ($(BUILD_TYPE),Debug)
	OPT_FLAGS=-g3
else
	OPT_FLAGS=-O3
endif

ODIR=$(BUILD_TYPE)

CXXFLAGS=-Wall $(OPT_FLAGS) -fmessage-length=0 -I$(TOMMATH_DIR)

all : $(LIBRARY)

$(TEST_PROG) : $(TEST_OBJS) $(LIBTOMMATH_PATH) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) $(LIBRARY) $(LIBTOMMATH_PATH)
	
test: $(TEST_PROG)
	./$(TEST_PROG)

clean :
	rm -f $(CLASS_OBJS) $(LIBRARY) $(TEST_OBJS) $(TEST_PROG) $(LIBTOMMATH_PATH)
	
$(CLASS_OBJS) : BigNum.h

$(LIBRARY) : $(CLASS_OBJS)
	$(AR) $(ARFLAGS) $@ $(CLASS_OBJS)

$(LIBTOMMATH_PATH) :
	$(MAKE) -C $(TOMMATH_DIR) clean
	$(MAKE) -C $(TOMMATH_DIR) $(LIBTOMMATH)
