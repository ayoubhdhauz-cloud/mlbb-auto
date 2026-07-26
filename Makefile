
ARCHS = arm64
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1
#THEOS_PACKAGE_SCHEME = rootless

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = 34306jit
#If you want to change TWEAK_NAME just change up here. It will automatically change these below, don't need to change it by hand anymore!

$(TWEAK_NAME)_FRAMEWORKS =  UIKit Foundation Security QuartzCore CoreGraphics CoreText  AVFoundation Accelerate GLKit SystemConfiguration GameController

${TWEAK_NAME}_CCFLAGS = -std=c++17 -fno-rtti -fno-exceptions -DNDEBUG -DkNO_SUBSTRATE -DkNO_KEYSTONE -fvisibility=hidden
${TWEAK_NAME}_CFLAGS = -fobjc-arc -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-value -fvisibility=hidden

$(TWEAK_NAME)_FILES = ImGuiDrawView.mm $(wildcard Esp/*.mm) $(wildcard Esp/*.m) $(wildcard IMGUI/*.cpp) $(wildcard IMGUI/*.mm) Il2cpp.mm

include $(THEOS_MAKE_PATH)/tweak.mk


