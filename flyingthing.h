#ifndef FLYINGTHING_H
#define FLYINGTHING_H

#include "monster.h"


class FlyingThing : public Monster
{
public:
    FlyingThing(int, int);
    ~FlyingThing();
};

#endif // FLYINGTHING_H
