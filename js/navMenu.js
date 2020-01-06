
//-------選單效果---------------------------------
var menu = $('.menu');

menu.mouseenter(function(){
  menu.addClass("open");
  console.log("in");
});
menu.mouseleave(function(){
  menu.removeClass("open");
});
//-------選單效果 end-----------------------------
