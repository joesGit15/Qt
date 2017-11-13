### How to get QML object and use QML object in c++ file

QML的本质也是有c++实现的，所以我们可以很方便的进行使用。

Qt的一个核心基础有一个元对象系统。请查看`QMetaObject`.

在c++中使用QML对象，分两步:

1. 找到这个对象:Qt的很多对象是具有父子关系的。而QML是一个对象树。通过`findChild(...)` and `findChildren(...)` 可以找到想要的对象。
2. 找到对象后，就是在c++环境调用QML对象的方法。`QMetaObject::invokeMethod`. 

详细内容，可以阅读Qt文档和实例。
