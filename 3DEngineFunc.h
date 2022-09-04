#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

struct _Vector3D
{
	// Coordinates of the Vector
	float x,y,z;

	
	_Vector3D()
	{
		x = 0;y = 0;z = 0;
	}

	// Constructor with specified inputs
	_Vector3D(float X=0, float Y=0, float Z=0)
	{
		x = X;
		y = Y;
		z = Z;
	}

	/* Distance from a vector to another vector
	*/
	float DistanceTo(_Vector3D Vector)
	{
		return sqrtf(pow(x - Vector.x, 2) +
			pow(y - Vector.y, 2) + pow(z - Vector.z, 2));
	}

	// The angle Between 2 vectors (0-180 degrees)
	float AngleTo(_Vector3D vector)
	{
		float Theta = (x * vector.x + y * vector.y + z * vector.z) / 
			(getMagnitude() * vector.getMagnitude());
		return  acosf(Theta);
			
	}

	// Get the size of the vector 
	float getMagnitude()
	{

		return sqrtf(x * x + y * y + z * z);
	}

	/* Compute the Cross Product of two vectors
	The return is a 3D vector */
	_Vector3D CrossProduct(_Vector3D R_Vector)
	{
		return _Vector3D(
			(y * R_Vector.z - z * R_Vector.y), 
			-(x * R_Vector.z - z * R_Vector.x),
			(x * R_Vector.y - y * R_Vector.x));
	}

	// Compute the dot Product of two vectors
	float DotProduct(_Vector3D R_Vector)
	{
		return (x * R_Vector.x + y * R_Vector.y + z * R_Vector.z);
	}

	// Return the 3D projection of vectorA on vectorB
	// *the size of A on B*
	_Vector3D Proj_OnVec(_Vector3D R_Vector)
	{
		return R_Vector*(DotProduct(R_Vector)/pow(R_Vector.getMagnitude(),2));
	}

	// Convert the Vector to 0-1 
	// only the size changes , not the directior 
	_Vector3D Normalize()
	{
		
		float magnitude = getMagnitude();
		return _Vector3D(x / magnitude, y / magnitude, z / magnitude);
	}

	// Custom operators to ease calculations
	//----------------------------------//
	friend _Vector3D operator+(_Vector3D L_Vec, _Vector3D R_Vec)
	{
		return _Vector3D(L_Vec.x + R_Vec.x, L_Vec.y + R_Vec.y, L_Vec.z + R_Vec.z);
	}
	friend _Vector3D operator-(_Vector3D L_Vec, _Vector3D R_Vec)
	{
		return _Vector3D(L_Vec.x - R_Vec.x, L_Vec.y - R_Vec.y, L_Vec.z - R_Vec.z);
	}
	friend _Vector3D operator/(_Vector3D L_Vec, float Constant)
	{
		return _Vector3D(L_Vec.x / Constant, L_Vec.y / Constant, L_Vec.z / Constant);
	}
	friend _Vector3D operator/(float Constant,_Vector3D L_Vec )
	{
		return _Vector3D(L_Vec.x / Constant, L_Vec.y / Constant, L_Vec.z / Constant);
	}
	friend _Vector3D operator*(_Vector3D L_Vec, float Constant)
	{
		return _Vector3D(L_Vec.x * Constant, L_Vec.y * Constant, L_Vec.z * Constant);
	}
	friend _Vector3D operator*(float Constant,_Vector3D L_Vec )
	{
		return _Vector3D(L_Vec.x * Constant, L_Vec.y * Constant, L_Vec.z * Constant);
	}
	//-----------------------------------//

	// Cout operator oveloading (Custom Print)
	friend std::ostream& operator<<(std::ostream& os,_Vector3D vec)
	{
		return os << "[" << vec.x << "," <<vec.y << "," << vec.z << "]";
	}

	
};


