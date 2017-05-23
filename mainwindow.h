#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <QRegularExpression>

#include<QProgressDialog>
#include<QTimer>

#include "pxrdenoise.h"
#include "preferencesUI.h"
#include "utils.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_run_clicked();
    void on_btn_ImagePath_clicked();
    void on_btn_outDir_clicked();
    void on_actionAboutQT_triggered();
    void on_actionAbout_triggered();
    void on_actionPreferences_triggered();
    void on_chbox_crossframe_stateChanged(int arg1);
    void on_lineEdit_imagePath_editingFinished();
    void on_lineEdit_outdir_editingFinished();
    void on_lineEdit_name_editingFinished();


    void renderStatus(const bool &arg1);
    void renderProgress();

    void statusBarMsg(const QString &value);

    void loadConfigFiles();

private:
    Ui::MainWindow *ui;
    Preferences *prefUi;
    PXRDenoise *pxrD;
    QTimer *timer;
    Utils *utl;

    QString render();
    void createFlagLine();

    QString getFlag_name() const;
    void setFlag_name(const QString &value);

    QDir getFlag_outDir() const;
    void setFlag_outDir(const QDir &value);

    QStringList getFlag_images() const;
    void setFlag_images(const QStringList &value);

    QString getFlag_layers() const;
    void setFlag_layers(const QString &value);

    QStringList getFlag_override() const;
    void setFlag_override(const QStringList &value);

    QStringList getFlag_configFiles() const;
    void setFlag_configFiles(const QStringList &value);

    int getFlag_Threads() const;
    void setFlag_Threads(const int &value);

    int getProg() const;
    void setProg(const int &value = 0);

    QString flag_name;
    QDir flag_outDir;
    QString flag_layers;
    QStringList flag_override;
    QStringList flag_images;
    QStringList flag_configFiles;
    int flag_Threads;

    int prog;

};

#endif // MAINWINDOW_H
