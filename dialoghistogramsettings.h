#ifndef DIALOGHISTOGRAMSETTINGS_H
#define DIALOGHISTOGRAMSETTINGS_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogHistogramSettings;
}

class DialogHistogramSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogHistogramSettings(QWidget *parent = 0);
    ~DialogHistogramSettings();
    int sliderValueLinear;
    int sliderValueGamma;
    int widgetindex;
private:
    Ui::DialogHistogramSettings *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void slotGammaTransformation();
    void slotHistogramEqualization(bool b);
    void slotInversion(bool b);
    void slotLinearTransformation();

signals:
    void signalGammaTransformation();
    void signalHistogramEqualization(bool b);
    void signalInversion(bool b);
    void signalLinearTransformation();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGHISTOGRAMSETTINGS_H
