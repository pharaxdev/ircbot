//#include <stdarg.h>
#include <openssl/sha.h>
#include "stdafx.h"

#ifndef _SHA1_H
#define _SHA1_H
class Sha1Hash
{
public:
        Sha1Hash();
        ~Sha1Hash();

        void UpdateData(const unsigned char *data, int len);
        void UpdateData(const std::string &text);

        void Initialize();
        void Finalize();

        unsigned char *getDigest(void) { return Digest; };
        int GetLength(void) { return SHA_DIGEST_LENGTH; };

private:
        SHA_CTX myChar;
        unsigned char Digest[SHA_DIGEST_LENGTH];
};

std::string sha1(const std::string text);
#endif
