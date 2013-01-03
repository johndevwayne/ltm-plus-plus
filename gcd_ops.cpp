/**
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 **/

#include "BigNum.h"

BigNum BigNum::Gcd(const BigNum &other) const {
    BigNum result;
    mp_gcd(*this, other, result);
    return result;
}

BigNum BigNum::Lcm(const BigNum &other) const {
    BigNum result;
    mp_lcm(*this, other, result);
    return result;
}

BigNum BigNum::ExtendedGcd(const BigNum &other, BigNum &u, BigNum &v) const {
    BigNum result;
    mp_exteuclid(*this, other, u, v, result);
    return result;
}
