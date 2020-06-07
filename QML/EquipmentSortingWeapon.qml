import QtQuick 2.0
import WeaponSort 1.0

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

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByIlvl)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByIlvl)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByIlvl ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: qsTr("ILVL")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.4

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByName)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByName)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByName ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: qsTr("Name")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.05

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByDps)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByDps)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByDps ? root.darkGray :
                                                                               root.darkDarkGray

            TextSmall {
                text: "DPS"
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.05

            onRectangleClicked: weaponModel.selectSort(WeaponSort.BySpeed)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.BySpeed)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.BySpeed ? root.darkGray :
                                                                                 root.darkDarkGray

            TextSmall {
                text: qsTr("Speed")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.15

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByPhase)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByPhase)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByPhase ? root.darkGray :
                                                                                 root.darkDarkGray

            TextSmall {
                text: qsTr("Phase")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.1

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByItemType)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByItemType)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByItemType ? root.darkGray :
                                                                                    root.darkDarkGray

            TextSmall {
                text: qsTr("Type")
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: parent.width * 0.2

            rectColor: root.darkDarkGray

            TextSmall {
                text: qsTr("Source")
            }
        }
    }
}
