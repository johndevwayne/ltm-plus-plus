/*
 * serial_ops.cpp
 *
 *  Created on: Dec 24, 2012
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 */

#include "BigNum.h"
#include <memory>
#include <algorithm>

int BigNum::SerializedSize() const
{
	return mp_signed_bin_size(*this);
}

std::vector<unsigned char> BigNum::Serialize() const {
	std::vector<unsigned char> result;
	Serialize(result);
	return result;
}

int BigNum::Serialize(std::vector<unsigned char> &buf) const {
    int bytesNeeded = SerializedSize();
    int oldLast = buf.size();
    buf.resize(buf.size() + bytesNeeded);
    mp_to_signed_bin(*this, &buf[oldLast]);
    return bytesNeeded;
}

BigNum BigNum::DeSerialize(const std::vector<unsigned char> &bin) {
	return BigNum(bin);
}
