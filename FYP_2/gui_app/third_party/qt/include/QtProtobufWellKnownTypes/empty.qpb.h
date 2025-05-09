/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_EMPTY_H
#define QPROTOBUF_EMPTY_H

#include <QtProtobuf/qprotobufmessage.h>
#include <QtProtobuf/qprotobufobject.h>
#include <QtProtobuf/qprotobuflazymessagepointer.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include "protobufwellknowntypes_exports.qpb.h"

#include <QtCore/qmetatype.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>

#include <memory>


namespace google::protobuf {
class Empty;
using EmptyRepeated = QList<Empty>;
namespace Empty_QtProtobufNested {
enum class QtProtobufFieldEnum;
} // namespace Empty_QtProtobufNested


class Empty_QtProtobufData;
class QPB_PROTOBUFWELLKNOWNTYPES_EXPORT Empty : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(Empty)

public:
    using QtProtobufFieldEnum = Empty_QtProtobufNested::QtProtobufFieldEnum;
    Empty();
    ~Empty();
    Empty(const Empty &other);
    Empty &operator =(const Empty &other);
    Empty(Empty &&other) noexcept;
    Empty &operator =(Empty &&other) noexcept;
    bool operator ==(const Empty &other) const;
    bool operator !=(const Empty &other) const;
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<Empty_QtProtobufData> dptr;
};
namespace Empty_QtProtobufNested {
Q_NAMESPACE_EXPORT(QPB_PROTOBUFWELLKNOWNTYPES_EXPORT)

} // namespace Empty_QtProtobufNested
} // namespace google::protobuf

Q_DECLARE_METATYPE(google::protobuf::Empty)
#endif // QPROTOBUF_EMPTY_H
