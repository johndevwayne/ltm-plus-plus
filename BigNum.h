/*
 *
 *  Created on: Dec 21, 2012
 *
 *  LICENSING: See LICENSE.txt or http://opensource.org/licenses/MIT
 */

#ifndef BIGNUM_H_
#define BIGNUM_H_

#include "tommath.h"

#include <string>
#include <iostream>
#include <ios>
#include <memory>
#include <vector>

/***
 *
 */
class BigNum
{
private:
    // Convenience typedefs

    typedef unsigned char byte;
    typedef std::vector<byte> bytevector;

	std::auto_ptr<mp_int> N;

	/*
	 * private sort-of copy constructor.
	 */
//	BigNum(const mp_int *NN) :
//			N(new mp_int)
//	{
//		mp_init_copy(*this, (mp_int *) NN);
//	}

	/*
	 * private constructor from serialized value
	 */

	BigNum(const bytevector &bin);

	// Not really const, but tommath is not const correct so we need this
	operator mp_int *() const {
		return N.get();
	}

	static const int NULLPTR = 0; // will be obsoleted by c+0011 nullptr

public:

	/*
	 * default constructor, creates a new BigNum representing 0.
	 */
	BigNum() :
			N(new mp_int)
	{
		mp_init(*this);
	}

	/*
	 * Copy constructor
	 */
	BigNum(const BigNum &other) :
			N(new mp_int)
	{
		mp_init_copy(*this, other.N.get());
	}

	/*
	 * Assignment overload
	 */
	BigNum& operator=(const BigNum &other)
	{
		mp_copy(other.N.get(), *this);
		return *this;
	}

	/*
	 * Constructs BigNum and initializes it to 'initialValue'.
	 * NOTE: this cannot be used to initialize the most negative integer
	 * of the type, typically a negative power of two.
	 */
	BigNum(long initialValue) :
			N(new mp_int)
	{
	    if (initialValue >= 0) {
	        mp_init_set_int(*this, initialValue);
	    } else {
	        mp_init_set_int(*this, -initialValue);
	        N->sign = MP_NEG;
	    }
	}

	/*
	 * Constructs BigNum and initializes it to the value represented
	 * by 'numstr', interpreted as a base 'radix' integer
	 */
	BigNum(const std::string numstr, int radix = 10) :
			N(new mp_int)
	{
		mp_init(*this);
		mp_read_radix(*this, numstr.c_str(), radix);
	}

	/*
	 * Constructs BigNum and initializes it to the value represented
	 * by 'numstr', interpreted as a base 'radix' integer
	 */
//	BigNum(const char *numstr, int radix = 10) :
//			N(new mp_int)
//	{
//		mp_init(*this);
//		mp_read_radix(*this, numstr, radix);
//	}

	std::string ToString(int radix = 10) const;

	// Serialize and DeSerialize methods
	int SerializedSize() const;
    bytevector Serialize() const;
    int Serialize(bytevector &buf) const;
	static BigNum DeSerialize(const bytevector &bin);

	// add / subtract operations

	// Returns *this + other
	BigNum Add(const BigNum &other) const;
	// Returns *this - other
	BigNum Subtract(const BigNum &other) const;

	BigNum AddMod(const BigNum &other, const BigNum &m) const;
	BigNum SubtractMod(const BigNum &other, const BigNum &m) const;

	// computes *this += other, returns reference to *this
	BigNum& AddTo(const BigNum &other);
	// computes *this -= other, returns reference to *this
	BigNum& SubtractFrom(const BigNum &other);

	BigNum& AddToMod(const BigNum &other, const BigNum &m);
	BigNum& SubtractFromMod(const BigNum &other, const BigNum &m);

	// Returns -*this
	BigNum Negate(const BigNum &other) const;
	// Returns abs(*this)
	BigNum Abs(const BigNum &other) const;

	BigNum& NegateInPlace();
	BigNum& AbsInPlace();

	// multiply / divide / modulo operations

	BigNum Mul(const BigNum &other) const;
	BigNum Sqr() const;
	BigNum Divide(const BigNum &other) const;
	BigNum Modulo(const BigNum &other) const;

	// computes q and r such that *this = q * other + r, 0<=r<other
	void DivideAndModulo(const BigNum &other, BigNum &quotient,
			BigNum &modulo) const;

	// *this *= other
	BigNum& MulBy(const BigNum &other);
	// *this *= *this
	BigNum& SqrInPlace();
	// *this /= other
	BigNum& DivideBy(const BigNum &other);
	// *this %= other
	BigNum& ModuloBy(const BigNum &other);

	// Return *this * other mod m
	BigNum MulMod(const BigNum &other, const BigNum &m) const;
	// Return x such that x * (*this) == 1 mod m.
	BigNum InverseMod(const BigNum &m) const;

	// *this = (*this) * other mod m.
	BigNum& MulByMod(const BigNum &other, const BigNum &m);

	// Higher-level ops

	// Returns (*this) ** exp
	BigNum Power(mp_digit exp) const;

	// Returns (*this) ** exp mod m
	BigNum PowerMod(const BigNum &exp, const BigNum &m) const;

	// gcd and lcm

	// returns gcd(*this, other)
	BigNum Gcd(const BigNum &other) const;
	BigNum Lcm(const BigNum &other) const;
	// Computes d = u * (*this) + v * other;
	// Returns d, and sets u and v.
	BigNum ExtendedGcd(const BigNum &other, BigNum &u, BigNum &v) const;

	// Encodings for interoperation with other implementations

	/**
	 * ToDER returns the DER encoding of an ASN1 Integer. The encoding is suitable
	 * for use in many standards, and is also the correct format for Java's
	 * BigInteger (byte []) constructor.
	 */
	bytevector ToDER() const;

	/*
	 * factory function that constructs a BigNum from an DER-encoded ASN1 integer.
	 */
	static BigNum FromDER(const bytevector &derEncodedInt);

    /**
     * ToDotNetBigInt returns the a byte array suitable for the
     * System.Numerics.BigInteger(byte [] value) constructor.
     * This is simply the DER encoding in reverse order, i.e. in
     * little-endian order.
     */
	bytevector ToDotNetBigInt() const;
    /*
     * factory function that constructs a BigNum from a byte array created by
     * System.Numerics.BigInteger.ToByteArray() method.
     */
    static BigNum FromDotNetBigInt(const bytevector &derEncodedInt);

	friend std::ostream& operator<<(std::ostream &out, const BigNum &bignum);

	// relational, tests

	bool IsNegative() const
	{
	    return N->sign;
	}

	bool IsNonNegative() const
	{
	    return ! IsNegative();
	}

	bool IsZero() const
	{
		return N->used == 0;
	}

	bool IsEven() const
	{
		return IsZero() || ((N->dp[0] & 1) == 0);
	}

	bool IsOdd() const
	{
		return (N->used > 0) && ((N->dp[0] & 1) == 1);
	}

    bool IsGreaterThan(const BigNum &other) const {
        return Cmp(other) > 0;
    }

    bool IsGreaterThanOrEqualTo(const BigNum &other) const {
        return Cmp(other) >= 0;
    }

    bool IsLessThan(const BigNum &other) const {
        return Cmp(other) < 0;
    }

    bool IsLessThanOrEqualTo(const BigNum &other) const {
        return Cmp(other) <= 0;
    }

    bool IsEqualTo(const BigNum &other) const {
        return Cmp(other) == 0;
    }

	int Cmp(const BigNum &other) const
	{
		return mp_cmp(*this, other);
	}

	// Convenient constants

    static const BigNum NEGATIVE_ONE;
	static const BigNum ZERO;
    static const BigNum ONE;
    static const BigNum TWO;
    static const BigNum TEN;

private:
	static void DoStaticInitialization();
};

#endif /* BIGNUM_H_ */
