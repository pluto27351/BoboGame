#import <UIKit/UIKit.h>
#import <FirebaseCore/FirebaseCore.h>

int main(int argc, char *argv[]) {
    [FIRApp configure];
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
