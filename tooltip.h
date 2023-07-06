#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QString>
#include <QMap>

// автоматический define сплиттера, в зависимости от версии компилятора
// если не произошла проблема, исправь версию. Чтобы узнать версию используй QString::number(QT_VERSION, 16)
#if QT_VERSION >= 0x050f00 // версия Qt 5.15.0
#define SPLITTER Qt::SplitBehavior(Qt::SkipEmptyParts)
#else
#define SPLITTER QString::SkipEmptyParts
#endif

class tooltip
{
public:
    tooltip();

    enum messageid
    {
        StartMessage,
        addFunc2,
        proverkaTableOfTrue,

    };

};

#endif // TOOLTIP_H
