#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    ui->timeLabel->setText("");

    ui->wellcomeLabel->setText("Benvingut! Si us plau, introdueix el teu codi");

    ui->code->setEchoMode(QLineEdit::Password);

    setWindowState(windowState() ^ Qt::WindowFullScreen);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    updateTime();

    ui->imageLabel->setPixmap(QPixmap(":/institut.png"));
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::updateTime()
{
    if (ui != NULL && ui->timeLabel != NULL)
    {
        QTime time = QTime::currentTime();
        QString myTime = QString("%1:%2:%3").arg(time.hour()).arg(time.minute()).arg(time.second());
        ui->timeLabel->setText(myTime);

        QDate date = QDate::currentDate();
        QString myDate = QString("%1/%2/%3").arg(date.day()).arg(date.month()).arg(date.year());
        ui->dateLabel->setText(myDate);
    }
}
