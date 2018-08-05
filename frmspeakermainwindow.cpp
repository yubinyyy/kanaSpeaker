#include "frmspeakermainwindow.h"
#include "ui_frmspeakermainwindow.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QCursor>
#include <QDomElement>
#include <QRandomGenerator>

static inline QString titleElement() { return QStringLiteral("title"); }
static inline QString folderElement() { return QStringLiteral("folder"); }
static inline QString bookmarkElement() { return QStringLiteral("bookmark"); }

FrmSpeakerMainWindow::FrmSpeakerMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmSpeakerMainWindow)
{
    ui->setupUi(this);
    mSettingDialog = new SettingDialog(this);


    QFont defaultFont;
    defaultFont.setFamily("Hiragino Mincho ProN");
    defaultFont.setPointSize(64);
    ui->blackboard->setFont(defaultFont);
    ui->blackboard->setReadOnly(true);


    QFile xmlFile(":data/kana.xml");
    if(!xmlFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(NULL, QString("title"), QString("open error!"));
    }

    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(&xmlFile, true, &errorStr, &errorLine,
                                &errorColumn))
    {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
    }


    QDomElement root = domDocument.documentElement();
    readXML(&root);

    connect(ui->randomBtn,SIGNAL(released()),this, SLOT(startTimer()));
    connect(&this->mTimer, SIGNAL(timeout()), this, SLOT(randomKana()));
    connect(ui->btnPreferences,SIGNAL(released()),this,SLOT(showPreferencesWidget()));
}

FrmSpeakerMainWindow::~FrmSpeakerMainWindow()
{
    delete mSettingDialog;
    delete ui;
}


void FrmSpeakerMainWindow::readXML(QDomNode *domNode)
{
    QDomNodeList childNodeList = domNode->childNodes();
    uint childCount = childNodeList.count();
    for(uint i = 0; i < childCount; i++)
    {
        QDomNode childNode = childNodeList.at(i);
        if(!childNode.isNull())
        {
            if(childNode.isText())
            {
                QDomNode parentNode = childNode.parentNode().parentNode();
                if(parentNode.isElement())
                {
                    //QDebug(QtDebugMsg)<<parentNode.toElement().tagName();
                    //continue;

                    //QDebug(QtDebugMsg)<<childNode.toText().data();
                    QString kana = childNode.toText().data();
                    if(parentNode.toElement().tagName() == "katakana")
                    {
                        for (int i = 0; i < kana.size(); ++i)
                        {
                            mKatakanaVec.push_back(kana.at(i));
                        }
                    }
                    else if(parentNode.toElement().tagName() == "hiragana")
                    {
                        for (int i = 0; i < kana.size(); ++i)
                        {
                            mHiraganaVec.push_back(kana.at(i));
                        }
                    }
                }
            }
            readXML(&childNode);
        }
    }
}


void FrmSpeakerMainWindow::randomKana()
{
   int count = mKatakanaVec.count() + mHiraganaVec.count();
   if(count <= 0)
   {
       return;
   }
   int index = rand()%(count+1);
   //QDebug(QtDebugMsg)<<"random index:"<<index;
   QChar kana;
   if(index < mKatakanaVec.count())
   {
        kana = mKatakanaVec[index];
        ui->blackboard->setText(kana);

   }
   else
   {
        kana = mHiraganaVec[count - index];
        ui->blackboard->setText(kana);
   }

   ui->blackboard->repaint();
}

void FrmSpeakerMainWindow::showPreferencesWidget()
{
    mSettingDialog->exec();
    mTimer.setInterval(mSettingDialog->getTimeStep() * 1000);
}

void FrmSpeakerMainWindow::startTimer()
{
    mTimer.stop();
    mTimer.setInterval(mSettingDialog->getTimeStep() * 1000);
    mTimer.start();
}
