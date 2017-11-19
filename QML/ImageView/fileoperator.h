#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtCore/qlist.h>

class FileOperator : public QObject
{
    Q_OBJECT
public:
    explicit FileOperator(QObject *parent = 0);

    Q_INVOKABLE QList<QUrl> getAllUrls(const QList<QUrl> &ltUrl);
    Q_INVOKABLE bool isDir(const QUrl &url);
    Q_INVOKABLE QString filename(const QUrl& url);

};

#endif // FILEOPERATOR_H
