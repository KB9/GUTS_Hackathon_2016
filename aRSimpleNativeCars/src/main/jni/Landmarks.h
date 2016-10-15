#pragma once

#include "Car.h"
#include <cmath>

class Landmark : public Model
{
public:
	
	Landmark(int order_index) :
		Model(LANDMARK_MODEL_PATH)//,
		//pattern(LANDMARK_PATTERN_PATHS[order_index])
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
			glLoadMatrixf(originMatrix);
			// glTranslatef(offset_x, offset_y, offset_z);
			
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
	
	int index()
	{
		return order_index;
	}
	
private:
	static constexpr char LANDMARK_MODEL_PATH[] = "Data/models/Porsche_911_GT3.obj";
	// static constexpr char LANDMARK_PATTERN_PATHS[][] = {
		// "single;Data/a.patt;80", "single;Data/b.patt;80", "single;Data/c.patt;80",
		// "single;Data/d.patt;80", "single;Data/f.patt;80", "single;Data/g.patt;80"
	// };
	
	static constexpr float DISTANCE_THRESHOLD = 0.5f;

	//PatternRef pattern;
	
	int order_index;
};