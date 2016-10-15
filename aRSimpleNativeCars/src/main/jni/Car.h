#pragma once

// extern float lightAmbient[4];
// extern float lightDiffuse[4];
// extern float lightPosition[4];

constexpr float lightAmbient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
constexpr float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr float lightPosition[4] = {0.0f, 0.0f, 1.0f, 0.0f};

struct Vector
{
	ARdouble x, y, z;
};

class PatternRef
{
public:
	PatternRef (const char* pattern) 
	{
		patternID = arwAddMarker(pattern);
		arwSetMarkerOptionBool(patternID, ARW_MARKER_OPTION_SQUARE_USE_CONT_POSE_ESTIMATION, false);
		arwSetMarkerOptionBool(patternID, ARW_MARKER_OPTION_FILTERED, true);
	}
	
	int getID()
	{
		return patternID;
	}
	
	ARdouble* getTransformationMatrix()
	{
		return transformationMatrix;
	}
private:
	int patternID;
	ARdouble transformationMatrix[16];
};


class Model
{
public:
	float offset_x, offset_y, offset_z;

	// @param model the full path to the obj file : 
	// "Data/models/Ferrari_Modena_Spider.obj";
	// "Data/models/Porsche_911_GT3.obj";
	
	// @param pattern the pattern description. eg 
	// "single;Data/hiro.patt;80"
	// "single;Data/kanji.patt;80"
	Model(const char* modelPath, float scalingFactor = 0.035f) 
	{
		model = glmReadOBJ2(modelPath, 0, 0); // context 0, don't read textures yet.
		
		if (!(model)) {
			LOGE("Error loading model from file '%s'.", modelPath);
			exit(-1);
		}
		glmScale(model, scalingFactor);
		glmCreateArrays(model, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		visible = true;
	}
	
	~Model()
	{
		clearObj();
	}
	
	void clearObj()
	{
		if (model != nullptr)
		{
			glmDelete(model, 0);
			model = nullptr;
		}
	}
	
	void setVisible(bool v)
	{
		visible = v;
	}
	
	virtual void render(ARdouble* worldOriginMatrix) = 0;
	
protected:
	GLMmodel *model;
	bool visible;
};

class Car : public Model{
public:
	using Model::Model;
	
	void setVelocity(Vector vel) {
		velocity = vel;
	}
	
	void render(ARdouble* worldOriginMatrix) override
	{
		//setVisible(arwQueryMarkerTransformation(model.patternID, model.transformationMatrix));
		if (visible) {
			//glLoadMatrixf(model.transformationMatrix);
			glLoadMatrixf(worldOriginMatrix);
			//glTranslatef(0.0,20.0,25.0);
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
		offset_y += translation;
		offset_z += translation;
		translation = 0;
	}
	
	int score()
	{
		return scoreCounter;
	}
	
	void scored()
	{
		scoreCounter++;
	}
	
	void rotate(float rot)
	{
		rotation = rot;
	}
	
	void move(float tr)
	{
		translation += tr;
	}
	
private:
	
	int scoreCounter;
	
	float rotation;
	float translation;
	Vector velocity;
};