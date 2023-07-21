#ifndef XORCRYPTER_H
#define XORCRYPTER_H

#include <QByteArray>
#include <QFile>

class XORCrypter
{
public:
    XORCrypter();

    const QByteArray &getKey() const;
    void setKey(const QByteArray &newKey);

    void writeEncryptenFile(QFile &encryptedFile, const QByteArray &text, const QByteArray& key, bool *ok = nullptr);   // записать зашифрованный файл
    void writeEncryptenFile(QFile &encryptedFile, const QByteArray &text, bool *ok = nullptr);   // записать зашифрованный файл

    QByteArray readEncryptenFile(QFile &file, const QByteArray &key, bool *ok = nullptr);      // прочитать зашифрованный файл
    QByteArray readEncryptenFile(QFile &file, bool *ok = nullptr);      // прочитать зашифрованный файл

    QByteArray xorEncryptDecrypt(const QByteArray &text, const QByteArray &key);    // функция для шифрования/расшифрования текста с использованием операции XOR
    QByteArray xorEncryptDecrypt(const QByteArray &text);   // функция для шифрования/расшифрования текста с использованием операции XOR

private:
    QByteArray key = "0123456789";      // ключ шифрования
};

#endif // XORCRYPTER_H
