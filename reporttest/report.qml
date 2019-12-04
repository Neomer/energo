import Qt 4.7
//import QtQuick 1.0
import "D:/project/Qt/energo/reporttest/main.js" as MainJS

Rectangle {
	color: "#fff"
    border.color: "#fff"
    border.width: 0
	width: window.width - 10
	height: window.height
	anchors.fill: parent
	Column {
		width: parent.width
		spacing: 3
		Row {
			width: parent.width
			Text {
				font.bold: true
				font.pointSize: 18
				font.family: "Verdana"
				text: "Document title"
			}
		}
		Row {
			width: parent.width
			Text {
				font.bold: true
				font.pointSize: 14
				font.family: "Verdana"
				color: "#AAAAAA"
				text: "Document header"
			}
		}
		Row {
			width: parent.width
			Grid {
				columns: 3
				spacing: 3
				width: parent.width
				Rectangle {
					border.width: 1
					width: 50
					Text {
						font.pointSize: 12
						font.family: "Verdana"
						text: "1"
					}
				}
				Rectangle {
					border.width: 1
					width: 150
					Text {
						font.pointSize: 12
						font.family: "Verdana"
						text: "Name"
					}
				}
				Rectangle {
					border.width: 1
					width: 350
					Text {
						font.pointSize: 12
						font.family: "Verdana"
						text: "Some information"
					}
				}
			}
		}
	}
}
