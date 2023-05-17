#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QGraphicsView>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _fieldScene = new QGraphicsScene( this );
    _fieldScene->addText( "There will be field here" );
    _fieldScene->setSceneRect( QRect() );
    ui->graphicsView->setScene( _fieldScene );

    qDebug() << _fieldScene->itemsBoundingRect();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonGenerate_clicked()
{
    if ( _checkInput() )
    {
        //uint rectHight = ( _fieldScene->itemsBoundingRect().size().height() / ui->lineEditH->text().toUInt() );
        uint sideLength = ( _fieldScene->itemsBoundingRect().size().width() / ui->lineEditW->text().toUInt() );


        int x, y = 0;

        for ( uint h = 0; h < ui->lineEditH->text().toUInt(); ++h )
        {
            x = 0;
            for ( uint w = 0; w < ui->lineEditW->text().toUInt(); ++w )
            {
                _fieldScene->addRect( QRect( x, y, sideLength, sideLength )
                                      , Qt::SolidLine /*, QBrush( QColor( 35, 80, 124 ), Qt::SolidPattern )*/ );
                x += sideLength;
            }
            y += sideLength;
        }
    }
}

bool MainWindow::_checkInput()
{
    if ( ui->lineEditH->text().isEmpty() )
    {
        QMessageBox::critical( this, "Ошибка", "Поле \"H\" должно быть заполнено.", QMessageBox::Ok );
        return false;
    }
    if ( ui->lineEditW->text().isEmpty() )
    {
        QMessageBox::critical( this, "Ошибка", "Поле \"W\" должно быть заполнено.", QMessageBox::Ok );
        return false;
    }

    bool ok = true;
    ui->lineEditH->text().toUInt( &ok );
    if ( !ok )
    {
        QMessageBox::critical( this, "Ошибка", "Некорректное значение в поле \"H\".", QMessageBox::Ok );
        return false;
    }

    ui->lineEditW->text().toUInt( &ok );
    if ( !ok )
    {
        QMessageBox::critical( this, "Ошибка", "Некорректное значение в поле \"W\".", QMessageBox::Ok );
        return false;
    }
    return true;
}
