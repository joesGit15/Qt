#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>
#include <QTextBrowser>
#include <QTableWidget>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>

class TcpServer;

namespace Ui {
class Widget;
}

//枚举变量，消息，新用户加入，用户退出，文件名，拒绝接收文件
enum MessageType{Message,NewParticipaint,ParticipantLeft,FileName,Refuse};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();    
protected:
    void newParticipaint(QString userName,QString localHostName,QString ipAddress);
    void participantLeft(QString userName,QString localHostName,QString time);//这2个函数的名字和上面枚举元素的名字是不一样的。
    void sendMessage(MessageType type,QString serverAddress = " ");
    void hasPendingFile(QString userName,QString serverAddress,QString clicentAddress,QString fileName);
    bool saveFile(const QString &fileName);
    void closeEvent(QCloseEvent *event);
    QString getIP();
    QString getUserName();
    QString getMessage();

private:
    void setMyLayout();
    void setToolBtn(QToolButton *btn);
    void setAllToolbtn();
    void setTableWidget();
private:
    Ui::Widget *ui;
    QTextBrowser *textBrowser;
    QTableWidget *tableWidget;
    QFontComboBox *fontComboBox;
    QComboBox *combox;
    QToolButton *toolbtnbold;
    QToolButton *toolbtnitalic;
    QToolButton *toolbtnunderline;
    QToolButton *toolbtncolor;
    QToolButton *toolbtnsend;
    QToolButton *toolbtnsave;
    QToolButton *toolbtnclear;
    QTextEdit *textEdit;
    QLabel *labelUserNum;
    QPushButton *btnSendMessage;
    QPushButton *btnExit;

    QUdpSocket *udpSocket;
    qint16 port;
    QString fileName;
    TcpServer *server;
    QColor color;
private slots:
    void processPendingDatagrams();
    void slotSendMessage();
    void getFileName(QString name);
    void slotToolbtnSendClick();
    void slotFontComBoxCurrentFontChange(QFont f);
    void slotComBoxCurrentIndexChanged(QString size);
    void slotToolBtnBoldClick(bool checked);
    void slotToolBtnItalicClick(bool checked);
    void slotToolBtnUnderlineClick(bool checked);
    void slotToolBtnColorClick();
    void slotCurrentFormatChanged(const QTextCharFormat &format);
    void slotToolBtnSaveClick();
    void slotToolBtnClearClick();
    void slotbtnExit();
};

#endif // WIDGET_H
