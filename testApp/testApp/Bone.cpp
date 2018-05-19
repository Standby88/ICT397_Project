#include "Bone.h"

Bone::Bone()
{
	name = ""; id = 12;
}

Bone::Bone(Mesh * in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = AiToGLMMat4(in_o_mat);

	mesh = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}

Bone::Bone(Mesh * in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = in_o_mat;

	mesh = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}

glm::mat4 Bone::GetParentTransforms()
{
	Bone* b = parent_bone;
	std::vector<glm::mat4> mats;
	while (b != nullptr)
	{
		{                      //to avoid confusion).
			glm::mat4 tmp_mat = AiToGLMMat4(b->node->mTransformation); //This bone's transformation.
			mats.push_back(tmp_mat);

			b = b->parent_bone;    //We set b to its own parent so the loop can continue.
		}
	}
	glm::mat4 concatenated_transforms;
	//IMPORTANT!!!! This next loop must be done in reverse, 
	//as multiplication with matrices is not commutative.
	for (int i = mats.size() - 1; i >= 0; i--)
	{
		concatenated_transforms *= mats.at(i);
	}
		

	return concatenated_transforms;    //Finally, we return the 
}
