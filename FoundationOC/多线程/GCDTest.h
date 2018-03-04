//
//  GCDTest.h
//  FoundationOC
//
//  Created by 刘吉六 on 2018/3/4.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#ifndef GCDTest_h
#define GCDTest_h

#import <Foundation/Foundation.h>

#define NSLog(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);

void GCDTest(void) {
    void GCDTest1(void);
    GCDTest1();
    
    NSLog(@"----exit----");
}

void GCDTest_createQueue(void (^block) (dispatch_queue_t, dispatch_queue_t)) {
    dispatch_queue_t backgroundSerialQueue = dispatch_queue_create("backgroundSerialQueue", DISPATCH_QUEUE_SERIAL);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    
    dispatch_queue_t serialQueue = dispatch_queue_create("serial", DISPATCH_QUEUE_SERIAL);
    dispatch_queue_t concurrentQueue = dispatch_queue_create("concurrent", DISPATCH_QUEUE_CONCURRENT);
    
    //避开主线程，单独开启一个线程做测试
    dispatch_async(backgroundSerialQueue, ^{
        NSLog(@"%@:背景线程", [NSThread currentThread]);
        
        block(serialQueue, concurrentQueue);
        
        dispatch_barrier_sync(serialQueue, ^{
            dispatch_semaphore_signal(semaphore);
        });
        dispatch_barrier_sync(concurrentQueue, ^{
            dispatch_semaphore_signal(semaphore);
        });
    });
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
}

void GCDTest1(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"%@:dispatch_sync(serialQueue)1", [NSThread currentThread]);
        });
        NSLog(@"dispatch_sync(serialQueue)1--");
        
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"dispatch_sync(serialQueue)2");
        });
        NSLog(@"dispatch_sync(serialQueue)2--");
        
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"dispatch_sync(serialQueue)3");
        });
        NSLog(@"dispatch_sync(serialQueue)3--");
        
        NSLog(@"************************");
        
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"%@:dispatch_sync(concurrentQueue)1", [NSThread currentThread]);
        });
        NSLog(@"dispatch_sync(concurrentQueue)1--");
        
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"dispatch_sync(concurrentQueue)2");
        });
        NSLog(@"dispatch_sync(concurrentQueue)2--");
        
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"dispatch_sync(concurrentQueue)3");
        });
        NSLog(@"dispatch_sync(concurrentQueue)3--");
    });
}

void GCDTest2(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_sync(serialQueue, ^{ //任务1
            NSLog(@"%@:---1", [NSThread currentThread]);
            //运行后程序卡着这里
            dispatch_sync(serialQueue, ^{ //任务2
                NSLog(@"%@:---2", [NSThread currentThread]);
            });
        });
    });
}

void GCDTest3(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        //只在这里把GCDTest2中的serialQueue改成concurrentQueue
        dispatch_sync(concurrentQueue, ^{ //任务1
            NSLog(@"%@:---1", [NSThread currentThread]);
            dispatch_sync(serialQueue, ^{ //任务2
                [NSThread sleepForTimeInterval:0.02];
                NSLog(@"%@:---2", [NSThread currentThread]);
            });
            NSLog(@"---3");
        });
    });
}

void GCDTest4(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        //只在这里把GCDTest2中的serialQueue改成concurrentQueue
        dispatch_sync(concurrentQueue, ^{ //任务1
            NSLog(@"%@:---1", [NSThread currentThread]);
            //运行后程序卡着这里
            dispatch_sync(serialQueue, ^{ //任务2
                NSLog(@"%@:---2", [NSThread currentThread]);
                dispatch_sync(concurrentQueue, ^{
                    NSLog(@"%@:---3", [NSThread currentThread]);
                    //最终程序卡在这里
                    dispatch_sync(serialQueue, ^{
                        NSLog(@"%@:---4", [NSThread currentThread]);
                    });
                });
            });
        });
    });
}

void GCDTest5(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-serialQueue--1", [NSThread currentThread]);
        });
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-serialQueue--2", [NSThread currentThread]);
        });
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-serialQueue--3", [NSThread currentThread]);
        });
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-sync-serialQueue--4", [NSThread currentThread]);
        });
        [NSThread sleepForTimeInterval:0.02];
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--5", [NSThread currentThread]);
        });
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-serialQueue--6", [NSThread currentThread]);
        });
    });
}

void GCDTest6(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--1", [NSThread currentThread]);
        });
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--2", [NSThread currentThread]);
        });
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--3", [NSThread currentThread]);
        });
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--4", [NSThread currentThread]);
        });
        
    });
}

void GCDTest7(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(serialQueue, ^{ //任务1
            NSLog(@"%@:---1", [NSThread currentThread]);
            dispatch_async(serialQueue, ^{ //任务2
                NSLog(@"%@:---2", [NSThread currentThread]);
            });
            NSLog(@"---3");
        });
    });
}

void GCDTest8(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
            dispatch_async(serialQueue, ^{ //任务1
                NSLog(@"%@:---1", [NSThread currentThread]);
                //运行后程序卡着这里
                dispatch_sync(serialQueue, ^{ //任务2
                    NSLog(@"%@:---2", [NSThread currentThread]);
                });
            });
        });
    });
}

void GCDTest9(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(serialQueue, ^{ //任务1
            NSLog(@"%@:---1", [NSThread currentThread]);
            dispatch_async(serialQueue, ^{ //任务2
                NSLog(@"%@:---2", [NSThread currentThread]);
                [NSThread sleepForTimeInterval:0.01];
                NSLog(@"---3");
            });
            [NSThread sleepForTimeInterval:0.01];
            NSLog(@"---4");
        });
    });
}

void GCDTest10(void) {
    dispatch_async(dispatch_get_main_queue(), ^{
        [NSThread sleepForTimeInterval:0.02];
        NSLog(@"%@:---1", [NSThread currentThread]);
        dispatch_async(dispatch_get_main_queue(), ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@:---2", [NSThread currentThread]);
        });
        NSLog(@"%@:---3", [NSThread currentThread]);
    });
    NSLog(@"%@:---4", [NSThread currentThread]);
}

void GCDTest11(void) {
    NSLog(@"---------GCDTest11-------");
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--1", [NSThread currentThread]);
        });
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--2", [NSThread currentThread]);
        });
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-sync-concurrentQueue--3", [NSThread currentThread]);
        });
        NSLog(@"------space------");
        dispatch_async(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-concurrentQueue--4", [NSThread currentThread]);
        });
    });
}

void GCDTest12(void) {
    NSLog(@"\n---------GCDTest12-------");
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.04];
            NSLog(@"%@-async-serialQueue--1", [NSThread currentThread]);
        });
        dispatch_async(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"%@-async-serialQueue--2", [NSThread currentThread]);
        });
        dispatch_sync(serialQueue, ^{
            NSLog(@"%@-sync-serialQueue--3", [NSThread currentThread]);
        });
        dispatch_async(serialQueue, ^{
            NSLog(@"%@-async-serialQueue--4", [NSThread currentThread]);
        });
    });
}

void GCDTest13(void) {
    NSLog(@"---------GCDTest13-------");
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--1");
        });
        NSLog(@"----");
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--2");
        });
        NSLog(@"----");
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--3");
        });
        NSLog(@"----");
        dispatch_sync(concurrentQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--4");
        });
        NSLog(@"----");
    });
}

void GCDTest14(void) {
    NSLog(@"\n---------GCDTest14-------");
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--1");
        });
        NSLog(@"----");
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--2");
        });
        NSLog(@"----");
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--3");
        });
        NSLog(@"----");
        dispatch_sync(serialQueue, ^{
            [NSThread sleepForTimeInterval:0.02];
            NSLog(@"--4");
        });
        NSLog(@"----");
    });
}

void GCDTest15(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
            dispatch_sync(serialQueue, ^{ //任务1
                NSLog(@"%@:---1", [NSThread currentThread]);
                //运行后程序卡着这里
                dispatch_sync(serialQueue, ^{ //任务2
                    NSLog(@"%@:---2", [NSThread currentThread]);
                });
                NSLog(@"--3");
            });
        });
    });
}

void GCDTest16(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
            dispatch_sync(concurrentQueue, ^{ //任务1
                NSLog(@"%@:---1", [NSThread currentThread]);
                dispatch_sync(concurrentQueue, ^{ //任务2
                    NSLog(@"%@:---2", [NSThread currentThread]);
                });
                NSLog(@"--3");
            });
            NSLog(@"--4");
        });
    });
}

void GCDTest17(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        
    });
}

void GCDTest18(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        
    });
}

void GCDTest19(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        
    });
}

void GCDTest20(void) {
    GCDTest_createQueue(^ (dispatch_queue_t serialQueue, dispatch_queue_t concurrentQueue) {
        
    });
}

#endif /* GCDTest_h */
