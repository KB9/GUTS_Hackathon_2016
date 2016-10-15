
#include <AR/gsub_es.h>

struct Vector
{
	ARdouble x, y, z;
};


struct ARModel {
    int patternID;
    ARdouble transformationMatrix[16];
    bool visible;
    GLMmodel *obj;
};



class Model
{
public:
	// @param model the full path to the obj file : 
	// "Data/models/Ferrari_Modena_Spider.obj";
	// "Data/models/Porsche_911_GT3.obj";
	
	// @param pattern the pattern description. eg 
	// "single;Data/hiro.patt;80"
	// "single;Data/kanji.patt;80"
	Model(const char* modelPath, const char* pattern, float scalingFactor = 0.035f) 
	{
		LOGE("initialized Car");
		model.patternID = arwAddMarker(pattern);
		arwSetMarkerOptionBool(model.patternID, ARW_MARKER_OPTION_SQUARE_USE_CONT_POSE_ESTIMATION, false);
		arwSetMarkerOptionBool(model.patternID, ARW_MARKER_OPTION_FILTERED, true);
		
		model.obj = glmReadOBJ2(modelPath, 0, 0); // context 0, don't read textures yet.
		
		if (!(model.obj)) {
			LOGE("Error loading model from file '%s'.", modelPath);
			exit(-1);
		}
		glmScale(model.obj, scalingFactor);
		
		glmCreateArrays(model.obj, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		model.visible = false;
	}
	
	~Model()
	{
		clearObj();
	}
	
	ARModel& getModel()
	{
		return model;
	}
	

	
	void clearObj()
	{
		if (model.obj != nullptr)
		{
			glmDelete(model.obj, 0);
			model.obj = nullptr;
		}
	}
	
	void render();
	
	bool visible() const
	{
		return model.visible;
	}
	
	void setVisible(bool v)
	{
		model.visible = v;
	}
	
	ARModel model;
};

class Car : public Model{
public:
	using Model::Model;
	
	void setVelocity(Vector vel) {
		velocity = vel;
	}
private:
	
	Vector velocity;
};