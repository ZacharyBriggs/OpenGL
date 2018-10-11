#include "Geometry.h"
#include <glm/glm/ext.hpp>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

//1. Function that generates a half circle given a number of points and radius.
std::vector<glm::vec4> Geometry::genHalfCircle(int np, int radius)
{
	//A vector of vec4s that the indices will be pushed onto and returned
	std::vector<glm::vec4> points;

	for (float i = 0; i < np; i++)
	{
		//We calculate the slice by divinding pi by the number of points.
		float slice = glm::pi<float>() / ((float)np - 1);
		//Theta is the current point multiplied by the slice we just calculated
		//This will give us the angle between the current point and the last point
		float theta = i * slice;
		//We calculate the point using theta and cos/sin
		//Cos always represents X while Sin represents Y
		//Z is set to 0 since we're only generating a circle, not a sphere.
		//Since we're using a vec4 we need a 4th value but it doesn't represent anything and we don't care about
		//it so we just set it to 0.
		points.push_back(glm::vec4(glm::cos(theta) * radius, glm::sin(theta) * radius, 0, 1));
	}
	return points;
}

//2. Function that generates a sphere given a half circle, and number of meridians.
std::vector<glm::vec4> Geometry::genSphere(std::vector<glm::vec4> points, unsigned int nm, glm::vec3 position)
{
	//THe points to be generated and returned at the end of the function
	std::vector<glm::vec4> allPoints;
	for (int i = 0; i < nm + 1; i++)
	{
		//sphereSlice is calculated by multiplying pi by 2 and then diving by the number of rotations/miridians
		float sphereSlice = (glm::pi<float>() * 2) / (float)nm;
		//Theta is the current point multiplied by the slice we just calculated
		//This will give us the angle between the current point and the last point
		float theta = i * sphereSlice;

		for (int j = 0; j < points.size(); j++)
		{
			//We rotate and the X so X doesn't change.
			float newX = points[j].x + position.x;
			//We calculate y by multiplying the old Y by cosine of theta and then adding it to
			//old Z multiplyed by negative sine of theta
			float newY = points[j].y * cos(theta) + points[j].z * -sin(theta) + position.y;
			//In order to calculate Z we do the opposite of the above except sine is not negative.
			float newZ = points[j].z * cos(theta) + points[j].y * sin(theta) + position.z;
			//We create a new point and give it the values we just calculated.
			glm::vec4 point = glm::vec4(newX, newY, newZ, 1);
			//We push the point onto the list of points.
			allPoints.push_back(point);
		}
	}
	return allPoints;
}

//3. Function that generates indices for geometry to be rendered using triangle strips.
std::vector<unsigned int> Geometry::genSphereIndices(unsigned int np, unsigned int nm)
{
	std::vector<unsigned int> indices;
	//2 5	5 8
	//1 4	4 7
	//0 3	3 6

	unsigned int group;
	unsigned int left_col;
	unsigned int right_col;

	for (int y = 0; y < nm; y++)
	{
		group = y * np;

		for (int j = 0; j < np; j++)
		{
			left_col = group + j;
			right_col = left_col + np;

			//We alternate between bot_left and bot_right to get the pattern for the sphere indices.
			//It'll look something like 0,3,1,4,2,5,etc.
			indices.push_back(left_col);
			indices.push_back(right_col);
		}
		indices.push_back(0xFFFF);
	}
	return indices;
}

//4. Ability to render a plane with predefined vertex information.
std::vector<Vertex> Geometry::genPlane(int size)
{
	//We generate the top left ,top right, bot left, bot right points and then return them.
	Vertex tl = Vertex(glm::vec4(-size, size, 0, 1), glm::vec4(1, 0, 0, 1),glm::vec2(0,0));
	Vertex tr = Vertex(glm::vec4(size, size, 0, 1), glm::vec4(1, 0, 0, 1), glm::vec2(1, 0));
	Vertex bl = Vertex(glm::vec4(size, -size, 0, 1), glm::vec4(1, 0, 0, 1), glm::vec2(1, 1));
	Vertex br = Vertex(glm::vec4(-size, -size, 0, 1), glm::vec4(1, 0, 0, 1), glm::vec2(0, 1));
	std::vector<Vertex> vertices = { tl,tr,bl,br };
	return vertices;
}

//5. Ability to render a cube with predefined vertex information.
std::vector<Vertex> Geometry::genCube(std::vector<Vertex> vertices)
{
	//We generate a cube with points that we define since procedurally is impossible
	//or just very difficult.
	//Each side of the cube is just like generating a plane.
	//Each side after the Front side shares ponts with the side before it so they'll 
	//only need two points rather than four. 
	std::vector<Vertex> verts;
	//Front
	verts.push_back(Vertex(glm::vec4(0, 1, 1, 1), glm::vec4(1), glm::vec2(0)));//0
	verts.push_back(Vertex(glm::vec4(1, 1, 1, 1), glm::vec4(1), glm::vec2(0)));//1
	verts.push_back(Vertex(glm::vec4(1, 0, 1, 1), glm::vec4(1), glm::vec2(0)));//2
	verts.push_back(Vertex(glm::vec4(0, 0, 1, 1), glm::vec4(1), glm::vec2(0)));//3

	//Bot
	verts.push_back(Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(1), glm::vec2(0)));//4
	verts.push_back(Vertex(glm::vec4(1, 0, 0, 1), glm::vec4(1), glm::vec2(0)));//5

	//Back
	verts.push_back(Vertex(glm::vec4(1, 1, 0, 1), glm::vec4(1), glm::vec2(0)));//6
	verts.push_back(Vertex(glm::vec4(0, 1, 0, 1), glm::vec4(1), glm::vec2(0)));//7

	//Top
	verts.push_back(Vertex(glm::vec4(0, 1, 1, 1), glm::vec4(1), glm::vec2(0)));//8
	verts.push_back(Vertex(glm::vec4(1, 1, 1, 1), glm::vec4(1), glm::vec2(0)));//9

	//Right
	verts.push_back(Vertex(glm::vec4(1, 1, 0, 1), glm::vec4(1), glm::vec2(0)));//10
	verts.push_back(Vertex(glm::vec4(1, 0, 0, 1), glm::vec4(1), glm::vec2(0)));//11

	//Left
	verts.push_back(Vertex(glm::vec4(0, 1, 0, 1), glm::vec4(1), glm::vec2(0)));//12
	verts.push_back(Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(1), glm::vec2(0)));//13
	return verts;
}

std::vector<unsigned int> Geometry::genCubeIndices()
{
	//Much like the verts we have to hard set the indices
	//Again we don't need to repeat points so each side shares points with the one before it.
	std::vector<unsigned int> indices =
	{
		//We draw two triangles to make a square.
		//First square => 0,1,2 Second square = 2,3,0
		//This repeats for each side of course.
		0,1,2,2,3,0,//front
		3,2,4,4,5,2,//Bot
		4,5,6,6,7,4,//Back
		6,7,8,8,9,6,//Top
		2,1,10,10,11,2,//Right
		0,3,12,12,13,0//Left
	};
	return indices;
}
