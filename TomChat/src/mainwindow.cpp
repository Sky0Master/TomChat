#include "mainwindow.h"
#include "tcp.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QTextCodec>
#define VERSION "TomChat V1.4"
using namespace std;
const char * FLAG="$TOM$";
TCP_Client tcp("111.229.102.159",20000);  //服务器IPv4地址,监听端口

void Receiver::run()
{

     char data[10240+10];
     while(true)
     {
         tcp.Recv(data);
         string temp=data;
         emit rec(QString::fromStdString(temp));
     }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    this->setWindowTitle(VERSION);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void sendQString(QString text)
{
    QByteArray cdata=text.toLocal8Bit();
    string temp=string(cdata);
    tcp.Send(temp.c_str());

}
void MainWindow::append_text_to_TextBrowser(string s)
{
    ui->textBrowser->moveCursor(QTextCursor::End);
    ui->textBrowser->insertPlainText(s.c_str());
}
void MainWindow::append_text_to_TextBrowser(char *s)
{
    ui->textBrowser->moveCursor(QTextCursor::End);
    ui->textBrowser->insertPlainText(s);
}
void MainWindow::append_red_text_to_TextBrowser(QString s)
{
    ui->textBrowser->append("<font color=\"red\">"+s+"</font>");
    append_text_to_TextBrowser("\n");
}

void MainWindow::on_SendButton_clicked()
{

   if(!tcp.state){ append_text_to_TextBrowser("未连接服务器，发送失败.\n");return;}
   //convert QString to char*
   QString text=ui->textEdit->toPlainText();
   if(text.toStdString().length() > 10000)
   {
        append_text_to_TextBrowser("发送失败!消息过长，请分开发送.\n");
        return;
   }
   if(text.toStdString().empty())
   {
        append_text_to_TextBrowser("不要发送空消息!");
        return;
   }
   sendQString(text);
   ui->textEdit->clear();
}
void MainWindow::display_Text(QString s)
{
    append_text_to_TextBrowser(s.toStdString());
    append_text_to_TextBrowser("\n");
}


void MainWindow::on_pushButton_clicked()
{
    if(tcp.state) {
        QMessageBox::information(NULL,"啊哦，出错了","请不要重复登录!\n如需更换ID请退出后重新运行程序");
        return;
    }
    if(ui->lineEdit->text().isEmpty())
    {
         QMessageBox::information(NULL,"啊哦，出错了","用户名不能为空！快为自己取一个炫酷的ID吧！");
         return;
    }
    if(tcp.Connect())
    {
        tcp.Send(FLAG);
        append_text_to_TextBrowser("登录成功! 已连接Tom服务器\n武汉加油!中国加油!\n---------------------------------------------\n");
        QString text=ui->lineEdit->text();
        sendQString(text);
        Receiver * r1 = new Receiver();
        connect(r1,SIGNAL(rec(QString)),this,SLOT(display_Text(QString)));
        r1->start();
    }

    else append_text_to_TextBrowser("连接失败!Tom可能正在睡觉\n");
}
 void MainWindow::closeEvent(QCloseEvent * event)
{
    QMessageBox::information(NULL,"Tom聊天室","再见朋友!");
    if(tcp.state) tcp.Send(tcp.END);
}

void MainWindow::on_textBrowser_cursorPositionChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}
