import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

MainPage{
    id: root
    signal openCardFromListClicked(var userId, var cardId);

    BackgroundGradient{
        anchors.fill: parent
    }
    TabBar{
        id: tabBar
        width: parent.width
        TabButton{
            text: "Поиск пациента";
            id: tb1
        }
        TabButton{
            text: "Список пациентов";
        }
        TabButton{
            text: "Заявки на регистрацию";
        }
    }

   StackLayout{
       anchors.left: parent.left
       anchors.right: parent.right
       anchors.bottom: parent.bottom
       anchors.top: tabBar.bottom
       currentIndex: tabBar.currentIndex


       SearchCardTab{
           id: searchCardTab
           userID: root.userID
           adminMode: true
           onOpenCardClicked: root.openCardFromListClicked(userID, cardId);
       }

       ShowCardsTab{
           id: showCardsTab
           userID: root.userID
           adminMode: true
           onOpenCardClicked: root.openCardFromListClicked(userID, cardId);
       }

       RequestsTab{

       }

   }

}
