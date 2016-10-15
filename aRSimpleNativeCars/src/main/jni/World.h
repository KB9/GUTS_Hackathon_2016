//
// Stores all objects, checks their collisions and calls their render method each frame.
// To render, it calculates the camera position relative to the marker, and passes this result to the objects, 
// which all render themselves with the appropriate offset.


#include <AR/gsub_es.h>
#include <AR/ar.h>


#define VIEW_SCALEFACTOR		1.0         // Units received from ARToolKit tracking will be multiplied by this factor before being used in OpenGL drawing.
#define VIEW_DISTANCE_MIN		40.0        // Objects closer to the camera than this will not be displayed. OpenGL units.
#define VIEW_DISTANCE_MAX		10000.0     // Objects further away from the camera than this will not be displayed. OpenGL units.


std::vector<Car*> cars;
std::vector<CheckPoint*> checkpoints;


class World
{
public:
	World() {

	}

	// Calculates camera position relative to marker. passes this to each object by calling their render() method.
	JNIEXPORT void JNICALL
	JNIFUNCTION_WORLD(drawFrame(JNIEnv * env, jobject obj)) {
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

		for (auto* car : cars) {
			car->update();
			checkpointCollisions(car);
			car->render(arwQueryMarkerTransformation(car->model.patternID, car->model.transformationMatrix));
		}
	}
	LOGE("LOGE  end drawframe");

	// Iterates through the cars, and check if they have collided with a checkpoint.
	// Only checks the next checkpoint for each car, i.e. car 2 has score 1, meaning it has gone through the first checkpoint. 
	// The function will only check for a collision between car 2 and checkpoint 2 in this case.
	checkpointCollision(Car car) {
		LOGE("LOGE Calculating checkpoint collisions");

		
	}

	int coordInRadius(checkpoint* chkp, Car* car) {

	}

	~World() {
		clearObj();
	}
};









