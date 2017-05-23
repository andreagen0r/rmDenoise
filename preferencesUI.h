#ifndef PREFERENCESUI_H
#define PREFERENCESUI_H

#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QSysInfo>

#include "settings.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();

signals:
       void preferencesUpdate();

private slots:
    void on_toolButton_appPath_clicked();
    void on_toolButton_configFiles_clicked();
    void on_btn_save_clicked();
    void on_btn_loadDefault_clicked();
    void on_lineEdit_appPath_textChanged(const QString &arg1);
    void on_lineEdit_configFiles_textChanged(const QString &arg1);
    void on_lineEdit_envKeyRenderman_textChanged(const QString &arg1);
    void on_lineEdit_envKeyMaya_textChanged(const QString &arg1);
    void on_lineEdit_envKeyPath_textChanged(const QString &arg1);
    void on_lineEdit_envValueRenderman_textChanged(const QString &arg1);
    void on_lineEdit_envValueMaya_textChanged(const QString &arg1);
    void on_lineEdit_envValuePath_textChanged(const QString &arg1);

    void on_lineEdit_configFiles_editingFinished();

    void on_lineEdit_appPath_editingFinished();

    void closeCheck();

private:
    Ui::Preferences *ui;

    void saveSettings();
    void showSettings(const QStringList &value);

    bool isStateChange() const;
    void setStateChange(const bool &value);
    bool stateChange;
};

#endif // PREFERENCESUI_H
