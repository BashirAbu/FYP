// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBARCATEGORYAXIS_H
#define QBARCATEGORYAXIS_H

#include <QtGraphs/QAbstractAxis>
#include <QtGraphs/qgraphsglobal.h>
#include <QtQml/QQmlEngine>

QT_BEGIN_NAMESPACE

class QBarCategoryAxisPrivate;

class Q_GRAPHS_EXPORT QBarCategoryAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(QString min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QString max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_NAMED_ELEMENT(BarCategoryAxis)

public:
    explicit QBarCategoryAxis(QObject *parent = nullptr);
    ~QBarCategoryAxis();

protected:
    QBarCategoryAxis(QBarCategoryAxisPrivate &d, QObject *parent = nullptr);

public:
    // TODO: Consider making these slots, available from QML.
    AxisType type() const override;
    void append(const QStringList &categories);
    void append(const QString &category);
    void remove(const QString &category);
    void insert(int index, const QString &category);
    void replace(const QString &oldCategory, const QString &newCategory);
    Q_INVOKABLE void clear();
    void setCategories(const QStringList &categories);
    QStringList categories();
    int count() const;
    QString at(int index) const;

    //range handling
    void setMin(const QString &minCategory);
    QString min() const;
    void setMax(const QString &maxCategory);
    QString max() const;
    void setRange(const QString &minCategory, const QString &maxCategory);

Q_SIGNALS:
    void categoriesChanged();
    void minChanged(const QString &min);
    void maxChanged(const QString &max);
    void rangeChanged(const QString &min, const QString &max);
    void countChanged();

private:
    Q_DECLARE_PRIVATE(QBarCategoryAxis)
    Q_DISABLE_COPY(QBarCategoryAxis)
};

QT_END_NAMESPACE

#endif // QBARCATEGORYAXIS_H
