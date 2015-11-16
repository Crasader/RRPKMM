package com.ibirdgame.archirun;


public enum PurchaseItem {
	//Origin
//	item0(0,"heart0", "5个爱心","30000824917511","140415032393","F7105C5125142E90E0430100007F2B79","5004258","001", "2.00",2),
//	item1(1,"heart1", "20个爱心","30000824917523","140415032394","F7105C5125152E90E0430100007F2B79","5004259","002", "4.00",4),
//	item2(2, "heart2", "40个爱心","30000824917513","140415032395","F7105C5125162E90E0430100007F2B79", "5004260","003", "6.00",6),
//	item3(3,"heart3",  "无限爱心","30000824917514","140415032396", "F7105C5125172E90E0430100007F2B79","5004261","004", "8.00",8),
//	item4(4, "hero1", "叛逆小萝莉","30000824917517","140415032400","F7105C51251A2E90E0430100007F2B79", "5004265","005", "8.00",8),
//	item5(5,"hero2",  "暴走女汉子","30000824917518","140415032401","F7105C51251B2E90E0430100007F2B79", "5004266","006", "10.00",10),
//	item6(6,"pet0",  "杰尼小精灵","30000876029307","150112081845", "","5109203", "007","2.00",2),
//	item7(7, "pet1", "皮卡小精灵","30000876029308","150112081846","", "5109204", "008","4.00",4),
//	item8(8,"pet2",  "妙娃小精灵","30000876029309","150112081847", "","5109205", "009","6.00",6),
//	item9(9,"goldGift",  "999999金币","30000824917527","140415032392","F7105C51251D2E90E0430100007F2B79", "5004257", "5004257","20.00",20),
//	item10(10, "gift", "豪华大礼包","30000824917528","140415032399","F7105C51251C2E90E0430100007F2B79", "5004264","010", "1.00",1),
//	item11(11, "accelerate", "开始加速1000米","30000824917524","140415032397", "F7105C5125192E90E0430100007F2B79","5004262","011", "1.00",2),
//	//item12(12,"accelerate",  "复活","30000842531104","150112081850","", "01C1993B9C2F6424E0530100007F0FD2", "4.00",4),
//	item13(13, "resurrect", "死亡复活","30000824917515","140415032398","F7105C5125182E90E0430100007F2B79", "5004263", "012","2.00",2);
	
	item0(0,"heart0", "5个爱心","30000910777601","140415032393","F7105C5125142E90E0430100007F2B79","5004258","002", "2.00",2),
	item1(1,"heart1", "20个爱心","30000910777602","140415032394","F7105C5125152E90E0430100007F2B79","5004259","003", "4.00",4),
	item2(2, "heart2", "40个爱心","30000910777603","140415032395","F7105C5125162E90E0430100007F2B79", "5004260","004", "6.00",6),
	item3(3,"heart3",  "无限爱心","30000910777604","140415032396", "F7105C5125172E90E0430100007F2B79","5004261","005", "8.00",8),
	item4(4, "hero1", "叛逆小萝莉","30000910777605","140415032400","F7105C51251A2E90E0430100007F2B79", "5004265","009", "8.00",6),
	item5(5,"hero2",  "暴走女汉子","30000910777606","140415032401","F7105C51251B2E90E0430100007F2B79", "5004266","010", "10.00",8),
	item6(6,"pet0",  "杰尼小精灵","000","150112081845", "","5109203", "000","2.00",2),
	item7(7, "pet1", "皮卡小精灵","000","150112081846","", "5109204", "000","4.00",4),
	item8(8,"pet2",  "妙娃小精灵","000","150112081847", "","5109205", "000","6.00",6),
	item9(9,"goldGift",  "金币大礼包","30000910777607","140415032392","F7105C51251D2E90E0430100007F2B79", "5004257", "001","20.00",20),
	item10(10, "gift", "豪华大礼包","30000910777608","140415032399","F7105C51251C2E90E0430100007F2B79", "5004264","008", "1.00",1),
	item11(11, "accelerate", "开始加速1000米","30000910777609","140415032397", "F7105C5125192E90E0430100007F2B79","5004262","006", "2.00",2),
	//item12(12,"accelerate",  "复活","30000842531104","150112081850","", "01C1993B9C2F6424E0530100007F0FD2", "4.00",4),
	item13(13, "resurrect", "死亡复活","30000910777610","140415032398","F7105C5125182E90E0430100007F2B79", "5004263", "007","2.00",2);
	public String title;
	
	public String idContentMM;

	public String idContentWO;

	public String idContentTE;
	public String idContentEG;
	public String idContentWS;//WoStore
	public String prize;
	public int type;
	public String desc;
	public double trueprize;

	PurchaseItem(int type,String desc, String title, String idContentMM, String idContentWO,String idContentTE, String idContentEG,String idContentWS,String prize,double trueprize) {
		this.type = type;
		this.desc=desc;
		this.title = title;
		this.idContentMM = idContentMM;
		this.prize = prize;
		this.idContentWO = idContentWO;
		this.idContentTE = idContentTE;
		this.idContentEG=idContentEG;
		this.idContentWS=idContentWS;
		this.trueprize=trueprize;
	} 
	

//	PurchaseItem(int type, String title, String idContentMM, String idContentWO,String idContentTE, String prize) {
//		this.type = type;
//		this.title = title;
//		this.idContentMM = idContentMM;
//		this.prize = prize;
//		this.idContentWO = idContentWO;
//		this.idContentTE = idContentTE;
//	} 
	
	public static PurchaseItem getPurchaseItemByType(int type){
			for (PurchaseItem item : PurchaseItem.values()) {
				if (type==item.type) {
					return item;
				}
			}	
		return null;
	}
}
