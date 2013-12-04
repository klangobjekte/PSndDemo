######################################################################
# Automatically generated by qmake (2.01a) Mo. Dez 2 19:31:19 2013
######################################################################

TEMPLATE = app
HEADERS = qwave2.h
SOURCES = qwave2.cc
TARGET = PSndDemo

QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

DEFINES = __STDC_CONSTANT_MACROS


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

#win32:LIBS += ../src/Debug/libqwave2.lib

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

win32 {
    INCLUDEPATH += . \
        "C:/Qt_Projekte/meta_mp" \
        "C:\Program Files\Mega-Nerd\libsndfile\include" \
        "C:/Qt_Projekte/PSndPlayer" \
        "C:/Qt_Projekte/PSndWave/QWave2" \
        "C:/Qt_Projekte/PSndWave" \
        "C:/Program Files/portaudio-r1891-build/include" \
        "C:/Program Files/ffmpeg-20131202-git-e3d7a39-win32-dev/include" \
        "C:/Program Files/ffmpeg-20131202-git-e3d7a39-win32-dev/include" \


    LIBS+= "C:\Qt_Projekte\meta-build-Desktop_Qt_4_8_4_MinGw2-Release\release\libmeta.a"
    LIBS += "C:/Program Files/Mega-Nerd/libsndfile/lib/libsndfile-1.lib" \
            "C:/Qt_Projekte/build-PSndPlayer-Desktop_MinGw-Debug/debug/PSndPlayer.dll" \
            "C:/Qt_Projekte/build-PSndWave-Desktop_MinGw-Debug/release/PSndWave.dll"
        LIBS += "C:/Program Files/ffmpeg-20131202-git-e3d7a39-win32-shared/bin/avformat-55.dll
        LIBS += "C:/Program Files/ffmpeg-20131202-git-e3d7a39-win32-shared/bin/avcodec-55.dll
        LIBS += "C:/Program Files/ffmpeg-20131202-git-e3d7a39-win32-shared/bin/avutil-52.dll
        LIBS += "C:/Program Files/mpg123-1.15.0-x86/libmpg123-0.dll"
        LIBS += "C:/Program Files/portaudio-r1891-build/lib/Win32/Release/portaudio_x86.dll

}
