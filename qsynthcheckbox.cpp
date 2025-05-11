#include "qsynthcheckbox.h"
#include <QPainter>
#include "cresourceinitializer.h"

QSynthCheckbox::QSynthCheckbox(QWidget *parent) :
    QPushButton(parent)
{
    CResourceInitializer::initializeResources();
    uncheckedImage=QImage(":/button_off.png");
    checkedImage=QImage(":/button_on.png");
    buttonImage=QImage(":/button.png");
    //connect(this,&QAbstractButton::clicked,this,&QSynthCheckbox::doClick);
}

QSynthCheckbox::~QSynthCheckbox()
{
}

void QSynthCheckbox::mousePressEvent(QMouseEvent* /*e*/)
{
    doClick();
}

void QSynthCheckbox::paintEvent(QPaintEvent* /*e*/)
{
    QRectF r=uncheckedImage.rect();
    r.setSize(r.size()*m_Zoom);
    //r.setSize(uncheckedImage.size());
    QPainter p(this);
    if ((m_StateList.size() == 2) && (m_StateList.first()=="Off") && (m_StateList.last()=="On"))
    {
        uncheckedImage = QImage(":/buttonoff.png").scaled(40,40);
        checkedImage = QImage(":/buttonon.png").scaled(40,40);
        r.moveTopLeft(QPoint((width()-r.width())/2.0,(height()-r.height())/3.0));
        //r.moveCenter(rect().center());
        (m_Value) ? p.drawImage(r,checkedImage) : p.drawImage(r,uncheckedImage);
    }
    else if (m_StateList.size()<3)
    {
        r.moveTopLeft(QPoint((width()-r.width())/2.0,(height()-r.height())/3.0));
        //r.moveCenter(rect().center());
        (m_Value) ? p.drawImage(r,checkedImage) : p.drawImage(r,uncheckedImage);
    }
    else
    {

        int t=2;
        r.moveBottom(rect().bottom()-6);
        r.moveLeft((width()-r.width())/2.0);
        p.drawImage(r,buttonImage);
        QFont f=p.font();
        f.setPointSizeF(10);
        p.setFont(f);
        float dist=float(height()-r.height())/m_StateList.size();
        t+=(dist/2)-6;
        QPen pen=p.pen();
        QBrush brush=p.brush();
        for (int i=0;i<m_StateList.size();i++)
        {
            (i==m_Value) ? p.drawImage(r.left(),t-8,QImage(":/led_on.png")) : p.drawImage(r.left(),t-8,QImage(":/led_off.png"));
            p.setPen(Qt::white);
            p.setBrush(Qt::white);
            p.drawText(r.left()+25,t+9,m_StateList.at(i));
            p.setPen(pen);
            p.setBrush(brush);
            p.drawText(r.left()+24,t+8,m_StateList.at(i));
            t+=dist;
        }
    }
}

void QSynthCheckbox::doClick()
{
    m_Value++;
    if (m_StateList.isEmpty())
    {
        if (m_Value > 1) m_Value=0;
    }
    else
    {
        if (m_Value >= m_StateList.size()) m_Value=0;
    }
    if (!signalsBlocked())
    {
        emit valueChanged(m_Value);
        emit toggled(bool(m_Value));
    }
    update();
}

QStringList& QSynthCheckbox::stateList()
{
    return m_StateList;
}

void QSynthCheckbox::setStateList(const QStringList &l)
{
    m_StateList=l;
    if (m_Value >= m_StateList.size())
    {
        m_Value=0;
        if (!signalsBlocked())
        {
            emit valueChanged(m_Value);
            emit toggled(bool(m_Value));
        }
    }
    update();
}

int QSynthCheckbox::value()
{
    return m_Value;
}

void QSynthCheckbox::setValue(int v)
{
    m_Value=v;
    if (!signalsBlocked())
    {
        emit valueChanged(m_Value);
        emit toggled(bool(m_Value));
    }
    update();
}

void QSynthCheckbox::addState(const QString &name)
{
    m_StateList.append(name);
}

void QSynthCheckbox::setZoom(const double zoom)
{
    m_Zoom=zoom;
}
