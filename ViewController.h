//
//  ViewController.h
//  Goo
//
//  Created by 马驰也 on 2016/12/26.
//  Copyright © 2016年 马驰也. All rights reserved.
//

#import <Cocoa/Cocoa.h>



@interface ViewController : NSViewController

@property (strong) IBOutlet NSView *mainView;

@property (unsafe_unretained) IBOutlet NSTextView *programView;

@property (unsafe_unretained) IBOutlet NSTextView *tokenView;
@property (weak) IBOutlet NSTableView *tokenList;

@property (unsafe_unretained) IBOutlet NSTextView *symbolView;

@property (unsafe_unretained) IBOutlet NSTextView *quadView;

@property (unsafe_unretained) IBOutlet NSTextView *targetView;

@property (weak) IBOutlet NSButton *doesOptim;


- (IBAction)compileProgram:(id)sender;


@end






