/*
 * BigNum.cpp
 *
 *  Created on: Dec 21, 2012
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 */

#include "BigNum.h"

BigNum::BigNum(const std::vector<unsigned char> &bin) :
        N(new mp_int) {
    mp_init_size(*this, 1);
    mp_read_signed_bin(*this, &bin[0], bin.size());
}

std::string BigNum::ToString(int radix) const {
    int charsNeeded;
    mp_radix_size(*this, radix, &charsNeeded);
    std::auto_ptr<char> str(new char[charsNeeded]);
    mp_toradix(*this, str.get(), radix);
    std::string result(str.get());
    return result;
}

const BigNum BigNum::NEGATIVE_ONE(-1L);
const BigNum BigNum::ZERO(0L);
const BigNum BigNum::ONE(1L);
const BigNum BigNum::TWO(2L);
const BigNum BigNum::TEN(10L);
