//
// Created by KavanBickerstaff on 15/10/2016.
//

#ifndef ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
#define ARSIMPLENATIVECARSPROJ_CARCONTROLS_H

#include <jni.h>
#include <android/log.h>

#include "Car.h"
#include "World.h"

GameMode gmode;

#define JNIFUNCTION_ACTIVITY(sig) Java_org_artoolkit_ar_samples_ARSimpleNativeCars_ARSimpleNativeCarsActivity_##sig

extern "C" {
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerLeftDown(JNIEnv* env, jobject object));
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerLeftUp(JNIEnv* env, jobject object));
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerRightDown(JNIEnv* env, jobject object));
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerRightUp(JNIEnv* env, jobject object));
	
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onAcceleratorUp(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeDown(JNIEnv* env, jobject object));
    JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onBrakeUp(JNIEnv* env, jobject object));
	
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(initCheckpoints(JNIEnv* env, jobject object));
	JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(initCTF(JNIEnv* env, jobject object));
};

bool steerLeftDown = false;
bool steerRightDown = false;
bool acceleratorDown = false;
bool brakeDown = false;


bool worldInitialized = false;

// Left pressed
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerLeftDown(JNIEnv* env, jobject object))
{
	steerLeftDown = true;
}

// Left up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerLeftUp(JNIEnv* env, jobject object))
{
	steerLeftDown = false;
}

// Right pressed
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerRightDown(JNIEnv* env, jobject object))
{
	steerRightDown = true;
}

// Right up
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(onSteerRightUp(JNIEnv* env, jobject object))
{
	steerRightDown = false;
}

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

// Initialize checkpoints mode
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(initCheckpoints(JNIEnv* env, jobject object))
{
	extern World* world;
	gmode = SINGLE_TIMED;
	//world->init(SINGLE_TIMED);

}

// Initialize CTF mode
JNIEXPORT void JNICALL JNIFUNCTION_ACTIVITY(initCTF(JNIEnv* env, jobject object))
{
	extern World* world;
	gmode = SINGLE_CAPTURE;
	//world->init(SINGLE_CAPTURE);
}

#define SPEED_INCREMENT 0.5f
#define TWO_PI (3.141592654f * 2.0f)
#define TURNING_ANGLE (TWO_PI / 72.0f)

void processInput(Car* playerCar)
{
	if (!playerCar) return;
	
	if (acceleratorDown)
	{	
		// Increment speed
		playerCar->setSpeed(playerCar->getSpeed() + SPEED_INCREMENT);
	}
	else
	{
		// Decrement speed
		playerCar->setSpeed(playerCar->getSpeed() - SPEED_INCREMENT);
		if (playerCar->getSpeed() < 0)
		{
			playerCar->setSpeed(0);
		}
	}
	
	// If the player is moving
	if (playerCar->getSpeed() > 0.0f)
	{
		// If steering left
		if (steerLeftDown)
		{
			playerCar->setRotation(playerCar->getRotation() + TURNING_ANGLE);
			if (playerCar->getRotation() > TWO_PI)
			{
				playerCar->setRotation(0.0f);
			}
			// playerCar->setRotation(playerCar->getRotation() - TURNING_ANGLE);
			// if (playerCar->getRotation() < 0.0f)
			// {
				// playerCar->setRotation(TWO_PI);
			// }
		}
		
		// If steering right
		if (steerRightDown)
		{
			playerCar->setRotation(playerCar->getRotation() - TURNING_ANGLE);
			if (playerCar->getRotation() < 0.0f)
			{
				playerCar->setRotation(TWO_PI);
			}
			// playerCar->setRotation(playerCar->getRotation() + TURNING_ANGLE);
			// if (playerCar->getRotation() > TWO_PI)
			// {
				// playerCar->setRotation(0.0f);
			// }
		}
	}
	
	// Stop if brake is pressed
	if (brakeDown)
	{
		playerCar->setSpeed(0);
	}
}

#endif //ARSIMPLENATIVECARSPROJ_CARCONTROLS_H
