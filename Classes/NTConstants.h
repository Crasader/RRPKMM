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

//==========================================触摸优先级的设定
enum{
	PRIORITY_MESSAGE_BOX = kCCMenuHandlerPriority-20,		//对话框
	PRIORITY_NTLAYER_GUIDE,									//引导层
	PRIORITY_NTLAYER_MSG,									//弹出层
	PRIORITY_NTLAYER_UI,									//UI层
	PRIORITY_NTLAYER_LEVEL_4,								//四级层
	PRIORITY_NTLAYER_LEVEL_3,								//三级层
	PRIORITY_NTLAYER_LEVEL_2,								//二级层
	PRIORITY_NTLAYER_LEVEL_1								//一级层
};
//===================================================================


//===========================================地图碰撞元素(中立元素，有益元素，有害元素)
enum{
	BOX_GOLDAREA_PROP1 = -6,	//金库元素1
	BOX_GOLDAREA_PROP2,			//金库元素2
	BOX_GOLDAREA_PROP3,			//金库元素3
	BOX_GOLDAREA_PROP4,			//金库元素4

	BOX_BALLOON1,				//气球1
	BOX_BALLOON2,				//气球2

	BOX_ROAD = 0,	//
	BOX_ROAD_1,		//路1
	BOX_ROAD_2,		//路2
	BOX_ROAD_3,		//路3
	BOX_BLOCK1,		//箱子
	BOX_BLOCK2,		//石头
	BOX_BLOCK3,		//油漆桶
	BOX_BLOCK4,		//化肥
	
	BOX_FLY_BLOCK,	//飞行障碍物

	BOX_SPRING,		//弹簧
	
	BOX_HOOK1,		//钩子
	BOX_HOOK2,		//钩子
	BOX_HOOK3,		//钩子

	BOX_COIN,		//金币
	BOX_BUFF_START,
	BOX_ENGINE,		//动力引擎
	BOX_LIQUID,		//变身药水
	BOX_MAGNET,		//磁铁
	BOX_SUPER_COIN,	//超级金币
	BOX_DEFENSE,	//防护罩
	BOX_BUFF_END,
	BOX_BOMB,			//炸弹
	BOX_BANANA_SKIN,	//香蕉皮
	BOX_MOUNT_HORSE,		//马坐骑
	BOX_MOUNT_BEAR,			//熊坐骑

	BOX_BRICK,			//砖头
	BOX_ICE_BOX,		//冰箱

	BOX_MAX
};
//============================================
const int box_count_coin[BOX_MAX]={
	0, 0, 0, 0, 1, 1, 1, 1, 20, 200, 11, 12, 13, 9, 0, 10, 10, 150, 1000, 20, 0, 100, 5, 500, 500, 100, 100};

//===========================================游戏场景
//地图元素中的Zorder
enum{
	GAME_MAP_SKY = -10,
	GAME_MAP_CLOUD,
	GAME_MAP_AUTO_BG,
	GAME_MAP_ROAD = 10,
	GAME_MAP_PROPS,
	GAME_MAP_COIN,
};
//滚动背景的图片名
const char autoBgFileName[8][20] = {
	"gd_tk.png", "gd_tk.png", "gd_zyj_0.png", 
	"gd_zyj_1.png", "gd_zj_0.png", "gd_zj_1.png",
	"jk_yj.png", "jk_yj.png"
};
//滚动背景先对道路移动速度的比值
const float autoBgSpeedScale[4] = {0.01f, 0.02f, 0.05f, 0.1f};

//道路高低类型
enum{
	ROAD_POSY_LOW = 0,
	ROAD_POSY_MED,
	ROAD_POSY_HIGH,
	ROAD_POSY_MAX
};
const int road_posy[ROAD_POSY_MAX] = {75, 120, 160};


//=========================================游戏道路数据配置
//道路阶段类型
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
//道路类型
enum{
	ROAD_NOMAL = BOX_ROAD_1,	//正常道路
	ROAD_BLANK					//空隙道路
};
//道路配置数据
enum{
	ROAD_DATA_TYPE,		//道路类型（0~1）
	ROAD_DATA_LENGTH,	//道路长度（0~15）
	ROAD_DATA_HEIGHT,	//道路高度（0~3）
	ROAD_DATA_MAX
};
#define ROAD_DATA_COUNT_EACH_LEVEL 20

//地图配置数据
//10个等级，每个等级20组，每组数据3个配置点
const int road_data[ROAD_HARD_LEVEL_MAX][ROAD_DATA_COUNT_EACH_LEVEL+1][ROAD_DATA_MAX] =
{
	//第一等级道路信息
	{
		{ROAD_NOMAL, 10, 0}, {ROAD_NOMAL, 10, 0}, {ROAD_NOMAL, 9, 0}, {ROAD_NOMAL, 9, 0}, 
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{13, 19, 0}
	},
	//第二等级道路信息
	{
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 16, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{12, 19, 0}
	},
	//第三等级道路信息
	{
		{ROAD_NOMAL, 8, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第四等级道路信息
	{
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, 
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL,4, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第五等级道路信息
	{
		{ROAD_NOMAL, 7, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第六等级道路信息
	{
		{ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 6, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, 
		{ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0}, {ROAD_BLANK, 150, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第七等级道路信息
	{
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 4, 0}, 
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第八等级道路信息
	{
		{ROAD_NOMAL, 5, 0}, {ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 3, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0},
		//最后一组标记普通道路和空隙的分界点
		{11, 19, 0}
	},
	//第九等级道路信息
	{
		{ROAD_NOMAL, 4, 0}, {ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, 
		{ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0}, {ROAD_BLANK, 200, 0},
		//最后一组标记普通道路和空隙的分界点
		{9, 19, 0}
	},
	//第十等级道路信息
	{
		{ROAD_NOMAL, 3, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 2, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, {ROAD_NOMAL, 1, 0}, 
		{ROAD_BLANK, 300, 0}, {ROAD_BLANK, 300, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, 
		{ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0}, {ROAD_BLANK, 250, 0},
		//最后一组标记普通道路和空隙的分界点
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
