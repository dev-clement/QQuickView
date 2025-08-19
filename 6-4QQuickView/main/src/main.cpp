#include <QDebug>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQuickView o_view;
    o_view.setSource(QUrl{"qrc:/qml/qml.qml"});
    o_view.show();

    QObject *po_rootObject = o_view.rootObject();
    qDebug() << "root object name: " << po_rootObject->objectName();
    qDebug() << "rect object name; " << po_rootObject->children().at(0)->objectName();

    QString o_objectName{"rect"};
    auto *po_object = po_rootObject->findChild<QObject *>(o_objectName);
    if (!po_object) {
        qDebug() << "The object with name : " + o_objectName + " isn't found";
        return EXIT_FAILURE;
    }

    QQuickItem *po_item = qobject_cast<QQuickItem *>(po_object);

    QColor o_color{ Qt::blue };
    po_item->setProperty("color", o_color);
    po_item->setProperty("width", QVariant::fromValue(800));
    po_item->setProperty("height", QVariant::fromValue(800));
    QQmlProperty::write(po_item, "height", QVariant::fromValue(300));
    return a.exec();
}
