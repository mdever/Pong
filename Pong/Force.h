#ifndef FORCE_H
#define FORCE_H

#include<vector>

#include "PhysicalObject.h"

class PhysicalObject;

class Force
{
public:
	virtual void apply_force(PhysicalObject &entity) = 0;
};

#endif