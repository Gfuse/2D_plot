/*
 * imagecompare.cpp
 *
 *  Created on:
 *      Author: Majid
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qwt_point_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_color_map.h>
#include <qwt_interval.h>
#include <qwt_date.h>
/*
 * make a time scale that
 *
 */
class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw( const QDateTime &base ):
        baseTime( base )
    {
    }
    virtual QwtText label( double v ) const
    {
        QDateTime upTime = baseTime.addSecs(static_cast<int>( v ) );
        return upTime.toString();
    }
private:
    QDateTime baseTime;
};

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom,"Date Time Utc");
    ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,new TimeScaleDraw( QDateTime::currentDateTimeUtc() ));
    ui->qwtPlot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft | Qt::AlignBottom );
    ui->qwtPlot->setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
    ui->qwtPlot->setAxisTitle(0,"Rate");
    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 131, 131, 131 ) );
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth( 1 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas->setPalette( canvasPalette );
    ui->qwtPlot->setCanvas(canvas);
    //ui->ScaleWidget->setColorBarEnabled(true);
    ui->ScaleWidget->setMargin(20);
    QVector<double> time, rate;
    root= new Signal<double>(nullptr,"root",time,rate);
    Signal<double>* stock=new Signal<double>(root,"0",time,rate);
    Signal<double>* commodity=new Signal<double>(root,"1",time,rate);
    Signal<double>* indices=new Signal<double>(root,"2",time,rate);
    Signal<double>* currency=new Signal<double>(root,"3",time,rate);
    Signal<double>* di_currency=new Signal<double>(root,"4",time,rate);
    for(size_t i=0;i<4;++i){
        time.clear();
        rate.clear();
        for(size_t n=0;n<1000;++n){
            time.push_back(n);
            rate.push_back(n*n/(i+1));
        }
        new Signal<double>(stock,"signal_"+QString::number(i),time,rate);
        ui->stocks->addItem("signal_"+QString::number(i));
        new Signal<double>(commodity,"signal_"+QString::number(i),time,rate);
        ui->commodity->addItem("signal_"+QString::number(i));
        new Signal<double>(indices,"signal_"+QString::number(i),rate,time);
        ui->indices->addItem("signal_"+QString::number(i));
        new Signal<double>(currency,"signal_"+QString::number(i),time,rate);
        ui->courrency->addItem("signal_"+QString::number(i));
        new Signal<double>(di_currency,"signal_"+QString::number(i),rate,time);
        ui->digitalcurrency->addItem("signal_"+QString::number(i));
    }
    connect(ui->stocks,&QComboBox::currentTextChanged,this,[=](){this->plot(ui->stocks->currentText(),"0");});
    connect(ui->commodity,&QComboBox::currentTextChanged,this,[=](){this->plot(ui->commodity->currentText(),"1");});
    connect(ui->indices,&QComboBox::currentTextChanged,this,[=](){this->plot(ui->indices->currentText(),"2");});
    connect(ui->courrency,&QComboBox::currentTextChanged,this,[=](){this->plot(ui->courrency->currentText(),"3");});
    connect(ui->digitalcurrency,&QComboBox::currentTextChanged,this,[=](){this->plot(ui->digitalcurrency->currentText(),"4");});
    this->show();
}
MainWindow::~MainWindow(){
    delete ui;
    delete root;
}
void MainWindow::plot(const QString &name,const QString &parent){
    std::pair<QVector<double>,QVector<double>>* data=root->read_data(name,parent);
    if(data!=nullptr){
        ui->qwtPlot->detachItems();
        QwtPointArrayData *data1=new QwtPointArrayData(data->first,data->second);
        QwtPlotCurve *curve1 = new QwtPlotCurve();
        curve1->setTitle( name );
        curve1->setPen( Qt::blue, 4 );
        curve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        curve1->setSamples(data1);
        curve1->attach(ui->qwtPlot);

        ui->qwtPlot->replot();
    }
}

