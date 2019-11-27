#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"
#include "pugixml.hpp"
#include <Game.h>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::initInstance() {
	
	bool bRet = false;
	do {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		pugi::xml_document doc;
		std::cout << doc.load_file("Resources\\config.xml");
		
		int width = atoi(doc.child("window").attribute("width").value());
		int height = atoi(doc.child("window").attribute("height").value());
	    std::cout << "WIDTH   " << width;
		std::string s =	doc.child("window").attribute("title").value();		
		std::locale loc;		
		std::wstring out;
		std::string::const_iterator i( s.begin() ), ie( s.end() );
		for( ; i!=ie; ++i )
		{
			out += std::use_facet<std::ctype<wchar_t> > ( loc ).widen( *i );
		}
		LPCTSTR title = out.c_str();
		
		CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(title,width,height));
	
		
		doc.~xml_document();

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		// OpenGLView initialized in HelloWorld/android/jni/helloworld/main.cpp
		// the default setting is to create a fullscreen view
		// if you want to use auto-scale, please enable view->create(320,480) in main.cpp
		// if the resources under '/sdcard" or other writeable path, set it.
		// warning: the audio source should in assets/
		// cocos2d::CCFileUtils::setResourcePath("/sdcard");
        CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationPortrait);

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd
                || ! pMainWnd->Create("cocos2d: Hello World",1024, 768 ,1024, 768));

		CCFileUtils::setResourcePath("../Resources/");

#endif  // CC_PLATFORM_LINUX

		bRet = true;
	} while (0);
	return bRet;
}

bool AppDelegate::applicationDidFinishLaunching() {

	CCDirector *pDirector = CCDirector::sharedDirector();

	pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	// For nonblured textures
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	USING_NS_CC;
	// Create game class instance
    Game game;
	// Create MainMenu scene
    CCScene *pScene = game.init();
	// Push MainMenu scene in Director
	pDirector->runWithScene(pScene);



	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
