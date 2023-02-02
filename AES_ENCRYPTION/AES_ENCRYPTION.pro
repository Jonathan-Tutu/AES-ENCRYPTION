QMAKE_CFLAGS += -std=c11
QMAKE_CXXFLAGS += -std=c++11

# Tell Qt's build system to use the C++11 standard
CONFIG += c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Cipher.c \
        main.c

HEADERS += \
    Cipher.h \
    Matrix.h
