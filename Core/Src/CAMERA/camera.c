#include "camera.h"
#include "ov2640.h"
/* Private defines start */


/* Private defined end */


uint8_t CAMERA_Init(void)
{
    #ifdef OV2640_DevE
	
		OV2640_Init();
	
    #endif
	return 0;
}
