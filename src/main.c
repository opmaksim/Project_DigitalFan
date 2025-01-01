#include "AP/apMain.h"
#include "Driver/Fan/Fan.h"
#include "Periph/TIM/TIM.h"

int main(void)
{
	apMain_init();
	while (1)
	{
		apMain_execute();
	}
}

