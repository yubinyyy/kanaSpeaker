#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

enum  RangeState
{
    KATAKANA,
    HIRAGANA,
    FIFTY
};

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    RangeState getRangeState();
    qint8 getTimeStep();
public slots:
    void updateTimeLabel();
private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
