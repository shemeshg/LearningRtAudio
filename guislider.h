#ifndef GUISLIDER_H
#define GUISLIDER_H

#include <QWidget>


namespace Ui { class GuiSlider; }


class GuiSlider : public QWidget
{
    Q_OBJECT

public:
    GuiSlider(const QString &name,int val, int min, int max,QWidget *parent = nullptr);
    ~GuiSlider();

private slots:

    void on_lineEdit_editingFinished();

    void on_horizontalSlider_sliderMoved(int position);



private:
    Ui::GuiSlider *ui;
};
#endif // GUISLIDER_H
