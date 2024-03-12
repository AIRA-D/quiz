#include "quiz.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Quiz w;
    w.show();
    return QApplication::exec();
}
