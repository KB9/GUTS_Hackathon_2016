//
// Stores all objects, checks their collisions and calls their render method each frame.
// To render, it calculates the camera position relative to the marker, and passes this result to the objects, 
// which all render themselves with the appropriate offset.
#pragma once

#include <AR/gsub_es.h>
#include <AR/ar.h>

#include "Landmarks.h"
#include "Car.h"

#define VIEW_SCALEFACTOR		1.0         // Units received from ARToolKit tracking will be multiplied by this factor before being used in OpenGL drawing.
#define VIEW_DISTANCE_MIN		40.0        // Objects closer to the camera than this will not be displayed. OpenGL units.
#define VIEW_DISTANCE_MAX		10000.0     // Objects further away from the camera than this will not be displayed. OpenGL units.


class World{
public:
	void init()
	{
		cars.emplace_back(new Car("Data/models/Ferrari_Modena_Spider.obj"));
		cars.emplace_back(new Car("Data/models/Porsche_911_GT3.obj"));
	}
	
	void execute()
	{
		// first update everything
		
		// check for collisions
		for (Car* car : cars)
		{
			int score = car.score();
			if (checkCollision(landmarks[score], car))
			{
				car->scored();
			}
		}
		
		//render everything
		
		
		LOGE("LOGE  start drawframe");
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
		// Set the projection matrix to that provided by ARToolKit.
		float proj[16];
		arwGetProjectionMatrix(proj);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(proj);
		glMatrixMode(GL_MODELVIEW);

		glStateCacheEnableDepthTest();

		glStateCacheEnableLighting();

		glEnable(GL_LIGHT0);
		
		bool visible = arwQueryMarkerTransformation(pattern.getID(), pattern.getTransformationMatrix());
		for (auto* car : cars) {
			car->render(pattern);
		}
		
	}
	
	void clearCars()
	{
		glStateCacheFlush(); // Make sure we don't hold outdated OpenGL state.
		for (auto *car : cars)
		{
			car->clearObj();
		}
	}
	
	bool checkCollision(Landmark* landmark, Car* car)
	{
		return true;
	}
private:
	PatternRef pattern;
	float lightAmbient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightPosition[4] = {0.0f, 0.0f, 1.0f, 0.0f};
	std::vector<Car*> cars;
	std::vector<Landmark*> landmarks;
}









