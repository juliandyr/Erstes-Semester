TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        carnivore.cpp \
        dinosaur.cpp \
        herbivore.cpp \
        main.cpp \
        park.cpp

HEADERS += \
    carnivore.h \
    dinosaur.h \
    herbivore.h \
    park.h
