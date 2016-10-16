#pragma once

#include "Car.h"
#include <cmath>


class Landmark : public Model
{
public:
	
	Landmark(int order_index, const char* mod, const char* pat) :
		Model(mod),
		pattern(pat)
	{	
		this->order_index = order_index;
	}
	
	bool checkCollisions(const Car& car)
	{	
		// float dst = sqrt(pow(car.offx - x, 2) + pow(car.y - y, 2) + pow(car.z - z, 2));
		// return dst < DISTANCE_THRESHOLD;
		return false;
	}
	
	void render(ARdouble* originMatrix)
	{
		if (visible)
		{
			LOGE("offset for the marker are %f %f, %f", offset_x, offset_y, offset_z);
			glLoadMatrixf(originMatrix);
			
			//glTranslatef(offset_x, offset_y, offset_z);
			
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient
			);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse
			);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition
			);
			LOGE("LOGE draw start");
			if (model == nullptr) {
				LOGE("the model is empty");
				exit(-1);
			}
			
			glmDrawArrays(model, 0);
			LOGE("LOGE draw end");
		}
	}
	// @param x,y,z coords of the root
	void update (float x, float y, float z)
	{
		// get the transformation matrix and check if visible
		visible = arwQueryMarkerTransformation(pattern.getID(), pattern.getTransformationMatrix());
		
		float* matrix = pattern.getTransformationMatrix();
		float marker_x = matrix[3];
		float marker_y = matrix[6];
		float marker_z = matrix[9];
		
		static constexpr int wtf = 1;
		offset_x = (x - marker_x) * wtf;
		offset_y = (y - marker_y) * wtf;
		offset_z = (z - marker_z) * wtf;
		
	}
	
	int index()
	{
		return order_index;
	}
	
private:
	
	static constexpr float DISTANCE_THRESHOLD = 0.5f;

	PatternRef pattern;
	
	int order_index;
};