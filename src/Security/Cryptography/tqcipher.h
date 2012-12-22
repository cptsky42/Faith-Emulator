#ifndef _EOFEMU_TQCIPHER_H
#define _EOFEMU_TQCIPHER_H

#include "common.h"

class TqCipher
{
public:
    static const size_t IV_SIZE = 512;
    static const size_t KEY_SIZE = 512;

public:
    TqCipher();
    ~TqCipher();

public:
    void generateIV(int32_t aP, int32_t aG);
    void generateKey(int32_t aA, int32_t aB);

    void encrypt(uint8_t* aBuf, size_t aLen);
    void decrypt(uint8_t* aBuf, size_t aLen);

    void resetCounters();

private:
    uint16_t mEnCounter;
    uint16_t mDeCounter;

    uint8_t mIV[IV_SIZE];
    uint8_t mKey[KEY_SIZE];

    bool mUseKey;
};

#endif // _EOFEMU_TQCIPHER_H
