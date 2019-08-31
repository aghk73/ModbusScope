#ifndef GRAPHVIEWZOOM_H
#define GRAPHVIEWZOOM_H

#include <QObject>
#include "myqcustomplot.h"
#include "guimodel.h"

class GraphViewZoom : public QObject
{
    Q_OBJECT
public:
    explicit GraphViewZoom(GuiModel* pGuiModel, MyQCustomPlot* pPlot, QObject *parent = nullptr);
    virtual ~GraphViewZoom();

    bool handleMousePress(QMouseEvent *event);
    bool handleMouseRelease(QMouseEvent *event);
    bool handleMouseWheel();
    bool handleMouseMove(QMouseEvent *event);

private slots:
    void handleZoomStateChanged();

private:
    GuiModel* _pGuiModel;
    MyQCustomPlot* _pPlot;

    int _startX;
    int _startY;

};

#endif // GRAPHVIEWZOOM_H
