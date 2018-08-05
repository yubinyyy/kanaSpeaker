#include "frmspeakermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmSpeakerMainWindow w;
    w.show();

    return a.exec();
}
