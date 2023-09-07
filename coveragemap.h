#ifndef COVERAGEMAP_H
#define COVERAGEMAP_H

#include <QStringList>
#include <QVector>

class CoverageMap   // карта покрытия
{
public:
    CoverageMap();

    QStringList horizontalHeaders;  // значения функции
    QStringList verticalHeaders;    // значения склеек
    QVector<QVector<bool>> coating;    // карта покрытия (строим двумерный массив покрытия значений). Формат: row<col>
};

#endif // COVERAGEMAP_H
