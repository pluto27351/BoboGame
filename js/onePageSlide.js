//-------單頁滑動效果------------------------------
var infos = [];
var infoBtns = [];
var now = 0;
var tScroll;
var width,pointW,initPos,monsterW;

document.addEventListener("wheel", myFunction);

$(document).ready(function(){
  tScroll =0;
  initPos = 60;
  pointW = $("footer>div:nth-child(2)").width();
  monsterW = $(".monster").width();
  width = $(window).width() - pointW - initPos - monsterW;
  for(var i=2;i<=6;i++){
      infos.push($(".container>div:nth-child("+ i +")"));

      var point = $("footer>div:nth-child("+ i +")");
      infoBtns.push(point);
      var x = (width / 4) * (i-2) + initPos;
      point.css("left",x);
      if(i==2){
        x = x + pointW/2 - $(".player").width()/2;
        $(".player").css("left",x);
      }
  }

  // infos[0].css("opacity","1");
});

function myFunction(event) {
  var d = (event.deltaY/100);
  tScroll += d;
  tScroll= Clamp(tScroll,0,40);  //0 25 50 75 100

  var disScroll = tScroll - (now*10);

  console.log("now = "+now);
  if(disScroll <= -10 && now !=0){
      infos[now].removeClass("now");
      now -= 1 ;disScroll=0;
      infos[now].addClass("now");
  }else if(disScroll >= 10 && now != 4){
      infos[now].removeClass("now");
      now += 1 ;disScroll=0;
      infos[now].addClass("now");
  }

  var x = width * (tScroll/40) +  initPos;
  x = x + pointW/2 - $(".player").width()/2;
  $(".player").css("left",x);

}

$(".point").click(function(){
  var i= $(this).attr("val");

  infos[now].removeClass("now");
  now = i-'0' ;disScroll=0;
  infos[now].addClass("now");

  tScroll = now*10;
  var x = width * (now/4) +  initPos;
  x = x + pointW/2 - $(".player").width()/2;
  $(".player").css("left",x);

  console.log("select now = "+now);
});

//-------單頁滑動效果 end-------------------------

function Clamp(n,min,max){
  return (n<min?min:(n > max? max:n));
}


//-------圖片箱-----------------------------------

var selectedPic = $(".selected");
$(".selectBox>img").mouseenter(function(){
  var picSrc = $(this).attr("src");
  $(".showPic").attr("src", picSrc);

  selectedPic.removeClass("selected");
  selectedPic = $(this);
  selectedPic.addClass("selected");
});
