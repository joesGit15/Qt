## How to use c++ class or object in QML?

1. 在C++中，实现一个类，注册为QML环境的一个类型，在QML环境中，使用该类型创建对象;
2. 在C++中，构造一个对象，将这个对象设置为QML的上下文属性，在QML环境中直接使用该属性；

### 类的注意事项

1. 从QObject或QObject的派生类继承；
2. Q_OBJECT;
3. signal and slot 自动就可以在QML中使用;
4. 使用Q_INVOKABLE修饰共有方法在QML中是可调用的(invokable);
5. 使用Q_ENUMS修饰共有枚举类型在QML中是可使用的;
6. 使用Q_PROPERTY修饰某些变量可以被QML使用，修改，甚至接收变量值改变的信号;
7. 在main函数中，使用`qmlRegister...`类型的函数，进行注册;
8. 在QML中，`import ...`注册时候填写的包的名字;
9. 像其他QML类型一样，即可使用；

详细内容，需要参考代码，一步一步理解。

