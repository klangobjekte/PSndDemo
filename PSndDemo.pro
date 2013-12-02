TEMPLATE = app
HEADERS = qwave2.h
SOURCES = qwave2.cc
TARGET = PSndDemo

QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)




#contains(QT_VERSION, 4.8.5){
#    QT += phonon
#        message(4.8.5)
#}



greaterThan(QT_VER_MAJ, 4) {
    QT += core \
         printsupport \
         gui \
         widgets
macx {
QT += macextras
}
         #webkit
#QTPLUGIN     += qsqlmysql
}

win32:LIBS += ../src/Debug/libqwave2.lib

macx { 

#QMAKE_CXXFLAGS += -stdlib=libc++
#QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 #1
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7 #2

    QMAKE_LFLAGS += -F/System/Library/Frameworks \
                    -F//Developer/Library/PrivateFrameworks
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.5

        INCLUDEPATH += /Developer/SDKs/libsndfile/libsndfile_86_10.5/local/include
        INCLUDEPATH += /Developer/Qt_projekte/PSndWave
        INCLUDEPATH += /Developer/Qt_projekte/PSndWave/QWave2
        INCLUDEPATH += /Developer/Qt_Projekte/PSndPlayer

        INCLUDEPATH += . \
        /usr/local/include
        #../src

        LIBS += -L/Developer/Qt_Projekte/PSndWave-build-Desktop_GCC_x86_32bit-Debug
        LIBS += -L/Developer/Qt_Projekte/PSndPlayer-build-Desktop_GCC_x86_32bit-Debug
        LIBS += -L/Developer/SDKs/libmp123/x86/lib
        LIBS += -L/Developer/SDKs/meta/x86/lib
        LIBS += -L/Developer/SDKs/libsndfile/libsndfile_86_10.5/local/lib
        #LIBS += -framework \
        #Carbon \
        #-framework \
        #CoreAudio
        LIBS += -lsndfile \
                -lPSndPlayer \
                -lPSndWave


        #QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
        #QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.5.sdk
        #CONFIG += x86


}

