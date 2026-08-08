#pragma once
#include "IMGUI/imgui_internal.h"
#include <vector>
#include <cmath>
#define kWidth  [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width
#define kHeight [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height
using namespace std;
static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y * rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x + rhs, lhs.y + rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x - rhs, lhs.y - rhs); }
static inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
static inline ImVec4  operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4  operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4  operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

// ── Existing bools ──────────────────────────────────────────────
bool Line      = false;
static bool MenDeal = true;
bool hackmap   = false;
bool ESPBox    = false;
bool ESPSkillCD = false;
bool ESPSpellCD = false;

// ── NEW: ESP extras ──────────────────────────────────────────────
bool ESPName     = false;   // draw hero name above box
bool ESPHPBar    = false;   // draw HP bar under box
bool ESPDistance = false;   // draw distance to enemy

// ── NEW: MISC ────────────────────────────────────────────────────
bool NoSkillCD   = false;   // skip all enemy skill cooldowns (visual + hook)
bool SpeedHack   = false;   // multiply local-player run speed
float SpeedMultiplier = 1.5f;

// ── Offset arrays (extended) ─────────────────────────────────────
void* offset[50];
size_t offsetField[50];

// Offset slots used:
//   offset[0]  = Camera.get_main
//   offset[1]  = Camera.WorldToViewportPoint
//   offset[2]  = BattleBridge.get_bStartBattle
//   offset[3]  = LogicBattleManager.GetPlayerLogic
//   offset[4]  = CoolDownData.GetCoolTime  (hooked for NoSkillCD)
//
//   offsetField[0]  = BattleManager.m_LocalPlayerShow
//   offsetField[1]  = ShowEntity.m_vCachePosition
//   offsetField[2]  = BattleManager.m_dicPlayerShow
//   offsetField[3]  = ShowEntity.m_bSameCampType
//   offsetField[4]  = ShowEntity.m_bDeath
//   offsetField[5]  = LogicFighter.m_SkillComp
//   offsetField[6]  = LogicSkillComp.m_CoolDownComp
//   offsetField[7]  = ShowEntity.m_OwnSkillComp
//   offsetField[8]  = ShowOwnSkillComp.skillUseTypeList
//   offsetField[9]  = ShowOwnSkillComp.m_SkillList
//   offsetField[10] = ShowSkillData.m_TranID
//   offsetField[11] = CoolDownComp.m_DicCoolInfo
//   offsetField[12] = ShowPlayer.m_iSummonStartSkillId
//   offsetField[13] = ShowEntity.m_iMaxHp        ← NEW
//   offsetField[14] = ShowEntity.m_iHp            ← NEW
//   offsetField[15] = ShowEntity.m_strName        ← NEW (monoString*)
//   offsetField[16] = LogicFighter.m_MoveComp     ← NEW (SpeedHack)
//   offsetField[17] = LogicMoveComp.m_fRunSpeed   ← NEW (SpeedHack)

float boxWidthScreen = 0;
void* BattleBridge_Instance;
void* BattleManager_Instance;
void* LogicBattleManager_Instance;
void* InstanceBattle;

// ── Helper: monoString → NSString ───────────────────────────────
static NSString* ReadMonoString(uintptr_t ptr) {
    if (!ptr) return @"";
    // monoString layout: klass(8) monitor(8) length(4) chars(utf16)
    int len = *(int*)(ptr + 0x10);
    if (len <= 0 || len > 64) return @"";
    return [[NSString alloc] initWithBytes:(void*)(ptr + 0x14)
                                    length:(NSUInteger)(len * 2)
                                  encoding:NSUTF16LittleEndianStringEncoding];
}

// ── Helper: 3D distance ──────────────────────────────────────────
static float Distance3D(Vector3 a, Vector3 b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

// ── Existing functions ───────────────────────────────────────────
void* get_main() {
    return reinterpret_cast<void*(*)()>((uintptr_t)offset[0])();
}
Vector3 WorldToViewportPoint(void* hack, Vector3 position, int mono) {
    return reinterpret_cast<Vector3(*)(void*, Vector3, int)>((uint64_t)offset[1])(hack, position, mono);
}
uintptr_t GetPlayerLogic(uint id) {
    if (!InstanceBattle) return 0;
    return reinterpret_cast<uintptr_t(*)(void*, uint)>((uint64_t)offset[3])((void*)InstanceBattle, id);
}

// ── GetCoolTime — hooked for NoSkillCD ───────────────────────────
typedef int (*GetCoolTime_t)(void*);
static GetCoolTime_t GetCoolTime_orig = nullptr;

static int GetCoolTime_Hook(void* instance) {
    if (NoSkillCD) return 0;
    if (GetCoolTime_orig) return GetCoolTime_orig(instance);
    return 0;
}

int GetCoolTime(void* instance) {
    return reinterpret_cast<int(*)(void*)>((uint64_t)offset[4])(instance);
}

Vector3 GetPlayerPosition(Vector3 position) {
    auto cam = get_main();
    if (!cam) return {0, 0};
    Vector3 screen = WorldToViewportPoint(cam, position, 2);
    if (screen.z > 0) {
        screen.x *= kWidth;
        screen.y = kHeight - screen.y * kHeight;
    } else {
        screen.x = kWidth - screen.x * kWidth;
        screen.y *= kHeight;
    }
    screen.z = screen.z;
    return screen;
}

struct CooldownValues {
    int skillCount;
    int skill1, skill2, skill3, skill4, spell;
};

CooldownValues getPlayerCoolDown(int keys, uintptr_t values) {
    auto logicFighter = GetPlayerLogic((uint)keys);
    if (!logicFighter) return {0,0,0,0,0,0};
    auto m_SkillComp = *(uintptr_t*)((uintptr_t)logicFighter + offsetField[5]);
    if (!m_SkillComp) return {0,0,0,0,0,0};
    auto m_CoolDownComp = *(uintptr_t*)((uintptr_t)m_SkillComp + offsetField[6]);
    if (!m_CoolDownComp) return {0,0,0,0,0,0};
    auto m_OwnSkillComp = *(uintptr_t*)((uintptr_t)values + offsetField[7]);
    if (!m_OwnSkillComp) return {0,0,0,0,0,0};
    int skillCount = 0, skill1 = 0, skill2 = 0, skill3 = 0, skill4 = 0, spell = 0;

    Dictionary1<int, List<int>*>* skillUseTypeList = *(Dictionary1<int, List<int>*>**)((uintptr_t)m_OwnSkillComp + offsetField[8]);
    if (!skillUseTypeList) return {0,0,0,0,0,0};
    for (int v = 0; v < skillUseTypeList->getSize(); v++) {
        auto keysskillUseType   = skillUseTypeList->getKeys()[v];
        auto valuesskillUseType = skillUseTypeList->getValues()[v];
        if (!keysskillUseType) continue;
        if (keysskillUseType != 1) continue;
        skillCount = valuesskillUseType->getSize();
        List<uintptr_t>* m_SkillList = *(List<uintptr_t>**)((uintptr_t)m_OwnSkillComp + offsetField[9]);
        if (!m_SkillList) return {0,0,0,0,0,0};
        for (int i = 0; i < 5; i++) {
            auto p_SkillList = m_SkillList->getItems()[i];
            if (!p_SkillList) continue;
            auto m_TranID     = *(int*)((uintptr_t)p_SkillList + offsetField[10]);
            auto m_DicCoolInfo = *(Dictionary1<int, uintptr_t>**)((uintptr_t)m_CoolDownComp + offsetField[11]);
            if (!m_DicCoolInfo) continue;
            for (int l = 0; l < m_DicCoolInfo->getSize(); l++) {
                auto keysCool   = m_DicCoolInfo->getKeys()[l];
                auto valuesCool = m_DicCoolInfo->getValues()[l];
                if (!keysCool || !valuesCool) continue;
                auto m_iSummonSkillId = *(int*)((uintptr_t)values + offsetField[12]);
                int coolTime = GetCoolTime((void*)valuesCool) / 1000;
                if (keysCool == m_iSummonSkillId) spell = coolTime;
                if ((int)m_TranID != keysCool) continue;
                if (i == 1) skill1 = coolTime;
                if (i == 2) skill2 = coolTime;
                if (i == 3) skill3 = coolTime;
                if (i == 4) skill4 = coolTime;
            }
        }
    }
    return {skillCount, skill1, skill2, skill3, skill4, spell};
}

// ── Speed Hack: apply every frame to local player ────────────────
static void ApplySpeedHack(uintptr_t m_LocalPlayerShow) {
    if (!SpeedHack || !offsetField[16] || !offsetField[17]) return;
    if (!m_LocalPlayerShow) return;
    // Try to read LogicFighter via BattleManager -> GetPlayerLogic for local player
    // offsetField[16] = LogicFighter.m_MoveComp offset
    // offsetField[17] = LogicMoveComp.m_fRunSpeed offset
    // We apply speed multiplier directly to the run-speed field
    auto m_MoveComp = *(uintptr_t*)(m_LocalPlayerShow + offsetField[16]);
    if (!m_MoveComp) return;
    float* speedPtr = (float*)(m_MoveComp + offsetField[17]);
    // Only write if current value is reasonable (avoid corrupting other data)
    if (*speedPtr > 0 && *speedPtr < 2000.0f) {
        *speedPtr = 350.0f * SpeedMultiplier; // 350 = typical MLBB base run speed
    }
}

// ── DrawESP ──────────────────────────────────────────────────────
void DrawESP(ImDrawList* draw) {
    if (!BattleBridge_Instance) return;
    auto get_bStartBattle = (bool(*)(void*))offset[2];
    bool bStartBattle = get_bStartBattle((void*)BattleBridge_Instance);
    if (!bStartBattle) return;
    if (!BattleManager_Instance) return;

    auto m_LocalPlayerShow = *(uintptr_t*)((uintptr_t)BattleManager_Instance + offsetField[0]);
    if (!m_LocalPlayerShow) return;
    auto selfPos    = *(Vector3*)((uintptr_t)m_LocalPlayerShow + offsetField[1]);
    auto Poslocalplayer = GetPlayerPosition(selfPos);

    // Apply Speed Hack to local player every frame
    ApplySpeedHack(m_LocalPlayerShow);

    auto m_dicPlayerShow = *(Dictionary1<int, uintptr_t>**)((uintptr_t)BattleManager_Instance + offsetField[2]);
    if (!m_dicPlayerShow) return;

    for (int i = 0; i < m_dicPlayerShow->getSize(); i++) {
        auto keys = m_dicPlayerShow->getKeys()[i];
        auto Pawn = m_dicPlayerShow->getValues()[i];
        if (!Pawn) continue;

        auto m_bSameCampType = *(bool*)((uintptr_t)Pawn + offsetField[3]);
        if (m_bSameCampType) continue;       // skip teammates
        auto m_bDeath = *(bool*)((uintptr_t)Pawn + offsetField[4]);
        if (m_bDeath) continue;              // skip dead

        auto _Position   = *(Vector3*)((uintptr_t)Pawn + offsetField[1]);
        auto RootPosW2S  = GetPlayerPosition(_Position);
        if (RootPosW2S.z <= 0) continue;    // behind camera

        ImVec2 drawPos      = ImVec2(RootPosW2S.x, RootPosW2S.y);
        ImVec2 rootPosVec2  = ImVec2(RootPosW2S.x, RootPosW2S.y);

        Vector3 EnemyHeadSc1 = GetPlayerPosition(_Position + Vector3(0, 1.5f, 0));
        ImVec2  EnemyHeadSc  = ImVec2(EnemyHeadSc1.x, EnemyHeadSc1.y);

        float boxHeightScreen = fabs(EnemyHeadSc.y - drawPos.y);
        boxWidthScreen = boxHeightScreen * 0.75f;

        ImVec2 boxTopLeft     = ImVec2(drawPos.x - boxWidthScreen / 2.0f, EnemyHeadSc.y);
        ImVec2 boxBottomRight = ImVec2(drawPos.x + boxWidthScreen / 2.0f, EnemyHeadSc.y + boxHeightScreen);

        // ── ESP Box ──────────────────────────────────────────────
        if (ESPBox) {
            ImU32 boxColor = IM_COL32(255, 255, 255, 255);
            draw->AddRect(boxTopLeft, boxBottomRight, boxColor, 0.0f, ImDrawFlags_None, 0.5f);
        }

        // ── Line ESP ─────────────────────────────────────────────
        if (Line) {
            draw->AddLine(
                ImVec2(Poslocalplayer.x, Poslocalplayer.y),
                drawPos,
                IM_COL32(255, 255, 255, 255), 0.5f);
        }

        // ── ESP Name ─────────────────────────────────────────────
        if (ESPName && offsetField[15]) {
            auto namePtr = *(uintptr_t*)((uintptr_t)Pawn + offsetField[15]);
            NSString* heroName = ReadMonoString(namePtr);
            if (heroName && heroName.length > 0) {
                const char* cName = [heroName UTF8String];
                auto textSize = ImGui::CalcTextSize(cName);
                draw->AddText(
                    NULL, 22,
                    ImVec2(boxTopLeft.x + (boxWidthScreen - textSize.x) / 2.0f, boxTopLeft.y - 24),
                    IM_COL32(255, 220, 50, 255),
                    cName);
            }
        }

        // ── ESP HP Bar ───────────────────────────────────────────
        if (ESPHPBar && offsetField[13] && offsetField[14]) {
            int maxHp = *(int*)((uintptr_t)Pawn + offsetField[13]);
            int curHp = *(int*)((uintptr_t)Pawn + offsetField[14]);
            if (maxHp > 0 && curHp >= 0) {
                float ratio = (float)curHp / (float)maxHp;
                if (ratio > 1.f) ratio = 1.f;
                if (ratio < 0.f) ratio = 0.f;

                float barX    = boxTopLeft.x - 4;
                float barTop  = boxTopLeft.y;
                float barBot  = boxBottomRight.y;
                float barH    = barBot - barTop;

                // Background
                draw->AddRectFilled(
                    ImVec2(barX - 3, barTop),
                    ImVec2(barX,     barBot),
                    IM_COL32(0, 0, 0, 180));

                // HP fill — green → yellow → red
                ImU32 hpCol;
                if (ratio > 0.6f)      hpCol = IM_COL32(50, 220, 50, 255);
                else if (ratio > 0.3f) hpCol = IM_COL32(230, 200, 0, 255);
                else                   hpCol = IM_COL32(220, 50, 50, 255);

                draw->AddRectFilled(
                    ImVec2(barX - 3, barTop + barH * (1.f - ratio)),
                    ImVec2(barX,     barBot),
                    hpCol);
            }
        }

        // ── ESP Distance ─────────────────────────────────────────
        if (ESPDistance) {
            float dist = Distance3D(selfPos, _Position);
            char distBuf[32];
            snprintf(distBuf, sizeof(distBuf), "%.0fm", dist);
            auto textSize = ImGui::CalcTextSize(distBuf);
            draw->AddText(
                NULL, 18,
                ImVec2(boxTopLeft.x + (boxWidthScreen - textSize.x) / 2.0f, boxBottomRight.y + 3),
                IM_COL32(150, 220, 255, 255),
                distBuf);
        }

        // ── Skill / Spell CD ─────────────────────────────────────
        if (ESPSkillCD || ESPSpellCD) {
            auto coolDownData = getPlayerCoolDown(keys, Pawn);
            if (ESPSkillCD) {
                if (coolDownData.skill1) {
                    std::string s = to_string(coolDownData.skill1);
                    auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - ts.x/2, rootPosVec2.y - 30), IM_COL32(255,255,0,255), s.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(255,255,0,255));
                }
                if (coolDownData.skill2) {
                    std::string s = to_string(coolDownData.skill2);
                    auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 40 - ts.x/2, rootPosVec2.y - 30), IM_COL32(255,255,0,255), s.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 40, rootPosVec2.y - 15), 10, IM_COL32(255,255,0,255));
                }
                if (coolDownData.skill3) {
                    std::string s = to_string(coolDownData.skill3);
                    auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 80 - ts.x/2, rootPosVec2.y - 30), IM_COL32(255,255,0,255), s.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 80, rootPosVec2.y - 15), 10, IM_COL32(255,255,0,255));
                }
            }
            if (coolDownData.skillCount >= 4) {
                if (ESPSkillCD && ESPSpellCD) {
                    if (coolDownData.skill4) {
                        std::string s = to_string(coolDownData.skill4);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 120 - ts.x/2, rootPosVec2.y - 30), IM_COL32(255,255,0,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 120, rootPosVec2.y - 15), 10, IM_COL32(255,255,0,255));
                    }
                    if (coolDownData.spell) {
                        std::string s = to_string(coolDownData.spell);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 160 - ts.x/2, rootPosVec2.y - 30), IM_COL32(30,144,255,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 160, rootPosVec2.y - 15), 10, IM_COL32(30,144,255,255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 225, rootPosVec2.y), IM_COL32(255,255,255,255));
                } else if (ESPSkillCD) {
                    if (coolDownData.skill4) {
                        std::string s = to_string(coolDownData.skill4);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 120 - ts.x/2, rootPosVec2.y - 30), IM_COL32(255,255,0,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 120, rootPosVec2.y - 15), 10, IM_COL32(255,255,0,255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255,255,255,255));
                } else if (ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string s = to_string(coolDownData.spell);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - ts.x/2, rootPosVec2.y - 30), IM_COL32(30,144,255,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30,144,255,255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255,255,255,255));
                }
            } else if (coolDownData.skillCount == 3) {
                if (ESPSkillCD && ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string s = to_string(coolDownData.spell);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + 120 - ts.x/2, rootPosVec2.y - 30), IM_COL32(30,144,255,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + 120, rootPosVec2.y - 15), 10, IM_COL32(30,144,255,255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255,255,255,255));
                } else if (ESPSkillCD) {
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 145, rootPosVec2.y), IM_COL32(255,255,255,255));
                } else if (ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string s = to_string(coolDownData.spell);
                        auto ts = ImGui::CalcTextSize(s.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - ts.x/2, rootPosVec2.y - 30), IM_COL32(30,144,255,255), s.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30,144,255,255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255,255,255,255));
                }
            }
        }
    }
}
