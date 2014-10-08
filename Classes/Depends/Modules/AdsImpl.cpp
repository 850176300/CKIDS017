#include "AdsImpl.h"
#include "STAds.h"
void AdsImpl::onBannerLoadSuccessfully()
{
}

void AdsImpl::onBannerLoadFailed( int errorCode )
{
}

void AdsImpl::onBannerClicked()
{
}

void AdsImpl::onBannerDismissed()
{
}

void AdsImpl::onInterstitialAdLoaded()
{
}

void AdsImpl::onInterstitialAdFailed( int errorCode )
{
}

void AdsImpl::onInterstitialShown()
{

		STAds::interstitialShown=true;
	
}

void AdsImpl::onInterstitialDismissed()
{
	STAds::interstitialShown=false;
}

AdsImpl* AdsImpl::getInstance()
{
	if (!instance)
	{
		instance = new AdsImpl();
	}
	return instance;
}

AdsImpl::AdsImpl()
{

}

AdsImpl* AdsImpl::instance = NULL;

