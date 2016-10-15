//
// Created by KavanBickerstaff on 15/10/2016.
//

#ifndef ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
#define ARSIMPLENATIVECARSPROJ_CARCONTROLS_H

#include <jni.h>
#include <android/log.h>

#include "Car.h"

#define JNIFUNCTION_ACTIVITY(sig) Java_org_artoolkit_ar_samples_ARSimpleNativeCars_ARSimpleNativeCarsActivity_##sig

extern "C" {
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorUp(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeUp(JNIEnv* env, jobject object));
};

bool acceleratorDown = false;
bool brakeDown = false;

// Accelerator pressed
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorDown(JNIEnv* env, jobject object))
{
    acceleratorDown = true;
}

// Accelerator up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorUp(JNIEnv* env, jobject object))
{
    acceleratorDown = false;
}

// Brake down
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeDown(JNIEnv* env, jobject object))
{
    brakeDown = true;
}

// Brake up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeUp(JNIEnv* env, jobject object))
{
    brakeDown = false;
}

void processInput(Car* playerCar)
{
	if (!playerCar) return;
	
	if (acceleratorDown)
	{
		playerCar->move(0.05f);
	}
}

#endif //ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
