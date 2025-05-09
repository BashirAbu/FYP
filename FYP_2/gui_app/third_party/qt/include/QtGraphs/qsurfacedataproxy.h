// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QSURFACEDATAPROXY_H
#define QSURFACEDATAPROXY_H

#include <QtGraphs/qabstractdataproxy.h>
#include <QtGraphs/qsurfacedataitem.h>

Q_MOC_INCLUDE(<QtGraphs/qsurface3dseries.h>)

QT_BEGIN_NAMESPACE

class QSurfaceDataProxyPrivate;
class QSurface3DSeries;

using QSurfaceDataRow = QList<QSurfaceDataItem>;
using QSurfaceDataArray = QList<QSurfaceDataRow>;

class Q_GRAPHS_EXPORT QSurfaceDataProxy : public QAbstractDataProxy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QSurfaceDataProxy)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)
    Q_PROPERTY(QSurface3DSeries *series READ series NOTIFY seriesChanged)

public:
    explicit QSurfaceDataProxy(QObject *parent = nullptr);
    ~QSurfaceDataProxy() override;

    QSurface3DSeries *series() const;
    int rowCount() const;
    int columnCount() const;
    const QSurfaceDataArray &array() const;
    const QSurfaceDataItem &itemAt(int rowIndex, int columnIndex) const;
    const QSurfaceDataItem &itemAt(const QPoint &position) const;

    void resetArray();
    void resetArray(QSurfaceDataArray newArray);

    void setRow(int rowIndex, QSurfaceDataRow row);
    void setRows(int rowIndex, QSurfaceDataArray rows);

    void setItem(int rowIndex, int columnIndex, QSurfaceDataItem item);
    void setItem(const QPoint &position, QSurfaceDataItem item);

    int addRow(QSurfaceDataRow row);
    int addRows(QSurfaceDataArray rows);

    void insertRow(int rowIndex, QSurfaceDataRow row);
    void insertRows(int rowIndex, QSurfaceDataArray rows);

    void removeRows(int rowIndex, int removeCount);

Q_SIGNALS:
    void arrayReset();
    void rowsAdded(int startIndex, int count);
    void rowsChanged(int startIndex, int count);
    void rowsRemoved(int startIndex, int count);
    void rowsInserted(int startIndex, int count);
    void itemChanged(int rowIndex, int columnIndex);

    void rowCountChanged(int count);
    void columnCountChanged(int count);
    void seriesChanged(QSurface3DSeries *series);

protected:
    explicit QSurfaceDataProxy(QSurfaceDataProxyPrivate &d, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QSurfaceDataProxy)

    friend class QQuickGraphsSurface;
};

QT_END_NAMESPACE

#endif
