var ansbox = document.getElementById("ans");
var queNum = [];
var queMax = 22;
var queMaxGet = 8;
var nowQueNo = 0;
var ansNo = [];
var dbQue;

$(document).ready(function(){
  var firebaseConfig = {
      apiKey: "AIzaSyBfco5_4skuKC8hFYtFTJMu4jw9QuulUVs",
      authDomain: "boboweb-870fd.firebaseapp.com",
      databaseURL: "https://boboweb-870fd.firebaseio.com",
      projectId: "boboweb-870fd",
      storageBucket: "boboweb-870fd.appspot.com",
      messagingSenderId: "794460010195",
      appId: "1:794460010195:web:e390afc09752bbc8e94626"
    };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  //dbQue = firebase.database().ref().child('question');

  // randomQue();
  // createQue();
  //setInterval(update,60);


});


function randomQue(){
  nowQueNo = 0;
  for(var i=0;i<queMax;i++){
    queNum[i] = i+1;
  }

  for(var i=0;i<30;i++){
    var a = Math.round(Math.random()* (queMax-1));
    var b = Math.round(Math.random()* (queMax-1));
    var t = queNum[a];
    queNum[a] = queNum[b];
    queNum[b] = t;
  }

  for(var i=1;i<=8;i++){
    $(".point_area img:nth-child("+i+")").css("opacity","100");
    $(".point_area img:nth-child("+i+")").css("filter","grayscale(100%)");
  }

}

function createQue(){

  if(nowQueNo >= queMaxGet) {
    alert("完成題目!")
    $(".startBtn").css("display","block");
    $(".question_area").css("background-image","url(img/monster22.png)");
    gameStart = false;
    return;
  }

  console.log("next");
  var dbQueNo = firebase.database().ref().child('question').child(queNum[nowQueNo]);

  dbQueNo.on('child_added', function (snapshot) {
    if(snapshot.key == 'q'){
      var data = snapshot.val();
      $('.question').html(data);
      var height = $('.question').height() /-2 ;
      $('.question').css('margin-top',height);
    }
    else if(snapshot.key == 'a'){
      var maxAns = snapshot.numChildren();
      var anss = [];

      var ansCount = snapshot.child('max').val();

      for(var i=0;i<maxAns-1;i++){
        anss.push(snapshot.child(i+1).val());
        if(i < ansCount)ansNo.push(1);
        else ansNo.push(0);
      }

      for(var i=0;i<30;i++){
        var a = Math.round(Math.random()* (maxAns-2));
        var b = Math.round(Math.random()* (maxAns-2));
        var t = anss[a];
        anss[a] = anss[b];
        anss[b] = t;

        t = ansNo[a];
        ansNo[a] = ansNo[b];
        ansNo[b] = t;

      }

      for(var i=0;i<maxAns-1;i++){
        var ans = anss[i];
        var newAns = document.createElement("div");
        newAns .setAttribute('class','answer_style set_left');
        var anstext = document.createElement("p");
        var ansbox = $(newAns);
        $(anstext).html(ans);

        ansbox.css('background-color',ballcolor[i]);
        ansbox.append($(anstext));
        $('.ans_area').append(ansbox);

        console.log("ans"+i + " : " + ansNo[i]);
      }

      for(var i=0;i<ansCount;i++){
        var diamond = document.createElement("img");
        diamond.setAttribute('src','img/test.png');
        diamond.setAttribute('class','diamond_style');
        if(i==ansCount-1) diamond.setAttribute('class','diamond_style last_box');
        diamonds.push($(diamond));
        diamondsball.push(-1);
        //$(diamond).css('color',ballcolor[i]);
        $('.diamond_area').append(diamond);
      }

      randomball(maxAns-1);
    }

      $(".question_area").css("background-image","url(img/monster.png)");
  });

  setTimeout(function () {
    checking = false;
    nowQueNo++;
  },500);

}

function clearQue(){
  $('.question').html("");
  $('.ans_area').empty();
  $('.diamond_area').empty();

  ansNo.length =0;
  diamonds.length = 0;
  diamondsball.length = 0;
}

// $(document).keyup(function(event){
//   if (event.keyCode == 73){
//     clearQue();
//     createQue();
//   }
// })
