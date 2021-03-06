#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    ui->cbRangeState->addItem("片假名");
    ui->cbRangeState->addItem("平假名");
    ui->cbRangeState->addItem("片假名+平假名");
    ui->hsTimeStep->setFocusPolicy(Qt::StrongFocus);


    connect(ui->hsTimeStep, SIGNAL(valueChanged(int)), this, SLOT(updateTimeLabel()));
    connect(ui->btnBack,SIGNAL(released()),this,SLOT(hide()));
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

RangeState SettingWidget::getRangeState()
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

qint8 SettingWidget::getTimeStep()
{
    return ui->hsTimeStep->value();
}

void SettingWidget::updateTimeLabel()
{
    ui->lbTimeValue->setText(QString("%1秒").arg(ui->hsTimeStep->value()));
}
