import QtQuick 2.0

RectangleBorders {
    Column {
        anchors.fill: parent

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorWarrior
            property string template: qsTr("Warrior DW Fury Pre-Raid")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorWarrior
            property string template: qsTr("Warrior DW Fury BWL")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorWarrior
            property string template: qsTr("Warrior DW Fury AQ")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorWarrior
            property string template: qsTr("Warrior DW Fury Naxx")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorHunter
            property string template: qsTr("Hunter 8/8 T2")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }

        RectangleBorders {
            height: parent.height / parent.children.length
            width: parent.width
            rectColor: root.colorMage
            property string template: qsTr("Fire Mage T3")
            onRectangleClicked: raid.selectTemplateCharacter(template)

            TextSmall {
                color: "black"
                text: parent.template
            }
        }
    }
}
