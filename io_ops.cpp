/*
 * io_ops.cpp
 *
 *  Created on: Dec 22, 2012
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 */

#include "BigNum.h"

using std::ostream;
ostream& operator<<(ostream &out, const BigNum &bn) {
	out << bn.ToString(10);
	return out;
}



