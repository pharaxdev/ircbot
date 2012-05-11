#include "sha1.h"
Sha1Hash::Sha1Hash()
{
        SHA1_Init(&myChar);
}

Sha1Hash::~Sha1Hash()
{

}

void Sha1Hash::UpdateData(const unsigned char *data, int len)
{
        SHA1_Update(&myChar, data, len);
}

void Sha1Hash::UpdateData(const std::string &text)
{
        UpdateData((unsigned char *)text.c_str(), (int)text.length());
}

void Sha1Hash::Initialize()
{
        SHA1_Init(&myChar);
}

void Sha1Hash::Finalize(void)
{
        SHA1_Final(Digest, &myChar);
}

std::string sha1(const std::string text)
{
	
	unsigned char* data = new unsigned char[SHA_DIGEST_LENGTH+1];
	Sha1Hash sha1;
	sha1.Initialize();
	sha1.UpdateData(text);
	sha1.Finalize();
	memcpy(data, sha1.getDigest(), SHA_DIGEST_LENGTH);
	std::stringstream ss;
	size_t len = strlen((const char*)data);
	for (size_t u = 0; u< len; ++u)
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[u]);
	std::string hash;
	ss >> hash;
	delete data;
	return hash;
}