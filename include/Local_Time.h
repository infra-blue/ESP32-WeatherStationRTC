#pragma once

#include <Timezone.h>

/**
 * @brief
 *    Change the timezone here
 *    The default timezone is Central European Time (Rome)
 *    You can find more timezones in the Timezone.h file
 *    Uncomment the timezone you want to use and comment the others
 */

//Central European Time (Rome)
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Daylight time = UTC + 1 hour
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Standard time = UTC + 2 hours
Timezone CE(CET, CEST);

Timezone* current_timezone = &CE;

/*
    // Australia Eastern Time Zone (Sydney)
    TimeChangeRule aEDT = {"AEDT", First, Sun, Oct, 2, 660};
    TimeChangeRule aEST = {"AEST", First, Sun, Apr, 3, 600};
    Timezone ausET(aEDT, aEST);
    
    // Moscow Standard Time (Moscow)
    TimeChangeRule msk = {"MSK", Last, Sun, Mar, 1, 180};
    Timezone tzMSK(msk);
    
    // United Kingdom (London)
    TimeChangeRule BST = {"BST", Last, Sun, Mar, 1, 60};
    TimeChangeRule GMT = {"GMT", Last, Sun, Oct, 2, 0};
    Timezone UK(BST, GMT);
    
    // US Eastern Time Zone (New York, Detroit)
    TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240};
    TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300};
    Timezone usET(usEDT, usEST);
    
    // US Central Time Zone (Chicago, Houston)
    TimeChangeRule usCDT = {"CDT", Second, Sun, Mar, 2, -300};
    TimeChangeRule usCST = {"CST", First, Sun, Nov, 2, -360};
    Timezone usCT(usCDT, usCST);
    
    // US Mountain Time Zone (Denver, Salt Lake City)
    TimeChangeRule usMDT = {"MDT", Second, Sun, Mar, 2, -360};
    TimeChangeRule usMST = {"MST", First, Sun, Nov, 2, -420};
    Timezone usMT(usMDT, usMST);

    // US Pacific Time Zone (Las Vegas, Los Angeles)
    TimeChangeRule usPDT = {"PDT", Second, Sun, Mar, 2, -420};
    TimeChangeRule usPST = {"PST", First, Sun, Nov, 2, -480};
    Timezone usPT(usPDT, usPST);
*/