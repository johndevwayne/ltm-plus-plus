/*
 * BigNum_test.cpp
 *
 *  Created on: Dec 21, 2012
 *
 *  LICENSING: See LICENSE.txt or http://www.wtfpl.net/about/
 */

#include "BigNum.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string p1024 =
            "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE65381FFFFFFFFFFFFFFFF";
    BigNum p(p1024, 16);
    BigNum a(7);
    BigNum result = a.PowerMod(p.Subtract(BigNum::ONE), p);
    cout << result << endl;
    cout << BigNum::NEGATIVE_ONE << endl;
    cout << BigNum::ZERO << endl;
    cout << BigNum::ONE << endl;
    cout << BigNum::TWO << endl;
    cout << BigNum::TEN << endl;
    cout << BigNum::TEN.Add(BigNum::NEGATIVE_ONE) << endl;
}
