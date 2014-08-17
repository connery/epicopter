#include <AeroQuad/UserConfiguration.h>
#include <WProgram.h>

// set USE_USB_SERIAL if communication should be do via USB                                                                                                                                                                                   // otherwise communication is done on Serial1                                                                                                                                                                                                // see WProgram.h for implementation details                                                                                                                                                                                                   

#if !defined (WirelessTelemetry)
  #define USE_USB_SERIAL
#endif


__attribute__(( constructor )) void premain() {
    init();
}

extern "C"{
        void _init(){};
}

// Uncomment this if compiling on OS X
/*extern "C"{
	void _init(){}; // dummy _init function for support of GNU toolchain from https://launchpad.net/gcc-arm-embedded
}*/

int main(void)
{
	//init();
  	setup();

	for (;;)
		loop();

	return 0;
}


#include "AeroQuad/AeroQuad.ino"

