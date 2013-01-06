/*
 * BigNumTest.h
 *
 *  Created on: Jan 5, 2013
 *
 *  LICENSING: See LICENSE.txt or http://opensource.org/licenses/MIT
 */

#ifndef BIGNUMTEST_H_
#define BIGNUMTEST_H_

#include <string>

struct TestVectorRaw {
        unsigned encodedLength;
        unsigned char encoded[128];
        std::string base10Int;
};

class BigNumTest {
    public:
        BigNumTest();
        void RunTests();
};

#endif /* BIGNUMTEST_H_ */
