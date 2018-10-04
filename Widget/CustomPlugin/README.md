## Qt 自定义插件学习分享

### 前言废话

世界上最好的教程,没有比帮助文档更加的详细了. 最正确的结论不是网上的博客, 也不是我当前的分享. 而是根据我的分享, 可以引导或启发他人开启自己的发现之路.

接触Qt已经很长时间,一直没有机会深入的了解Qt自定义插件这部分的内容. 因为Qt自身带有的控件已经满足工作的要求了. 还有就是工作业务还没有达到模块化的级别. 所以, 大多数都是看见网上他人在分享这部分的内容. 

学习的过程是一个循序渐进的过程, 目前时机已经成熟. 对于Qt的整个框架的认识, 也在一点点的透彻起来.

### 插件思想

通过Qt Designer 来拖动控件的方法, 很方便初学者的学习. 插件思想的本质依然是静态库或动态库的思想. 既然自定义的控件要和Qt Creator 融合起来, 那么势必就要遵循一些Qt Creator的接口了. 这里Qt提供了一些接口类, 我们通过子类化这些接口类, 按照Qt的约定, 生成插件库. 然后放到特定的目录, 重启Qt Creator, 运气好的话, 新建一个工程, 就像使用库的方式一样, 而且你也会在Qt 设计师中的控件列表中看到新添加的自定义控件的小图标了.

在Qt的帮助文档中,Qt Designer Manual中的高级部分, 可以查看相关的内容:

> Customizing Qt Designer Forms
> Using Custom Widgets with Qt Designer
> Creating Custom Widgets for Qt Designer
> Creating Custom Widget Extensions
> Qt Designer's UI File Format 

### 创建插件工程

Qt Creator -> File -> New File or Project -> Other Project -> Qt Custom Designer Widget

即可一步一步创建一个插件工程.

对了, 通过这种方式创建的工程, 是很难符合要求的. 因为不知道为什么, 少了一些东西.

完好的工程框架, 可以参考 **customwidgetplugin** 工程.

**提议:** 请自觉把上面列举的帮助文档的内容,阅读学习一下. 不然很难理解整个工程.

**注意:** 我的开发环境Ubuntu 18.04.1, Qt 5.8.0 for linux

### 安装插件

库生成以后, 需要把对应的文件拷贝到Qt安装目录下的特定目录.

特定目录介绍如下:

1. /home/joe/Qt5.8.0/Tools/QtCreator/lib/Qt/plugins/designer 如果想在设计师中看到插件,则需要把生成的库放到此目录下. 由于本人习惯手写布局, 所以上面的项目中并没有此目录的安装.
2. QT_INSTALL_HEADERS:/home/joe/Qt5.8.0/5.8/gcc_64/include   头文件目录, 把插件库对外开放的头文件,放到此目录下面, 可以自建个子目录
3. QT_INSTALL_PLUGINS:/home/joe/Qt5.8.0/5.8/gcc_64/plugins   存放插件库的目录

我只使用了2和3.

配置文件没有错误的话, 命令行:make install, 就把头文件和库文件,复制到了特定的目录.

### 使用插件

插件其实也就是静态库或动态库. 使用例子的工程参见 **UseCustomWidgetPlugin**.

**注意:** pro文件中库的引用和头文件的包含.


### 结束语

我喜欢引导,悟性高了,大彻大悟,悟性不够,还需积累磨炼.

---


