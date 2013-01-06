/*
 * encode.cpp
 *
 *  Created on: Jan 4, 2013
 *
 *  LICENSING: See LICENSE.txt or http://opensource.org/licenses/MIT
 */
#include "BigNum.h"
#include <algorithm>

BigNum::bytevector BigNum::ToDER() const {
    const byte ZEROBYTE = (byte) 0;
    const byte BYTEMASK = (byte) 0xff;

    bytevector result (mp_unsigned_bin_size(*this), ZEROBYTE);
    mp_to_unsigned_bin(*this, &result[0]);
    if (N->sign == MP_ZPOS) {

        // positive integer

        if (*result.begin() >= 128) {
            result.insert(result.begin(), ZEROBYTE);
        }

    } else {

        // negative integer, we must two's complement the result
        unsigned carry = 1;
        for (bytevector::reverse_iterator ri = result.rbegin(); ri != result.rend(); ++ri) {
            unsigned sum = ~(*ri) + carry;
            *ri = sum & BYTEMASK;
            carry = sum >> 8;
        }
        if (carry == 1) {
            result.insert(result.begin(), (byte) 0xff);
        }
    }
    return result;
}

BigNum BigNum::FromDER(const bytevector &derEncodedInt) {
    BigNum result;
    mp_read_unsigned_bin(result, &derEncodedInt[0], derEncodedInt.size());
    if (derEncodedInt[0] >= 128) {
        // We need to subtract 2**(N+1)
        BigNum pow2(1);
        mp_mul_2d(pow2, 8 * derEncodedInt.size(), pow2);
        result.SubtractFrom(pow2);
    }
    return result;
}

BigNum::bytevector BigNum::ToDotNetBigInt() const {
    bytevector result = ToDER();
    std::reverse(result.begin(), result.end());
    return result;
}

BigNum BigNum::FromDotNetBigInt(const bytevector &derEncodedInt) {
    bytevector tmp (derEncodedInt);
    std::reverse(tmp.begin(), tmp.end());
    return FromDER(tmp);
}


