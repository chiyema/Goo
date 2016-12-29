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

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


- (IBAction)compileProgram:(id)sender {
    NSString* programNSString = _programView.string;
    const char* programChar = [programNSString UTF8String];
    string programString = programChar;
    programString += "\n";
    
    bool optimization;
    if ([_doesOptim state] == NSOnState) optimization = true;
    else optimization = false;
    
    morphologyMain(programString, optimization);   //词法分析

    string compileString = getErrorResult();
        
        
    if (compileString == "") {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"编译通过!"];
        [alert runModal];
        
        string tokenString = getTokenResult();
        NSString* tokenNSString = [NSString stringWithUTF8String:tokenString.c_str()];
        _tokenView.string = tokenNSString;
        
        string symbolString = getSymbolResult();
        NSString* symbolNSString = [NSString stringWithUTF8String:symbolString.c_str()];
        _symbolView.string = symbolNSString;
        
        string quadString = getQuadResult();
        NSString* quadNSString = [NSString stringWithUTF8String:quadString.c_str()];
        _quadView.string = quadNSString;
        
        string targetString = getTargetResult();
        NSString* targetNSString = [NSString stringWithUTF8String:targetString.c_str()];
        _targetView.string = targetNSString;
        
    }
    else {
        NSString* compileNSString = [NSString stringWithUTF8String:compileString.c_str()];
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:compileNSString];
        [alert runModal];
        _tokenView.string = @"Token";
        _symbolView.string = @"Symbol";
        _quadView.string = @"Quad";
        _targetView.string = @"Target";
        
        string tokenString = getTokenResult();
        NSString* tokenNSString = [NSString stringWithUTF8String:tokenString.c_str()];
        _tokenView.string = tokenNSString;
        
        string symbolString = getSymbolResult();
        NSString* symbolNSString = [NSString stringWithUTF8String:symbolString.c_str()];
        _symbolView.string = symbolNSString;
        
        string quadString = getQuadResult();
        NSString* quadNSString = [NSString stringWithUTF8String:quadString.c_str()];
        _quadView.string = quadNSString;
    
        string targetString = getTargetResult();
        NSString* targetNSString = [NSString stringWithUTF8String:targetString.c_str()];
        _targetView.string = targetNSString;
    }
}
@end



