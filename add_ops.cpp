/*
 * add_ops.cpp
 *
 *  Created on: Dec 22, 2012
 *
 *  LICENSING: See LICENSE.txt or http://opensource.org/licenses/MIT
 */

#include "BigNum.h"

BigNum BigNum::Add(const BigNum &other) const {
	BigNum result;
	mp_add(*this, other, result);
	return result;
}

BigNum BigNum::Subtract(const BigNum &other) const {
	BigNum result;
	mp_sub(*this, other, result);
	return result;
}

BigNum BigNum::AddMod(const BigNum &other, const BigNum &m) const {
	BigNum result;
	mp_addmod(*this, other, m, result);
	return result;
}

BigNum BigNum::SubtractMod(const BigNum &other, const BigNum &m) const {
	BigNum result;
	mp_submod(*this, other, m, result);
	return result;
}

BigNum& BigNum::AddTo(const BigNum &other) {
	mp_add(*this, other, *this);
	return *this;
}

BigNum& BigNum::SubtractFrom(const BigNum &other) {
	mp_sub(*this, other, *this);
	return *this;
}

BigNum& BigNum::AddToMod(const BigNum &other, const BigNum &m) {
	mp_addmod(*this, other, m, *this);
	return *this;
}

BigNum& BigNum::SubtractFromMod(const BigNum &other, const BigNum &m) {
	mp_submod(*this, other, m, *this);
	return *this;
}

BigNum BigNum::Negate(const BigNum &other) const {
	BigNum result;
	mp_neg(other, result);
	return result;
}

BigNum BigNum::Abs(const BigNum &other) const {
	BigNum result;
	mp_abs(other, result);
	return result;
}

BigNum& BigNum::NegateInPlace() {
	mp_neg(*this, *this);
	return *this;
}\
BigNum& BigNum::AbsInPlace() {
	mp_abs(*this, *this);
	return *this;
}
