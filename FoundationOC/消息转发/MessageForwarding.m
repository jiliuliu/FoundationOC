//
//  MessageForwarding.m
//  FoundationOC
//
//  Created by 刘吉六 on 2018/1/9.
//  Copyright © 2018年 liujiliu. All rights reserved.
//

#import "MessageForwarding.h"
#import <objc/runtime.h>

/*
 消息派发
 
 id returnValue = [someObject messageName:parameter];
 Id returnValue = objc_msgSend(someObject, @selector(messageName:), parameter);
 
 objc_msgSend函数会在类中搜索方法列表，找到就跳转方法实现，否则沿着继承体系继续往上找，最终找不到就执行消息转发
 objc_msgSend会将匹配结果缓存在快速映射表中，对比静态绑定的函数调用操作
 
 struct objc_method {
     SEL method_name;
     char *method_types;
     IMP method_imp;
 }
 
 
 消息转发
 
 在本类和父类中都找不到此方法，就执行消息转发。
 a.动态方法解析：看类是否能动态添加方法
 b.有没有其他对象能处理这条消息，没有则启动完整的消息转发机制，系统把消息封装成NSInvocation对象中，再给接收者发过去。
 
 1.类在收到无法解读的消息后，调用
 + (BOOL)resolveInstanceMethod:(SEL)selector;
 + (BOOL)resolveClassMethod:(SEL)selector;
 表示这个类是否新增一个实例方法来处理这个选择子，使用这个方法的前提是相关方法的实现代码已经写好，只等着运行的时候动态插入类中
 
 2.备援接受者
 - (id)forwardingTargetForSelector:(SEL)selector;
 把消息转给其它对象来处理
 
 3.系统把消息封装成NSInvocation对象中，再给接收者发过去。
 - (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector;
 // 处理转发的消息，进入此方法，就不会产生崩溃
 - (void)forwardInvocation:(NSInvocation *)anInvocation;
 */

@implementation MessageForwarding

+ (void)printTestInfo {
    MessageForwarding *stu = [MessageForwarding new];
    stu.obj = [SomeObject new];
    //分别注释几个方法来分析
    [stu studying];
    [stu eat];
    [stu watchTV];
}

//1.类在收到无法解读的消息后，调用
+ (BOOL)resolveInstanceMethod:(SEL)sel {
    NSLog(@"resolveInstanceMethod:%@", NSStringFromSelector(sel));
    if ([NSStringFromSelector(sel) isEqualToString:@"studying"]) {
        SEL newSel = @selector(study);
        Method method = class_getInstanceMethod(self, newSel);
        class_addMethod(self, sel, method_getImplementation(method), method_getTypeEncoding(method));
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}

// 2.备援接受者，把消息转给其它对象来处理
- (id)forwardingTargetForSelector:(SEL)aSelector {
    NSLog(@"forwardingTargetForSelector:%@", NSStringFromSelector(aSelector));
    if ([NSStringFromSelector(aSelector) isEqualToString:@"eat"]) {
        return self.obj;
    }
    return [super forwardingTargetForSelector:aSelector];
}

//3.系统把消息封装成NSInvocation对象中，再给接收者发过去。
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    NSLog(@"methodSignatureForSelector:%@", NSStringFromSelector(aSelector));
    NSMethodSignature *ms = [super methodSignatureForSelector:aSelector];
    if (ms == nil) {
        ms = [SomeObject instanceMethodSignatureForSelector:aSelector];
    }
    return ms;
}

//3.系统把消息封装成NSInvocation对象中，再给接收者发过去。
// 处理转发的消息，进入此方法，就不会产生崩溃
- (void)forwardInvocation:(NSInvocation *)anInvocation {
    NSLog(@"forwardInvocation:%@", NSStringFromSelector(anInvocation.selector));
    if (anInvocation) {
        [anInvocation invokeWithTarget:self.obj];
    }
}

- (void)study {
    NSLog(@"正在读书");
}

@end



@implementation SomeObject

- (void)eat {
    NSLog(@"SomeObject在eat");
}

- (void)watchTV {
    NSLog(@"SomeObject在watchTV");
}
@end
