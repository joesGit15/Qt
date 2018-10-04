INCLUDEPATH += $$PWD

HEADERS += $$PWD/analogclock.h
SOURCES += $$PWD/analogclock.cpp

src_file = $$PWD/analogclock.h
dst_dir = $$OUT_PWD/
linux {
    QMAKE_PRE_LINK += cp -r -f $$src_file $$dst_dir
}

#QT_INSTALL_LIBS:/home/joe/Qt5.8.0/5.8/gcc_64/lib
#QT_INSTALL_HEADERS:/home/joe/Qt5.8.0/5.8/gcc_64/include
header_files.path = $$[QT_INSTALL_HEADERS]/QtPlugins
header_files.files = analogclock.h
#unix:headers.extra = cp analogclock.h AnalogClock

#QT_INSTALL_PLUGINS:/home/joe/Qt5.8.0/5.8/gcc_64/plugins
target.path  = $$[QT_INSTALL_PLUGINS]/designer

INSTALLS += header_files target
