
#ifndef TEST_GRAPHDATAHANDLER_H__
#define TEST_GRAPHDATAHANDLER_H__

#include <QObject>

#include "settingsmodel.h"
#include "result.h"

/* Forward declaration */
class GraphDataModel;

class TestGraphDataHandler: public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void registerList();
    void manyInactiveRegisters();

    void graphData();
    void graphDataTwice();
    void graphData_fail();

private:

    void doHandleRegisterData(QList<Result<qint64> >& modbusResults, QList<QVariant> &actRawData);

    SettingsModel* _pSettingsModel;
    GraphDataModel* _pGraphDataModel;

};

#endif /* TEST_GRAPHDATAHANDLER_H__ */
