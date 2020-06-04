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
        property string crit: character.meleeCritChance.length < 8 ? qsTr("Critical strike: ") :
                                                                     qsTr("Crit: ")

        text: crit + character.meleeCritChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Hit: ") + character.meleeHitChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("Attack Power: ") + character.meleeAttackPower
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("MH Skill: ") + character.wpnSkillMh
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: qsTr("OH Skill: ") + character.wpnSkillOh
    }
}
