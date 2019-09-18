// 安裝步驟-----------------------------------------------------------------------------------------
//
//  跟官方差不多
//  https://firebase.google.com/docs/admob/cpp/cocos2d-x?hl=zh-cn#prerequisites
//
//  加入GoogleService-Info.plist(已上傳) . Firebase C++ SDK(自己載) . Pod(pod已打好上傳 差update)
//
//  最後7.的 Build Phases > Link Binary with Libraries 以添加 GameController.framework。
//  多添加一個"MediaPlayer.framework"
//
//  pro.ios_mac->ios->main.m 裡加入2行 (應將該是已經加入了 我有上傳這檔案)
//    #import <UIKit/UIKit.h>
//    #import <FirebaseCore/FirebaseCore.h>  //++
//
//    int main(int argc, char *argv[]) {
//        [FIRApp configure];                //++
//        NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//        int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
//        [pool release];
//        return retVal;
//    }

//  我有加妳進firebase得共用penny20801@gmail.com這帳號  你看看有沒有 沒有再跟我說～
//---------------------------------------------------------------------------------------------



// .h檔 ---------------------------------------------------------------------------------------------
//
//  #include "firebase/app.h"
//  #include "firebase/database.h"
//
//  firebase::App* app;
//  firebase::database::Database *database;
//  firebase::database::DatabaseReference dbref;
//  firebase::Future<firebase::database::DataSnapshot> data;

//---------------------------------------------------------------------------------------------




// .cpp檔---------------------------------------------------------------------------------------------
//
//  void init(){
//      //獲取資料
//      app = firebase::App::Create(::firebase::AppOptions());
//      database = firebase::database::Database::GetInstance(app);
//      dbref = database->GetReference();
//      data = dbref.GetReference().GetValue();
//  }
//
//
//  void doStep(float dt){  // 要等data抓到 snapshot才能獲取到資料
//      if(data.status() != firebase::kFutureStatusPending){
//          if(data.status() != firebase::kFutureStatusComplete){
//              CCLOG("ERROR : GetValue() return an invalid result");
//          }else if(data.error() != firebase::database::kErrorNone){
//              CCLOG("ERRPR : GetValue return error %d : %s",data.error(),data.error_message());
//          }else {
//              // 主要區！！！
//              const firebase::database::DataSnapshot *snapshot =  data.result();
//              auto children = snapshot->children();
//
//              for(int i=0;i<5;i++){
//                  auto child_data = children[i].children();
//                  auto c_name  = child_data[0].key_string().c_str();
//                  auto c_score = child_data[0].value().int64_value();
//
//                  int sc = (int)_dis*10;  //_dis是距離  用int存->3.5用35存入!!!!!
//
//                  if(sc >= c_score){   //比大小 存資料
//                      for(int j=4;j >i;j--){                 //資料往下移
//                          children[j].GetReference().RemoveValue();
//                          child_data = children[j-1].children();
//                          c_name  = child_data[0].key_string().c_str();
//                          c_score = child_data[0].value().int64_value();
//                          children[j].GetReference().Child(c_name).SetValue(c_score);
//                      }
//                      children[i].GetReference().RemoveValue();
//                      children[i].GetReference().Child("new").SetValue(sc);  //new是使用者名字 sc是距離
//
//                      i=100;                                  //跳離迴圈
//                      data = dbref.GetReference().GetValue(); //獲取新連結(好像也可以不用)
//                  }
//              }
//          }
//      }
//  }

//-------------------------------------------------------------------------------------------------------
