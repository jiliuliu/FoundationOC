//
//  MessageForwarding.h
//  FoundationOC
//
//  Created by 刘吉六 on 2018/1/9.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import <Foundation/Foundation.h>


@class SomeObject;
@interface MessageForwarding : NSObject

+ (void)printTestInfo;

@property (nonatomic, strong) SomeObject *obj;

- (void)studying;

- (void)eat;

- (void)watchTV;

@end


@interface SomeObject: NSObject

- (void)eat;

- (void)watchTV;

@end
