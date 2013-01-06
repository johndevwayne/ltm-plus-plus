/*
 * BigNumTest.cpp
 *
 *  Created on: Jan 5, 2013
 *
 *  LICENSING: See LICENSE.txt or http://opensource.org/licenses/MIT
 */

#include "BigNumTest.h"
#include "BigNum.h"

#include "DotNetTestVectors.h"
#include "DerTestVectors.h"

BigNumTest::BigNumTest() {

}

void BigNumTest::RunTests() {
    unsigned numFailed = 0;
    size_t numTestVectors = sizeof(dotNetTestVectors)/sizeof(TestVectorRaw);
    for (unsigned i=0; i<numTestVectors; i++) {
        TestVectorRaw &tv = dotNetTestVectors[i];
        std::vector<unsigned char> encoded (tv.encoded, tv.encoded + tv.encodedLength);
        std::string answer = tv.base10Int;
        BigNum bn = BigNum::FromDotNetBigInt(encoded);
        if (bn.ToString(10) != answer) {
            ++numFailed;
            std::cerr << "Failure for test vector " << i << ": " << answer << std::endl;
        }
    }
    if (numFailed > 0) {
        std::cerr << "Failed " << numFailed << " out of " << numTestVectors <<
                " .NET BigInteger tests" << std::endl;
    } else {
        std::cerr << "Passed " << numTestVectors << " .NET BigInteger tests" << std::endl;
    }
    numFailed = 0;
    numTestVectors = sizeof(derTestVectors)/sizeof(TestVectorRaw);
    for (unsigned i=0; i<numTestVectors; i++) {
        TestVectorRaw &tv = derTestVectors[i];
        std::vector<unsigned char> encoded (tv.encoded, tv.encoded + tv.encodedLength);
        std::string answer = tv.base10Int;
        BigNum bn = BigNum::FromDER(encoded);
        if (bn.ToString(10) != answer) {
            ++numFailed;
            std::cerr << "Failure for test vector " << i << ": " << answer << std::endl;
        }
    }
    if (numFailed > 0) {
        std::cerr << "Failed " << numFailed << " out of " << numTestVectors <<
                " .NET BigInteger tests" << std::endl;
    } else {
        std::cerr << "Passed " << numTestVectors << " DER BigInteger tests" << std::endl;
    }
}
