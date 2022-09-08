#ifndef GUISLIDER_H
#define GUISLIDER_H

#include <QWidget>
#include "Components/RtGuiControl.h"


namespace Ui { class GuiSlider; }


class GuiSlider : public QWidget
{
    Q_OBJECT

public:
    GuiSlider(RtAudioNs::Components::RtGuiControl &rtg,QWidget *parent = nullptr);
    ~GuiSlider() override;

    GuiSlider(const GuiSlider&) = delete;
    GuiSlider& operator=(const GuiSlider&)= delete;
    GuiSlider(GuiSlider&&) = delete;
    GuiSlider& operator=(GuiSlider&&) = delete;

private slots:

    void onLineEditEditingFinished();

    void onHorizontalSliderSliderMoved(int position);



private:
    Ui::GuiSlider *ui;
    RtAudioNs::Components::RtGuiControl &rtg;
};
#endif // GUISLIDER_H
