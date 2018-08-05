#ifndef FRMSPEAKERMAINWINDOW_H
#define FRMSPEAKERMAINWINDOW_H

#include <QWidget>
#include <QDomNode>
#include <QTimer>
#include "settingdialog.h"

namespace Ui {
class FrmSpeakerMainWindow;
}

class FrmSpeakerMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSpeakerMainWindow(QWidget *parent = 0);
    ~FrmSpeakerMainWindow();

public slots:
    void startTimer();
    void randomKana();
    void showPreferencesWidget();
private:
    QVector<QChar> mKatakanaVec;
    QVector<QChar> mHiraganaVec;
    SettingDialog *mSettingDialog;
    QTimer mTimer;

    void readXML(QDomNode *domNode);
    Ui::FrmSpeakerMainWindow *ui;
};

#endif // FRMSPEAKERMAINWINDOW_H
