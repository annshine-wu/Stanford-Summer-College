function reorderCards(spotID, orderNumber) {
  var element = document.getElementById(spotID);
  element.style.order = orderNumber;
}

function displayAllCards(){
  var cardArray = ["cardOne", "cardTwo", "cardThree", "cardFour", "cardFive", "cardSix"];
  for(var x = 0; x < 6; x++){
    document.getElementById(cardArray[x]).src = "back.png";
  }
  cardCheckArray = ["true", "true", "true", "true", "true", "true"];
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

function randomizeCards(){
  var spotArray = ["spotOne", "spotTwo", "spotThree", "spotFour", "spotFive", "spotSix"];
  for(var x = 0; x < 6; x++){
    var randomNum = getRandomInt(0,spotArray.length);
    reorderCards(spotArray[randomNum], x+1);
    spotArray.splice(randomNum,1);
  }
  displayAllCards();
}

document.getElementById('resetButton').addEventListener("click", randomizeCards);

var counter = 0;
var flipCardOne;
var flipCardTwo;
var flipCardOneIndex;
var flipCardTwoIndex;
var check = true;
var cardCheckArray = ["true", "true", "true", "true", "true", "true"];

function matchCards(){
  if(flipCardOne.alt == flipCardTwo.alt){
    cardCheckArray[flipCardOneIndex] = "false";
    cardCheckArray[flipCardTwoIndex] = "false";
    flipCardOne.src = "clear.png";
    flipCardTwo.src = "clear.png";
  } else{
    flipCardOne.src = "back.png"
    flipCardTwo.src = "back.png"
  }
  check = true;
}

function flipCard(cardNumber, imageSource, index){
  if(check && cardCheckArray[index] == "true"){
    document.getElementById(cardNumber).src = imageSource;
    counter += 1;
  }
  if(counter == 1 && check == true){
    flipCardOne = document.getElementById(cardNumber);
    flipCardOneIndex = index;
  } else if(counter == 2 && check == true){
    if(flipCardOne.id != document.getElementById(cardNumber).id){
      flipCardTwo = document.getElementById(cardNumber);
      flipCardTwoIndex = index;
      check = false;
      counter = 0;
      setTimeout(matchCards, 1500);
    } else{
      counter = 1;
    }
  }
}
