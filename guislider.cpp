#include "./guislider.h"
#include "./ui_guislider.h"
#include "RangeUtils.h"

GuiSlider::GuiSlider(RtGuiSlider &rtg, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiSlider), rtg(rtg)
{

    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(rtg.name));    
    ui->horizontalSlider->setRange(0,INT_MAX);

    float val=rtg.val;
    ui->horizontalSlider->setValue(rescaleRange(val, rtg.min, rtg.max, 0,(float)INT_MAX));
    ui->lineEdit->setText(QString::number(rtg.val));
}

GuiSlider::~GuiSlider()
{
    delete ui;
}








void GuiSlider::on_lineEdit_editingFinished()
{
    float val=(int)ui->lineEdit->text().toFloat();
    ui->horizontalSlider->setValue(rescaleRange(val, rtg.min, rtg.max, 0,(float)INT_MAX));
    rtg.setVal( val);
}


void GuiSlider::on_horizontalSlider_sliderMoved(int position)
{    
    float val=rescaleRange(position, 0,(float)INT_MAX,rtg.min, rtg.max);
    val=int(val/rtg.step) * rtg.step;
    val=constrainRange(val,rtg.min,rtg.max);
    ui->lineEdit->setText(QString::number(val));
    rtg.setVal( val);
}




