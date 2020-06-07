import QtQuick 2.0
import ItemSort 1.0

RectangleBorders {
    height: 60
    width: parent.width

    property int sortBoxHeight: 35
    property int sortBoxWidth: 100

    Row {
        height: parent.height
        width: parent.width - 3
        anchors {
            right: parent.right
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.05

            onRectangleClicked: itemModel.selectSort(ItemSort.ByIlvl)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByIlvl)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByIlvl ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: qsTr("ILVL")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.4

            onRectangleClicked: itemModel.selectSort(ItemSort.ByName)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByName)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByName ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: qsTr("Name")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.2

            onRectangleClicked: itemModel.selectSort(ItemSort.ByPhase)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByPhase)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByPhase ? root.darkGray :
                                                                             root.darkDarkGray

            TextSmall {
                text: qsTr("Phase")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.1

            onRectangleClicked: itemModel.selectSort(ItemSort.ByItemType)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByItemType)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByItemType ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: qsTr("Type")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.25

            rectColor: root.darkDarkGray

            TextSmall {
                text: qsTr("Source")
            }
        }
    }
}
