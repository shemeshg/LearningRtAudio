#ifndef GUISLIDER_H
#define GUISLIDER_H

#include <QWidget>
#include "WaveTableCallback.h"

namespace Ui { class GuiSlider; }


class GuiSlider : public QWidget
{
    Q_OBJECT

public:
    GuiSlider(RtGuiControl &rtg,QWidget *parent = nullptr);
    ~GuiSlider();

private slots:

    void on_lineEdit_editingFinished();

    void on_horizontalSlider_sliderMoved(int position);



private:
    Ui::GuiSlider *ui;
    RtGuiControl &rtg;
};
#endif // GUISLIDER_H
