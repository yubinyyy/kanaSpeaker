#ifndef FRMSPEAKERMAINWINDOW_H
#define FRMSPEAKERMAINWINDOW_H

#include <QWidget>
#include <QDomNode>

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
    void randomKana();
private:
    QVector<QChar> mKatakanaVec;
    QVector<QChar> mHiraganaVec;

    void readXML(QDomNode *domNode);
    Ui::FrmSpeakerMainWindow *ui;
};

#endif // FRMSPEAKERMAINWINDOW_H
