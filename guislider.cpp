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
    ui->horizontalSlider->setValue(rescaleRange(val, rtg.getMin(), rtg.getMax(), 0,(float)INT_MAX));
    ui->lineEdit->setText(QString::number(rtg.getVal()));
}

GuiSlider::~GuiSlider()
{
    delete ui;
}








void GuiSlider::on_lineEdit_editingFinished()
{
    float val=(int)ui->lineEdit->text().toFloat();
    ui->horizontalSlider->setValue(rescaleRange(val, rtg.getMin(), rtg.getMax(), 0,(float)INT_MAX));
    rtg.setVal( val);
}


void GuiSlider::on_horizontalSlider_sliderMoved(int position)
{    
    float val=rescaleRange(position, 0,(float)INT_MAX,rtg.getMin(), rtg.getMax());
    val=int(val/rtg.getStep()) * rtg.getStep();
    val=constrainRange(val,rtg.getMin(),rtg.getMax());
    ui->lineEdit->setText(QString::number(val));
    rtg.setVal( val);
}




