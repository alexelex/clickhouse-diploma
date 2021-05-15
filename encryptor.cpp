#include<cstring>
#include<memory>
#include<iostream>
#include<string>
#include<openssl/evp.h>

std::string EncryptNBytes(const char * data, size_t bytes, const char * iv, const char * key)
    {
        const EVP_CIPHER * evp_cipher = EVP_aes_128_ctr();
	    std::cout << "EncryptNBytes " << bytes << '\n';
	    std::string ciphertext(bytes, '0');
        char * ciphertext_ref = ciphertext.data();

        auto evp_ctx_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
        auto * evp_ctx = evp_ctx_ptr.get();

        if (EVP_EncryptInit_ex(evp_ctx, evp_cipher, nullptr, nullptr, nullptr) != 1)
            return "Failed to initialize encryption context with cipher";

        if (EVP_EncryptInit_ex(evp_ctx, nullptr, nullptr,
            reinterpret_cast<const unsigned char*>(key),
            reinterpret_cast<const unsigned char*>(iv)) != 1)
            return "Failed to set key and IV";

        int output_len = 0;
        if (EVP_EncryptUpdate(evp_ctx,
            reinterpret_cast<unsigned char*>(ciphertext_ref), &output_len,
            reinterpret_cast<const unsigned char*>(data), static_cast<int>(bytes)) != 1)
            return "Failed to encrypt";

        ciphertext_ref += output_len;
        std::cout << ciphertext << " " << output_len << "\n";

        int final_output_len = 0;
        if (EVP_EncryptFinal_ex(evp_ctx,
            reinterpret_cast<unsigned char*>(ciphertext_ref), &final_output_len) != 1)
	    return "Failed to fetch ciphertext";
	    std::cout << ciphertext << " " << final_output_len << "\n";
        return ciphertext;
    }

int main() {
    std::string data = "SomeStringToEncr";
    std::string data2 = data + data;
    size_t block_size = 16;
    std::string key = "1234567812345678";
    std::string iv(block_size, '\0');

    {
        std::cout << "Encryp data, iv = 00...00\n";
        auto res = EncryptNBytes(data.data(), data.size(), iv.data(), key.data());
        std::cout << "Encryp datadata, iv = 00...00\n";
        auto res2 = EncryptNBytes(data2.data(), data.size(), iv.data(), key.data());
        assert(res1 == res2.substr(0, res1.size());
    }

    std::string iv2(block_size, '\0');
    iv2[block_size - 1] = '\1';
    {
        std::cout << "Encryp data, iv = 00...01\n";
        auto res = EncryptNBytes(data.data(), data.size(), iv2.data(), key.data());
        std::cout << "Encryp datadata, iv = 00...01\n";
        auto res2 = EncryptNBytes(data2.data(), data.size(), iv2.data(), key.data());
        assert(res1 == res2.substr(0, res1.size());
    }

    std::string data3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    std::cout << "Encryp equal chars, iv = 00...00\n";
    auto res1 = EncryptNBytes(data3.data(), data3.size(), iv.data(), key.data());
    std::cout << "Encryp equal chars, iv = 00...01\n";
    auto res2 = EncryptNBytes(data3.data(), data3.size(), iv2.data(), key.data());
    std::cout << "data was encryted with an CTR mode block size offset. Let's find it\n";

    std::cout << res1 << '\n';
    std::cout << res2 << '\n';

    size_t block = 8;
    std::cout << "Let's check at least " << block << " bytes \n";

    auto str = res2.substr(0, block);
    for (size_t i = 0; i != data3.size() - block; ++i)
    {
        auto local = res1.substr(i, block);
    	if (local == str)
        {
            assert(res1.substr(i, i) == res2.substr(0, i));
	        std::cout << "offset = block size = " << i << '\n';
	    }
    }

    uint64_t counter = 'A';
    size_t offset = 3;
    bool is_little_endian = false;
    std::memcpy(iv.data() + offset, &counter, sizeof(counter));

    for (size_t i = 0; i != iv.size(); ++i) {
    	std::cout << i << " index of " << iv[i] << '\n';
        if (iv[i] == counter && i == offset)
            is_little_endian = true;
    }

    if (is_little_endian)
        std::cout << "Little endian copy from uint64_t\n";
    else
        std::cout << "Big endian copy from uint64_t\n";
}
