#include "mmkdata.h"

MmkData::MmkData()
{

}

const QString &MmkData::getFunc16() const
{
    return func16;
}

void MmkData::setFunc16(const QString &newFunc16)
{
    func16 = newFunc16;
}

const QString &MmkData::getFunc2() const
{
    return func2;
}

void MmkData::setFunc2(const QString &newFunc2)
{
    func2 = newFunc2;
}

const QStringList &MmkData::getTruthTable() const
{
    return truthTable;
}

void MmkData::setTruthTable(const QStringList &newTruthTable)
{
    truthTable = newTruthTable;
}

const QStringList &MmkData::getValuesTable() const
{
    return valuesTable;
}

void MmkData::setValuesTable(const QStringList &newValuesTable)
{
    valuesTable = newValuesTable;
}

const QList<QStringList> &MmkData::getGlueList() const
{
    return glueList;
}

void MmkData::setGlueList(const QList<QStringList> &newGlueList)
{
    glueList = newGlueList;
}

const MmkData::CoverageMap &MmkData::getCoverageMap() const
{
    return coverageMap;
}

void MmkData::setCoverageMap(const MmkData::CoverageMap &newCoverageMap)
{
    coverageMap = newCoverageMap;
}

const QStringList &MmkData::getCoreDnf() const
{
    return coreDnf;
}

void MmkData::setCoreDnf(const QStringList &newCoreDnf)
{
    coreDnf = newCoreDnf;
}

const QList<QStringList> &MmkData::getVariativePart() const
{
    return variativePart;
}

void MmkData::setVariativePart(const QList<QStringList> &newVariativePart)
{
    variativePart = newVariativePart;
}
