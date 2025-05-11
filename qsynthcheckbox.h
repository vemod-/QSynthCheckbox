#ifndef QSYNTHCHECKBOX_H
#define QSYNTHCHECKBOX_H

#include <QPushButton>
#include <QImage>
#include <QResizeEvent>
#include <QPaintEvent>

class QSynthCheckbox : public QPushButton
{
    Q_OBJECT

public:
    explicit QSynthCheckbox(QWidget *parent = nullptr);
    ~QSynthCheckbox();
    QStringList& stateList();
    void setStateList(const QStringList& l);
    int value();
    void addState(const QString& name);
    void setZoom(const double zoom);
public slots:
    void setValue(int v);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent* e);
signals:
    void valueChanged(int value);
    //void toggled(bool value);
private:
    QImage checkedImage;
    QImage uncheckedImage;
    QImage buttonImage;
    QStringList m_StateList;
    int m_Value=0;
    double m_Zoom=1;
private slots:
    void doClick();
};

#endif // QSYNTHCHECKBOX_H
