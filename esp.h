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
void* offset[50];
size_t offsetField[50];
float boxWidthScreen = 0;
void *BattleBridge_Instance;
void *BattleManager_Instance;
void *LogicBattleManager_Instance;
void *InstanceBattle;
bool ESPSkillCD;  
bool ESPSpellCD;

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
     if(!BattleBridge_Instance) return;
      auto get_bStartBattle = (bool (*)(void *))offset[2];
	    bool bStartBattle = get_bStartBattle((void *)BattleBridge_Instance);
	    if (!bStartBattle) return;
       if (!BattleManager_Instance) return;
       auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + offsetField[0]);
        if (!m_LocalPlayerShow) return;
        auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + offsetField[1]);
         auto Poslocalplayer = GetPlayerPosition(selfPos);
    auto m_dicPlayerShow = *(Dictionary1<int, uintptr_t> **)((uintptr_t)BattleManager_Instance + offsetField[2]);
    if (!m_dicPlayerShow) return;
    for (int i = 0; i < m_dicPlayerShow->getSize(); i++) {
        auto keys = m_dicPlayerShow->getKeys()[i];
        auto Pawn = m_dicPlayerShow->getValues()[i];
        if (!Pawn) continue;
        auto m_bSameCampType = *(bool *)((uintptr_t)Pawn + offsetField[3]);
        if (m_bSameCampType) continue;
        auto m_bDeath = *(bool *) ((uintptr_t)Pawn + offsetField[4]);
        if (m_bDeath) continue;
        auto _Position = *(Vector3 *) ((uintptr_t)Pawn + offsetField[1]);
        auto RootPosW2S = GetPlayerPosition(_Position);
        ImVec2 drawPos = ImVec2(RootPosW2S.x, RootPosW2S.y);
        ImVec2 rootPosVec2 = ImVec2(RootPosW2S.x, RootPosW2S.y);
        Vector3 EnemyHeadSc1 = GetPlayerPosition(_Position + Vector3(0, 1.5f, 0));
        ImVec2 EnemyHeadSc = ImVec2(EnemyHeadSc1.x, EnemyHeadSc1.y);
        float boxHeightScreen = abs(EnemyHeadSc.y - drawPos.y);
                boxWidthScreen = boxHeightScreen * 0.75f;
                ImVec2 boxTopLeft = ImVec2(drawPos.x - boxWidthScreen / 2.0f, EnemyHeadSc.y);
                ImVec2 boxBottomRight = ImVec2(drawPos.x + boxWidthScreen / 2.0f, EnemyHeadSc.y + boxHeightScreen);                
                if(ESPBox)
                {
                    ImU32 boxColor = IM_COL32(255, 255, 255, 255);
                    float boxThickness = 0.5f;
                    draw->AddRect(boxTopLeft, boxBottomRight, boxColor, 0.0f, ImDrawFlags_None, boxThickness);
                }
                if(Line)
                {

                        draw->AddLine(ImVec2(Poslocalplayer.x, Poslocalplayer.y), drawPos, IM_COL32(255, 255, 255, 255) , 0.5f);
                       
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