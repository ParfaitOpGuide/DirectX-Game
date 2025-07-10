#pragma once
class CameraNumHolder
{
	 
public:
		static CameraNumHolder* getInstance()
		{
			static CameraNumHolder sharedInstance;
			return &sharedInstance;
		}
		int view1CameraNum = 0;
		int view2CameraNum = 2;
		int view3CameraNum = 5;

private:
	CameraNumHolder() = default;
	~CameraNumHolder() = default;
	CameraNumHolder(CameraNumHolder const&) {};
	CameraNumHolder& operator=(CameraNumHolder const&) {};
};

