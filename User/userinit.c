#include "userinit.h"
#include "moteid.h"
#define DEBUG 1
#if DEBUG
#include "runtime/uartstdio.h"
#define PRINTF(...)   uart_printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


/*********************************************************************************************************
** Function name:       userinit
** Descriptions:        �û���ʼ���������Զ�����Ҫ��ʼ���Ĺ��ܣ���������㣩
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
** Created by:          ��УԴ
** Created Date:        2018-04-05
*********************************************************************************************************/
void userinit(void){
  //��ʼ��Radio ֮ǰ ��ʼ���������
  moteid_init();
  parainit(get_moteid());
  NETSTACK_RADIO.init();
}

int parainit(uint16_t moteid){
  PRINTF("time is up");
   PRINTF("time is up");
    PRINTF("time is up"); PRINTF("time is up"); PRINTF("time is up"); PRINTF("time is up"); PRINTF("time is up"); PRINTF("time is up"); PRINTF("time is up");
    return 1;
}