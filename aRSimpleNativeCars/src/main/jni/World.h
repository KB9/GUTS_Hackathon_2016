//
// Stores all objects, checks their collisions and calls their render method each frame.
// To render, it calculates the camera position relative to the marker, and passes this result to the objects, 
// which all render themselves with the appropriate offset.
#pragma once

#include <AR/gsub_es.h>
#include <AR/ar.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"


#include "Landmarks.h"
#include "Car.h"
#include <vector>
#define VIEW_SCALEFACTOR		1.0         // Units received from ARToolKit tracking will be multiplied by this factor before being used in OpenGL drawing.
#define VIEW_DISTANCE_MIN		40.0        // Objects closer to the camera than this will not be displayed. OpenGL units.
#define VIEW_DISTANCE_MAX		10000.0     // Objects further away from the camera than this will not be displayed. OpenGL units.


class World{
public:
	World(const char* pat):
		pattern(pat){}
	void init()
	{
		cars.emplace_back(new Car("Data/models/Ferrari_Modena_Spider.obj"));
		cars.emplace_back(new Car("Data/models/Porsche_911_GT3.obj"));
		landmarks.emplace_back(new Landmark(0, "Data/models/Porsche_911_GT3.obj", "single;Data/hiro.patt;80"));
	}
	
	void execute()
	{
		// initial cleanup
		
		LOGE("LOGE  start drawframe");
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Set the projection matrix to that provided by ARToolKit.
		
		float proj[16];
		arwGetProjectionMatrix(proj);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(proj);
		glMatrixMode(GL_MODELVIEW);
		glStateCacheEnableDepthTest();
		glStateCacheEnableLighting();
		glEnable(GL_LIGHT0);
		
		// check if the world marker is visible, and set its matrix
		bool visible = arwQueryMarkerTransformation(pattern.getID(), pattern.getTransformationMatrix());
		const float* matrix = pattern.getTransformationMatrix();
		
		
		LOGE("visible : %d", visible);
		
		if (!visible) return;
		float x, y, z;
		
		
		calculateDistance(landmarks[0], &x, &y, &z);
		// first update everything
		//FIXME
		landmarks[0]->update(x, y, z);
		landmarks[0]->render(pattern.getTransformationMatrix());
		
		// check for collisions
		for (Car* car : cars)
		{
			//DOES NOT BELONG HERE
			car->update();
			//END
			int score = car->score();
			if (checkCollision(landmarks[score], car))
			{
				car->scored();
			}
		}
		
		//render everything
		
		for (auto* car : cars) {
			car->render(pattern.getTransformationMatrix());
		}
		
	}
	
	int patternID() const{
		return pattern.getID();
	}
	
	void  calculateDistance(Landmark* mark, float* x, float*y, float* z)
	{
		float* root_ptr = pattern.getTransformationMatrix();
		float* mark_ptr = mark->transformationMatrix();
		
		if (!root_ptr || !mark_ptr) return;
		
		glm::mat4 root_transform = glm::make_mat4(root_ptr);
		glm::mat4 mark_transform = glm::make_mat4(mark_ptr);
		
		glm::mat4 inverted_root = glm::inverse(root_transform);
		
		//glm::mat4 root_to_mark = root_transform * mark_transform;
		glm::mat4 root_to_mark = inverted_root * mark_transform;
		
		
		const float* source = (const float*)glm::value_ptr(root_to_mark);
		
		*x = source[12];
		*y = source[13];
		*z = source[14];
		
		LOGE("the three values of love are %f %f %f", *x, *y, *z);
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
	
	Car* getPlayerCar()
	{
		return cars[0];
	}
private:
	PatternRef pattern;
	float lightAmbient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightPosition[4] = {0.0f, 0.0f, 1.0f, 0.0f};
	std::vector<Car*> cars;
	std::vector<Landmark*> landmarks;
};









