TEMPLATE = aux

INSTALLER = joe_app_installer

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
