#pragma once
class Locomotive
{
private:
	int tractiveForce;
	int locomotiveNumber;
	int lifeTime;
public:
	Locomotive(int force,int lifeTime,int number);
	int getTractiveForce();
	int getLocomotiveNumber();
	int getLifeTime();
	void setLifeTime(int time);
	void setTractiveForce(int force);
	void setLocomotiveNumber(int number);
};

