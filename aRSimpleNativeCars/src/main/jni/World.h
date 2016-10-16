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
	enum GameType
	{
		
	};
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
		
		// first, update all the transformation matrices
		bool visible = arwQueryMarkerTransformation(pattern.getID(), pattern.getTransformationMatrix());
		landmarks[0]->update();
		
		
		
		const float* matrix = pattern.getTransformationMatrix();
		LOGE("visible : %d", visible);
		
		if (!visible) return;
		float x = 0, y = 0, z = 0;
		
		
		
		bool success = calculateDistance(landmarks[0], &x, &y, &z);
		
		
		
		if (success)
		{
			landmarks[0]->setOffset(x, y, z);
			// first update everything
			//FIXME
			
			landmarks[0]->render(matrix);
			
			// check for collisions
			// for (Car* car : cars)
			// {
				// //END
				// int score = car->score();
				// if (landmarks[0]->handleCollision(car))
				// {
				// }
			// }
			landmarks[0]->handleCollision(cars[0]);
		}
		
		//render everything
		
		for (auto* car : cars) {
			car->update();
			car->render(pattern.getTransformationMatrix());
		}
		
	}
	
	int patternID() const{
		return pattern.getID();
	}
	
	bool calculateDistance(Landmark* mark, float* x, float*y, float* z)
	{
		float* root_ptr = pattern.getTransformationMatrix();
		float* mark_ptr = mark->transformationMatrix();
		
		if (!root_ptr || !mark_ptr) return false;
		
		glm::mat4 root_transform = glm::make_mat4(root_ptr);
		glm::mat4 mark_transform = glm::make_mat4(mark_ptr);
		
		glm::mat4 inverted_root = glm::inverse(root_transform);
		
		//glm::mat4 root_to_mark = root_transform * mark_transform;
		glm::mat4 root_to_mark = inverted_root * mark_transform;
		
		const float* source = (const float*)glm::value_ptr(root_to_mark);
		
		if (source[12] <= 1.0f && source[13] <= 1.0f && source[14] <= 1.0f) return false;
		
		*x = source[12];
		*y = source[13];
		*z = source[14];
	
		
		return true;
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









