#ifndef __NTCOINPOSDATA__
#define __NTCOINPOSDATA__

#include "NTConstants.h"

//��ͬ��·�ȼ��³��ֽ��Ⱥ�ĸ���
const float coin_show_probability[ROAD_HARD_LEVEL_MAX] = 
{
	0.2f, 0.3f, 0.35f, 0.40f, 0.50f, 0.60f, 0.70f, 0.80f, 0.80f, 0.70f
};

//��ͬ��·�ȼ��½��Ⱥ�ڳ���BUFF�ĸ���
const float buff_show_probability[ROAD_HARD_LEVEL_MAX] = 
{
	0.4f, 0.4f, 0.35f, 0.40f, 0.50f, 0.60f, 0.70f, 0.80f, 0.80f, 0.70f
};
//���Ⱥ��������ֵĸ���BUFF�ĸ��ʣ����䣬 ������㣩
const float buff_type_probability[BOX_BUFF_END-BOX_BUFF_START-1] = {0.2f, 0.4f, 0.6f, 0.7f, 1.0f};

#define COIN_GAP 22
#define COIN_PICTURE_START	39
#define COIN_TYPE_MAX	49
#define COIN_WIDTH_COUNT	5
#define COIN_HEIGHT_COUNT	7
#define COIN_POS_DATA	COIN_GAP*COIN_WIDTH_COUNT

#define GET_LETTER_COIN_INDEX_BY_ASCALL(x) x-55
#define GET_NUMBER_COIN_INDEX_BY_ASCALL(x) x-48
//=========================================

#endif /* defined(__NTCOINPOSDATA__) */
