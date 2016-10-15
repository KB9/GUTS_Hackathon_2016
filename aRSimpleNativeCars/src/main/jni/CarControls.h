//
// Created by KavanBickerstaff on 15/10/2016.
//

#ifndef ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
#define ARSIMPLENATIVECARSPROJ_CARCONTROLS_H

#include <jni.h>
#include <android/log.h>

#define JNIFUNCTION_ACTIVITY(sig) Java_org_artoolkit_ar_samples_ARSimpleNativeCars_ARSimpleNativeCarsActivity_##sig

extern "C" {
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorUp(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeUp(JNIEnv* env, jobject object));
};

// Accelerator pressed
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorDown(JNIEnv* env, jobject object))
{
    LOGE("Accelerator pressed");
}

// Accelerator up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorUp(JNIEnv* env, jobject object))
{
    LOGE("Accelerator released");
}

// Brake down
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeDown(JNIEnv* env, jobject object))
{
    LOGE("Brake pressed");
}

// Brake up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeUp(JNIEnv* env, jobject object))
{
    LOGE("Brake released");
}

#endif //ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
