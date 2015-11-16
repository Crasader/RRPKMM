package com.lt.parkour2014_1078;



import com.ibirdgame.archirun.NetUtility;

import android.app.Application;
import android.util.Log;

/**
 * Created by afwang on 13-9-17.
 */
public class CmgameApplication extends Application {
	 private int phoneflag;
  public void onCreate() {
	  phoneflag = NetUtility.getOperatorType(this);
	  
	  if(phoneflag == 2)
	  {
		  
		  com.unicom.dcLoader.Utils.getInstances().initSDK(this, new com.unicom.dcLoader.Utils.UnipayPayResultListener() {
  			
  			@Override
  			public void PayResult(String arg0, int arg1, int arg2, String arg3) {
  				Log.e("init","init is back");
  			}
  		});
	  }

  }
}
