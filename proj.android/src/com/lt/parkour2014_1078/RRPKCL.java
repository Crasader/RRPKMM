/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.lt.parkour2014_1078;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.sdk.log.EgameAgent;

import com.ibirdgame.archirun.NetUtility;
import com.ibirdgame.archirun.PayWrapper;
import com.umeng.analytics.game.UMGameAgent;
//import com.unicom.dcLoader.Utils;





import com.unicom.dcLoader.Utils;

import android.os.Bundle;

public class RRPKCL extends Cocos2dxActivity{
	
	public static int phoneflag;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		phoneflag = NetUtility.getOperatorType(this);
		
		PayWrapper.initContext(this);
		 UMGameAgent.init( this );
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// RRPKCM should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    protected void onPause()
    {
      super.onPause();
//      Utils.getInstances().onPause(this);
      if(phoneflag == 2)
		{
			Utils.getInstances().onPause(this);
		}
		else if (phoneflag == 3) {
			EgameAgent.onPause(this);
		}

      UMGameAgent.onPause(this);
    }

    protected void onResume()
    {
      super.onResume();
//      Utils.getInstances().onResume(this);
      if(phoneflag == 2)
		{
			Utils.getInstances().onResume(this);
		}
		else if(phoneflag == 3)
		{
			EgameAgent.onResume(this);
		}
      UMGameAgent.onResume(this);
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
