#ifndef TIMEZONECONF_H
#define TIMEZONECONF_H

#include <Timezone.h>

// Central European Time (Rome)
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Daylight time = UTC + 1 hour
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Standard time = UTC + 2 hours
Timezone CE(CET, CEST);

// Eastern Standard Time (USA, Canada)
TimeChangeRule EST = {"EST", First, Sun, Nov, 2, -300};   // Standard time = UTC - 5 hours
TimeChangeRule EDT = {"EDT", Second, Sun, Mar, 2, -240};  // Daylight time = UTC - 4 hours
Timezone ET(EST, EDT);

// Central Standard Time (USA, Canada)
TimeChangeRule CST = {"CST", First, Sun, Nov, 2, -360};   // Standard time = UTC - 6 hours
TimeChangeRule CDT = {"CDT", Second, Sun, Mar, 2, -300};  // Daylight time = UTC - 5 hours
Timezone CT(CST, CDT);

// Mountain Standard Time (USA, Canada)
TimeChangeRule MST = {"MST", First, Sun, Nov, 2, -420};   // Standard time = UTC - 7 hours
TimeChangeRule MDT = {"MDT", Second, Sun, Mar, 2, -360};  // Daylight time = UTC - 6 hours
Timezone MT(MST, MDT);

// Pacific Standard Time (USA, Canada)
TimeChangeRule PST = {"PST", First, Sun, Nov, 2, -480};   // Standard time = UTC - 8 hours
TimeChangeRule PDT = {"PDT", Second, Sun, Mar, 2, -420};  // Daylight time = UTC - 7 hours
Timezone PT(PST, PDT);

// Eastern European Time (EET)
TimeChangeRule EET = {"EET", Last, Sun, Oct, 3, 120};     // Standard time = UTC + 2 hours
TimeChangeRule EEST = {"EEST", Last, Sun, Mar, 2, 180};   // Daylight time = UTC + 3 hours
Timezone EE(EET, EEST);

// British Summer Time (BST)
TimeChangeRule GMT = {"GMT", Last, Sun, Oct, 1, 0};       // Standard time = UTC
TimeChangeRule BST = {"BST", Last, Sun, Mar, 1, 60};      // Daylight time = UTC + 1 hour
Timezone BT(GMT, BST);

// Australian Eastern Time (Sydney)
TimeChangeRule AEST = {"AEST", First, Sun, Apr, 3, 600};   // Standard time = UTC + 10 hours
TimeChangeRule AEDT = {"AEDT", First, Sun, Oct, 2, 660};   // Daylight time = UTC + 11 hours
Timezone AET(AEST, AEDT);

// Australian Central Time (Adelaide)
TimeChangeRule ACST = {"ACST", First, Sun, Apr, 3, 570};   // Standard time = UTC + 9.5 hours
TimeChangeRule ACDT = {"ACDT", First, Sun, Oct, 2, 630};   // Daylight time = UTC + 10.5 hours
Timezone ACT(ACST, ACDT);

// Australian Western Time (Perth)
TimeChangeRule AWST = {"AWST", Last, Sun, Oct, 1, 480};    // Standard time = UTC + 8 hours
Timezone AWT(AWST, AWST);  // No daylight saving time in Western Australia

// Japan Standard Time (Tokyo)
TimeChangeRule JST = {"JST", Last, Sun, Oct, 1, 540};      // Standard time = UTC + 9 hours
Timezone JT(JST, JST);  // No daylight saving time in Japan

// Korea Standard Time (Seoul)
TimeChangeRule KST = {"KST", Last, Sun, Oct, 1, 540};      // Standard time = UTC + 9 hours
Timezone KT(KST, KST);  // No daylight saving time in Korea

// Singapore Time (Singapore)
TimeChangeRule SGT = {"SGT", Last, Sun, Oct, 1, 480};      // Standard time = UTC + 8 hours
Timezone ST(SGT, SGT);  // No daylight saving time in Singapore

// Hong Kong Time (Hong Kong)
TimeChangeRule HKT = {"HKT", Last, Sun, Oct, 1, 480};      // Standard time = UTC + 8 hours
Timezone HT(HKT, HKT);  // No daylight saving time in Hong Kong

// China Standard Time (China)
TimeChangeRule CST_ASIA = {"CST", Last, Sun, Oct, 1, 480}; // Standard time = UTC + 8 hours
Timezone CT_ASIA(CST_ASIA, CST_ASIA);  // No daylight saving time in China

// Choose your time zone from the list above
Timezone *localTimezone = &CE;

#endif
