#include "./guislider.h"
#include "./ui_guislider.h"


GuiSlider::GuiSlider(RtGuiSlider &rtg, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiSlider), rtg(rtg)
{

    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(rtg.name));
    ui->horizontalSlider->setRange(rtg.min,rtg.max);
    ui->horizontalSlider->setValue(rtg.val);
    ui->lineEdit->setText(QString::number(rtg.val));
}

GuiSlider::~GuiSlider()
{
    delete ui;
}








void GuiSlider::on_lineEdit_editingFinished()
{

    ui->horizontalSlider->setValue((int)ui->lineEdit->text().toFloat());
    rtg.val = ui->lineEdit->text().toFloat();
}


void GuiSlider::on_horizontalSlider_sliderMoved(int position)
{
    ui->lineEdit->setText(QString::number(position));
}




