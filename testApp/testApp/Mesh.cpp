#include "Mesh.h"
#include "GameObject3D.h"
#include <glm/gtx/string_cast.hpp>


Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, vector<VertexBoneData> bone_id_weights)
{
	this->vertices = vertices;

	this->indices = indices;

	this->textures = textures;
	
	this->bones_id_weights_for_each_vertex = bone_id_weights;
	// Now that we have all the required data, set the vertex buffers and its attribute pointers.
	this->setupMesh();
}

void Mesh::DrawCharacter(Shader shader, GameObject3D * parentGObj)
{
	// Bind appropriate textures
	GLuint diffuseNormal = 1;
	GLuint specularNormal = 1;

	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		stringstream ss;
		string number;
		string name = this->textures[i].type;

		if (name == "texture_diffuse")
		{
			ss << diffuseNormal++; // Transfer GLuint to stream
		}
		else if (name == "texture_specular")
		{
			ss << specularNormal++; // Transfer GLuint to stream
		}

		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
		// And finally bind the texture active texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}	

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//set every active texture to zero
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Mesh::Mesh()
{

}

void Mesh::setMesh()
{
	this->setupMesh();
}

void Mesh::drawTerrain(Shader shader)
{
	glUniform1i(glGetUniformLocation(shader.Program, "t1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "t2"), 1);
	glUniform1i(glGetUniformLocation(shader.Program, "t3"), 2);
	glUniform1i(glGetUniformLocation(shader.Program, "t4"), 3);
	GLuint t1 = terrainTex[0];
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t1);

	GLuint t2 = terrainTex[1];
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t2);

	GLuint t3 = terrainTex[2];
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t3);

	GLuint t4 = terrainTex[3];
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, t4);
	// Draw mesh
	glBindVertexArray(this->VAOT);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::Draw(Shader shader)
{
	// Bind appropriate textures
	GLuint diffuseNormal = 1;
	GLuint specularNormal = 1;

	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		stringstream ss;
		string number;
		string name = this->textures[i].type;

		if (name == "texture_diffuse")
		{
			ss << diffuseNormal++; // Transfer GLuint to stream
		}
		else if (name == "texture_specular")
		{
			ss << specularNormal++; // Transfer GLuint to stream
		}

		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
		// And finally bind the texture active texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	// Also set each mesh's shininess property to a default value 
	//since we didn't take any of assimps values at the current time
	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//set every active texture to zero
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Mesh::setTerrainMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAOT);
	glGenBuffers(1, &this->VBOT);
	glGenBuffers(1, &this->EBOT);

	glBindVertexArray(this->VAOT);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOT);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	//height value
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, height));


	glBindVertexArray(0);
}


void Mesh::setupMesh()
{

	//vertices data
	glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bone data
	if (bones_id_weights_for_each_vertex.size() > 0)
	{
		glGenBuffers(1, &VBO_bones);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glBufferData(GL_ARRAY_BUFFER, bones_id_weights_for_each_vertex.size() * sizeof(bones_id_weights_for_each_vertex[0]), &bones_id_weights_for_each_vertex[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	

	//numbers for sequence indices
	glGenBuffers(1, &EBO_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// create VAO and binding data from buffers to shaders
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); // offsetof(Vertex, normal) = returns the byte offset of that variable from the start of the struct
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, height));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glEnableVertexAttribArray(4);
	glVertexAttribIPointer(4, 4, GL_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)offsetof(VertexBoneData, weights));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indices);
	glBindVertexArray(0);

	/*
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	//height value
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, height));


	glBindVertexArray(0);*/
}