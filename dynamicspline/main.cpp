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
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <thread>
#include <vector>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE
using namespace std;

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    QMainWindow window;
    Chart *chart = new Chart;

    ifstream inf("data_ACCL.txt");
    string line;

    vector<string> data_input;
    vector<double> se;
    //cout<<se.size()<<endl;
    int i = 1;
    while (getline(inf, line)) {
        if (i>2)
        {
            data_input.push_back(line);
            if(chart->minValue > ::atof(line.c_str()))
            {
                chart->minValue = ::atof(line.c_str());
            }
            if(chart->maxValue < ::atof(line.c_str()))
            {
                chart->maxValue = ::atof(line.c_str());
            }
        }
        else
        {
            se.push_back(::atof(line.c_str()));
        }
        i++;
    }
    //cout<<se.size()<<endl;
    chart->data = data_input;
    chart->se = se;
    chart->axisY()->setRange(chart->minValue, chart->maxValue);

    chart->setTitle("ACCL data");
    //chart->legend()->hide();
    chart->setAnimationOptions(QChart::NoAnimation);
    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::NonCosmeticDefaultPen);
    window.setCentralWidget(&chartView);
    window.resize(400, 300);
    window.show();
    return a.exec();
}
