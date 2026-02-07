#include "qsynthcheckbox.h"
#include <QPainter>
#include "cresourceinitializer.h"
#include "qdprpixmap.h"

QSynthCheckbox::QSynthCheckbox(QWidget *parent) :
    QPushButton(parent)
{
    CResourceInitializer::initializeResources();
    setImages();
}

QSynthCheckbox::~QSynthCheckbox()
{
}

void QSynthCheckbox::mousePressEvent(QMouseEvent* /*e*/)
{
    doClick();
}

void QSynthCheckbox::setImages() {
    buttonImage = QDPRPixmap(QPixmap(":/button.png"));
    ledonImage = QDPRPixmap(QPixmap(":/led_on.png"));
    ledoffImage = QDPRPixmap(QPixmap(":/led_off.png"));
    if ((m_StateList.size() == 2) && (m_StateList.first() == "Off") && (m_StateList.last() == "On"))
    {
        uncheckedImage = QDPRPixmap(QSize(40,40),":/buttonoff.png");
        checkedImage = QDPRPixmap(QSize(40,40),":/buttonon.png");
    }
    else {
        uncheckedImage = QDPRPixmap(QPixmap(":/button_off.png"));
        checkedImage = QDPRPixmap(QPixmap(":/button_on.png"));
    }
}

void QSynthCheckbox::paintEvent(QPaintEvent* /*e*/)
{
    QRect r = QDPRPixmap::realRect(uncheckedImage);
    r.setSize(r.size() * m_Zoom);
    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    if ((m_StateList.size() == 2) && (m_StateList.first()=="Off") && (m_StateList.last()=="On"))
    {
        r.moveTopLeft(QPoint((width()-r.width())/2.0,(height()-r.height())/3.0));
        (m_Value) ? p.drawPixmap(r,checkedImage) : p.drawPixmap(r,uncheckedImage);
    }
    else if (m_StateList.size()<3)
    {
        r.moveTopLeft(QPoint((width()-r.width())/2.0,(height()-r.height())/3.0));
        (m_Value) ? p.drawPixmap(r,checkedImage) : p.drawPixmap(r,uncheckedImage);
    }
    else
    {

        int t=2;
        r.moveBottom(rect().bottom()-6);
        r.moveLeft((width()-r.width())/2.0);
        p.drawPixmap(r,buttonImage);
        QFont f=p.font();
        f.setPointSizeF(10);
        p.setFont(f);
        float dist=float(height()-r.height())/m_StateList.size();
        t+=(dist/2)-6;
        QPen pen=p.pen();
        QBrush brush=p.brush();
        for (int i = 0;i < m_StateList.size(); i++)
        {
            (i == m_Value) ? p.drawPixmap(r.left(),t-8,ledonImage) : p.drawPixmap(r.left(),t-8,ledoffImage);
            p.setPen(Qt::white);
            p.setBrush(Qt::white);
            p.drawText(r.left()+25,t + 9,m_StateList.at(i));
            p.setPen(pen);
            p.setBrush(brush);
            p.drawText(r.left() + 24,t + 8,m_StateList.at(i));
            t += dist;
        }
    }
}

void QSynthCheckbox::doClick()
{
    m_Value++;
    if (m_StateList.isEmpty())
    {
        if (m_Value > 1) m_Value = 0;
    }
    else
    {
        if (m_Value >= m_StateList.size()) m_Value = 0;
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
        m_Value = 0;
        if (!signalsBlocked())
        {
            emit valueChanged(m_Value);
            emit toggled(bool(m_Value));
        }
    }
    setImages();
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
    setImages();
}

void QSynthCheckbox::setZoom(const double zoom)
{
    m_Zoom = zoom;
}
