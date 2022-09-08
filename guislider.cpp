#include "./guislider.h"
#include "./ui_guislider.h"
#include "Components/RangeUtils.h"

GuiSlider::GuiSlider(RtAudioNs::Components::RtGuiControl &rtg, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiSlider), rtg(rtg)
{

    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(rtg.getName()));
    ui->horizontalSlider->setRange(0,INT_MAX);

    float val=rtg.getVal();
    ui->horizontalSlider->setValue((int)rescaleRange(val, rtg.getMin(), rtg.getMax(), 0,(double)INT_MAX));
    ui->lineEdit->setText(QString::number(rtg.getVal()));

    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &GuiSlider::onLineEditEditingFinished);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &GuiSlider::onHorizontalSliderSliderMoved);
}

GuiSlider::~GuiSlider()
{
    delete ui;
}








void GuiSlider::onLineEditEditingFinished()
{
    float val=(int)ui->lineEdit->text().toFloat();
    ui->horizontalSlider->setValue(rescaleRange(val, rtg.getMin(), rtg.getMax(), 0,(float)INT_MAX));
    rtg.setVal( val);
}


void GuiSlider::onHorizontalSliderSliderMoved(int position)
{    
    float val=rescaleRange(position, 0,(float)INT_MAX,rtg.getMin(), rtg.getMax());
    val=int(val/rtg.getStep()) * rtg.getStep();
    val=constrainRange(val,rtg.getMin(),rtg.getMax());
    ui->lineEdit->setText(QString::number(val));
    rtg.setVal( val);
}




