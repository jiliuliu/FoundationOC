//
//  Person.m
//  FoundationOC
//
//  Created by 刘吉六 on 2018/1/9.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import "Person.h"
#import "SIXRuntime.h"

@implementation Person

+ (void)printTestInfo {
    Person *per = [Person new];
    
    //结果都是Person
    NSLog(@"per.class:%@, Person.class:%@,per.class:%@,Person.class:%@", per.class, Person.class, per.class.class, Person.class.class);
    
    [SIXRuntime six_swizzleMethods:self originalSelector:@selector(six_walk) swizzledSelector:@selector(six_sleep)];
    [SIXRuntime six_swizzleMethods:self originalSelector:@selector(six_look) swizzledSelector:@selector(six_listen)];
    
    [SIXRuntime six_swizzleMethods:self originalSelector:@selector(six_say) swizzledSelector:@selector(six_sayxx)];
    
    NSArray *funcNames = [SIXRuntime six_intanceMethodList:Person.class];
    for (NSString *funcName in funcNames) {
        if ([funcName hasPrefix:@"six_"]) {
//            [per performSelector:NSSelectorFromString(funcName)];
            SEL selector = NSSelectorFromString(funcName);
            IMP imp = [per methodForSelector:selector];
            void (*func)(id, SEL) = (void *)imp;
            func(per, selector);
        }
    }
    
    funcNames = [SIXRuntime six_classMethodList:Person.class];
    for (NSString *funcName in funcNames) {
        if ([funcName hasPrefix:@"six_"]) {
            [Person performSelector:NSSelectorFromString(funcName)];
        }
    }
}

- (void)six_walk {
    NSLog(@"walk:%@", NSStringFromSelector(_cmd));
}

- (void)six_sleep {
    NSLog(@"sleep:%@", NSStringFromSelector(_cmd));
}

- (void)six_sayxx {
    NSLog(@"say:%@", NSStringFromSelector(_cmd));
}

+ (void)six_look {
    NSLog(@"look:%@", NSStringFromSelector(_cmd));
}

+ (void)six_listen {
    NSLog(@"listen:%@", NSStringFromSelector(_cmd));
}


@end
