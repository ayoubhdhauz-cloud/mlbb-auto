ARCHS = arm64
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = 34306jit

$(TWEAK_NAME)_FRAMEWORKS = UIKit Foundation Security QuartzCore CoreGraphics CoreText AVFoundation Accelerate GLKit SystemConfiguration GameController Metal MetalKit

$(TWEAK_NAME)_CCFLAGS = -std=c++17 -fno-rtti -fno-exceptions -DNDEBUG -DkNO_SUBSTRATE -DkNO_KEYSTONE -fvisibility=hidden \
    -Wno-nontrivial-memcall \
    -Wno-module-import-in-extern-c \
    -Wno-missing-template-arg-list-after-template-kw

$(TWEAK_NAME)_CFLAGS = -fobjc-arc \
    -Wno-deprecated-declarations \
    -Wno-unused-variable \
    -Wno-unused-value \
    -Wno-format-security \
    -Wno-nontrivial-memcall \
    -Wno-module-import-in-extern-c \
    -fvisibility=hidden

$(TWEAK_NAME)_FILES = ImGuiDrawView.mm \
    $(wildcard Esp/*.mm) \
    $(wildcard Esp/*.m) \
    $(wildcard IMGUI/*.cpp) \
    $(wildcard IMGUI/*.mm) \
    Il2cpp.mm

$(TWEAK_NAME)_LDFLAGS = -L$(THEOS_PROJECT_DIR)/5Toubun -ldobby

include $(THEOS_MAKE_PATH)/tweak.mk
