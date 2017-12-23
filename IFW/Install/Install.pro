TEMPLATE = aux

INSTALLER = joe_app_installer

INPUT = $$PWD/config/config.xml $$PWD/packages

example.input = INPUT
example.output = $$INSTALLER
example.commands = ~/Qt/QtIFW-3.0.2/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}

QMAKE_EXTRA_COMPILERS += example

DISTFILES += \
    packages/ColorComponent/meta/package.xml \
    packages/ColorComponent/meta/license.txt \
    packages/ColorComponent/meta/installscript.qs \
    packages/ShapeComponent/meta/installscript.js \
    packages/ShapeComponent/meta/package.xml \
    packages/ShapeComponent.Circle/meta/installscript.js \
    packages/ShapeComponent.Circle/meta/package.xml \
    packages/ShapeComponent.Rectangle/meta/installscript.js \
    packages/ShapeComponent.Rectangle/meta/package.xml
