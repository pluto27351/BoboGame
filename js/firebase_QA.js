var dataOpen = 0;

$(document).ready(function(){
  console.log("sadasd");
  // var firebaseConfig = {
  //     apiKey: "AIzaSyBfco5_4skuKC8hFYtFTJMu4jw9QuulUVs",
  //     authDomain: "boboweb-870fd.firebaseapp.com",
  //     databaseURL: "https://boboweb-870fd.firebaseio.com",
  //     projectId: "boboweb-870fd",
  //     storageBucket: "boboweb-870fd.appspot.com",
  //     messagingSenderId: "794460010195",
  //     appId: "1:794460010195:web:e390afc09752bbc8e94626"
  //   };
  // // Initialize Firebase
  // firebase.initializeApp(firebaseConfig);
  //dbQue = firebase.database().ref().child('question');

  // randomQue();
  // createQue();

  //setInterval(update,60);

});
$(".cardData ").click(function(){
  console.log("123");
});

// $(".card").click(function(){
//   console.log("123");
//   // if(dataOpen == 0){
//   //   console.log("456");
//   //   dataOpen = 1;
//   //   $(".cardData").addClass("open");
//   // }
// });




//
// function randomQue(){
//   nowQueNo = 0;
//   for(var i=0;i<queMax;i++){
//     queNum[i] = i+1;
//   }
//
//   for(var i=0;i<30;i++){
//     var a = Math.round(Math.random()* (queMax-1));
//     var b = Math.round(Math.random()* (queMax-1));
//     var t = queNum[a];
//     queNum[a] = queNum[b];
//     queNum[b] = t;
//   }
//
//   // for(var i=0;i<queMax;i++){
//   //     console.log(i + " = " + queNum[i]);
//   // }
// }
//
// function createQue(){
//   if(nowQueNo >= queMaxGet) {
//     alert("完成題目!")
//     return;
//   }
//
//   var dbQueNo = firebase.database().ref().child('question').child(queNum[nowQueNo]);
//
//   dbQueNo.on('child_added', function (snapshot) {
//     if(snapshot.key == 'q'){
//       var data = snapshot.val();
//       $('.question').html(data);
//       var height = $('.question').height() /-2 ;
//       $('.question').css('margin-top',height);
//     }
//     else if(snapshot.key == 'a'){
//       var maxAns = snapshot.numChildren();
//       var anss = [];
//
//       var ansCount = snapshot.child('max').val();
//
//       for(var i=0;i<maxAns-1;i++){
//         anss.push(snapshot.child(i+1).val());
//         if(i < ansCount)ansNo.push(1);
//         else ansNo.push(0);
//       }
//
//       for(var i=0;i<30;i++){
//         var a = Math.round(Math.random()* (maxAns-2));
//         var b = Math.round(Math.random()* (maxAns-2));
//         var t = anss[a];
//         anss[a] = anss[b];
//         anss[b] = t;
//
//         t = ansNo[a];
//         ansNo[a] = ansNo[b];
//         ansNo[b] = t;
//
//       }
//
//       for(var i=0;i<maxAns-1;i++){
//         var ans = anss[i];
//         // console.log("ans =" + anss[i] + "correct = " + ansNo[i]);
//         var newAns = document.createElement("div");
//         newAns .setAttribute('class','answer_style set_left');
//         // if((i+1) == maxAns-1){newball.setAttribute('class','answer_style set_left last_box')}
//         var anstext = document.createElement("p");
//         var ansbox = $(newAns);
//         $(anstext).html(ans);
//
//         ansbox.css('background-color',ballcolor[i]);
//         ansbox.append($(anstext));
//         $('.ans_area').append(ansbox);
//       }
//
//       for(var i=0;i<ansCount;i++){
//         var monster = document.createElement("img");
//         monster.setAttribute('src','img/test.png');
//         monster.setAttribute('class','monster_style');
//         if(i==ansCount-1) monster.setAttribute('class','monster_style last_box');
//         monsters.push($(monster));
//         monstersball.push(-1);
//         //$(monster).css('color',ballcolor[i]);
//         $('.monster_area').append(monster);
//       }
//
//       randomball(maxAns-1);
//
//     }
//   });
//
//   gameStart = true;
//   //randomball(ballAmount);
//   nowQueNo++;
// }
