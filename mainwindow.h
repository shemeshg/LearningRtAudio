#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TestRtAudio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&)= delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onPushButtonClicked();

private:
    Ui::MainWindow *ui;
    RtAudioNs::TestRtAudio tra;
};
#endif // MAINWINDOW_H
