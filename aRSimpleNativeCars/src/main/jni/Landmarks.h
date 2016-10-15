#include "Car.h"
#include <cmath>

class Landmark : public Model
{
public:
	
	Landmark(int order_index) :
		pattern(LANDMARK_PATTERN_PATHS[order_index])
	{
		Model::Model(LANDMARK_MODEL_PATH);
		
		this->order_index = order_index;
	}
	
	bool checkCollisions(const Car& car)
	{	
		float dst = sqrt(pow(car.x - x, 2) + pow(car.y - y, 2) + pow(car.z - z, 2));
		return dst < DISTANCE_THRESHOLD;
	}
	
	void render(double* originMatrix)
	{
		if (visible)
		{
			glLoadMatrix(originMatrix);
			glTranslatef(x, y, z);
			
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
	const char* LANDMARK_MODEL_PATH = "path_to_landmark_model";
	const char* LANDMARK_PATTERN_PATHS[] = {
		"landmark_pattern_1", "landmark_pattern_2", "landmark_pattern_3",
		"landmark_pattern_4", "landmark_pattern_5", "landmark_pattern_6"
	};
	
	constexpr float DISTANCE_THRESHOLD = 0.5f;

	PatternRef pattern;
	
	int order_index;
}