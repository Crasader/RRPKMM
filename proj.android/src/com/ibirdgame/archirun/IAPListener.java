package com.ibirdgame.archirun;

import java.util.HashMap;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.lt.parkour2014_1078.RRPKCL;
import com.umeng.analytics.game.UMGameAgent;

import mm.purchasesdk.OnPurchaseListener;
import mm.purchasesdk.Purchase;
import mm.purchasesdk.PurchaseCode;
import android.content.Context;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class IAPListener implements OnPurchaseListener {
	private final String TAG = "IAPListener";
	private RRPKCL context;
	private IAPHandler iapHandler;
	public static PurchaseItem mPurchaseItem;
	
	public IAPListener(Context context, IAPHandler iapHandler) {
		this.context = (RRPKCL) context;
		this.iapHandler = iapHandler;
	}

	@Override
	public void onAfterApply() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onAfterDownload() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onBeforeApply() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onBeforeDownload() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onInitFinish(int code) {
		Log.d(TAG, "Init finish, status code = " + code);
		Message message = iapHandler.obtainMessage(IAPHandler.INIT_FINISH);
		String result = "鍒濆鍖栫粨鏋滐�?" + Purchase.getReason(code);
		message.obj = result;
		message.sendToTarget();
	}

	@Override
	public void onBillingFinish(int code, HashMap arg1) {
		Log.d(TAG, "billing finish, status code = " + code);
		String result = "璁㈣喘缁撴灉锛氳璐垚鍔�";
		Message message = iapHandler.obtainMessage(IAPHandler.BILL_FINISH);
		// 姝ゆ璁㈣喘鐨刼rderID
		String orderID = null;
		// 鍟嗗搧鐨刾aycode
		String paycode = null;
		// 鍟嗗搧鐨勬湁鏁堟�?(浠呯璧佺被鍨嬪晢鍝佹湁鏁�)
		String leftday = null;
		// 鍟嗗搧鐨勪氦鏄� ID锛岀敤鎴峰彲浠ユ牴鎹繖涓氦鏄揑D锛屾煡璇㈠晢鍝佹槸鍚�?凡缁忎氦鏄�
		String tradeID = null;
		mPurchaseItem= PayWrapper.mPurchaseItem;
		String ordertype = null;
		if (code == PurchaseCode.ORDER_OK || (code == PurchaseCode.AUTH_OK) ||(code == PurchaseCode.WEAK_ORDER_OK)) {
			/**
			 * 鍟嗗搧璐拱鎴愬姛鎴栬�呭凡缁忚喘涔般��? 姝ゆ椂浼氳繑鍥炲晢鍝佺殑paycode锛宱rderID,浠ュ強鍓�?綑鏃堕棿(绉熻祦绫诲�?�鍟嗗搧)
			 */
//			Toast.makeText(context, "ID " + JniTestHelper.itemID, Toast.LENGTH_LONG).show();
			Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			    @Override
			      public void run() {
			    	int orderidx=mPurchaseItem.type;
			    	
		  			UMGameAgent.pay(mPurchaseItem.trueprize,mPurchaseItem.desc,0,0,7);
		  			if(orderidx==11)
		  				 PayWrapper.buyGame(11);
		  			 else if(orderidx==13)
		  				PayWrapper.buyGame(1);
		  			 else
		  				PayWrapper.BuyItemSucceed(orderidx);
		  			
			      }
			    });

		} else {
			Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			    @Override
			      public void run() {
			    	int orderidx1=mPurchaseItem.type;
					Log.i("","Jerry--Failed--orderidx "+String.valueOf(orderidx1));
					if(orderidx1==13)
					 {
						PayWrapper.buyGame(13);
					 }
					else if(orderidx1==11)
						PayWrapper.buyGame(0);
			      }
			    });
			result = "璁㈣喘缁撴灉锛�" + Purchase.getReason(code);
		}
		System.out.println(result);

	}

	@Override
	public void onQueryFinish(int code, HashMap arg1) {
		Log.d(TAG, "license finish, status code = " + code);
		Message message = iapHandler.obtainMessage(IAPHandler.QUERY_FINISH);
		String result = "鏌ヨ鎴愬姛,璇ュ晢鍝佸凡璐�?";
		// 姝ゆ璁㈣喘鐨刼rderID
		String orderID = null;
		// 鍟嗗搧鐨刾aycode
		String paycode = null;
		// 鍟嗗搧鐨勬湁鏁堟�?(浠呯璧佺被鍨嬪晢鍝佹湁鏁�)
		String leftday = null;
		if (code != PurchaseCode.QUERY_OK) {
			/**
			 * 鏌ヨ涓嶅埌鍟嗗搧璐拱鐨勭浉鍏充俊鎭�
			 */
			result = "鏌ヨ缁撴灉锛�" + Purchase.getReason(code);
		} else {
			/**
			 * 鏌ヨ鍒板晢鍝佺殑鐩稿叧淇℃伅銆�?
			 * 姝ゆ椂浣犲彲浠ヨ幏寰�?晢鍝佺殑paycode锛宱rderid锛屼互鍙婂晢鍝佺殑鏈夋晥鏈焞eftday锛堜粎绉熻祦绫诲瀷鍟嗗搧鍙互杩斿洖锛�
			 */
			leftday = (String) arg1.get(OnPurchaseListener.LEFTDAY);
			if (leftday != null && leftday.trim().length() != 0) {
				result = result + ",鍓╀綑鏃堕棿 锛� " + leftday;
			}
			orderID = (String) arg1.get(OnPurchaseListener.ORDERID);
			if (orderID != null && orderID.trim().length() != 0) {
				result = result + ",OrderID 锛� " + orderID;
			}
			paycode = (String) arg1.get(OnPurchaseListener.PAYCODE);
			if (paycode != null && paycode.trim().length() != 0) {
				result = result + ",Paycode:" + paycode;
			}
		}
		System.out.println(result);
	}

	

	@Override
	public void onUnsubscribeFinish(int code) {
		// TODO Auto-generated method stub
		String result = "閫�璁㈢粨鏋滐細" + Purchase.getReason(code);
		System.out.println(result);
	}
}
