import QtQuick 2.0

Column {
    property string fontFamily: root.fontText

    anchors {
        fill: parent
        leftMargin: 10
        topMargin: 2
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Strength: ") + character.strength
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Agility: ") + character.agility
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Stamina: ") + character.stamina
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Intellect: ") + character.intellect
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Spirit: ") + character.spirit
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Spell Damage: ") + character.spellPower
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Spell Hit: ") + character.spellHitChance
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Spell Crit: ") + character.spellCritChance
    }
}
