#include "registermodel.h"

#include "QDebug"

RegisterModel::RegisterModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    dataList.clear();

    // TODO: this is dummy data
    RegisterData data;
    data.bActive = true;
    data.reg = 40001;
    data.text = "Register 1";
    dataList.append(data);

    data.reg = 40002;
    data.bActive = false;
    data.text = "Register 2";
    dataList.append(data);

    data.reg = 40003;
    data.bActive = false;
    data.text = "Register 3";
    dataList.append(data);
}

int RegisterModel::rowCount(const QModelIndex & /*parent*/) const
{
    return dataList.size();
}

int RegisterModel::columnCount(const QModelIndex & /*parent*/) const
{
    /*
    * bActive
    * Register
    * Text
    * */
    return 3; // Number of visible members of struct
}

QVariant RegisterModel::data(const QModelIndex &index, int role) const
{

    switch (index.column())
    {
    case 0:
        if (role == Qt::CheckStateRole)
        {
            if (dataList[index.row()].bActive)
            {
                return Qt::Checked;
            }
            else
            {
                return Qt::Unchecked;
            }
        }
        break;
    case 1:
        if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
        {
            return dataList[index.row()].reg;
        }
        break;
    case 2:
        if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
        {
            return dataList[index.row()].text;
        }
        break;
    default:
        return QVariant();
        break;

    }

    return QVariant();
}

QVariant RegisterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Active");
            case 1:
                return QString("Register");
            case 2:
                return QString("Text");
            default:
                return QVariant();
            }
        }
        else
        {
            //Can't happen because it is hidden
        }
    }

    return QVariant();
}


bool RegisterModel::setData(const QModelIndex & index, const QVariant & value, int role)
{

    switch (index.column())
    {
    case 0:
        if (role == Qt::CheckStateRole)
        {
            if (value == Qt::Checked)
            {
                dataList[index.row()].bActive = true;
            }
            else
            {
                dataList[index.row()].bActive = false;
            }
        }
        break;
    case 1:
        if (role == Qt::EditRole)
        {
            // TODO: check and parse data
            dataList[index.row()].reg = value.toInt();
        }
        break;
    case 2:
        if (role == Qt::EditRole)
        {
            // TODO: check and parse data
            dataList[index.row()].text = value.toString();
        }
        break;
    default:
        break;

    }

    /* TODO: Return only true is succeeded */
    return true;
}

Qt::ItemFlags RegisterModel::flags(const QModelIndex & index) const
{
    if (index.column() == 0)
    {
        // checkable
        return Qt::ItemIsSelectable |  Qt::ItemIsUserCheckable | Qt::ItemIsEnabled ;
    }
    else
    {
        return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
    }

}


bool RegisterModel::removeRows (int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (qint32 i = 0; i < count; i++)
    {
        Q_UNUSED(i);
        if (row < dataList.size())
        {
            dataList.removeAt(row);
        }
    }
    endRemoveRows();

    return true;
}

bool RegisterModel::insertRows (int row, int count, const QModelIndex &parent)
{

    if (
        (count != 1)
        || (row != dataList.size())
        )
    {
        qDebug() << "RegisterModel: Not supported";
    }

    Q_UNUSED(row);
    Q_UNUSED(count);
    beginInsertRows(parent, dataList.size(), dataList.size());

    RegisterData data;
    data.bActive = false;
    data.reg = 0;
    data.text = "Register x";
    dataList.append(data);

    endInsertRows();

    return true;
}

uint RegisterModel::checkedRegisterCount()
{
    uint count = 0;

    for (int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].bActive)
        {
            count++;
        }
    }

    return count;
}

void RegisterModel::getCheckedRegisterList(QList<quint16> * pRegisterList)
{
    pRegisterList->clear();
    for (int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].bActive)
        {
            pRegisterList->append(dataList[i].reg);
        }
    }
}

void RegisterModel::getCheckedRegisterTextList(QList<QString> * pRegisterTextList)
{
    pRegisterTextList->clear();
    for (int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].bActive)
        {
            pRegisterTextList->append(dataList[i].text);
        }
    }
}
