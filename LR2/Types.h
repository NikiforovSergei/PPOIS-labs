#pragma once

enum TYPE { PASSENGER, CARGO, MIXED, UNKNOWN };

inline const char* toString(TYPE t)
{
    switch (t)
    {
    case PASSENGER:   return "Passenger";
    case CARGO:   return "Cargo";
    case MIXED: return "Mixed";
    default:      return "Unknown";
    }
}