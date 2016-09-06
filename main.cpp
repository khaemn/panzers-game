#include <QApplication>
#include "Engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Engine * game = new Engine();
    game->show();
    game->run();
    return a.exec();
}
