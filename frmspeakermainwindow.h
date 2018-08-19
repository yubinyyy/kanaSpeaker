#ifndef FRMSPEAKERMAINWINDOW_H
#define FRMSPEAKERMAINWINDOW_H

#include <QWidget>
#include <QDomNode>
#include <QTimer>
#include <vector>
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
    void initKanaVec();
    void raddomKana();
    void reset();
    void showPreferencesWidget();
private:
    std::vector<QChar> mKatakanaVec;
    std::vector<QChar> mHiraganaVec;
    std::vector<int> mIndexVec;
    SettingDialog *mSettingDialog;
    QTimer mTimer;

    RangeState mCurrentRangeState;
    qint8 mCurrentTimeStep;

    void readXML(QDomNode *domNode);
    Ui::FrmSpeakerMainWindow *ui;
};

#endif // FRMSPEAKERMAINWINDOW_H
