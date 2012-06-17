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
    ui->code->installEventFilter(this);

    setWindowState(windowState() ^ Qt::WindowFullScreen);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    updateTime();

    ui->imageLabel->setPixmap(QPixmap(":/institut.png"));

    httpDaemon = new HttpDaemon(8080);
}

MainDialog::~MainDialog()
{
    delete ui;
    delete httpDaemon;
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

bool MainDialog::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->code && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            checkCode();
        }

        return false;
    }
    else
    {
        return QObject::eventFilter(object, event);
    }
}

void MainDialog::checkCode()
{
    QCryptographicHash hash(QCryptographicHash::Sha1);

    hash.addData(ui->code->text().toUtf8());

    QString hashValue = QString(hash.result().toHex());

    qDebug() << hashValue;
}
