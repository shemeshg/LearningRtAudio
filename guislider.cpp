#include "./guislider.h"
#include "./ui_guislider.h"


GuiSlider::GuiSlider(const QString &name,int val, int min, int max, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiSlider)
{

    ui->setupUi(this);
    ui->label->setText(name);
    ui->horizontalSlider->setRange(min,max);
    ui->horizontalSlider->setValue(val);
    ui->lineEdit->setText(QString::number(val));



}

GuiSlider::~GuiSlider()
{
    delete ui;
}








void GuiSlider::on_lineEdit_editingFinished()
{

    ui->horizontalSlider->setValue((int)ui->lineEdit->text().toFloat());
}


void GuiSlider::on_horizontalSlider_sliderMoved(int position)
{
    ui->lineEdit->setText(QString::number(position));
}




