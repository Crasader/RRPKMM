package com.ibirdgame.archirun;



import java.util.HashMap;
import java.util.Map;

import mm.purchasesdk.Purchase;
import mm.purchasesdk.PurchaseSkin;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.paysdk.EgamePayListener;
import cn.play.dserv.CheckTool;
import cn.play.dserv.ExitCallBack;

import com.ibirdgame.archirun.IAPListener;
import com.ibirdgame.archirun.IAPHandler;

import com.lt.parkour2014_1078.RRPKCL;
import com.umeng.analytics.game.UMGameAgent;


import com.unicom.dcLoader.Utils;
import com.unicom.dcLoader.Utils.UnipayPayResultListener;


//import cn.cmgame.billing.api.BillingResult;
//import cn.cmgame.billing.api.GameInterface;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class PayWrapper {
	static Activity mContext;
	static int type;
	public static native void purchaseSucceed(String item);
	public static native void purchaseFailed(String item);
	public static native void purchaseConcel(String item);
	public static native void buyHeart(int i);
	public static native void buyHero(int i);
	public static native void buyPet(int i);
	public static native void buyGame(int i);
	public static native void buyGift(int i);
	public static native void BuyItemSucceed(int i);
	public static PurchaseItem mPurchaseItem;
	public static PayWrapper instance;
	private static SharedPreferences mSharedPreferences;
	static boolean isBlankCopy=false;
	private static boolean isWoStore=false;
	private static boolean isChinaTeleCom=false;
	
	public static Purchase purchase;
	private static IAPListener mListener;
	private ProgressDialog mProgressDialog;
	
	private static final String APPID = "300009107776";
	private static final String APPKEY = "A7B21BC4BE937AB6D65DE081AB4B8DC1";
	
	 public static void initContext(Activity context)
	{
		
		mContext=context;
		if (RRPKCL.phoneflag == 3) {
			
		}
	}
	
	
	static void showToastJerry()
	{
		Log.i("","Jerry--showToast--1");	
		Toast.makeText(mContext, "本次支付不支持电信用户", 1000).show();
	}
	public static SharedPreferences getPreferences(){
		if(mSharedPreferences == null){
			mSharedPreferences=mContext.getSharedPreferences("arichirun",mContext.MODE_WORLD_READABLE);
		}
		
		return mSharedPreferences;
	}
	public static PayWrapper getInstance()
	{
		if(instance==null){
			instance=new PayWrapper();
		}
		return instance;
	}
	static void Cocos_initPay()
	{
		Log.i("","Jerry--initPay");	
		Message msg = new Message();
		msg.what = 1000;
		handler.sendMessage(msg);
	}
	static void ShowToast()
	{
		Log.i("","Jerry--showToast--0");	
		Message msg = new Message();
		msg.what = 0;
		msg.obj = "Jerry--Toast";
		
		handler.sendMessage(msg);
	//
	}
	static void ShowLog(boolean b)
	{
	Log.i("","Jerry--"+String.valueOf(b));
	}
	static void Cocos_order(int orderidx)
	{
		Log.i("","Jerry--order--"+String.valueOf(orderidx));	
		Message msg = new Message();
		msg.what = 1001;
		msg.arg1 = orderidx;		
		handler.sendMessage(msg);
	}
	static void Cocos_more()
	{
		Log.i("","Jerry--More");	
		Message msg = new Message();
		msg.what = 1002;
		handler.sendMessage(msg);
	}
	static void Cocos_exit()
	{
		Log.i("","Jerry--Exit");	
		Message msg = new Message();
		msg.what = 1003;
		handler.sendMessage(msg);
	}
	static void more()
	{
		//GameInterface.viewMoreGames(mContext);	
		
		mContext.runOnUiThread(new Runnable() {		
			@Override
			public void run() {
				 Uri uri = Uri.parse("http://www.play.cn/");  
				  Intent it = new Intent(Intent.ACTION_VIEW, uri);  
				  mContext.startActivity(it);
			}
		});
	}
	static void exit()
	{
		System.exit(0);
//		GameInterface.exit(mContext, new GameInterface.GameExitCallback() {
//		      @Override
//		      public void onConfirmExit() {
//		        System.exit(0);
//		      }
//
//		      @Override
//		      public void onCancelExit() {
//		       // Toast.makeText(MainActivity.this, "取消退出", Toast.LENGTH_SHORT).show();
//		      }
//		    });
		
//		mContext.runOnUiThread(new Runnable() {		
//			@Override
//			public void run() {
//				CheckTool.exit(mContext, new ExitCallBack() { 
//
//					@Override
//					public void exit() {
//						//退出游戏操作
//						mContext.finish();
//			            System.exit(0);
//					}
//
//					@Override
//					public void cancel() {
//						//取消退出，返回游戏
//						
//					}
//				});	
//			}
//		});
		
	}
	 static void initPay()
	 {
		 if(isBlankCopy)	{
				return;
			}
		// 初始化SDK
		   // GameInterface.initializeApp((Activity) mContext);
		    
//		   if( GameInterface.isMusicEnabled())
//		   {
//			   BuyItemSucceed(11);
//		   }else
//		   {
//			   BuyItemSucceed(12);
//		   }
		    
		 if (RRPKCL.phoneflag == 1) {
		 IAPHandler iapHandler = new IAPHandler(mContext);

	        /**
			* step1.实例化PurchaseListener。实例化传入的参数与您实现PurchaseListener接口的对象有关。
			 	  * 例如，此Demo代码中使用IAPListener继承PurchaseListener，其构造函数需要Context实例。
			*/
			mListener = new IAPListener(mContext, iapHandler);
			
			/**
			 * step2.实例化Purchase对象。在实例化Purhcase对象后，必须为purchase实例setAppInfo 
			 *接口。该接口函数需要传入APPID，APPKEY。
			 */
			purchase = Purchase.getInstance();
			try {
				purchase.setAppInfo(APPID, APPKEY,PurchaseSkin.SKIN_SYSTEM_ONE);

			} catch (Exception e1) {
				e1.printStackTrace();
			}
			/**
			 * step3.IAP组件初始化开始，
			 * 参数PurchaseListener，初始化函数需传入step1时实例化的onPurchaseListener。
			 */
			try {
				purchase.init(mContext, mListener);

			} catch (Exception e) {
				e.printStackTrace();
				return;
			}
			
		 }
		 else if(RRPKCL.phoneflag == 3)
		 {
			 
			 EgamePay.init(mContext);
		 }
	      
	 }
	 
	 private static class paylistener implements UnipayPayResultListener {
			@Override
			public void PayResult(String paycode, int flag, int flag2, String error) {
				switch (flag) {
				case 1:// success
					Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
						@Override
						public void run() {
							UMGameAgent.pay(2,"diamond20",1,0,6);
							
							int orderidx=mPurchaseItem.type;
					    	
				  			UMGameAgent.pay(mPurchaseItem.trueprize,mPurchaseItem.desc,0,0,6);
				  			if(orderidx==11)
				  				 PayWrapper.buyGame(11);
				  			 else if(orderidx==13)
				  				PayWrapper.buyGame(1);
				  			 else
				  				PayWrapper.BuyItemSucceed(orderidx);
						}
					});
					break;
				case 2:// fail

					int orderidx1=mPurchaseItem.type;
					Log.i("","Jerry--Failed--orderidx "+String.valueOf(orderidx1));
					if(orderidx1==13)
					 {
						PayWrapper.buyGame(13);
					 }
					else if(orderidx1==11)
						PayWrapper.buyGame(0);
					break;
				case 3:// cancel
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
					
					break;
				default:
					break;
				}
			}

		}
	
	 static void order(int orderidx)
	 {
//		    final GameInterface.IPayCallback payCallback = new GameInterface.IPayCallback() {
//		        @Override
//		        public void onResult(int resultCode, String billingIndex, Object obj) {
//		          String result = "";
//		          switch (resultCode) {
//		            case BillingResult.SUCCESS:
//		              result = "购买道具：[" + billingIndex + "] 成功！";
//		              int orderidx=mPurchaseItem.type;
//		  			UMGameAgent.pay(mPurchaseItem.trueprize,mPurchaseItem.desc,0,0,7);
//		  			if(orderidx==11)
//		  				 buyGame(11);
//		  			 else if(orderidx==13)
//		  				 buyGame(1);
//		  			 else
//		  			 BuyItemSucceed(orderidx);
//		              break;
//		            case BillingResult.FAILED:
//		              result = "购买道具：[" + billingIndex + "] 失败！";
//		          	int orderidx1=mPurchaseItem.type;
//					Log.i("","Jerry--Failed--orderidx "+String.valueOf(orderidx1));
//					if(orderidx1==13)
//					 {
//						 buyGame(13);
//					 }
//					else if(orderidx1==11)
//						 buyGame(0);
//		              break;
//		            default:
//		              result = "购买道具：[" + billingIndex + "] 取消！";
//		          	int orderidx11=mPurchaseItem.type;
//					Log.i("","Jerry--Failed--orderidx "+String.valueOf(orderidx11));
//					if(orderidx11==13)
//					 {
//						 buyGame(13);
//					 }
//					else if(orderidx11==11)
//						 buyGame(0);
//		              break;
//		          }
//		          Toast.makeText(mContext, result, Toast.LENGTH_SHORT).show();
//		        }
//		      };
		 
		 
		 
		 if(isBlankCopy)	
			{
			 if(orderidx==11)
				 buyGame(11);
			 else if(orderidx==13)
				 buyGame(1);
			 else
			 BuyItemSucceed(orderidx);
			 return;

			}
		 mPurchaseItem= PurchaseItem.getPurchaseItemByType(orderidx);
		 
		 switch (RRPKCL.phoneflag) {
		 case 1:
			 purchase.order(mContext, mPurchaseItem.idContentMM, mListener);
			 break;
		 case 2:
			 Utils.getInstances().pay(mContext, mPurchaseItem.idContentWS, new paylistener());
			 break;
		 case 3:
			HashMap<String, String> payParams=new HashMap<String, String>();
			payParams.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, mPurchaseItem.idContentEG);
			Pay(payParams);
			break;
			default:
				break;
		 }
	 }	
	 
	 
	 
	 
	 private static void Pay(HashMap<String, String> payParams) {
		 EgamePay.pay(mContext, payParams,new EgamePayListener() {
				@Override
				public void paySuccess(Map<String, String> params) {
					Log.e("instance", "jobj create Already");  
					UMGameAgent.pay(2,"diamond20",1,0,7);
					
					int orderidx=mPurchaseItem.type;
			    	
		  			UMGameAgent.pay(mPurchaseItem.trueprize,mPurchaseItem.desc,0,0,7);
		  			if(orderidx==11)
		  				 PayWrapper.buyGame(11);
		  			 else if(orderidx==13)
		  				PayWrapper.buyGame(1);
		  			 else
		  				PayWrapper.BuyItemSucceed(orderidx);
				}
				
				@Override
				public void payFailed(Map<String, String> params, int errorInt) {
					int orderidx1=mPurchaseItem.type;
					Log.i("","Jerry--Failed--orderidx "+String.valueOf(orderidx1));
					if(orderidx1==13)
					 {
						PayWrapper.buyGame(13);
					 }
					else if(orderidx1==11)
						PayWrapper.buyGame(0);
			      
				}
				
				@Override
				public void payCancel(Map<String, String> params) {
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
	 }
		
	 static Handler handler = new Handler(){
			
			public void handleMessage(Message msg){
				switch(msg.what){
				case 1000:
				  initPay();
				  	break;
				case 1001:
					order(msg.arg1);
					break;
				case 0:
					showToastJerry();
					break;
				case 1002:
					more();
					break;
				case 1003:
					exit();
					break;
				}
			}
		};
	}
