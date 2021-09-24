#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include "dbworker.h"
#include "myfunctions.h"
#include "treeviewmodel.h"
#include "imageprovider.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/icon.png"));
    QCoreApplication::setApplicationName("Российский реестр грыж");


    DBWorker dbWorker;
    MyFunctions myFunctions;
    TreeViewModel treeViewModel;
    treeViewModel.initModel(dbWorker);
    dbWorker.setTreeViewModel(&treeViewModel);
    ImageProvider imageProvider;
    dbWorker.setImageProvider(&imageProvider);

//    qmlRegisterType<UserStatus>("my.UserStatus", 1, 0, "UserStatus");
//    //qmlRegisterUncreatableType<UserStatus::userStatus>("my.UserStatus", 1, 0, "userStatus", "Error: UserStatus cannot be created");
//    //qmlRegisterUncreatableType<UserStatus::userStatus>("my.UserStatus", 1, 0, "userStatus", "Error: UserStatus cannot be created");
//    qmlRegisterUncreatableType<UserStatus::userStatus>("my.UserStatus", 1, 0, "UserStatus", "Error: UserStatus cannot be created");



    QQmlApplicationEngine engine;



    engine.rootContext()->setContextProperty("dbWorker", &dbWorker);
    engine.rootContext()->setContextProperty("myFunctions", &myFunctions);
    engine.rootContext()->setContextProperty("treeViewModel", &treeViewModel);
    engine.rootContext()->setContextProperty("STATUS_ADMIN", STATUS_ADMIN);
    engine.rootContext()->setContextProperty("STATUS_DOCTOR_REQUEST", STATUS_DOCTOR_REQUEST);
    engine.rootContext()->setContextProperty("STATUS_DOCTOR", STATUS_DOCTOR);
    engine.rootContext()->setContextProperty("STATUS_ORDINARY_USER", STATUS_ORDINARY_USER);

    engine.addImageProvider("provider", &imageProvider);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
