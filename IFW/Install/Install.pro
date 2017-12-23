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
    packages/ColorComponent.HSV/meta/package.xml \
    packages/ColorComponent.HSV.H/meta/package.xml \
    packages/ColorComponent.HSV.S/meta/package.xml \
    packages/ColorComponent.HSV.V/meta/package.xml \
    packages/ColorComponent.RGB/meta/package.xml \
    packages/ColorComponent.RGB.R/meta/package.xml \
    packages/ColorComponent.RGB.G/meta/package.xml \
    packages/ColorComponent.RGB.B/meta/package.xml \
    packages/ShapeComponent/meta/installscript.js \
    packages/ShapeComponent/meta/package.xml \
    packages/ShapeComponent.Circle/meta/installscript.js \
    packages/ShapeComponent.Circle/meta/package.xml \
    packages/ShapeComponent.Rectangle/meta/installscript.js \
    packages/ShapeComponent.Rectangle/meta/package.xml \
    packages/PhoneComponent/meta/installscript.js \
    packages/PhoneComponent/meta/package.xml \
    packages/PCComponent/meta/package.xml \
    packages/PCComponent/data/installcontent.txt
