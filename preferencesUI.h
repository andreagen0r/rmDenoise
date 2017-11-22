#ifndef PREFERENCESUI_H
#define PREFERENCESUI_H

#include <QDialog>
#include <memory>

class QCompleter;

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
    void preferencesUpdated();

private slots:
    void on_toolButton_appPath_clicked();
    void on_toolButton_configFiles_clicked();

    void on_lineEdit_appPath_editingFinished();
    void on_lineEdit_configFiles_editingFinished();
    void on_lineEdit_envKeyRenderman_editingFinished();
    void on_lineEdit_envValueRenderman_editingFinished();
    void on_lineEdit_envKeyMaya_editingFinished();
    void on_lineEdit_envValueMaya_editingFinished();
    void on_lineEdit_envKeyPath_editingFinished();
    void on_lineEdit_envValuePath_editingFinished();

    void on_btn_loadDefault_clicked();
    void on_btn_save_clicked();
    void closeCheck();

private:
    Ui::Preferences *ui;

    bool m_isStateChange;
    std::unique_ptr<QCompleter> m_completer;

    void saveSettings();
    void loadSettings();
};

#endif // PREFERENCESUI_H
