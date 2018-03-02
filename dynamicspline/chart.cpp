/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <vector>
#include <QTimer>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series1(0),
    m_series2(0),
    m_series3(0),
    //m_series4(0),
    //m_series5(0),
    m_axis(new QValueAxis),
    m_step(0),
    m_x(0.1),
    m_y1(1),
    m_y2(1),
    m_y3(1),
    m_y4(1),
    m_y5(1),
    minValue(0),
    maxValue(0),
    sample(0),
    count(2),
    sec(0),
    interval(500)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    //m_timer.setInterval(32);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dataskip()));
    timer->start(interval);

    m_series1 = new QScatterSeries(this);
    QPen red(Qt::red);
    red.setWidth(0);
    m_series1->setPen(red);
    m_series1->setName("m/s");
    //m_series1->append(m_x, m_y1);

    m_series2 = new QScatterSeries(this);
    QPen green(Qt::green);
    green.setWidth(0);
    m_series2->setPen(green);
    m_series2->setName("m/s");
    //m_series2->append(m_x, m_y2);

    m_series3 = new QScatterSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(0);
    m_series3->setPen(blue);
    m_series3->setName("m/s");
    //m_series3->append(m_x, m_y3);
/*
    m_series4 = new QScatterSeries(this);
    QPen yellow(Qt::black);
    yellow.setWidth(0);
    m_series4->setPen(yellow);
    m_series4->setName("m/s");
    //m_series4->append(m_x, m_y4);

    m_series5 = new QScatterSeries(this);
    QPen black(Qt::black);
    black.setWidth(0);
    m_series5->setPen(black);
    m_series5->setName("m/s");
    //m_series5->append(m_x, m_y5);
*/
    addSeries(m_series1);
    addSeries(m_series2);
    addSeries(m_series3);
    //addSeries(m_series4);
    //addSeries(m_series5);

    createDefaultAxes();


    setAxisX(m_axis, m_series1);
    setAxisX(m_axis, m_series2);
    setAxisX(m_axis, m_series3);
    //setAxisX(m_axis, m_series4);
    //setAxisX(m_axis, m_series5);

    m_axis->setTickCount(0);
    axisX()->setRange(0, 0.2);
    //axisY()->setRange(-12, 15);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::dataskip()
{
    if(count < (se[0]*se[1]*sec+2))
    {
        count = se[0]*se[1]*sec+2;
    }
    sec += interval/1000;
    qDebug()<<sec;
    qDebug()<<count<<" "<<minValue<<" "<<maxValue;
    qDebug()<<se[0]<<se[1]<<(se[0]*se[1]*sec+2);
}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / m_axis->tickCount();
    //qDebug()<<"x: "<<x;
    qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    //qDebug()<<"m_axis: "<<m_axis->tickCount();
    //qDebug()<<"y: "<<y;
    m_x += y;
    //qDebug()<<"m_x: "<<m_x;
    //m_y = QRandomGenerator::global()->bounded(5) - 2.5;

    if(count<(data.size()-2))
    {
        //qDebug() << count;
        //qDebug() << "m_x: " << m_x;
        m_y1 = ::atof(data[count].c_str());
        m_series1->append(m_x, m_y1);
        m_y2 = ::atof(data[count+1].c_str());
        m_series2->append(m_x, m_y2);
        m_y3 = ::atof(data[count+2].c_str());
        m_series3->append(m_x, m_y3);
        //m_y4 = ::atof(data[count+3].c_str());
        //m_series4->append(m_x, m_y4);
        //m_y5 = ::atof(data[count+4].c_str());
        //m_series5->append(m_x, m_y5);
    }

    scroll(x, 0);
    count += 3;
    if (m_x == 100)
        m_timer.stop();
}
