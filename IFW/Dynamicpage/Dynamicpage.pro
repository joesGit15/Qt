TEMPLATE = aux

INSTALLER = joe_dynamic_install

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER

win {
    BinaryFilePath = "binarycreator.exe"
}else{
    BinaryFilePath = "~/Qt/QtIFW-3.0.2/bin/binarycreator"
}

exists($$BinaryFilePath) {
    example.commands = ~/Qt/QtIFW-3.0.2/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
    QMAKE_EXTRA_COMPILERS += example
}

FORMS += \
    packages/org.dynamicpage/meta/targetwidget.ui \
    packages/org.dynamicpage/meta/readytoinstallwidget.ui \
    packages/org.dynamicpage/meta/licensewidget.ui \
    packages/org.dynamicpage/meta/installationwidget.ui

RESOURCES += \
    resources/additional.qrc

TRANSLATIONS += ch.ts
