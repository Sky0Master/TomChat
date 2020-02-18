#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <cstring>
#include <string>
#include <QCloseEvent>
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void append_text_to_TextBrowser(string);
    void append_text_to_TextBrowser(char *);
    void append_red_text_to_TextBrowser(QString);
    ~MainWindow();

private slots:
    void on_SendButton_clicked();
    void on_pushButton_clicked();
    void display_Text(QString);
    void on_textBrowser_cursorPositionChanged();

private:
    Ui::MainWindow *ui;
protected:
    virtual void closeEvent(QCloseEvent *);
};


#endif // MAINWINDOW_H
