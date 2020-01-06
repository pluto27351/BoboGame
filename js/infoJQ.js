var infobox = $('.infobox');
var nowopen = $('.open');

infobox.click(function(){
  if(!$(this).hasClass("open")){
    nowopen.removeClass("open");
    $(this).addClass("open");
    nowopen = $(this);
  }else{
  }
});
