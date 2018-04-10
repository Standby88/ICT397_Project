// PhysicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PhysicsFacade.h"
#include <fstream>

int main()
{
	std::cout << "Hello World!" << std::endl;

	//-------------------------------------------------------------
	char* filename = "height128.raw";
	unsigned char* terrainData = NULL; 
	int size = 128;
	//open for binary read
	std::ifstream infile(filename, std::ios::binary);
	if (!infile)
	{
		std::cerr << "Cannot open file: " << filename << std::endl;
		return false;
	}

	//allocate memory
	if (terrainData)
	{
		delete[] terrainData;
	}
	if (size > 0)
	{
		terrainData = new unsigned char[size*size];
	}
	if (terrainData == NULL)
	{
		return false;
	}

	//read in heightfield
	//get length of file
	infile.seekg(0, std::ios::end);
	int length = infile.tellg();

	//read data as a block
	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char*>(terrainData), length);
	infile.close();
	//-----------------------------------------------------------

	PhysicsFacade pf = PhysicsFacade();
	PhysicsVector grav(0, -10, 0);
	PhysicsVector planeNorm(0, 1, 0);
	float offSet = 1;

	pf.InitGravity(grav);
	//pf.CreateStaticRigidPlane(planeNorm, offSet);
	pf.CreateHeightFieldRigidBody(10, 10, terrainData, 1, 1, false, false);
	pf.CreateFallingSphereRigidBody(1);
	for (int i = 0; i < 300; i++)
	{
		pf.StepSimulation(1 / 60.f, 10);
	}
	
	std::getchar();
	//pf.~PhysicsFacade();
	

    return 0;
}

