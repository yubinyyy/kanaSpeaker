#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

enum  RangeState
{
    KATAKANA,
    HIRAGANA,
    FIFTY
};

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    RangeState getRangeState();
    qint8 getTimeStep();
public slots:
    void updateTimeLabel();
    //void slotBackToMainWindow();
private:



    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
