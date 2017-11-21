TEMPLATE = app

QT += qml quick sql

CONFIG += c++14

SOURCES += src/main.cpp \
    src/childrenlistmodel.cpp \
    src/parentslistmodel.cpp \
    src/child.cpp \
    src/parent.cpp \
    src/database.cpp \
    src/timetableslistmodel.cpp \
    src/timetable.cpp \
    src/groupslistmodel.cpp \
    src/childimageprovider.cpp

HEADERS += \
    src/childrenlistmodel.h \
    src/parentslistmodel.h \
    src/child.h \
    src/parent.h \
    src/database.h \
    src/timetableslistmodel.h \
    src/timetable.h \
    src/groupslistmodel.h \
    src/childimageprovider.h

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)


