#pragma once
#ifndef BONE_H
#define BONE_H
#include "MathLib.h"
#include "FrameTime.h"
//#include "Animation.h"
#include <string>
#include <vector>

#include <assimp/scene.h>
#include <iostream> 

class Mesh;
//class Animation;
class GameObject;
class Skeleton;
static aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat)
{
	return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}

static glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat)
{
	glm::mat4 tmp;
	tmp[0][0] = in_mat.a1;
	tmp[1][0] = in_mat.b1;
	tmp[2][0] = in_mat.c1;
	tmp[3][0] = in_mat.d1;

	tmp[0][1] = in_mat.a2;
	tmp[1][1] = in_mat.b2;
	tmp[2][1] = in_mat.c2;
	tmp[3][1] = in_mat.d2;

	tmp[0][2] = in_mat.a3;
	tmp[1][2] = in_mat.b3;
	tmp[2][2] = in_mat.c3;
	tmp[3][2] = in_mat.d3;

	tmp[0][3] = in_mat.a4;
	tmp[1][3] = in_mat.b4;
	tmp[2][3] = in_mat.c4;
	tmp[3][3] = in_mat.d4;
	return tmp;
}
class Bone
{
public:
	std::string name;
	Mesh* mesh;
	aiNode* node;
	aiNodeAnim* animNode;
	Bone* parent_bone;
	glm::mat4 parent_transform;
	glm::mat4 offset_matrix;
	Skeleton* parent_skeleton;
	int id;
	Bone();
	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);
	glm::mat4 GetParentTransforms();

};
class Skeleton
{
public:
	std::vector<Bone> bones;
	glm::mat4 globalInverseTransform;
	std::vector<glm::mat4> boneMats;

	Skeleton()
	{

	}

	Skeleton(std::vector<Bone> in_bones, glm::mat4 in_globalInverseTransform)
	{
		Init(in_bones, in_globalInverseTransform);
	}
	void Init(std::vector<Bone> in_bones, glm::mat4 in_globalInverseTransform)
	{
		bones = in_bones;
		globalInverseTransform = in_globalInverseTransform;

		for (int i = 0; i < bones.size(); i++)
			bones.at(i).parent_skeleton = this;
	}
	//This next function is pretty self-explanatory...
	Bone* FindBone(std::string name)
	{
		for (int i = 0; i < bones.size(); i++)
		{
			if (bones.at(i).name == name)
				return &bones.at(i);
		}
		return nullptr;
	}

	//This one isn't really...
	void UpdateBoneMatsVector()
	{
		//The purpose of this function is to gather all of the bones'
		//global transformations (which we calculate below) and place them, in order,
		//in a vector of glm::mat4s. This is necessary because we'll have to pass
		//these matrices into the shader later on, and this format makes that really
		//easy.

		//If there are no bones, why bother?
		if (bones.size() == 0)
		{
			return;
		}

		//Make sure there's nothning left in the vector.
		boneMats.clear();



		//Here we must update the matrices to the shader until the MAX_BONES constant
		//in the shader, which is 100. You could set this as an engine variable but
		//for the purposes of this tutorial simply typing i < 100 will do.
		//We do this in order to make certain that every index in the shader's array
		//of matrices is filled, that there are no garbage or left-over matrices from
		//some other draw call.
		for (int i = 0; i < 100; i++)
		{
			//If we are past the number of bones in the actual skeleton, we simply
			//pass in an identity matrix.
			if (i > bones.size() - 1)
			{
				boneMats.push_back(glm::mat4(1.0));
			}
			else
			{
				//Now for the complicated stuff...
				//To get the concatenated transformation, we multiply the concatenated transforms of
				//the bone's parents with the bone's transformation.
				glm::mat4 concatenated_transformation = (bones.at(i).GetParentTransforms() * AiToGLMMat4(bones.at(i).node->mTransformation));

				//DISCLAIMER! By concatenated_transformation, what I actually mean is the transformation of the current bone in the
				//skeleton's local (or object) space. At this point it is not in world space, as being in world space requires multiplication by the
				//model matrix, which happens only in the shader stage.

				//REMEMBER: TO UNDERSTAND MATRIX MULTIPLICATION, WE MUST READ IT BACKWARDS!
				//Here we transform the bone back to the origin (with the offset matrix),
				//we multiply it by the concatenated transforms,
				//and then by the globalInverseTransform.
				boneMats.push_back(globalInverseTransform * concatenated_transformation* bones.at(i).offset_matrix);
			}
		}
	}
	void Update()
	{
		//This is the function where we'll update all of the animated transformations 
		//when we start implementing animations, but for now all we have to do is
		//update the vector of bone matrices.
		UpdateBoneMatsVector();
	}
};

#endif
