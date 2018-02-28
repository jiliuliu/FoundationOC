//
//  Student.m
//  FoundationOC
//
//  Created by 刘吉六 on 2018/1/3.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import "Student.h"
#import "SIXRuntime.h"

@interface Student ()

@end

@implementation Student

//生成emil成员变量，getter，setter方法
@synthesize emil;

//生成_tel成员变量，getter，setter方法
@synthesize tel = _tel;

@dynamic sex;

+ (void)printTestInfo {
    Student *stu = [Student new];
    
    NSLog(@"\n------------属性列表\n%@", [SIXRuntime six_propertyList:[stu class]]);
    NSLog(@"\n------------成员变量列表\n%@", [SIXRuntime six_instanceVarList:[stu class]]);
    NSLog(@"\n------------实例方法列表\n%@", [SIXRuntime six_intanceMethodList:[stu class]]);
}

- (void)studying {
    NSLog(@"正在读书");
}

- (CGFloat)height {
    return 175;
}

- (void)setHeight:(CGFloat)height {
}

- (NSString *)emil {
    return emil;
}

- (void)setEmil:(NSString *)newEmil {
    emil = newEmil;
}

- (void)setTel:(NSString *)tel {
    _tel = tel;
}

- (NSString *)tel {
    return _tel;
}


@end



@implementation Student (Category)


@end

