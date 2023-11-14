#include "Area.h"

Area:: Area(const string &AreaName, int water)
{

	if (water < 0) throw NEGATIVE_LEVEL;
    _area = AreaName;
    _wLevel = water;

}


//Area* PlainRegion::Area_transfer(Weather *wethr)
void PlainRegion::Area_transfer(Weather *wethr)
{
    if(wethr->getWeatherName() == "Rainy")
    {
        _wLevel = _wLevel + 20;

    }
    else if(wethr->getWeatherName() == "Cloudy")
    {
        _wLevel = _wLevel - 1;
    }
	else if(wethr->getWeatherName() == "Sunny")
    {
        _wLevel = _wLevel - 3;
    }
    wethr->setHumidty(wethr->getHumidy() + 5);


}


//Area* GrassLandRegion::Area_transfer(Weather *wethr)
void GrassLandRegion::Area_transfer(Weather *wethr)
{
    if(wethr->getWeatherName() == "Rainy")
    {
        _wLevel = _wLevel + 15;

    }
    else if(wethr->getWeatherName() == "Cloudy")
    {
        _wLevel = _wLevel - 2;
    }
	else if(wethr->getWeatherName() == "Sunny")
    {
        _wLevel = _wLevel - 6;
    }
    wethr->setHumidty(wethr->getHumidy() + 10);


}




//Area* LakesRegion::Area_transfer(Weather *wethr)
void LakesRegion::Area_transfer(Weather *wethr)
{
    if(wethr->getWeatherName() == "Rainy")
    {
        _wLevel = _wLevel + 20;

    }
    else if(wethr->getWeatherName() == "Cloudy")
    {
        _wLevel = _wLevel - 3;
    }
	else if(wethr->getWeatherName() == "Sunny")
    {
        _wLevel = _wLevel - 10;
    }
    wethr->setHumidty(wethr->getHumidy() + 15);


}

Area* GrassLandRegion :: change_Area()
{
	if(_wLevel < 16)
	{
		return new PlainRegion(_wLevel);
	}
	else if(_wLevel > 16 && _wLevel <=50 )
	{
		return new GrassLandRegion(_wLevel);
	}
	else if(_wLevel > 50)
	{

		return new LakesRegion(_wLevel);
	}
return 0;

}


Area* LakesRegion :: change_Area()
{
	if(_wLevel < 51)
	{
		return new GrassLandRegion(_wLevel);
	}
	else if(_wLevel >= 50 )
	{
		return new LakesRegion(_wLevel);
	}

return 0;
}


Area* PlainRegion :: change_Area()
{
	if(_wLevel <= 15 && _wLevel > 0)
	{
		return new PlainRegion(_wLevel);
	}
	else if(_wLevel > 15 )
	{
		return new GrassLandRegion(_wLevel);
	}
return 0;

}












