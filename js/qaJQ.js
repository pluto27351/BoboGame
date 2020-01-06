var openCard = null;
var onBox = 0
var cardBox = $(".cardBox");
$(document).ready(function(){
  createQA();

});

function createQA(){
  var question = firebase.database().ref().child('question');

  question.on('child_added', function (snapshot) {
    // console.log(snapshot.child("q").val());
    var newBox = document.createElement("div");
    newBox.setAttribute('class','box');
    var front = document.createElement("div");
    front.setAttribute('class','card front');
    var frontText ="<p>" + snapshot.child("q").val() + "</p>" ;
    $(front).append(frontText);

    var back = document.createElement("div");
    back.setAttribute('class','card back');
    var backText = document.createElement("p");
    var ansAmount = snapshot.child("a/max").val();
    for(var i=0;i<ansAmount;i++){
      if(i != 0)$(backText).append("<br />");
      $(backText).append(snapshot.child("a/"+(i+1)).val());
    }
    $(back).append($(backText));

    $(newBox).append($(front));
    $(newBox).append($(back));
    cardBox.append($(newBox));

  });
}

// $(".box").click(function(event){
$(document).on('click', '.box', function(){
  console.log("box");
  if($(this).hasClass("flipped")){
    openCard.toggleClass("flipped");
    openCard = null;
  }else{
    if(openCard)openCard.toggleClass("flipped");
    openCard = $(this);
    openCard.toggleClass("flipped");
  }
  onBox = 1;
})

$(document).on('click', 'body', function(){
  console.log("body");
  if(onBox == 0){
    if(openCard)openCard.toggleClass("flipped");
    openCard = null;
  }
  onBox = 0;
})
