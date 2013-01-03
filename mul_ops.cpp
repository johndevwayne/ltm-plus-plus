/*
 * mul_ops.cpp
 *
 *  Created on: Dec 22, 2012
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 */

#include "BigNum.h"

BigNum BigNum::Mul(const BigNum &other) const {
	BigNum result;
	mp_mul(*this, other, result);
	return result;
}

BigNum BigNum::Sqr() const {
	BigNum result;
	mp_sqr(*this, result);
	return result;
}

BigNum BigNum::Divide(const BigNum &other) const {
	BigNum result;
	mp_div(*this, other, result, (mp_int *) NULL);
	return result;
}

BigNum BigNum::Modulo(const BigNum &other) const {
	BigNum result;
	mp_div(*this, other, (mp_int *) NULL, result);
	return result;
}

BigNum BigNum::InverseMod(const BigNum &m) const {
	BigNum result;
	mp_invmod(*this, m, result);
	return result;
}

BigNum& BigNum::MulBy(const BigNum &other) {
	mp_mul(*this, other, *this);
	return *this;
}

BigNum& BigNum::SqrInPlace() {
	mp_sqr(*this, *this);
	return *this;
}

BigNum& BigNum::DivideBy(const BigNum &other) {
	mp_div(*this, other, (mp_int *) NULL, *this);
	return *this;
}

BigNum& BigNum::ModuloBy(const BigNum &other) {
	mp_div(*this, other, *this, (mp_int *) NULL);
	return *this;
}

BigNum BigNum::MulMod(const BigNum &other, const BigNum &m) const {
	BigNum result;
	mp_mulmod(*this, other, m, result);
	return result;
}

BigNum& BigNum::MulByMod(const BigNum &other, const BigNum &m) {
	mp_mulmod(*this, other, m, *this);
	return *this;
}

BigNum BigNum::Power(mp_digit exp) const {
	BigNum result;
	mp_expt_d(*this, exp, result);
	return result;
}

BigNum BigNum::PowerMod(const BigNum &exp, const BigNum &m) const {
	BigNum result;
	mp_exptmod(*this, exp, m, result);
	return result;
}
