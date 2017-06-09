#ifndef MC_VAR_H_
#define MC_VAR_H_

struct Connection{
	uint8_t px:1;
	uint8_t gcs:1;
}connected = { 0, 0 };

//uint8_t 		px_connected 			= 0;
//uint8_t			gcs_connected			= 0;
uint8_t 		sys_id_px				= 0;

#endif /* MC_VAR_H_ */
