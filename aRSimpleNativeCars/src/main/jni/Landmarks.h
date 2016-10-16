#pragma once

#include "Car.h"
#include <cmath>


class Landmark : public Model
{
public:
	
	Landmark(int id, const char* mod, const char* pat, float scaling = 0.035f) :
		Model(id, mod, scaling),
		pattern(pat)
	{	
	}
	
	bool handleCollision(Car* car, GameMode mode)
	{
		this->mode = mode;
		if (mode == SINGLE_TIMED){
			if (!active)
				return false;
			
			// if the score is different from the id of this, it means its not the right landmark next
			if(id != car->score())
			{
				return false;
			}
		}
		
		if (mode == MULTI_CAPTURE)
		{
			//capture the flag. if the car already owns this, do nothing
			if(car->getID() == owner)
				return false;
		}
		
		float dstX = std::abs(car->offset_x - offset_x);
		float dstY = std::abs(car->offset_y - offset_y);
		//float dstZ = std::abs(car->offset_z - offset_z);
		
		//bool hasHitCheckpoint = (dstX <= DISTANCE_THRESHOLD) && (dstY <= DISTANCE_THRESHOLD) && (dstZ <= DISTANCE_THRESHOLD);
		bool hasHitCheckpoint = (dstX <= DISTANCE_THRESHOLD) && (dstY <= DISTANCE_THRESHOLD);
		//LOGE("pleb: %f %f %f %s", dstX, dstY, dstZ, hasHitCheckpoint ? "yas" : "nay");
		if (hasHitCheckpoint)
		{
			car->scored();
			owner = car->getID();
			
			if(mode == SINGLE_TIMED)
			{
				//in single player mode, the landmark is deactivated once it has been triggered
				active = false;
			}
			
		}
		
		return hasHitCheckpoint;
	}
	
	void render(const ARdouble* originMatrix)
	{
		if (visible && active)
		{
			LOGE("offset for the marker are %f %f, %f", offset_x, offset_y, offset_z);
			glLoadMatrixf(originMatrix);
			
			glTranslatef(offset_x, offset_y, offset_z);
			const float* ambient = lightAmbient;
			
			if (mode == MULTI_CAPTURE) {
				if (owner == 1)
				{
					ambient =ambientPlayer1;
				}
				else if(owner == 2)
					ambient = ambientPlayer2;
			}
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient
			);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient
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
	
	// int index()
	// {
		// return order_index;
	// }
	
private:
	GameMode mode = MULTI_CAPTURE;
	static constexpr float DISTANCE_THRESHOLD = 100.0f;
	bool active = true;
	PatternRef pattern;
	
	int owner = -1; // the car id who owns this Landmark
};