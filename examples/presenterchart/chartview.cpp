/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QLineSeries>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QAreaSeries>
#include <QTime>

ChartView::ChartView(QWidget* parent):QChartView(parent),
m_index(0)
{
    setChartTitle("Charts presenter");
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    m_timer.setInterval(3000);

//![1]
    QLineSeries* series0 = new QLineSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);

    QScatterSeries* series1 = new QScatterSeries(this);
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);
    series1->setBrush(Qt::white);

    QSplineSeries* series2 = new QSplineSeries(this);
    QPen green(Qt::green);
    green.setWidth(3);
    series2->setPen(green);

    QAreaSeries* series3 = new QAreaSeries(series0);
    QPen yellow(Qt::black);
    yellow.setWidth(3);
    series3->setPen(yellow);
    series3->setBrush(Qt::yellow);
//![1]

//![2]
    int numPoints = 10;

    for (int x = 0; x <= numPoints; ++x) {
        qreal y = qrand() % 100;
        series0->append(x,y);
        series1->append(x,y);
        series2->append(x,y);
    }
//![2]

//![3]
    m_series<<series0;
    m_titles<<chartTitle()+": LineChart";
    m_series<<series1;
    m_titles<<chartTitle()+": ScatterChart";
    m_series<<series2;
    m_titles<<chartTitle()+": SplineChart";
    m_series<<series3;
    m_titles<<chartTitle()+": AreaChart";
//![3]

    addSeries(series0);
    setChartTitle(m_titles.at(0));

//![4]
    foreach (QSeries* series, m_series) {
        QObject::connect(series,SIGNAL(clicked(const QPointF&)),this,SLOT(handlePointClicked(const QPointF&)));
    }
//![4]

    m_timer.start();
}

ChartView::~ChartView()
{
    if(m_series.size()==0) return;
    removeSeries(m_series.at(m_index));
    qDeleteAll(m_series);
}

//![5]
void ChartView::handleTimeout()
{
    if(m_series.size()==0) return;
    removeSeries(m_series.at(m_index));
    m_index++;
    m_index=m_index%m_series.size();
    addSeries(m_series.at(m_index));
    setChartTitle(m_titles.at(m_index));
}
//![5]

//![6]
void ChartView::handlePointClicked(const QPointF& point)
{
    setChartTitle(m_titles.at(m_index) + QString(" x: %1 y: %2").arg(point.x()).arg(point.y()));
}
//![6]
