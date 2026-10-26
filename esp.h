#pragma once
#include "IMGUI/imgui_internal.h"
#include <vector>
#define kWidth  [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width
#define kHeight [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height
using namespace std;
static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
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
bool Line = false;
static bool MenDeal = true;
bool hackmap = false;
bool ESPBox = false;
bool ESPHpBar = true;  // แสดง HP bar
bool ESPName = false;  // แสดงชื่อ
void* offset[50];
size_t offsetField[50];
float boxWidthScreen = 0;
void *BattleBridge_Instance;
void *BattleManager_Instance;
void *LogicBattleManager_Instance;
void *InstanceBattle;
bool ESPSkillCD;  
bool ESPSpellCD;

// ══════════════════════════════════════════════════════════════════
// MARK: - Hardcoded offsets from BrazilixDump (instant ESP on load)
// ══════════════════════════════════════════════════════════════════
// ShowEntity offsets
#define OFF_DEATH           0xCD    // bool m_bDeath
#define OFF_SAME_CAMP       0x2B1   // bool m_bSameCampType
#define OFF_POSITION        0x294   // Vector3 m_vCachePosition
#define OFF_HP              0x1AC   // int m_Hp
#define OFF_HP_MAX          0x1B0   // int m_HpMax
#define OFF_IS_PLAYER       0x93    // bool IsPlayer
#define OFF_IS_SELF         0x250   // bool m_bSelf
#define OFF_LEVEL           0x198   // int m_Level

// BattleManager offsets
#define OFF_BM_LOCAL_PLAYER 0x50    // ShowPlayer m_LocalPlayerShow
#define OFF_BM_DIC_PLAYER   0x68    // Dictionary m_dicPlayerShow

void *get_main() {
	return reinterpret_cast<void *(*)()>((uintptr_t)offset[0])();
}
Vector3 WorldToViewportPoint(void *hack, Vector3 position, int mono) {
	return reinterpret_cast<Vector3 (*)(void*, Vector3, int)>((uint64_t)offset[1])(hack, position, mono);
}
uintptr_t GetPlayerLogic(uint id) {
    if (!InstanceBattle) return 0;
    return reinterpret_cast<uintptr_t(*)(void *, uint)>((uint64_t)offset[3])((void *)InstanceBattle, id);
}
int GetCoolTime(void* instance) {
    return reinterpret_cast<int(*)(void *)>((uint64_t)offset[4])(instance);
}
Vector3 GetPlayerPosition(Vector3 position) {
    auto cam = get_main();
    if (!cam) return {0,0};
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
    int skill1;
    int skill2;
    int skill3;
    int skill4;
    int spell;
};
CooldownValues getPlayerCoolDown(int keys, uintptr_t values) {
    auto logicFighter = GetPlayerLogic((uint)keys);
    if (!logicFighter) return {0, 0, 0, 0, 0, 0};
    auto m_SkillComp = *(uintptr_t *) ((uintptr_t)logicFighter + offsetField[5]);
    if (!m_SkillComp) return {0, 0, 0, 0, 0, 0};
    auto m_CoolDownComp = *(uintptr_t *) ((uintptr_t)m_SkillComp + offsetField[6]);
    if (!m_CoolDownComp) return {0, 0, 0, 0, 0, 0};
    auto m_OwnSkillComp = *(uintptr_t *) ((uintptr_t)values + offsetField[7]);
    if (!m_OwnSkillComp) return {0, 0, 0, 0, 0, 0};
    int skillCount = 0, skill1 = 0, skill2 = 0, skill3 = 0, skill4 = 0, spell = 0;

    Dictionary1<int, List<int> *> *skillUseTypeList = *(Dictionary1<int, List<int> *> **) ((uintptr_t)m_OwnSkillComp + offsetField[8]);
    if (!skillUseTypeList) return {0, 0, 0, 0, 0, 0};
    for (int v = 0; v < skillUseTypeList->getSize(); v++) {
        auto keysskillUseType = skillUseTypeList->getKeys()[v];
        auto valuesskillUseType = skillUseTypeList->getValues()[v];
        if (!keysskillUseType) continue;
        if (keysskillUseType != 1) continue;
        skillCount = valuesskillUseType->getSize();
        List<uintptr_t> *m_SkillList = *(List<uintptr_t> **) ((uintptr_t)m_OwnSkillComp + offsetField[9]);
        if (!m_SkillList) return {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i++) {
            auto p_SkillList = m_SkillList->getItems()[i];
            if (!p_SkillList) continue;
            auto m_TranID = *(int *) ((uintptr_t)p_SkillList + offsetField[10]);
            auto m_DicCoolInfo = *(Dictionary1<int, uintptr_t> **) ((uintptr_t)m_CoolDownComp + offsetField[11]);
            if (!m_DicCoolInfo) continue;
            for (int l = 0; l < m_DicCoolInfo->getSize(); l++) {
                auto keysCool = m_DicCoolInfo->getKeys()[l];
                auto valuesCool = m_DicCoolInfo->getValues()[l];
                if (!keysCool || !valuesCool) continue;
                auto m_iSummonSkillId = *(int *) ((uintptr_t)values + offsetField[12]);
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
void DrawESP(ImDrawList* draw) {
    // ── Safety checks ──────────────────────────────────────────────────────
    if (!BattleManager_Instance) return;

    // ── Optional: check battle started via Il2Cpp offset (skip if not ready) ──
    if (offset[2]) {
        auto get_bStartBattle = (bool (*)(void *))offset[2];
        if (BattleBridge_Instance && !get_bStartBattle((void *)BattleBridge_Instance)) return;
    }

    // ── Local player position (use hardcoded offset — always works) ────────
    auto m_LocalPlayerShow = *(uintptr_t *)((uintptr_t)BattleManager_Instance + OFF_BM_LOCAL_PLAYER);
    if (!m_LocalPlayerShow) return;
    auto selfPos = *(Vector3 *)((uintptr_t)m_LocalPlayerShow + OFF_POSITION);
    auto Poslocalplayer = GetPlayerPosition(selfPos);

    // ── Player dictionary ──────────────────────────────────────────────────
    auto m_dicPlayerShow = *(Dictionary1<int, uintptr_t> **)((uintptr_t)BattleManager_Instance + OFF_BM_DIC_PLAYER);
    if (!m_dicPlayerShow) return;

    for (int i = 0; i < m_dicPlayerShow->getSize(); i++) {
        auto keys = m_dicPlayerShow->getKeys()[i];
        auto Pawn = m_dicPlayerShow->getValues()[i];
        if (!Pawn) continue;

        // Skip allies and dead
        bool isSameCamp = *(bool *)((uintptr_t)Pawn + OFF_SAME_CAMP);
        if (isSameCamp) continue;
        bool isDead = *(bool *)((uintptr_t)Pawn + OFF_DEATH);
        if (isDead) continue;
        // Skip non-players (soldiers, towers, etc)
        bool isPlayer = *(bool *)((uintptr_t)Pawn + OFF_IS_PLAYER);
        if (!isPlayer) continue;

        // ── Position ─────────────────────────────────────────────────────
        auto _Position = *(Vector3 *)((uintptr_t)Pawn + OFF_POSITION);
        auto RootPosW2S = GetPlayerPosition(_Position);
        if (RootPosW2S.z <= 0) continue; // behind camera

        ImVec2 drawPos    = ImVec2(RootPosW2S.x, RootPosW2S.y);
        ImVec2 rootPosVec2 = drawPos;

        Vector3 EnemyHeadSc1 = GetPlayerPosition(_Position + Vector3(0, 1.8f, 0));
        ImVec2  EnemyHeadSc  = ImVec2(EnemyHeadSc1.x, EnemyHeadSc1.y);

        float boxHeightScreen = fabsf(EnemyHeadSc.y - drawPos.y);
        if (boxHeightScreen < 5.0f) continue; // too far / off screen
        boxWidthScreen = boxHeightScreen * 0.65f;

        ImVec2 boxTopLeft     = ImVec2(drawPos.x - boxWidthScreen / 2.0f, EnemyHeadSc.y);
        ImVec2 boxBottomRight = ImVec2(drawPos.x + boxWidthScreen / 2.0f, EnemyHeadSc.y + boxHeightScreen);

        // ── HP ────────────────────────────────────────────────────────────
        int hp    = *(int *)((uintptr_t)Pawn + OFF_HP);
        int hpMax = *(int *)((uintptr_t)Pawn + OFF_HP_MAX);
        float hpPct = (hpMax > 0) ? (float)hp / (float)hpMax : 0.0f;

        // ── ESP Box ───────────────────────────────────────────────────────
        if (ESPBox) {
            // Corner box style
            float cLen = boxWidthScreen * 0.25f;
            ImU32 col = IM_COL32(255, 60, 60, 255); // red
            float th = 1.5f;
            // Top-left
            draw->AddLine(boxTopLeft, ImVec2(boxTopLeft.x + cLen, boxTopLeft.y), col, th);
            draw->AddLine(boxTopLeft, ImVec2(boxTopLeft.x, boxTopLeft.y + cLen), col, th);
            // Top-right
            draw->AddLine(ImVec2(boxBottomRight.x, boxTopLeft.y), ImVec2(boxBottomRight.x - cLen, boxTopLeft.y), col, th);
            draw->AddLine(ImVec2(boxBottomRight.x, boxTopLeft.y), ImVec2(boxBottomRight.x, boxTopLeft.y + cLen), col, th);
            // Bottom-left
            draw->AddLine(ImVec2(boxTopLeft.x, boxBottomRight.y), ImVec2(boxTopLeft.x + cLen, boxBottomRight.y), col, th);
            draw->AddLine(ImVec2(boxTopLeft.x, boxBottomRight.y), ImVec2(boxTopLeft.x, boxBottomRight.y - cLen), col, th);
            // Bottom-right
            draw->AddLine(boxBottomRight, ImVec2(boxBottomRight.x - cLen, boxBottomRight.y), col, th);
            draw->AddLine(boxBottomRight, ImVec2(boxBottomRight.x, boxBottomRight.y - cLen), col, th);
        }

        // ── HP Bar ────────────────────────────────────────────────────────
        if (ESPHpBar) {
            float barX   = boxTopLeft.x - 5.0f;
            float barTop = boxTopLeft.y;
            float barBot = boxBottomRight.y;
            float barH   = barBot - barTop;
            float filled = barH * hpPct;
            // Background
            draw->AddRectFilled(ImVec2(barX - 3, barTop), ImVec2(barX, barBot), IM_COL32(0, 0, 0, 180));
            // HP fill — green to red based on %
            ImU32 hpCol = hpPct > 0.5f
                ? IM_COL32(int(255*(1-hpPct)*2), 255, 0, 255)
                : IM_COL32(255, int(255*hpPct*2), 0, 255);
            draw->AddRectFilled(ImVec2(barX - 3, barTop + (barH - filled)), ImVec2(barX, barBot), hpCol);
        }

        // ── Line ──────────────────────────────────────────────────────────
        if (Line) {
            draw->AddLine(ImVec2(Poslocalplayer.x, Poslocalplayer.y), drawPos,
                IM_COL32(255, 60, 60, 200), 1.0f);
        }
if (ESPSkillCD || ESPSpellCD) {
            auto coolDownData = getPlayerCoolDown(keys, Pawn);
            if (ESPSkillCD) {
                if (coolDownData.skill1) {
                    std::string strCoolDown = to_string(coolDownData.skill1);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
                if (coolDownData.skill2) {
                    std::string strCoolDown = to_string(coolDownData.skill2);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 1) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 1), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
                if (coolDownData.skill3) {
                    std::string strCoolDown = to_string(coolDownData.skill3);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 2) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 2), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
            }
            if (coolDownData.skillCount >= 4) {
                if (ESPSkillCD && ESPSpellCD) {
                    if (coolDownData.skill4) {
                        std::string strCoolDown = to_string(coolDownData.skill4);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                    }
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 4) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 4), rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 225, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (ESPSkillCD) {
                    if (coolDownData.skill4) {
                        std::string strCoolDown = to_string(coolDownData.skill4);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                }
            } else if (coolDownData.skillCount == 3) {
                if (ESPSkillCD && ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (ESPSkillCD) {
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 145, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (ESPSpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                }
            }
        }

}
}
