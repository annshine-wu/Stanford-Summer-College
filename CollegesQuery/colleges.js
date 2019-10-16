// I've included both the universities full names and their nicknames
// use the nicknames for this assignment.  I've included the full names
// so those who aren't familiar with Bay Area universities will know
// what the names of the universities actually are.

var univArray = new Array(
		{name: "Stanford University", nickname: "Stanford", ownership: "private", SATh: 1570, SATl: 1380, tuition: 44757},
		{name: "University of California, Berkeley", nickname: "UC Berkeley", ownership: "public", SATh: 1500, SATl: 1250, tuition: 13844},
		{name: "University of California, Santa Cruz", nickname: "UC Santa Cruz", ownership: "public", SATh: 1280, SATl: 1000, tuition: 13398},
		{name: "San Francisco State University", nickname: "SFSU", ownership: "public", SATh: 1110, SATl: 880, tuition: 6468},
		{name: "San Jose State University", nickname: "SJSU", ownership: "public", SATh: 1160, SATl: 880, tuition: 9496},
		{name: "Sonoma State University", nickname: "Sonoma State", ownership: "public", SATh: 1090, SATl: 880, tuition: 7276},
		{name: "California State University, East Bay", nickname: "CalState East Bay", ownership: "public", SATh: 1010, SATl: 800, tuition: 6550, room: 6435},
		{name: "University of San Francisco", nickname: "USF", ownership: "private", SATh: 1270, SATl: 1070, tuition: 41450},
		{name: "Santa Clara University", nickname: "SCU", ownership: "private", SATh: 1380, SATl: 1190, tuition: 43812},
		{name: "Mills College", nickname: "Mills College", ownership: "private", SATh: 1250, SATl: 1040, tuition: 42918}
		);

function updateTable() {
	var ownershipChoice = "";
	var maxTuition = document.getElementById('maximumTuitionInput').value;
	var maxSAT = document.getElementById('highsatInput').value;
	var minSAT = document.getElementById('lowsatInput').value;
	var filteredArr = [];
	var arr = document.getElementById("searchForm");
	for (var i = 0; i < arr.length; i++) {
			if (arr[i].checked){
				ownershipChoice = arr[i].value;
			}
	}
	var count = 0;
	if(maxSAT == ""){
		maxSAT = 2400;
	}
	if(minSAT == ""){
		minSAT = 0;
	}
	if(ownershipChoice != "dontcare"){
		for(var i = 0; i < univArray.length; i++){
			if(univArray[i].ownership == ownershipChoice && univArray[i].SATh <= maxSAT && univArray[i].SATl >= minSAT){
				filteredArr[count] = univArray.slice(i , i+1)[0];
				count += 1;
			}
		}
	} else{
		for(var i = 0; i < univArray.length; i++){
			if(univArray[i].SATh <= maxSAT && univArray[i].SATl >= minSAT){
				filteredArr[count] = univArray.slice(i , i+1)[0];
				count += 1;
			}
		}
	}

	if(maxTuition != ""){
		for(var i = 0; i < filteredArr.length; i++){
			if(filteredArr[i].tuition > maxTuition){
				filteredArr.splice(i,1);
				i--;
			}
		}
	}

	var size = filteredArr.length;
	var replaceTable = "";
	replaceTable += '<tr>' + '<th>Name</th>' + '<th>SAT High</th>' + '<th>SAT Low</th>' + '<th>Tuition</th>' + '</tr>';
	for (var i = 0; i < size; i++) {
		replaceTable += '<tr>' + '<td>' + filteredArr[i].nickname + '</td>' + '<td>' + filteredArr[i].SATh + '</td>' +
		'<td>' + filteredArr[i].SATl + '</td>' + '<td>' + filteredArr[i].tuition + '</td>' + '</tr>';
	}
	document.getElementById('displayTable').innerHTML = replaceTable;
}

document.getElementById('updateButton').addEventListener("click", updateTable);
