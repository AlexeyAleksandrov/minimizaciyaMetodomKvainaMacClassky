#ifndef MMKDATA_H
#define MMKDATA_H

#include <QString>
#include <QStringList>

// класс представляющий собой информацию о минимизации
class MmkData
{
public:
    MmkData();

public:
    struct CoverageMap      // карта покрытия
    {
        QStringList horizontalHeaders;  // значения функции
        QStringList verticalHeaders;    // значения склеек
        QVector<QVector<bool>> coating;    // карта покрытия (строим двумерный массив покрытия значений)
    };

    const QString &getFunc16() const;
    void setFunc16(const QString &newFunc16);
    const QString &getFunc2() const;
    void setFunc2(const QString &newFunc2);
    const QStringList &getTruthTable() const;
    void setTruthTable(const QStringList &newTruthTable);
    const QStringList &getValuesTable() const;
    void setValuesTable(const QStringList &newValuesTable);
    const QList<QStringList> &getGlueList() const;
    void setGlueList(const QList<QStringList> &newGlueList);
    const CoverageMap &getCoverageMap() const;
    void setCoverageMap(const CoverageMap &newCoverageMap);
    const QStringList &getCoreDnf() const;
    void setCoreDnf(const QStringList &newCoreDnf);
    const QList<QStringList> &getVariativePart() const;
    void setVariativePart(const QList<QStringList> &newVariativePart);

private:
    QString func16;     // функция в 16й ССЧ
    QString func2;      // функция в 2й ССЧ
    QStringList truthTable;     // таблица истинности
    QStringList valuesTable;    //таблица значений (для формирования МДНФ/МКНФ)
    QList<QStringList> glueList;    // список склеек
    CoverageMap coverageMap;        // карта покрытия
    QStringList coreDnf;     // значения, формирующие ядровую ДНФ
    QList<QStringList> variativePart;   // возможные наборы значений вариативной части (без ядровой)
};

#endif // MMKDATA_H
