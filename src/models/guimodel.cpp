#include <QColor>
#include "util.h"
#include "guimodel.h"


const QString GuiModel::_cWindowTitle = QString("ModbusScope");

GuiModel::GuiModel(QObject *parent) : QObject(parent)
{
    _frontGraph = 0;
    _projectFilePath = "";
    _dataFilePath = "";
    _bHighlightSamples = true;
    _bValueTooltip = false;
    _bLegendVisibility = false;
    _legendPosition = BasicGraphView::LEGEND_MIDDLE;
    _guiState = INIT;
    _windowTitle = _cWindowTitle;

    _startTime = 0;
    _endTime = 0;
    _successCount = 0;
    _errorCount = 0;

    QStringList docPath = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    if (docPath.size() > 0)
    {
        _lastDir = docPath[0];
    }

    _guiSettings.xScaleMode = BasicGraphView::SCALE_AUTO;
    _guiSettings.yScaleMode = BasicGraphView::SCALE_AUTO;
    _guiSettings.yMax = 10;
    _guiSettings.yMin = 0;
    _guiSettings.xslidingInterval = 30;    
}

GuiModel::~GuiModel()
{

}

void GuiModel::triggerUpdate(void)
{
    emit frontGraphChanged();
    emit highlightSamplesChanged();
    emit valueTooltipChanged();
    emit windowTitleChanged();
    emit communicationStatsChanged();

    emit legendVisibilityChanged();
    emit legendPositionChanged();

    emit yAxisMinMaxchanged();
    emit xAxisSlidingIntervalChanged();

    emit xAxisScalingChanged();
    emit yAxisScalingChanged();

    emit guiStateChanged();
    emit projectFilePathChanged();
    emit dataFilePathChanged();
}

/*
 Return index of activeGraphList */
qint32 GuiModel::frontGraph() const
{
    return _frontGraph;
}

void GuiModel::setFrontGraph(const qint32 &frontGraph)
{
    if (_frontGraph != frontGraph)
    {
        _frontGraph = frontGraph;

        if (frontGraph != -1)
        {
            emit frontGraphChanged();
        }
    }
}

bool GuiModel::highlightSamples() const
{
    return _bHighlightSamples;
}

void GuiModel::setHighlightSamples(bool bHighlightSamples)
{
    if (_bHighlightSamples != bHighlightSamples)
    {
        _bHighlightSamples = bHighlightSamples;
         emit highlightSamplesChanged();
    }
}

bool GuiModel::valueTooltip() const
{
    return _bValueTooltip;
}

void GuiModel::setValueTooltip(bool bValueTooltip)
{
    if (_bValueTooltip != bValueTooltip)
    {
        _bValueTooltip = bValueTooltip;
         emit valueTooltipChanged();
    }
}

QString GuiModel::windowTitle()
{
    return _windowTitle;
}

void GuiModel::setWindowTitleDetail(QString detail)
{
    QString tmpTitle;
    if (detail == "")
    {
        tmpTitle = _cWindowTitle;
    }
    else
    {
        tmpTitle = QString(tr("%1 - %2")).arg(_cWindowTitle).arg(detail);
    }

    if (tmpTitle != _windowTitle)
    {
        _windowTitle = tmpTitle;
        emit windowTitleChanged();
    }
}

bool GuiModel::legendVisibility()
{
    return _bLegendVisibility;
}

void GuiModel::setLegendVisibility(bool bLegendVisibility)
{
    if (_bLegendVisibility != bLegendVisibility)
    {
        _bLegendVisibility = bLegendVisibility;
         emit legendVisibilityChanged();
    }
}

BasicGraphView::LegendsPositionOptions GuiModel::legendPosition()
{
    return _legendPosition;
}

void GuiModel::setLegendPosition(BasicGraphView::LegendsPositionOptions pos)
{
    if (_legendPosition != pos)
    {
        _legendPosition = pos;
         emit legendPositionChanged();
    }
}

QString GuiModel::projectFilePath()
{
    return _projectFilePath;
}

QString GuiModel::dataFilePath()
{
    return _dataFilePath;
}

void GuiModel::setProjectFilePath(QString path)
{
    if (_projectFilePath != path)
    {
        _projectFilePath = path;
        emit projectFilePathChanged();
    }
}

void GuiModel::setDataFilePath(QString path)
{
    if (_dataFilePath != path)
    {   
        _dataFilePath = path;
        emit dataFilePathChanged();
    }
}

void GuiModel::setLastDir(QString dir)
{
    _lastDir = dir;
}

QString GuiModel::lastDir()
{
    return _lastDir;
}

void GuiModel::setxAxisScale(BasicGraphView::AxisScaleOptions scaleMode)
{
    if (_guiSettings.xScaleMode != scaleMode)
    {
        _guiSettings.xScaleMode = scaleMode;
        emit xAxisScalingChanged();
    }
}

BasicGraphView::AxisScaleOptions GuiModel::xAxisScalingMode()
{
    return _guiSettings.xScaleMode;
}

void GuiModel::setxAxisSlidingInterval(qint32 slidingSec)
{
    if (_guiSettings.xslidingInterval != (quint32)slidingSec)
    {
        _guiSettings.xslidingInterval = (quint32)slidingSec;
        emit xAxisSlidingIntervalChanged();
    }

}

quint32 GuiModel::xAxisSlidingSec()
{
    return _guiSettings.xslidingInterval;
}

BasicGraphView::AxisScaleOptions GuiModel::yAxisScalingMode()
{
    return _guiSettings.yScaleMode;
}

void GuiModel::setyAxisScale(BasicGraphView::AxisScaleOptions scaleMode)
{
    if (_guiSettings.yScaleMode != scaleMode)
    {
        _guiSettings.yScaleMode = scaleMode;
        emit yAxisScalingChanged();
    }
}

void GuiModel::setyAxisMin(qint32 newMin)
{
    const qint32 diff = _guiSettings.yMax - _guiSettings.yMin;
    qint32 newMax = _guiSettings.yMax;

    if (newMin >= _guiSettings.yMax)
    {
        newMax = newMin + diff;
    }

    if (_guiSettings.yMin != newMin)
    {
        _guiSettings.yMin = newMin;
        setyAxisMax(newMax);
        emit yAxisMinMaxchanged();
    }
}

void GuiModel::setyAxisMax(qint32 newMax)
{
    const qint32 diff = _guiSettings.yMax - _guiSettings.yMin;

    qint32 newMin = _guiSettings.yMin;

    if (newMax <= _guiSettings.yMin)
    {
        newMin = newMax - diff;
    }

    if (_guiSettings.yMax != newMax)
    {
        _guiSettings.yMax = newMax;
        setyAxisMin(newMin);
        emit yAxisMinMaxchanged();
    }
}

void GuiModel::setGuiState(quint32 state)
{
    if (_guiState != state)
    {
        _guiState = state;
        emit guiStateChanged();
    }
}

quint32 GuiModel::guiState()
{
    return _guiState;
}

qint64 GuiModel::communicationStartTime()
{
    return _startTime;
}

void GuiModel::setCommunicationStartTime(qint64 startTime)
{
    if (_startTime != startTime)
    {
        _startTime = startTime;
        // No signal yet
    }
}

qint64 GuiModel::communicationEndTime()
{
    return _endTime;
}

void GuiModel::setCommunicationEndTime(qint64 endTime)
{
    if (_endTime != endTime)
    {
        _endTime = endTime;
        // No signal yet
    }
}

quint32 GuiModel::communicationErrorCount()
{
    return _errorCount;
}

quint32 GuiModel::communicationSuccessCount()
{
    return _successCount;
}

double GuiModel::startMarkerPos()
{
    return _startMarkerPos;
}

double GuiModel::endMarkerPos()
{
    return _endMarkerPos;
}

void GuiModel::setCommunicationStats(quint32 successCount, quint32 errorCount)
{
    if (
        (_successCount != successCount)
        || (_errorCount != errorCount)
        )
    {
        _successCount = successCount;
        _errorCount = errorCount;
        emit communicationStatsChanged();
    }
}

void GuiModel::clearMarkersState(void)
{
    if (_bStartMarkerState || _bEndMarkerState)
    {
        _bStartMarkerState = false;
        _bEndMarkerState = false;

        emit markerStateCleared();
    }
}

void GuiModel::setStartMarkerPos(double pos)
{
    if (
            (_startMarkerPos != pos)
            || (!_bStartMarkerState)
        )
    {
        if (pos != _endMarkerPos)
        {
            _bStartMarkerState = true;
            _startMarkerPos = pos;

            emit startMarkerPosChanged();
        }
    }
}

void GuiModel::setEndMarkerPos(double pos)
{
    if (
            (_endMarkerPos != pos)
            || (!_bEndMarkerState)
        )
    {
        if (pos != _startMarkerPos)
        {
            _bEndMarkerState = true;
            _endMarkerPos = pos;

            emit endMarkerPosChanged();
        }
    }
}

qint32 GuiModel::yAxisMin()
{
    return _guiSettings.yMin;
}

qint32 GuiModel::yAxisMax()
{
    return _guiSettings.yMax;
}
