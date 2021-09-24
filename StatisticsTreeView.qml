import QtQuick 2.0

ListView{
    id: view
    model: treeViewModel.data
    focus: true
    pixelAligned: true
    smooth: true
    clip: true

    highlight: Rectangle{
        width: parent.width
        color: "transparent"
    }

    delegate: TreeViewDelegate{
        width: parent.width
    }

}
