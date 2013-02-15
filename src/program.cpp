#include <QtCore/QCoreApplication>

#include "common.h"
#include "server.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    #ifdef _WIN32
    SetConsoleTitleA("Faith Emulator for " TARGET_SYSTEM " (" TARGET_ARCH ") by CptSky");
    #endif

    fprintf(stdout, "Faith Emulator by CptSky...\n");
    fprintf(stdout, "Build for %s (%s), using Qt %s, the %s...\n",
            TARGET_SYSTEM, TARGET_ARCH, QT_VERSION_STR, __TIMESTAMP__);
    fprintf(stdout, "\n");

    Server server;
    return a.exec();
}
