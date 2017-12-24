TEMPLATE = aux

INSTALLER = joe_dynamic_install

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER
example.commands = ~/Qt/QtIFW-3.0.2/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}

QMAKE_EXTRA_COMPILERS += example

DISTFILES += \
    packages/org.dynamicpage/meta/installscript.js \
    packages/org.dynamicpage/meta/package.xml \
    packages/org.dynamicpage.one/data/data.one.txt \
    packages/org.dynamicpage.one/meta/package.xml \
    packages/org.dynamicpage.one/meta/installscript.qs \
    packages/org.dynamicpage.two/data/data.two.txt \
    packages/org.dynamicpage.two/meta/package.xml \
    packages/org.dynamicpage.two/meta/installscript.qs

FORMS += \
    packages/org.dynamicpage/meta/targetwidget.ui \
    packages/org.dynamicpage/meta/readytoinstallwidget.ui \
    packages/org.dynamicpage/meta/licensewidget.ui \
    packages/org.dynamicpage/meta/installationwidget.ui

RESOURCES += \
    resources/additional.qrc
