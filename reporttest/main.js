function CreateGRID() {
	var val = JSON.parse(window.data);
	for (var row in val.rows)
	{
		var textElement = Qt.createQmlObject(
				'import Qt 4.7; Text { text: "' + val.rows[row] + '"}',
		                                     grid);
		//grid.children.push(Text);
	}
}
