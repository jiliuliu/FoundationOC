//
//  Student.h
//  FoundationOC
//
//  Created by 刘吉六 on 2018/1/3.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol StudentProtocol

/**
 在类里只会生成setter、getter方法的声明，
 系统将不会自动生成对应属性的setter、getter方法的实现和成员变量
 */
@property (nonatomic, assign) NSInteger age;

@end



@interface Student : NSObject <StudentProtocol>

//打印日志
+ (void)printTestInfo;

/**
 1.生成属性name
 2.生成name的setter、getter方法的声明
 3.生成name的setter、getter方法的实现
 4.生成_name成员变量
 */
@property (nonatomic, strong) NSString *name;

/**
 同时重写属性的setter、getter
 系统将不会自动生成成员变量
 */
@property (nonatomic, assign) CGFloat height;

/**
 系统会自动生成_weight和getter方法
 */
@property (nonatomic, assign, readonly) CGFloat weight;

/**
 @synthesize emil;
 生成属性emil的成员变量emil（注意没有下划线）和setter、getter方法的实现
 */
@property (nonatomic, strong) NSString *emil;

/**
 @synthesize tel=_tel;
 生成属性tel的成员变量_tel和setter、getter方法的实现
 */
@property (nonatomic, strong) NSString *tel;

/**
 @dynamic sex
 只会生成setter、getter方法的声明，
 系统将不会自动生成对应属性的setter、getter方法的实现和成员变量
 */
@property (nonatomic, assign) BOOL sex;

- (void)studying;


@end


@interface Student (Category)

/**
 只会生成setter、getter方法的声明，
 系统将不会自动生成对应属性的setter、getter方法的实现和成员变量
 */
@property (nonatomic, strong) NSString *address;

@end
