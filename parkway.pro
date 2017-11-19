TEMPLATE = app

QT += qml quick sql

CONFIG += c++14

SOURCES += main.cpp \
    childrenlistmodel.cpp \
    parentslistmodel.cpp \
    child.cpp \
    parent.cpp \
    database.cpp \
    timetableslistmodel.cpp \
    timetable.cpp \
    groupslistmodel.cpp \
    childimageprovider.cpp

HEADERS += \
    childrenlistmodel.h \
    parentslistmodel.h \
    child.h \
    parent.h \
    database.h \
    timetableslistmodel.h \
    timetable.h \
    groupslistmodel.h \
    childimageprovider.h

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)


