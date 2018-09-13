#include "moteid.h"
#include "cfs-coffee-arch.h"
uint16_t moteid;

void moteid_init(void)
{
    uint32_t id;
  stm32f10xx_flash_read(MOTE_ID_FLASH_ADDR,&id,4);
  moteid = id >> 16;
}

uint16_t get_moteid(void)
{
  return moteid;
}
uint16_t get_cluster_name(uint16_t moteid)
{
  return (((moteid-1)/5)+1);
}