//Author:        Salman Ahmed
//Date:          2022.01.05.
//Title:         Area Weather Stimulation
#include <iostream>
#include<exception>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "Area.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct AreaOwner
{
	int water_amount;
	string ownerName;    // Struct of Area Owners to be make Vector of.
	Area* area;

};

bool isEmpty(ifstream& cFile)
{
    return cFile.peek() == ifstream::traits_type::eof();   // checking if the file is empty or not.
}


void Rounds(const string &str, vector <AreaOwner> &ownersList, int &humidity) // Reading the text file and deciding the land regions.
{

	ifstream f;
	f.open(str.c_str());
	if(f.fail())
	{
		cout<<"File Not Found \n";
		exit(1);
	}
	else if (isEmpty(f))
	{
		cout <<"File is empty ";
        exit(1);

	}



int number;
f>>number;
f.ignore();

for(int i =0; i<number; i++)
{

	try
	{
            AreaOwner A1;
            string oneline;
            getline(f,oneline,'\n');//getting one line
            stringstream ss(oneline);//String Stream
            string oName; char region;
            ss >> oName >> A1.ownerName >> region>> A1.water_amount;
            if(region=='P'){
                A1.area = new PlainRegion(A1.water_amount);

            }
            else if (region=='G'){
                A1.area = new GrassLandRegion(A1.water_amount);

            }
             else if (region=='L'){
                A1.area = new LakesRegion(A1.water_amount);

            }
            else
            {
                cout<<"Area Region is not Valid"<<endl;
                exit(1);
            }

            ownersList.push_back(A1);
        }catch(Area ::Excpetions errs)
        {
            cout << "Water level cannot be Negative" <<errs<< endl;
            exit(1);
        }
        catch(...)
		 {
    		cout<<"An unexpected exception occurred."<<endl;
    		exit(1);
		 }
        }

    f>> humidity;
	}


bool Stimulations(vector<AreaOwner> &ownersList ,int humidity)
{
	Weather w(humidity);
    Weather* weather = w.wthr;
    cout << "Humidity is : " << weather->getHumidy() <<endl;
    ///Weather wdr = Weather::getInstance();
    cout<<"-----------------------------------"<<endl;
    cout<<"Stimulation Rounds"<<endl;
    cout<<"-----------------------------------"<<endl;

    for (int i=0; i<10; i++)
    {
    	cout<<"==================================="<<endl;
        cout << "Simulation No:" << i+1 <<endl;
        cout<<"==================================="<<endl;

        for (int unsigned j=0; j<ownersList.size();j++)
        {
        	//cout << ownersList[j].ownerName <<endl;
           //cout << " before" << weather->getHumidy() <<endl;

        	weather->weatherChange();
        	weather = weather->wthr;
            ownersList[j].area->Area_transfer(weather);
           //ownersList[j].area = ownersList[j].area->change_Area();
          //cout << " after" << weather->getHumidy() <<endl;
         //cout << weather->getHumidy() <<endl;
            if(ownersList[j].area->get_wLevel()>=0)
            {
                //ownersList[j].area = ownersList[j].area->Area_transfer(weather);
                ownersList[j].area = ownersList[j].area->change_Area();
                cout << "Mr. " << ownersList[j].ownerName << " ";
                cout << ownersList[j].area->getAreaName() << " ";
                cout << ownersList[j].area->get_wLevel() << " Km^3"<<endl;
            }
            else
            {
                cout << "Amount of stored water cannot be negative!" << endl;
                return false;
            }
        }

    }
    return true;

}


void waterLevel(vector<AreaOwner> ownersList,string &proprtyOwner,int &max_level)
{
    max_level = ownersList[0].area->get_wLevel();
    proprtyOwner = ownersList[0].ownerName;

        for(int unsigned i=0; i<ownersList.size(); i++)
        {


        if (ownersList[i].area->get_wLevel() > max_level)
        {
            max_level = ownersList[i].area->get_wLevel();
            proprtyOwner = ownersList[i].ownerName;
        }

		}
    }


#define NORMAL_MODE
#ifdef NORMAL_MODE



int main(int argc, char** argv) {

	string proprtyOwner;
    int max_level;
    int humidity;
    vector<AreaOwner> ownersList;
    Rounds("t2.txt",ownersList,humidity);

    if (Stimulations(ownersList,humidity))
    {
        waterLevel(ownersList,proprtyOwner,max_level);
        cout<<"\n\n---------------------------------------------------------------------------"<<endl;
        cout << "Mr. "<<proprtyOwner<<" has the most water after 10 Simulation Rounds that is : "<<max_level<<" km^3. |"<< endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
    }
    else
    {
        cout <<"Simulation process was not completed!\n";
    }

    return 0;
}


#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("TransferWeather","one"){
    Weather* weather1 = new Weather(35);
    REQUIRE(weather1->wthr->getWeatherName()=="Sunny");
    Weather* weather2 = new Weather(45);
    REQUIRE(weather2->wthr->getWeatherName()=="Cloudy");
    Weather* weather3 = new Weather(86);
    REQUIRE(weather3->wthr->getWeatherName()=="Rainy");
    delete weather1;
    //weather1 = new Weather(65);
   //Weather* weather1 = new Weather(35);
  //REQUIRE(weather1->wthr->getWeatherName()=="Sunny");
}


TEST_CASE("CheckArea","second"){

    Area* a1 = new PlainRegion(12);
    REQUIRE(a1->getAreaName()=="Plain");
    Area* a2 = new GrassLandRegion(45);
    REQUIRE(a2->getAreaName()=="GrassLand");
    Area* a3 = new LakesRegion(58);
    REQUIRE(a3->getAreaName()=="LakesRegion");
    Weather* w1 = new Weather(92);
    w1 = w1->wthr;
    //a1 = a2;
    a1->Area_transfer(w1);// 20 increase in water
    CHECK(a1->get_wLevel() == 32);
    a1= a1->change_Area();
    CHECK(a1->getAreaName() =="GrassLand");

    a2->Area_transfer(w1); // 15 increase in water
    CHECK(a2->get_wLevel() == 60);
    a2 =a2->change_Area();
    CHECK(a2->getAreaName() =="LakesRegion");

    Weather* w2 = new Weather(18);
    w2 = w2->wthr;
    a3->Area_transfer(w2); // 15 increase in water
    CHECK(a3->get_wLevel() == 48);
    a3 = a3->change_Area();
    CHECK(a3->getAreaName() =="GrassLand");


}


TEST_CASE("second", "t1.txt"){
    string propertyOwner;
    int max_level;
    int humidity;
    vector<AreaOwner> ownerList;
    Rounds("t1.txt",ownerList,humidity);
    waterLevel(ownerList,propertyOwner,max_level);
    REQUIRE(max_level == 86);


}
TEST_CASE("first","t2.txt"){
    string ownerArea;
    int humidity;
    vector<AreaOwner> ownersList;
    Rounds("t2.txt",ownersList,humidity);
    REQUIRE(ownersList[0].ownerName == "Bean");
    REQUIRE(ownersList[1].ownerName == "Green");
    REQUIRE(ownersList[2].ownerName == "Dean");
    REQUIRE(ownersList[3].ownerName == "Teen");
    REQUIRE(ownersList[0].water_amount == 56);
    REQUIRE(ownersList[1].water_amount == 26);
    REQUIRE(ownersList[2].water_amount == 12);
    REQUIRE(ownersList[3].water_amount == 35);
    REQUIRE(ownersList[0].area->getAreaName()=="LakesRegion");
    REQUIRE(ownersList[1].area->getAreaName()=="GrassLand");
    REQUIRE(ownersList[2].area->getAreaName()=="Plain");
    REQUIRE(ownersList[3].area->getAreaName()=="GrassLand");
    Weather* weather1 = new Weather(25);
    weather1 = weather1->wthr;
    ownersList[0].area->Area_transfer(weather1);
    ownersList[0].area->change_Area();
    //ownersList[0].area->(weather1);

    REQUIRE(ownersList[0].area->get_wLevel() == 46);
    //REQUIRE(ownersList[0].area->getAreaName() == "GrassLand");


}

TEST_CASE("Area_change()","new vector pushing "){
    vector<Area*> cont;
    cont.push_back(new PlainRegion(15));
    //cont.push_back(new PlainRegion(0));
//    cont.push_back(new PlainRegion(40));
//    cont.push_back(new PlainRegion(40));
//    cont.push_back(new PlainRegion(400000));
//    cont.push_back(new GrassLandRegion(16));
//    cont.push_back(new GrassLandRegion(15));
//    cont.push_back(new GrassLandRegion(0));
//    cont.push_back(new GrassLandRegion(1000));
//    cont.push_back(new GrassLandRegion(50));

//    for(int i = 0; i<3; i++){
//        cont[i] = cont[i]->change_Area();
//    }
    cont[0]->change_Area();
    //cont[1] = cont[1]->change_Area();
//    cont[2] = cont[2]->change_Area();
//    cont[3] = cont[3]->change_Area();
//    cont[5] = cont[5]->change_Area();
//    cont[6] = cont[6]->change_Area();
//    cont[7] = cont[7]->change_Area();
//    cont[8] = cont[8]->change_Area();
//    cont[9] = cont[9]->change_Area();
//    cont[10] = cont[10]->change_Area();

    REQUIRE(cont.at(0)->getAreaName() == "Plain");
    //REQUIRE(cont.at(1)->getAreaName() == "Plain");
//    REQUIRE(cont.at(2)->getAreaName() == "GrassLand");
//    REQUIRE(cont.at(3)->getAreaName() == "GrassLand");
//    REQUIRE(cont.at(4)->getAreaName() == "GrassLand");
//    REQUIRE(cont.at(5)->getAreaName() == "GrassLand");
//    REQUIRE(cont.at(6)->getAreaName() == "Plain");
//    REQUIRE(cont.at(7)->getAreaName() == "Plain");
//    REQUIRE(cont.at(8)->getAreaName() == "LakesRegion");
//    REQUIRE(cont.at(9)->getAreaName()== "Grassland");

}






#endif // NORMAL_MODE


