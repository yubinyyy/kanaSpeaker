#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    ui->cbRangeState->addItem("片假名");
    ui->cbRangeState->addItem("平假名");
    ui->cbRangeState->addItem("片假名+平假名");
    ui->hsTimeStep->setFocusPolicy(Qt::StrongFocus);


    connect(ui->hsTimeStep, SIGNAL(valueChanged(int)), this, SLOT(updateTimeLabel()));
    connect(ui->btnBack,SIGNAL(released()),this,SLOT(hide()));
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

RangeState SettingDialog::getRangeState()
{
    int index = ui->cbRangeState->currentIndex();
    switch (index ) {
    case 0:
        return KATAKANA;
    case 1:
        return HIRAGANA;
    case 2:
        return FIFTY;
    default:
        return FIFTY;
    }
}

qint8 SettingDialog::getTimeStep()
{
    return ui->hsTimeStep->value();
}

void SettingDialog::updateTimeLabel()
{
    ui->lbTimeValue->setText(QString("%1秒").arg(ui->hsTimeStep->value()));
}
