// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QGRPCCHANNELOPERATION_H
#define QGRPCCHANNELOPERATION_H

#include <QtCore/QObject>
#include <QtGrpc/qgrpcmetadata.h>
#include <QtGrpc/qtgrpcglobal.h>
QT_BEGIN_NAMESPACE

class QAbstractProtobufSerializer;
class QGrpcCallOptions;
class QGrpcChannelOperationPrivate;
class QGrpcStatus;

class Q_GRPC_EXPORT QGrpcChannelOperation : public QObject
{
    Q_OBJECT
public:
    explicit QGrpcChannelOperation(QLatin1StringView method, QLatin1StringView service,
                                   QByteArrayView arg, const QGrpcCallOptions &options,
                                   std::shared_ptr<QAbstractProtobufSerializer> serializer);

    QLatin1StringView method() const;
    QLatin1StringView service() const;
    QByteArrayView argument() const;
    const QGrpcCallOptions &options() const;
    std::shared_ptr<const QAbstractProtobufSerializer> serializer() const;

    const QGrpcMetadata &clientMetadata() const;
    const QGrpcMetadata &serverMetadata() const;

    void setArgument(QByteArrayView arg);
    void setOptions(QGrpcCallOptions &options);

    void setClientMetadata(const QGrpcMetadata &metadata);
    void setClientMetadata(QGrpcMetadata &&metadata);
    void setServerMetadata(const QGrpcMetadata &metadata);
    void setServerMetadata(QGrpcMetadata &&metadata);

Q_SIGNALS:
    void dataReady(const QByteArray &data);
    void sendData(const QByteArray &data) const;
    void errorOccurred(const QGrpcStatus &status);
    void finished();

    void cancelled();

private:
    Q_DISABLE_COPY_MOVE(QGrpcChannelOperation)
    Q_DECLARE_PRIVATE(QGrpcChannelOperation)
};

QT_END_NAMESPACE

#endif // QGRPCCHANNELOPERATION_H
