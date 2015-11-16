package com.ibirdgame.archirun;
import android.content.Context;
import android.telephony.TelephonyManager;
import android.util.Log;

public class NetUtility {
	private static String TAG = "NetUtility";
	public static int CHINAMOBILE = 1;
	public static int CHINAUNICOM = 2;
	public static int CHINATELECOM = 3;
	public static int UNKNOWN = 0;
	
	
	public static int getOperatorType(Context mContext) {

        TelephonyManager telManager = (TelephonyManager) mContext.getSystemService(Context.TELEPHONY_SERVICE);  
        String imsi = telManager.getSubscriberId(); 

	
        if(imsi!=null){ 
            if(imsi.startsWith("46000") || imsi.startsWith("46002") || imsi.startsWith("46007")){
            	Log.e(TAG, "mobile");
            	return CHINAMOBILE;
            }else if(imsi.startsWith("46001")){ 
            	Log.e(TAG, "unicom");
            	return CHINAUNICOM;
            }else if(imsi.startsWith("46003")){ 
            	Log.e(TAG, "telecom");
            	return CHINATELECOM;
            } 
        }  
        return UNKNOWN;
	}
}
