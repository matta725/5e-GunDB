// DB-GunDB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "gundb.h"

using namespace std;


// from Prof. Bailey @ OSU
float
Ranf(float low, float high)
{
    float r = (float)rand();               // 0 - RAND_MAX
    float t = r / (float)RAND_MAX;       // 0. - 1.

    return   low + t * (high - low);
}

int
Ranf(int ilow, int ihigh)
{
    float low = (float)ilow;
    float high = ceilf((float)ihigh);

    return (int)Ranf(low, high);
}

void
TimeOfDaySeed()
{
    struct tm y2k = { 0 };
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time_t  timer;
    time(&timer);
    double seconds = difftime(timer, mktime(&y2k));
    unsigned int seed = (unsigned int)(1000. * seconds);    // milliseconds
    srand(seed);
}

//Prof Bailey End


void displayStats(string desc, string brand, string prefix, string dmg, string range, string capacity, string reload, string misfire, string accuracy, string radius) {
    if ((desc.find("RPG")) != std::string::npos) {
        cout << "\nGENERATED GUN: " << desc << "\n";
        cout << " * Brand: " << brand << "\n * Weapon Modifier: " << prefix << "\n * Damage: " << dmg << "\n * Range: " << range << "\n * Capacity: " << capacity << "\n * Reload Speed: " << reload << "\n * Explosion Radius: " << radius << "\n * Explosion Save DC: " << accuracy << "\n\n";
    }
    else {
        cout << "\nGENERATED GUN: " << desc << "\n";
        cout << " * Brand: " << brand << "\n * Weapon Modifier: " << prefix << "\n * Damage: " << dmg << "\n * Range: " << range << "\n * Capacity: " << capacity << "\n * Reload Speed: " << reload << "\n * Misfire: " << misfire << "\n * Accuracy Bonus: " << accuracy << "\n\n";
    }
    
}

int rollTable(int luck) {
    int roll = Ranf(1, 100);
    if ((roll + luck) > 100) {
        roll = 100;
    }
    if ((roll + luck) < 0) {
        roll = 0;
    }
    //cout << roll << "\n";
    if (roll <= 5) {
        return 0;
    }
    else if(roll <= 20) {
        return 1;
    }
    else if (roll <= 40) {
        return 2;
    }
    else if (roll <= 60) {
        return 3;
    }
    else if (roll <= 80) {
        return 4;
    }
    else if (roll <= 95) {
        return 5;
    }
    else if (roll <= 100) {
        return 6;
    }
    return -1;
}

void rngGun(int type, int luck) {
    if (type > 0 && type < 6) {
        // continue generation
        struct gunDB gun;
        switch (type) {
            case 1:
                gun.readDB(1);
                break;
            case 2:
                gun.readDB(2);
                break;
            case 3:
                gun.readDB(3);
                break;
            case 4:
                gun.readDB(4);
                break;
            case 5:
                gun.readDB(5);
                break;
        }
        if (gun.desc == "") {
            cout << "An error occurred while generating the weapon. :( \n\n";
        }
        else {
            int rollBrand = Ranf(0, gun.brand.size());
            string brand = gun.brand[rollBrand];
            int rollPrefix = Ranf(0, gun.prefix.size());
            string prefix = gun.prefix[rollPrefix];
            int rollDmg = rollTable(luck);
            string dmg = gun.dmg[rollDmg];
            int rollRange = rollTable(luck);
            string range = gun.range[rollRange];
            int rollCapacity = rollTable(luck);
            string capacity = gun.capacity[rollCapacity];
            int rollReload = rollTable(luck);
            string reload = gun.reload[rollReload];
            int rollMisfire = rollTable(luck);
            string misfire = gun.misfire[rollMisfire];
            int rollAccuracy = rollTable(luck);
            string accuracy = gun.accuracy[rollAccuracy];
            string radius = "0";
            displayStats(gun.desc, brand, prefix, dmg, range, capacity, reload, misfire, accuracy, radius);
        }
    }
        if (type == 6) {
            struct gunDB rpg;
            rpg.readDB(6);
            int rollBrand = Ranf(0, rpg.brand.size());
            string brand = rpg.brand[rollBrand];
            int rollPrefix = Ranf(0, rpg.prefix.size());
            string prefix = rpg.prefix[rollPrefix];
            int rollDmg = rollTable(luck);
            string dmg = rpg.dmg[rollDmg];
            int rollRange = rollTable(luck);
            string range = rpg.range[rollRange];
            int rollCapacity = rollTable(luck);
            string capacity = rpg.capacity[rollCapacity];
            int rollReload = rollTable(luck);
            string reload = rpg.reload[rollReload];
            int rollRadius = rollTable(luck);
            string radius = rpg.radius[rollRadius];
            int rollSave = rollTable(luck);
            string save = rpg.save[rollSave];
            string misfire = "nada";
            if (rpg.desc == "") {
                cout << "An error occurred while generating the weapon. :( \n\n";
            }
            else {
                displayStats(rpg.desc, brand, prefix, dmg, range, capacity, reload, misfire, save, radius);
            }
        }
        else if (!(type > 0 && type < 7)) {
            cout << "ERROR: Gun Type Invalid\n\n";
        }
}

void rngGunType(string type) {
    int gunType = stoi(type);
    rngGun(gunType, 0);
}

void rngGunRand() {
    int gunType = Ranf(1, 6);
    rngGun(gunType, 0);
}

void luckyGunType(string type, int luck) {
    int gunType = stoi(type);
    rngGun(gunType, luck);
}

void luckyGunRand(int luck) {
    int gunType = Ranf(1, 6);
    rngGun(gunType, luck);
}

int main()
{
    string exit = "";
    TimeOfDaySeed();
    while (exit != "x") {
        cout << "Menu:\n A- Create completely random gun,\n S- Create random gun of specified type,\n D- Create lucky random gun,\n F- Create lucky gun of specified type,\n X- Exit program\n";
        cin >> exit;
        transform(exit.begin(), exit.end(), exit.begin(), ::tolower);
        if (exit == "a") {
            rngGunRand();
        }
        else if (exit == "s") {
            string type = "";
            bool looper = true;
            while (looper == true) {
                cout << "-- What kind of gun would you like to create? --\n 1- Pistol, 2- Sniper Rifle, 3- Shotgun, 4- Assault Rifle, 5- SMG, 6- RPG\n";
                cin >> type;
                if (type == "1" || type == "2" || type == "3" || type == "4" || type == "5" || type == "6") {
                    looper = false;
                    rngGunType(type);
                }
                else {
                    cout << "Please type a valid option.\n\n";
                }
            }
        }
        else if (exit == "d") {
            int luck;
            cout << "-- Enter an integer between -100 and 100 to influence the weapon roll --\n";
            cin >> luck;
            luckyGunRand(luck);
        }
        else if (exit == "f") {
            string type = "";
            bool looper = true;
            while (looper == true) {
                cout << "-- What kind of gun would you like to create? --\n 1- Pistol, 2- Sniper Rifle, 3- Shotgun, 4- Assault Rifle, 5- SMG, 6- RPG\n";
                cin >> type;
                if (type == "1" || type == "2" || type == "3" || type == "4" || type == "5" || type == "6") {
                    looper = false;
                    int luck;
                    cout << "-- Enter an integer between -100 and 100 to influence the weapon roll --\n";
                    cin >> luck;
                    luckyGunType(type, luck);
                }
                else {
                    cout << "Please type a valid option.\n\n";
                }
            }
        }
        else {
            cout << "Please enter a valid menu option. \n\n";
        }
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
