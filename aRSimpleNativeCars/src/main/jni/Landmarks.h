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
	
	bool handleCollision(Car* car)
	{
		float dstX = std::abs(car->offset_x - offset_x);
		float dstY = std::abs(car->offset_y - offset_y);
		float dstZ = std::abs(car->offset_z - offset_z);
		
		bool hasHitCheckpoint = (dstX <= DISTANCE_THRESHOLD) && (dstY <= DISTANCE_THRESHOLD) && (dstZ <= DISTANCE_THRESHOLD);
		LOGE("pleb: %f %f %f %s", dstX, dstY, dstZ, hasHitCheckpoint ? "yas" : "nay");
		if (hasHitCheckpoint)
		{
			car->scored();
			active = false;
		}
		
		return hasHitCheckpoint;
	}
	
	void render(ARdouble* originMatrix)
	{
		if (visible && active)
		{
			LOGE("offset for the marker are %f %f, %f", offset_x, offset_y, offset_z);
			glLoadMatrixf(originMatrix);
			
			glTranslatef(offset_x, offset_y, offset_z);
			
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
	
	void update()
	{
		visible = arwQueryMarkerTransformation(pattern.getID(), pattern.getTransformationMatrix());
	}
	// @param x,y,z coords of the root
	void setOffset (float x, float y, float z)
	{
		// get the transformation matrix and check if visible
		
		
		// float* matrix = pattern.getTransformationMatrix();
		// float marker_x = matrix[3];
		// float marker_y = matrix[7];
		// float marker_z = matrix[11];
		
		// static constexpr int wtf = 1;
		// offset_x = (x - marker_x) * wtf;
		// offset_y = (y - marker_y) * wtf;
		// offset_z = (z - marker_z) * wtf;
		
		offset_x = x;
		offset_y = y;
		offset_z = z;
		
	}
	
	int patternID() const{
		return pattern.getID();
	}
	
	float* transformationMatrix()
	{
		return pattern.getTransformationMatrix();
	}
	
	int index()
	{
		return order_index;
	}
	
private:
	
	static constexpr float DISTANCE_THRESHOLD = 100.0f;
	bool active = true;
	PatternRef pattern;
	
	int order_index;
};