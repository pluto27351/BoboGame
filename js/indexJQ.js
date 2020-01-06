

// $(".ball").mouseenter(function(){
//  console.log("132");
//   $(this).css("animation", "keepRot 2s infinite linear");
// });
// $(".ball").mouseleave(function(){
//    $(this).css("animation", "none");
//  });

$(document).ready(function(){
  var n=1;
  for(var i=1;i<6;i++){
    setTimeout(function () {
      console.log(".balls>a:nth-child("+ n +")");
      $(".balls>a:nth-child("+ n +")").addClass("ballon");
      n++
    }, i*200);
  }

 });

//
//$(".ball").mouseenter(function(){
//    $(this).addClass("flipped");
//});
//$(".ball").mouseleave(function(){
//    $(this).removeClass("flipped");
//});

//
//  //---沒用了-----------------------
//
//
//  // var ballSize = [];
//  var pi = (Math.PI );
//
//  $(document).ready(function(){
//    // ballSize.push($('.info img').width());
//    // ballSize.push($('.info img').height());
//
//  });
//
//  $(".ball").mouseenter(function(){
//    // $(this).children("img").css("width", ballSize[0]*1.05);
//    $(this).children("img").animateRotate(160,500);
//  });
//
//  $(".ball").mouseleave(function(){
//    // $(this).children("img").css("width", ballSize[0]);
//    $(this).children("img").animateRotate(0,500);
//  });
//
//
//  function getMousePos(event) {
//         var e = event;
//         var scrollX = document.documentElement.scrollLeft || document.body.scrollLeft;
//         var scrollY = document.documentElement.scrollTop || document.body.scrollTop;
//         var x = e.clientX + scrollX;
//         var y = e.clientY + scrollY;
//         //alert('x: ' + x + '\ny: ' + y);
//         mouxeX= x;
//         mouxeY = y;
//  }
//
//  $.fn.animateRotate = function (angle, duration, easing, complete) {
//    var args = $.speed(duration, easing, complete);
//    var step = args.step;
//    var initR = MatrixToReg(this.css('transform'));
//    angle -= initR;
//    var high = angle / (Math.cos((pi*1.2)+pi) + 1);
//    return this.each(function(i, e) {
//      args.complete = $.proxy(args.complete, e);
//      args.step = function(now) {
//        var a = (Math.cos((pi*1.2) / angle * now + pi) + 1) * high;  //回彈  *1.2->增加時間 0~1.2pi
//      //  var a = (Math.cos(pi / angle * now + pi) + 1)/2*now;      //正常  +pi->位移圖形至-1~1段落(0~pi)
//        $.style(e, 'transform', 'rotate(' + (a+initR) + 'deg)');
//        if (step) return step.apply(e, arguments);
//      };
//      $({deg: 0}).animate({deg: angle}, args);
//    });
//  };
//
//  function MatrixToReg(matrix){
//    var values = matrix.split('(')[1].split(')')[0].split(',');
//    var a = values[0];
//    var b = values[1];
//    var c = values[2];
//    var d = values[3];
//    var scale = Math.sqrt(a * a + b * b);
//
//    var sin = b / scale;
//    return (Math.round(Math.atan2(b, a) * (180 / Math.PI)));
//
//  }
//
//  // $(".logo").mouseenter(function(){
//  //   $(".logo img").css("width", logoSize[0]*1.05);
//  //   $(".logo img").animateRotate(160,500);
//  // });
//  //
//  // $(".logo").mouseleave(function(){
//  //   $(".logo img").css("width", logoSize[0]);
//  //   $(".logo img").animateRotate(0,500);
//  //
//  // });
