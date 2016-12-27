//
//  ViewController.m
//  Goo
//
//  Created by 马驰也 on 2016/12/26.
//  Copyright © 2016年 马驰也. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

#include "BRIDGE.h"



- (void)viewDidLoad {
    [super viewDidLoad];
    _programView.accessibilityPlaceholderValue = @"在这里输入程序";

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


- (IBAction)compileProgram:(id)sender {
    NSString* programNSString = _programView.string;
    const char* programString = [programNSString UTF8String];
    
    morphologyMain(programString);   //词法分析
    
    string tokenString = getTokenResult();
    NSString* tokenNSString = [NSString stringWithUTF8String:tokenString.c_str()];
    //cout << tokenString;
    _tokenView.string = tokenNSString;
//    _tokenList. = @"apple";

    
    grammarMain();   //文法分析
    
    string compileString = getErrorResult();
    
    
    if (compileString == "") {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"编译成功"];
        [alert runModal];

        quadMain();  //生成四元式
        targetMain();   //生成目标代码
        string quadString = getQuadResult();
        NSString* quadNSString = [NSString stringWithUTF8String:quadString.c_str()];
        //cout << quadString;
        _quadView.string = quadNSString;
    }
    else {
        
        
        NSString* compileNSString = [NSString stringWithUTF8String:compileString.c_str()];
        //cout << compileString;
        
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:compileNSString];
        [alert runModal];
        
        _quadView.string = @"";
    }
    
    string symbolString = getSymbolResult();
    NSString* symbolNSString = [NSString stringWithUTF8String:symbolString.c_str()];
    //cout << symbolString;
    _symbolView.string = symbolNSString;
    
    
    
}
@end
