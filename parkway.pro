TEMPLATE = app

QT += qml quick sql

CONFIG += c++11

SOURCES += main.cpp \
    childrenlistmodel.cpp \
    parentslistmodel.cpp \
    child.cpp \
    parent.cpp \
    database.cpp \
    timetableslistmodel.cpp \
    timetable.cpp \
    groupslistmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    database/parkway.db \
    images/calendar.png

HEADERS += \
    childrenlistmodel.h \
    parentslistmodel.h \
    child.h \
    parent.h \
    database.h \
    timetableslistmodel.h \
    timetable.h \
    groupslistmodel.h
