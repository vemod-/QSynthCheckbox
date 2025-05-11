!contains(PROFILES,$$_FILE_){
PROFILES+=$$_FILE_

INCLUDEPATH += $$PWD

SOURCES += $$PWD/qsynthcheckbox.cpp

HEADERS  += $$PWD/qsynthcheckbox.h

RESOURCES += $$PWD/QCheckboxResources.qrc
}
