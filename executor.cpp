#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cstring>
#include<memory>
#include<iostream>
#include<fstream>
#include<string>
#include<openssl/evp.h>
#include<limits>
#include<cmath>


// copy from encryptor.cpp
std::string EncryptNBytes(const char * data, size_t bytes, const char * iv, const char * key)
{
    const EVP_CIPHER * evp_cipher = EVP_aes_128_ctr();
    std::cout << "EncryptNBytes " << bytes << '\n';
    std::string ciphertext(bytes, '0');
    char * ciphertext_ref = ciphertext.data();

    auto evp_ctx_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
    auto * evp_ctx = evp_ctx_ptr.get();

    if (EVP_EncryptInit_ex(evp_ctx, evp_cipher, nullptr, nullptr, nullptr) != 1)
        std::cerr << "Failed to initialize encryption context with cipher";

    if (EVP_EncryptInit_ex(evp_ctx, nullptr, nullptr,
        reinterpret_cast<const unsigned char*>(key),
        reinterpret_cast<const unsigned char*>(iv)) != 1)
        std::cerr << "Failed to set key and IV";

    int output_len = 0;
    if (EVP_EncryptUpdate(evp_ctx,
        reinterpret_cast<unsigned char*>(ciphertext_ref), &output_len,
        reinterpret_cast<const unsigned char*>(data), static_cast<int>(bytes)) != 1)
        std::cerr << "Failed to encrypt";

    ciphertext_ref += output_len;

    // for small parts you can compare them in hex format
    if (output_len < 20)
    {
        std::cout << ciphertext << " " << output_len << "\n";
        for (auto i : ciphertext)
            std::printf("%02x ", i & 0xff);
        std::cout << '\n';
    }
    else
        std::cout << output_len << '\n';

    int final_output_len = 0;
    if (EVP_EncryptFinal_ex(evp_ctx,
        reinterpret_cast<unsigned char*>(ciphertext_ref), &final_output_len) != 1)
        std::cerr << "Failed to fetch ciphertext";

    // ciphertext.substr(output_len) must be empty, just in case
    std::cout << ciphertext.substr(output_len) << " " << final_output_len << "\n";

    assert(output_len + final_output_len == bytes);

    // for aes-ctr in openssl get_block_size returns 1, but actually block_size == 16
    // therefore, final_ex always does nothing

    assert(final_output_len == 0);
    return ciphertext;
}

std::string DecryptNBytes(const char * data, size_t bytes, const char * iv, const char * key)
{
    const EVP_CIPHER * evp_cipher = EVP_aes_128_ctr();
    std::cout << "DecryptNBytes " << bytes << '\n';
    std::string plaintext(bytes, '0');
    char * plaintext_ref = plaintext.data();

    auto evp_ctx_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
    auto * evp_ctx = evp_ctx_ptr.get();

    if (EVP_DecryptInit_ex(evp_ctx, evp_cipher, nullptr, nullptr, nullptr) != 1)
        std::cerr << "Failed to initialize decryption context with cipher";

    if (EVP_DecryptInit_ex(evp_ctx, nullptr, nullptr,
        reinterpret_cast<const unsigned char*>(key),
        reinterpret_cast<const unsigned char*>(iv)) != 1)
        std::cerr << "Failed to set key and IV";

    int output_len = 0;
    if (EVP_DecryptUpdate(evp_ctx,
        reinterpret_cast<unsigned char*>(plaintext_ref), &output_len,
        reinterpret_cast<const unsigned char*>(data), static_cast<int>(bytes)) != 1)
        std::cerr << "Failed to decrypt";

    plaintext_ref += output_len;
    if (output_len < 20)
    {
            std::cout << plaintext << " " << output_len << "\n";
            for (auto i : plaintext)
                std::printf("%02x ", i & 0xff);
            std::cout << '\n';
    }
    else
        std::cout << output_len << '\n';

    int final_output_len = 0;
    if (EVP_DecryptFinal_ex(evp_ctx,
        reinterpret_cast<unsigned char*>(plaintext_ref), &final_output_len) != 1)
        std::cerr << "Failed to fetch plaintext";

    // ciphertext.substr(output_len) must be empty, just in case
    std::cout << plaintext.substr(output_len) << " " << final_output_len << "\n";

    assert(output_len + final_output_len == bytes);

    // for aes-ctr in openssl get_block_size returns 1, but actually block_size == 16
    // therefore, final_ex always does nothing

    assert(final_output_len == 0);
    return plaintext;
}


auto getFunction(const char* type)
{
    if (*type == 'e')
        return EncryptNBytes;
    return DecryptNBytes;
}

void BigEndianCopy(char * to, uint64_t value)
{
    size_t dev = std::pow(2, CHAR_BIT);
    size_t size = sizeof(value);
    for (size_t i = 0; i != size; ++i)
    {
        to[size - i - 1] = value % dev;
        value /= dev;
    }
}


// execute e/d filename key file_for_init_iv output_file
// example: ./a.out e file keykey file 8 out

int main(int argc, char * argv[]) {
    if (argc < 2)
    {
        std::cout << "empty input\n";
    std::cout << "usage:  execute e/d filename key file_for_init_iv output_file\n";
        return 1;
    }

    auto func = getFunction(argv[1]);

    std::string key = "1234567812345678";
    std::ifstream iv_in(argv[4], std::ios::binary);

    int offset, iv_size = 8;
    std::cout << "INIT offset counter size\n";

    std::cin >> offset;

    std::ifstream in(argv[2], std::ios::binary);
    std::string data((std::istreambuf_iterator<char>(in)),
                     std::istreambuf_iterator<char>());

    if (offset)
    {
        std::string temp(offset, '\0');
        data.insert(0, temp);
    }

    std::string iv(16, '\0');
    iv_in.read(iv.data(), iv_size);
    for (auto i : iv)
        std::printf("%02x ", i & 0xff);
    std::cout << '\n';

    for (auto i : key)
        std::printf("%02x ", i & 0xff);
    std::cout << '\n';

    uint64_t counter;
    std::cin >> counter;

    if (counter)
        BigEndianCopy(iv.data() + iv_size, counter);

    for (auto i : iv)
        std::printf("%02x ", i & 0xff);
    std::cout << '\n';

    int size;
    std::cin >> size;
    if (size <= 0)
        size = data.size();

    std::ofstream out(argv[5]);
    auto res = func(data.data(), size, iv.data(), key.data());
    if (offset)
        res = res.substr(offset);
    out << res;
}
