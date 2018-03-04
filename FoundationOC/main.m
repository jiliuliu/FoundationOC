//
//  main.m
//  FoundationOC
//
//  Created by 刘吉六 on 2017/8/16.
//  Copyright © 2017年 liujiliu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Student.h"
#import "Person.h"
#import "MessageForwarding.h"
#import "ARC.h"
#import "NARC.h"
#import "GCDTest.h"




int main(int argc, const char * argv[]) {
    @autoreleasepool {
        void test(void);
        test();
    }
    return 0;
}

void test(void) {
    GCDTest();
    
    //        [ARC test];
    //
    //        [NARC test];
    
    //运行时runtime
    //        [Person printTestInfo];
    
    //消息转发解析
    //        [MessageForwarding printTestInfo];
    
    //property解析
    //        [Student printTestInfo];
}






