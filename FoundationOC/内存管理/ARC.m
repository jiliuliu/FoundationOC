
///
//  MemoryManagementTest.m
//  FoundationOC
//
//  Created by 刘吉六 on 2018/2/28.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import "ARC.h"

extern void _objc_autoreleasePoolPrint();
extern uintptr_t _objc_rootRetainCount(id obj);

@implementation ARC

+ (void)test {
    //
    [self test1];
    
    [self test2];
}

+ (void)test1 {
    __weak NSMutableArray *weakArr1;
    __weak NSMutableArray *weakArr2;
    {
        NSMutableArray *arr1 = [[NSMutableArray alloc] init];
        weakArr1 = arr1;
        
        NSMutableArray *arr2 = [NSMutableArray array];
        weakArr2 = arr2;
    }
    NSLog(@"weakArr1:%@", weakArr1);
    NSLog(@"weakArr2:%@", weakArr2);
    
    __weak NSMutableArray *weakArr3;
    @autoreleasepool {
        NSMutableArray *arr3 = [NSMutableArray array];
        weakArr3 = arr3;
    }
    NSLog(@"weakArr3:%@", weakArr3);
}

+ (void)test2 {
    //自己生成并持有的对象
    NSMutableArray *arr1 = [[NSMutableArray alloc] init];
    
    //不是自己生成，也不持有
    //怎么证明？那它为什么没有释放啊？请继续看下文。
    NSMutableArray *arr2 = [NSMutableArray array];
    
}

+ (void)test3 {
    
}

+ (void)test4 {
    
}

+ (void)test5 {
    
}

+ (void)test6 {
    
}

+ (void)test7 {
    
}

@end
