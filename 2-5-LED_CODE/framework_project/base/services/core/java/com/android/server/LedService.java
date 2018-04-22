/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.server;

import android.util.Log;
import android.util.Slog;

import android.os.ILedService;


public class LedService extends ILedService.Stub {

	 static final String TAG = "LedService";

   	public int LedCtrl(int which, int status) throws android.os.RemoteException 
	{
	       Slog.e(TAG, "LedCtr which="+which+" status="+ status);
		return native_LedCtrl(which, status);
   	}
	public LedService() {
		native_LedOpen();
	}

 	public native static int native_LedCtrl(int which, int status);
	public native static int native_LedOpen();
	public native static void native_LedClose();

}
