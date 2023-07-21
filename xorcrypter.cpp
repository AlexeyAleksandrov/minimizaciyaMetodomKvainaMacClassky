#include "xorcrypter.h"

XORCrypter::XORCrypter()
{

}

const QByteArray &XORCrypter::getKey() const
{
    return key;
}

void XORCrypter::setKey(const QByteArray &newKey)
{
    key = newKey;
}

void XORCrypter::writeEncryptenFile(QFile &encryptedFile, const QByteArray &text, const QByteArray& key, bool *ok)
{
    QByteArray encryptedText = xorEncryptDecrypt(text, key);

    // Запись зашифрованного текста в файл
    bool writed = encryptedFile.open(QIODevice::WriteOnly);
    encryptedFile.write(encryptedText);
    encryptedFile.close();

    if(ok != nullptr)
    {
        *ok = writed;
    }
}

void XORCrypter::writeEncryptenFile(QFile &encryptedFile, const QByteArray &text, bool *ok)
{
    writeEncryptenFile(encryptedFile, text, this->key, ok);
}

QByteArray XORCrypter::readEncryptenFile(QFile &file, const QByteArray& key, bool *ok)
{
    // Чтение зашифрованного текста из файла
    bool readed = file.open(QIODevice::ReadOnly);
    QByteArray encryptedData = file.readAll();
    file.close();

    QByteArray decryptedText = xorEncryptDecrypt(encryptedData, key);

    if(ok != nullptr)
    {
        *ok = readed;
    }

    return decryptedText;
}

QByteArray XORCrypter::readEncryptenFile(QFile &file, bool *ok)
{
    return readEncryptenFile(file, this->key, ok);
}

// функция для шифрования/расшифрования текста с использованием операции XOR
QByteArray XORCrypter::xorEncryptDecrypt(const QByteArray& text, const QByteArray& key)
{
    QByteArray result;
    int keyLength = key.length();

    for (int i = 0; i < text.length(); ++i)
    {
        result.append(text.at(i) ^ key.at(i % keyLength));
    }

    return result;
}

QByteArray XORCrypter::xorEncryptDecrypt(const QByteArray &text)
{
    return xorEncryptDecrypt(text, this->key);
}
