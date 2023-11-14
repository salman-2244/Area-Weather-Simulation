#pragma once
#include "Weather.h"

class Area
{

	public:

		enum Excpetions {NEGATIVE_LEVEL};
		virtual Area* change_Area() = 0;
		virtual void Area_transfer(Weather *wethr)=0;
		//Area(const string &AreaName, int water);
		string getAreaName() {return _area;}
		int get_wLevel(){return _wLevel;}
		void setAreaName(string a_name) { _area = a_name; }
		void set_wLevel(int water) {_wLevel = water;}
	protected:
		string _area;
		int _wLevel;
		Area(const string &AreaName, int water);
	};

		class PlainRegion : public Area
		{

			public:
				PlainRegion(int water) : Area("Plain", water) {}
				void Area_transfer(Weather *wethr) override;
				Area* change_Area() override;
			};

		class GrassLandRegion : public Area
		{

			public:
				GrassLandRegion(int water) : Area("GrassLand", water) {}
				void Area_transfer(Weather *wethr) override;
				Area* change_Area() override;
			};

		class LakesRegion : public Area
		{

			public:
				LakesRegion(int water) : Area("LakesRegion", water) {}
				void Area_transfer(Weather *wethr) override;
				Area* change_Area() override;
			};



