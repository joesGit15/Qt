#include "fileoperator.h"

#include <QtCore/qdir.h>

FileOperator::FileOperator(QObject *parent)
    : QObject(parent)
{

}

QList<QUrl> FileOperator::getAllUrls(const QList<QUrl> &ltUrl)
{
    Q_ASSERT(!ltUrl.isEmpty());

    QList<QUrl> allUrls;
    QFileInfoList ltInfo;

    QString filename = ltUrl.first().path();
    QFileInfo info(filename);

    /** Step1:add dir */
    QDir dir;
    if(info.isDir()){
        dir.cd(filename);
    }else{
        dir = info.absoluteDir();
    }

    dir.setFilter(QDir::Dirs|QDir::NoDot);
    ltInfo = dir.entryInfoList();
    for(const QFileInfo &info:ltInfo){
        allUrls << QUrl::fromLocalFile(info.absoluteFilePath());
    }

    if(!info.isDir()){
        /** Step2:add select url file*/
        for(const QUrl &url:ltUrl){
            allUrls << url;
        }
    }

    /** Step3:add other url */
    dir.setFilter(QDir::Readable|QDir::Files);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png";
    dir.setNameFilters(nameFilters);
    ltInfo = dir.entryInfoList();
    QUrl url;
    for(const QFileInfo &info:ltInfo){
        url = QUrl::fromLocalFile(info.absoluteFilePath());
        if(!allUrls.contains(url)){
            allUrls << url;
        }
    }

    return allUrls;
}

bool FileOperator::isDir(const QUrl &url)
{
    QString filename = url.path();
    QFileInfo info(filename);
    return info.isDir();
}

QString FileOperator::filename(const QUrl &url)
{
    QString filepath = url.path();
    QFileInfo info(filepath);
    return info.baseName();
}

void FileOperator::removefile(const QUrl &url)
{
    QString filepath = url.path();
    QFile::remove(filepath);
}
