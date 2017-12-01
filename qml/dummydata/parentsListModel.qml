import QtQuick 2.0

ListModel
{
    function setChild(name)
	{
	}

    property var parentsNames: ["Alan", "Isabel", "Alex", "Alan Dowling", "Michelle Gilchrist", "Rohan Gilchrist"]

    ListElement
    {
        name: "Alan"
        email: "parent1@mail.com"
        phone: "555 123456"
    }
	
	ListElement
    {
        name: "Isabel"
        email: "parent2@mail.com"
        phone: "555 123456"
    }

    ListElement
    {
        name: "Alex"
        email: "paren3@mail.com"
        phone: "555 123456"
    }

    ListElement
    {
        name: "Alan Dowling"
        email: "parent4@mail.com"
        phone: "555 123456"
    }

    ListElement
    {
        name: "Michelle Gilchrist"
        email: "parent5@mail.com"
        phone: "555 123456"
    }

    ListElement
    {
        name: "Rohan Gilchrist"
        email: "parent6@mail.com"
        phone: "555 123456"
    }


}

