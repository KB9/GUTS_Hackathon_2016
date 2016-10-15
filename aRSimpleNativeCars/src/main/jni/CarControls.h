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

#define SPEED_INCREMENT 0.5f
#define TWO_PI (3.141592654f * 2.0f)

void processInput(Car* playerCar)
{
	if (!playerCar) return;
	
	if (acceleratorDown)
	{
		playerCar->setRotation(playerCar->getRotation() + (TWO_PI / 180.0f));
		if (playerCar->getRotation() > TWO_PI)
		{
			playerCar->setRotation(0.0f);
		}
		
		playerCar->setSpeed(playerCar->getSpeed() + SPEED_INCREMENT);
	}
	else
	{
		playerCar->setSpeed(playerCar->getSpeed() - SPEED_INCREMENT);
		if (playerCar->getSpeed() < 0)
		{
			playerCar->setSpeed(0);
		}
	}
	
	if (brakeDown)
	{
		playerCar->setSpeed(0);
	}
}

#endif //ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
