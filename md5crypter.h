#ifndef MD5CRYPTER_H
#define MD5CRYPTER_H

#include <QString>
#include <QStringList>
#include <QCryptographicHash>
#include <QDebug>

#define HASH_TAG "HASH="    // тег хеша в строке
#define XOR_VALUE 0x5555      // XOR символа

class md5crypter
{
public:
    md5crypter() {}

    // добавление хеша
    static QString crypt(QString sourcetext, bool useXor = false) // возвращает текст с добавленным в него хешем
    {
        QString outputtext = sourcetext;
        QString hash = QString(QCryptographicHash::hash(sourcetext.toLatin1(),QCryptographicHash::Md5).toHex()); // получаем хэш
        outputtext = sourcetext; // записываем исходный текст
        outputtext.append(HASH_TAG); // добавляем тэг хеш
        outputtext.append(hash); // добавляем сам хеш

        // шифрование
        if(useXor)
        {
            outputtext = xorStr(outputtext);
            qDebug() << "Зашифрован через XOR";
        }

        return outputtext;
    };

    inline static void cryptStr(QString &sourcetext, bool useXor = false) // добавление хеша в строку
    {
        sourcetext = crypt(sourcetext, useXor);
    };

    // извлечение хеша
    static QString decrypt(QString cryptedtext, bool &ok, bool useXor = false) // возвращает текст без хеша, проверяя корректность
    {
        // расшифрование
        if(useXor)
        {
           cryptedtext = xorStr(cryptedtext);
           qDebug() << "Расшифрован через XOR";
           qDebug() << "Результат расшифровки: " + cryptedtext;
        }

        if(!cryptedtext.contains(HASH_TAG)) // если строка не содержит тега хеша
        {
            ok = false;
            return cryptedtext;
        }
        QStringList fileHexList = cryptedtext.split(HASH_TAG); // разбиваем на до и после хэша
        if(fileHexList.size() != 2) // если не получилось разбить
        {
            ok = false;
            return cryptedtext;
        }
        QString hashFromFile = fileHexList.at(1); // получаем хэш из файла
        QString hash = QString(QCryptographicHash::hash(fileHexList.at(0).toLatin1(),QCryptographicHash::Md5).toHex()); // получаем хэш содержимого
        if(hashFromFile != hash) // если хеши различаются
        {
            ok = false;
            return cryptedtext;
        }
        QString outputtext = fileHexList.at(0); // возвращаем всё, что до хеша
        ok = true;
        return outputtext;
    };

    inline static void decryptStr(QString &sourcetext, bool &ok, bool useXor = false) // просто вытащить хеш из строки и проверить его правильность
    {
        sourcetext = decrypt(sourcetext, ok, useXor);
    };

    static QString xorStr(QString str)     // шифрование/расшифрование через XOR
    {
//        int size = str.size();
//        const char *data = str.toStdString().c_str();
//        QString result;

//        for(int i=0; i<size; i++)
//        {
//            result.append((char)((unsigned short)data[i] + (unsigned short)XOR_VALUE));     // добавляем символ с XOR
//        }

//        return result;
        return str;

//        QString encryptionKey = "secretkey";
//        return encryptDecrypt(str, encryptionKey);
    }

    static QString encryptDecrypt(const QString& input, const QString& key)
    {
        QString output;
        for (int i = 0; i < input.size(); ++i)
        {
            output += input.at(i).unicode() ^ key.at(i % key.size()).unicode();
        }
        return output;
    }
};


#endif // MD5CRYPTER_H
