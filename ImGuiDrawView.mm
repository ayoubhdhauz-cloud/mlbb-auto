//Require standard library
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <Foundation/Foundation.h>
//Imgui library
#import "Esp/CaptainHook.h"
#import "Esp/ImGuiDrawView.h"
#import "IMGUI/imgui.h"
#import "IMGUI/imgui_impl_metal.h"
#import "IMGUI/zzz.h"
//Patch library
#import "5Toubun/NakanoIchika.h"
#import "5Toubun/NakanoNino.h"
#import "5Toubun/NakanoMiku.h"
#import "5Toubun/NakanoYotsuba.h"
#import "5Toubun/NakanoItsuki.h"
#include "hack/Vector3.h"
#include "hack/Vector2.h"
#include "obfuscate.h"
#include <vector>
#include "Il2cpp.h"
#import "esp.h"
#import "5Toubun/dobby.h"
#import "IMGUI/imgui_impl_metal.h"
#include "IMGUI/imgui_internal.h"
#define kScale [UIScreen mainScreen].scale
#define patch_NULL(a, b) vm(ENCRYPTOFFSET(a), strtoul(ENCRYPTHEX(b), nullptr, 0))
#define patch(a, b) vm_unity(ENCRYPTOFFSET(a), strtoul(ENCRYPTHEX(b), nullptr, 0))

@interface ImGuiDrawView () <MTKViewDelegate>
@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;
@end

@implementation ImGuiDrawView




- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];

    if (!self.device) abort();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    
    ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF((void*)zzz_compressed_data, zzz_compressed_size, 60.0f, NULL, io.Fonts->GetGlyphRangesVietnamese());
    
    ImGui_ImplMetal_Init(_device);


    return self;
}

+ (void)showChange:(BOOL)open
{
    MenDeal = open;
}

- (MTKView *)mtkView
{
    return (MTKView *)self.view;
}

- (void)loadView
{

 

    CGFloat w = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width;
    CGFloat h = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height;
    self.view = [[MTKView alloc] initWithFrame:CGRectMake(0, 0, w, h)];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.mtkView.device = self.device;
    self.mtkView.delegate = self;
    self.mtkView.clearColor = MTLClearColorMake(0, 0, 0, 0);
    self.mtkView.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0];
    self.mtkView.clipsToBounds = YES;
    // ── Init Il2Cpp functions + method offsets ONCE ──────────────────────
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Attach();
        offset[0] = get_offset(KH_STR("UnityEngine.CoreModule.dll"), KH_STR("UnityEngine"), KH_STR("Camera"), KH_STR("get_main"), 0);
        offset[1] = get_offset(KH_STR("UnityEngine.CoreModule.dll"), KH_STR("UnityEngine"), KH_STR("Camera"), KH_STR("WorldToViewportPoint"), 2);
        offset[2] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleBridge"), KH_STR("get_bStartBattle"), 0);
        offset[3] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("LogicBattleManager"), KH_STR("GetPlayerLogic"), 1);
        offset[4] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("CoolDownData"), KH_STR("GetCoolTime"), 0);
        offsetField[5]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicFighter"), KH_STR("m_SkillComp"));
        offsetField[6]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicSkillComp"), KH_STR("m_CoolDownComp"));
        offsetField[7]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_OwnSkillComp"));
        offsetField[8]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("ShowOwnSkillComp"), KH_STR("skillUseTypeList"));
        offsetField[9]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("ShowOwnSkillComp"), KH_STR("m_SkillList"));
        offsetField[10] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowSkillData"), KH_STR("m_TranID"));
        offsetField[11] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("CoolDownComp"), KH_STR("m_DicCoolInfo"));
        offsetField[12] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowPlayer"), KH_STR("m_iSummonStartSkillId"));
    });

    // ── Refresh singleton instances EVERY frame (changes each match) ──────
    Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleData"), KH_STR("m_BattleBridge"), &BattleBridge_Instance);
    Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleManager"), KH_STR("Instance"), &BattleManager_Instance);
    Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("LogicBattleManager"), KH_STR("Instance"), &InstanceBattle);
}



#pragma mark - Interaction

- (void)updateIOWithTouchEvent:(UIEvent *)event
{
    UITouch *anyTouch = event.allTouches.anyObject;
    CGPoint touchLocation = [anyTouch locationInView:self.view];
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(touchLocation.x, touchLocation.y);

    BOOL hasActiveTouch = NO;
    for (UITouch *touch in event.allTouches)
    {
        if (touch.phase != UITouchPhaseEnded && touch.phase != UITouchPhaseCancelled)
        {
            hasActiveTouch = YES;
            break;
        }
    }
    io.MouseDown[0] = hasActiveTouch;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

#pragma mark - MTKViewDelegate

- (void)drawInMTKView:(MTKView*)view
{
   
    
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = view.bounds.size.width;
    io.DisplaySize.y = view.bounds.size.height;

    CGFloat framebufferScale = view.window.screen.scale ?: UIScreen.mainScreen.scale;
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);
    io.DeltaTime = 1 / float(view.preferredFramesPerSecond ?: 120);
    
    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
    

//Define your bool/function in here
    static bool show_s1 = false;    
    static bool show_s2 = false;    
    static bool show_s3 = false;    
    static bool show_s4 = false;    
    static bool show_s5 = false;    
    static bool show_s6 = false;                    
    static bool show_s7 = false;        
    static bool show_s8 = false;      
    static bool show_s9 = false;     
    static bool show_s10 = false;     
    static bool show_s11 = false;     
    static bool show_s12 = false;     

//Define active function
    static bool show_s0_active = false;
    static bool show_s1_active = false;
    
        
        if (MenDeal == true) {
            [self.view setUserInteractionEnabled:YES];
        } else if (MenDeal == false) {
            [self.view setUserInteractionEnabled:NO];
        }

        MTLRenderPassDescriptor* renderPassDescriptor = view.currentRenderPassDescriptor;
        if (renderPassDescriptor != nil)
        {
            id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
            [renderEncoder pushDebugGroup:@"ImGui Jane"];

            ImGui_ImplMetal_NewFrame(renderPassDescriptor);
            ImGui::NewFrame();

            
            ImFont* font = ImGui::GetFont();
            font->Scale = 15.f / font->FontSize;
            
            CGFloat x = (([UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width) - 360) / 2;
            CGFloat y = (([UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height) - 300) / 2;
            
            ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
            
            if (MenDeal == true)
            {                
                ImGui::Begin(KH_STR("Hack Mobile Legend Auto Update"), &MenDeal);
if (ImGui::BeginTabBar("FuncTabBar_English")) {
                    if (ImGui::BeginTabItem("Esp")) {
ImGui::Checkbox("Line", &Line);
ImGui::Checkbox("Esp Box", &ESPBox);
ImGui::Checkbox("Esp Skill CD", &ESPSkillCD);
ImGui::Checkbox("Esp Spell CD", &ESPSpellCD);

ImGui::EndTabItem();
                    }


                    ImGui::EndTabBar();

            }





                
                

                

                ImGui::End();
                //require this one inside this to attach when first open menu
                
            }
            ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
DrawESP(draw_list);


//This function is a patch example function, doesn't work on this menu because I didn't add the button into menu UI
            


            ImGui::Render();
            ImDrawData* draw_data = ImGui::GetDrawData();
            ImGui_ImplMetal_RenderDrawData(draw_data, commandBuffer, renderEncoder);
          
            [renderEncoder popDebugGroup];
            [renderEncoder endEncoding];

            [commandBuffer presentDrawable:view.currentDrawable];
        }

        [commandBuffer commit];
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size
{
    
}
@end

