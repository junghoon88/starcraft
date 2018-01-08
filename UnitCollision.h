#pragma once

class Unit;
class Building;
class nrMineral;
class nrGas;

class UnitCollision
{
public:
	UnitCollision();
	~UnitCollision();

	bool isCollision(Unit* unitMove, Unit* unitHold);
	bool isCollision(Unit* unit, Building* building);
	bool isCollision(Unit* unit, nrMineral* mineral);
	bool isCollision(Unit* unit, nrGas* gas);



};

