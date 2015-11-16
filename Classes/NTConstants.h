#ifndef __NTCONSTANTS__
#define __NTCONSTANTS__

#include "cocos2d.h"
#include "NTBox.h"
#include "NTGameSave.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
/*#include "NTCoinPosData.h"*/

//==========================================�������ȼ����趨
enum{
	PRIORITY_MESSAGE_BOX = kCCMenuHandlerPriority-20,		//�Ի���
	PRIORITY_NTLAYER_GUIDE,									//������
	PRIORITY_NTLAYER_MSG,									//������
	PRIORITY_NTLAYER_UI,									//UI��
	PRIORITY_NTLAYER_LEVEL_4,								//�ļ���
	PRIORITY_NTLAYER_LEVEL_3,								//������
	PRIORITY_NTLAYER_LEVEL_2,								//������
	PRIORITY_NTLAYER_LEVEL_1								//һ����
};
//===================================================================


//===========================================��ͼ��ײԪ��(����Ԫ�أ�����Ԫ�أ��к�Ԫ��)
enum{
	BOX_GOLDAREA_PROP1 = -6,	//���Ԫ��1
	BOX_GOLDAREA_PROP2,			//���Ԫ��2
	BOX_GOLDAREA_PROP3,			//���Ԫ��3
	BOX_GOLDAREA_PROP4,			//���Ԫ��4

	BOX_BALLOON1,				//����1
	BOX_BALLOON2,				//����2

	BOX_ROAD = 0,	//
	BOX_ROAD_1,		//·1
	BOX_ROAD_2,		//·2
	BOX_ROAD_3,		//·3
	BOX_BLOCK1,		//����
	BOX_BLOCK2,		//ʯͷ
	BOX_BLOCK3,		//����Ͱ
	BOX_BLOCK4,		//����
	
	BOX_FLY_BLOCK,	//�����ϰ���

	BOX_SPRING,		//����
	
	BOX_HOOK1,		//����
	BOX_HOOK2,		//����
	BOX_HOOK3,		//����

	BOX_COIN,		//���
	BOX_BUFF_START,
	BOX_ENGINE,		//��������
	BOX_LIQUID,		//����ҩˮ
	BOX_MAGNET,		//����
	BOX_SUPER_COIN,	//�������
	BOX_DEFENSE,	//������
	BOX_BUFF_END,
	BOX_BOMB,			//ը��
	BOX_BANANA_SKIN,	//�㽶Ƥ
	BOX_MOUNT_HORSE,		//������
	BOX_MOUNT_BEAR,			//������

	BOX_BRICK,			//שͷ
	BOX_ICE_BOX,		//����

	BOX_MAX
};
//============================================
const int box_count_coin[BOX_MAX]={
	0, 0, 0, 0, 1, 1, 1, 1, 20, 200, 11, 12, 13, 9, 0, 10, 10, 150, 1000, 20, 0, 100, 5, 500, 500, 100, 100};

//===========================================��Ϸ����
//��ͼԪ���е�Zorder
enum{
	GAME_MAP_SKY = -10,
	GAME_MAP_CLOUD,
	GAME_MAP_AUTO_BG,
	GAME_MAP_ROAD = 10,
	GAME_MAP_PROPS,
	GAME_MAP_COIN,
};
//����������ͼƬ��
const char autoBgFileName[8][20] = {
	"gd_tk.png", "gd_tk.png", "gd_zyj_0.png", 
	"gd_zyj_1.png", "gd_zj_0.png", "gd_zj_1.png",
	"jk_yj.png", "jk_yj.png"
};
//���������ȶԵ�·�ƶ��ٶȵı�ֵ
const float autoBgSpeedScale[4] = {0.01f, 0.02f, 0.05f, 0.1f};

//��·�ߵ�����
enum{
	ROAD_POSY_LOW = 0,
	ROAD_POSY_MED,
	ROAD_POSY_HIGH,
	ROAD_POSY_MAX
};
const int road_posy[ROAD_POSY_MAX] = {75, 120, 160};


//=========================================��Ϸ��·��������
//��·�׶�����
enum{
	ROAD_HARD_LEVEL_500,
	ROAD_HARD_LEVEL_1000,
	ROAD_HARD_LEVEL_2000,
	ROAD_HARD_LEVEL_3000,
	ROAD_HARD_LEVEL_4000,
	ROAD_HARD_LEVEL_5000,
	ROAD_HARD_LEVEL_6000,
	ROAD_HARD_LEVEL_7000,
	ROAD_HARD_LEVEL_8000,
	ROAD_HARD_LEVEL_9000,
	ROAD_HARD_LEVEL_MAX
};
//��·����
enum{
	ROAD_NOMAL = BOX_ROAD_1,	//������·
	ROAD_BLANK					//��϶��·
};
//��·��������
enum{
	ROAD_DATA_TYPE,		//��·���ͣ�0~1��
	ROAD_DATA_LENGTH,	//��·���ȣ�0~15��
	ROAD_DATA_HEIGHT,	//��·�߶ȣ�0~3��
	ROAD_DATA_MAX
};
#define ROAD_DATA_COUNT_EACH_LEVEL 20

//��ͼ��������
//10���ȼ���ÿ���ȼ�20�飬ÿ������3�����õ�
const int road_data[ROAD_HARD_LEVEL_MAX][ROAD_DATA_COUNT_EACH_LEVEL+1][ROAD_DATA_MAX] =
{
	//��һ�ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 10, 0}, {ROAD_NOMAL, 10, 0}, {ROAD_NOMAL, 9, 0}, {ROAD_NOMAL, 9, 0}, 
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{13, 19, 0}
	},
	//�ڶ��ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 16, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{12, 19, 0}
	},
	//�����ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//���ĵȼ���·��Ϣ
	{
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL,4, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//����ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//�����ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//���ߵȼ���·��Ϣ
	{
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//�ڰ˵ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{11, 19, 0}
	},
	//�ھŵȼ���·��Ϣ
	{
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{9, 19, 0}
	},
	//��ʮ�ȼ���·��Ϣ
	{
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_BLANK, 300, 0}, {ROAD_BLANK, 300, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0},
		//���һ������ͨ��·�Ϳ�϶�ķֽ��
		{7, 19, 0}
	}
};
//=========================================================

enum{
	PET_1,
	PET_2,
	PET_3,
	PET_MAX
};
enum{
	PET_DATA_SCALE,
	PET_DATA_MAX
};

const float pet_data[PET_MAX][PET_DATA_MAX] = {
	{0.6f},
	{0.6f},
	{0.6f}
};

enum{
	ACTOR_1,
	ACTOR_2,
	ACTOR_3,
	ACTOR_MAX
};

enum{
	ACTOR_DATA_JUMP_HIGH,
	ACTOR_DATA_JUMP_TIMES,
	ACTOR_DATA_CAN_OUT_OF_LEFT_SCREEN,
	ACTOR_DATA_HP,
	ACTOR_DATA_MAX
};

const int actor_data[ACTOR_MAX][ACTOR_DATA_MAX] = {
	{1200,	1,	0,	1},
	{1000,	2,	0,	1},
	{1100,	1,	0,	1}
};

#define ACTOR_STAND_MIN_HIGH 50

#define GRAVITY_G 4000
#define GLIDE_G 100


#define ACTOR_BASE_MAX_LEFT_POSX 250
#define ACTORNPC_BASE_MAX_LEFT_POSX 350

enum{
	ACTOR_ARMTURE_SCALE,
	ACTOR_ARMTURE_CONTENSIZE_SCALEX,
	ACTOR_ARMTURE_CONTENSIZE_SCALEY,
	ACTOR_ARMTURE_ARMATURE_SCALE,
	ACTOR_ARMTURE_MAX
};
const float actor_armture_data[ACTOR_MAX][ACTOR_ARMTURE_MAX] = {
	{0.4f, 0.8f, 1.0f, 1.2f}, 
	{0.4f, 0.8f, 1.0f, 1.1f}, 
	{0.4f, 0.8f, 1.0f, 1.2f}
};

#define FIGHT_LOGO	5


enum{
	ACTOR_BASE_EXTRA_GOLD,
	ACTOR_ADD_EXTRA_GOLD,
	ACTOR_BASE_EXTRA_MARK,
	ACTOR_ADD_EXTRA_MARK,
	ACTOR_BUY_PRICE,
	ACTOR_BASE_LEVEL_UP_GOLD,
	ACTOR_ADD_LEVEL_UP_GOLD,
	ACTOR_MAX_LEVEL,
	ACTOR_INFO_MAX,
};

const float actor_info[ACTOR_MAX][ACTOR_INFO_MAX] = {
	{20, 2, 10, 2, 0, 1000, 1000, 30}, 
	{50, 2, 50, 2, 8, 1200, 1200, 30},
	{200, 1, 200, 1, 10, 1000, 1000, 50}
};

enum{
	PET_BASE_EXTRA_GOLD,
	PET_ADD_EXTRA_GOLD,
	PET_BASE_EXTRA_MARK,
	PET_ADD_EXTRA_MARK,
	PET_BUY_PRICE,
	PET_BASE_LEVEL_UP_GOLD,
	PET_ADD_LEVEL_UP_GOLD,
	PET_MAX_LEVEL,
	PET_INFO_MAX,
};

const float pet_info[PET_MAX][PET_INFO_MAX] = {
	{10, 2, 10, 2, 20000, 900, 900, 30},
	{20, 2, 30, 2, 40000, 1000, 1000, 30},
	{40, 1, 60, 1, 60000, 600, 600, 60}
};

const float actor_defense_offx[ACTOR_MAX] = {0.25f, 0.0f, 0.0f};

//=========================================
static void Cocos_order(int id)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    //getStaticMethodInfo
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");
    
    if (!isHave) {
        CCLog("jni:Method not found");
    }else{
        CCLog("jni:Method found");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,id);
    }
    CCLog("jni-java");
#endif
}


#endif /* defined(__NTCONSTANTS__) */
