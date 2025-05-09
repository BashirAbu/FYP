/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_ANY_H
#define QPROTOBUF_ANY_H

#include <QtProtobuf/qprotobufmessage.h>
#include <QtProtobuf/qprotobufobject.h>
#include <QtProtobuf/qprotobuflazymessagepointer.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include <QtProtobufWellKnownTypes/qprotobufanysupport.h>
#include "protobufwellknowntypes_exports.qpb.h"

#include <QtCore/qmetatype.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>

#include <memory>


namespace google::protobuf {
class Any;
using AnyRepeated = QList<Any>;
namespace Any_QtProtobufNested {
enum class QtProtobufFieldEnum;
} // namespace Any_QtProtobufNested


class Any_QtProtobufData;
class QPB_PROTOBUFWELLKNOWNTYPES_EXPORT Any : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(Any)
    Q_PROPERTY(QString typeUrl READ typeUrl WRITE setTypeUrl SCRIPTABLE true)
    Q_PROPERTY(QByteArray value READ value WRITE setValue SCRIPTABLE true)

public:
    using QtProtobufFieldEnum = Any_QtProtobufNested::QtProtobufFieldEnum;
    Any();
    ~Any();
    Any(const Any &other);
    Any &operator =(const Any &other);
    Any(Any &&other) noexcept;
    Any &operator =(Any &&other) noexcept;
    bool operator ==(const Any &other) const;
    bool operator !=(const Any &other) const;

    QString typeUrl() const;

    QByteArray value() const;
    void setTypeUrl(const QString &typeUrl);
    void setValue(const QByteArray &value);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<Any_QtProtobufData> dptr;
};
namespace Any_QtProtobufNested {
Q_NAMESPACE_EXPORT(QPB_PROTOBUFWELLKNOWNTYPES_EXPORT)

enum class QtProtobufFieldEnum {
    TypeUrlProtoFieldNumber = 1,
    ValueProtoFieldNumber = 2,
};
Q_ENUM_NS(QtProtobufFieldEnum)

} // namespace Any_QtProtobufNested
} // namespace google::protobuf

Q_DECLARE_METATYPE(google::protobuf::Any)
#endif // QPROTOBUF_ANY_H
