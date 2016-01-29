LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

SDL_IMAGE_PATH := ../SDL2_image

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
					$(LOCAL_PATH)/$(SDL_IMAGE_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp \ MapView.cpp \ LTexture.cpp \ TTile.cpp \ EventHandler.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image

LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
