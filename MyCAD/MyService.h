#pragma once
#include "ExSystemServices.h"
#include "ExHostAppServices.h"

class MyService: public ExSystemServices, public ExHostAppServices
{
protected:
	ODRX_USING_HEAP_OPERATORS(ExSystemServices);
};

