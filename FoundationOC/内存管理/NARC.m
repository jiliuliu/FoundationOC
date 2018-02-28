//
//  NARC.m
//  FoundationOC
//
//  Created by 刘吉六 on 2018/2/28.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import "NARC.h"

@implementation NARC

+ (void)test {
    [self test1];
}

+ (void)test1 {
    //mrc下
    
    //array1自己生成并持有
    NSMutableArray *array1 = [[NSMutableArray alloc] init];
    
    NSMutableArray *array2 = [NSMutableArray array];
    //这句，array2才持有对象
    [array2 retain];
    
    NSLog(@"%ld, %ld", array1.retainCount, array2.retainCount);
    
    NSString *array = @"dsd";
    NSLog(@"++++:%ld", array.retainCount);
    
}

+ (void)test2 {
    
}

+ (void)test3 {
    
}

+ (void)test4 {
    
}

@end
