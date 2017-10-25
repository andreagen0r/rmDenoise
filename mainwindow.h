#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QProgressDialog>
#include <QTimer>
#include <QCompleter>
#include <QDirModel>

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
    Preferences *m_prefUi;
    PXRDenoise *m_pxrDenoise;
    QTimer *m_timer;
    Utils *m_utl;

    QCompleter *m_completer;

    QString render();
    void createFlagLine();


    QString m_flagName;
    QDir m_flagOutDir;
    QString m_flagLayers;
    QStringList m_flagOverride;
    QStringList m_flagImages;
    QStringList m_flagConfigFiles;
    int m_flagThreads;
    int m_progress;

};

#endif // MAINWINDOW_H
