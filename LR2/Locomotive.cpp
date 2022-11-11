#include "Locomotive.h"

Locomotive::Locomotive(int force,int lifeTime,int number)
{
	this->setTractiveForce(force);
	this->setLifeTime(lifeTime);
	this->setLocomotiveNumber(number);
}

int Locomotive::getTractiveForce()
{
	return tractiveForce;
}

int Locomotive::getLocomotiveNumber()
{
	return locomotiveNumber;
}

int Locomotive::getLifeTime()
{
	return lifeTime;
}

void Locomotive::setTractiveForce(int force)
{
	tractiveForce = force;
}

void Locomotive::setLocomotiveNumber(int number)
{
	locomotiveNumber = number;
}

void Locomotive::setLifeTime(int time)
{
	lifeTime = time;
}