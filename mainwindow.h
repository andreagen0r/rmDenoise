#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pxrdenoise.h"
#include "preferencesUI.h"

#include <QDir>
#include <memory>
#include <map>
#include <string>
#include <iostream>

class QCompleter;

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

    void on_chbox_n_toggled(bool checked);

    void on_chbox_filtervariance_toggled(bool checked);

    void on_chbox_crossframe_toggled(bool checked);

    void on_chbox_v_toggled(bool checked);

    void on_chbox_skipfirst_toggled(bool checked);

    void on_chbox_skiplast_toggled(bool checked);

    void on_chbox_layers_toggled(bool checked);

    void on_chbox_t_toggled(bool checked);
    void on_spnBox_threads_valueChanged(const QString &arg1);

    void on_chbox_override_toggled(bool checked);


private:
    Ui::MainWindow *ui;
    std::unique_ptr<PXRDenoise> m_pxrDenoise;
    std::unique_ptr<QTimer> m_timer;
    std::unique_ptr<QCompleter> m_completer;

    QString render();
    void createFlagLine();
    void loadFirstTime();

    void registerCommandLine(const bool &in_checked, const std::string &in_flagKey,
                             const std::string &in_flagValue);

    bool checkImages(const QStringList &value);
    QStringList notValidImages(const QStringList &value);
    QStringList validImages(const QStringList &value);
    bool checkDir(const QString &value);

    QString m_flagName;
    QDir m_flagOutDir;
    QString m_flagLayers;
    QStringList m_flagOverride;
    QStringList m_flagImages;
    QStringList m_flagConfigFiles;

    int m_progress;

    std::map<std::string, std::string> m_test;

};

#endif // MAINWINDOW_H
