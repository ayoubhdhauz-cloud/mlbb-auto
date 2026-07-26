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
    
    ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(
        (void*)zzz_compressed_data, zzz_compressed_size,
        60.0f, NULL, io.Fonts->GetGlyphRangesVietnamese());
    
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

    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Attach();

        // ── Method offsets ──────────────────────────────────────
        offset[0] = get_offset(KH_STR("UnityEngine.CoreModule.dll"), KH_STR("UnityEngine"), KH_STR("Camera"), KH_STR("get_main"), 0);
        offset[1] = get_offset(KH_STR("UnityEngine.CoreModule.dll"), KH_STR("UnityEngine"), KH_STR("Camera"), KH_STR("WorldToViewportPoint"), 2);
        offset[2] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleBridge"), KH_STR("get_bStartBattle"), 0);
        offset[3] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("LogicBattleManager"), KH_STR("GetPlayerLogic"), 1);
        offset[4] = get_offset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("CoolDownData"), KH_STR("GetCoolTime"), 0);

        // ── Hook GetCoolTime for No Skill CD feature ────────────
        if (offset[4]) {
            DobbyHook(offset[4], (void*)GetCoolTime_Hook, (void**)&GetCoolTime_orig);
        }

        // ── Field offsets (original) ────────────────────────────
        offsetField[0]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleManager"), KH_STR("m_LocalPlayerShow"));
        offsetField[1]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_vCachePosition"));
        offsetField[2]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleManager"), KH_STR("m_dicPlayerShow"));
        offsetField[3]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_bSameCampType"));
        offsetField[4]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_bDeath"));
        offsetField[5]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicFighter"), KH_STR("m_SkillComp"));
        offsetField[6]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicSkillComp"), KH_STR("m_CoolDownComp"));
        offsetField[7]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_OwnSkillComp"));
        offsetField[8]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("ShowOwnSkillComp"), KH_STR("skillUseTypeList"));
        offsetField[9]  = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("ShowOwnSkillComp"), KH_STR("m_SkillList"));
        offsetField[10] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowSkillData"), KH_STR("m_TranID"));
        offsetField[11] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("CoolDownComp"), KH_STR("m_DicCoolInfo"));
        offsetField[12] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowPlayer"), KH_STR("m_iSummonStartSkillId"));

        // ── Field offsets (NEW features) ────────────────────────
        // ESP HP Bar
        offsetField[13] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_iMaxHp"));
        offsetField[14] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_iHp"));
        // ESP Name
        offsetField[15] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("ShowEntity"), KH_STR("m_strName"));
        // Speed Hack — LogicFighter.m_MoveComp, LogicMoveComp.m_fRunSpeed
        offsetField[16] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicFighter"), KH_STR("m_MoveComp"));
        offsetField[17] = Il2CppGetFieldOffset(KH_STR("Assembly-CSharp.dll"), KH_STR("Battle"), KH_STR("LogicMoveComp"), KH_STR("m_fRunSpeed"));

        // ── Static instances ────────────────────────────────────
        Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleData"), KH_STR("m_BattleBridge"), &BattleBridge_Instance);
        Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("BattleManager"), KH_STR("Instance"), &BattleManager_Instance);
        Il2CppGetStaticFieldValue(KH_STR("Assembly-CSharp.dll"), KH_STR(""), KH_STR("LogicBattleManager"), KH_STR("Instance"), &InstanceBattle);
    });
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

    if (MenDeal == true) {
        [self.view setUserInteractionEnabled:YES];
    } else {
        [self.view setUserInteractionEnabled:NO];
    }

    MTLRenderPassDescriptor* renderPassDescriptor = view.currentRenderPassDescriptor;
    if (renderPassDescriptor != nil)
    {
        id <MTLRenderCommandEncoder> renderEncoder =
            [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder pushDebugGroup:@"ImGui Jane"];

        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui::NewFrame();

        // Font scale
        ImFont* font = ImGui::GetFont();
        font->Scale = 15.f / font->FontSize;

        // Window position (centered)
        CGFloat x = (([UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width)  - 400) / 2;
        CGFloat y = (([UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height) - 350) / 2;

        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(400, 350), ImGuiCond_FirstUseEver);

        if (MenDeal == true)
        {
            ImGui::Begin(KH_STR("Hack Mobile Legend Auto Update"), &MenDeal);

            if (ImGui::BeginTabBar("FuncTabBar_English"))
            {
                // ════════════════════════════════════════════════
                //  TAB 1 — ESP
                // ════════════════════════════════════════════════
                if (ImGui::BeginTabItem(KH_STR("Esp")))
                {
                    ImGui::Separator();

                    // Row 1: Line + Box
                    ImGui::Checkbox(KH_STR("Line"),     &Line);
                    ImGui::SameLine(140);
                    ImGui::Checkbox(KH_STR("Esp Box"),  &ESPBox);

                    // Row 2: Skill CD + Spell CD
                    ImGui::Checkbox(KH_STR("Skill CD"), &ESPSkillCD);
                    ImGui::SameLine(140);
                    ImGui::Checkbox(KH_STR("Spell CD"), &ESPSpellCD);

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Text(KH_STR("Extra ESP"));
                    ImGui::Separator();
                    ImGui::Spacing();

                    // Row 3: Name + HP Bar
                    ImGui::Checkbox(KH_STR("Name"),     &ESPName);
                    ImGui::SameLine(140);
                    ImGui::Checkbox(KH_STR("HP Bar"),   &ESPHPBar);

                    // Row 4: Distance
                    ImGui::Checkbox(KH_STR("Distance"), &ESPDistance);

                    ImGui::EndTabItem();
                }

                // ════════════════════════════════════════════════
                //  TAB 2 — MISC
                // ════════════════════════════════════════════════
                if (ImGui::BeginTabItem(KH_STR("Misc")))
                {
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Text(KH_STR("Skill"));
                    ImGui::Separator();
                    ImGui::Spacing();

                    // No Skill CD
                    ImGui::Checkbox(KH_STR("No Skill CD"), &NoSkillCD);
                    if (NoSkillCD) {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), KH_STR("[ON]"));
                    }
                    ImGui::TextDisabled(KH_STR("  Force enemy skill cooldown to 0"));

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Text(KH_STR("Movement"));
                    ImGui::Separator();
                    ImGui::Spacing();

                    // Speed Hack toggle
                    ImGui::Checkbox(KH_STR("Speed Hack"), &SpeedHack);
                    if (SpeedHack) {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), KH_STR("[ON]"));
                    }

                    // Speed multiplier slider (only active when SpeedHack is on)
                    if (!SpeedHack) ImGui::BeginDisabled();
                    ImGui::SliderFloat(KH_STR("Speed x"), &SpeedMultiplier, 1.0f, 5.0f, "%.1fx");
                    if (!SpeedHack) ImGui::EndDisabled();

                    ImGui::TextDisabled(KH_STR("  1.0 = normal  |  5.0 = max"));

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }

            ImGui::End();
        }

        // Draw ESP overlay (always runs, guards are inside DrawESP)
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        DrawESP(draw_list);

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
