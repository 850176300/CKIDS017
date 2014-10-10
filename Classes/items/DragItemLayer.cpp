//
//  DragItemLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-28.
//
//

#include "DragItemLayer.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
#include "Collsion.h"
USING_NS_ST;
#define SPACE 15//间隔定义

DragItemLayer* DragItemLayer::createWithArray(Direction direc,cocos2d::CCArray *arr) {
    DragItemLayer* pRet = new DragItemLayer();
    
    if (pRet && pRet->initWithArray(direc,arr)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

DragItemLayer* DragItemLayer::create(Direction direc,ItemBase *item, ...) {
    va_list args;
    va_start(args,item);
    
    DragItemLayer* pRet = DragItemLayer::createWithItems(direc,item, args);
    
    va_end(args);
    
    return pRet;
}

DragItemLayer* DragItemLayer::createWithItems(Direction direc,ItemBase *firstItem, va_list args) {
    CCArray* pArray = NULL;
    if( firstItem )
    {
        pArray = CCArray::create(firstItem, NULL);
        ItemBase *i = va_arg(args, ItemBase*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, ItemBase*);
        }
    }
    return DragItemLayer::createWithArray(direc,pArray);
}

bool DragItemLayer::initWithArray(Direction direc,cocos2d::CCArray *arr) {
    CCAssert(arr != NULL, "初始化DragItemLayer对象时，传入的arr必须不能为空！");
    if (CCLayer::init()) {
        itemArray = arr;
        itemArray->retain();
        performDistance = CCPointZero;
        canMove = false;
        isbDraging = false;
        _container = CCLayer::create();
        _frame = ClipLayer::create();
        _contentOffset = ccp(0, 0);
        _scrollSize = CCSizeMake(0, 0);
    
        _direction = direc;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(arr, pObj){
            ItemBase* item = dynamic_cast<ItemBase*>(pObj);
            switch (direc) {
                case kDragLayerHorizontal:
                {
                    item->setAnchorPoint(ccp(0.5, 0));
                    CCSize itemSize = item->getContentSize();
                    item->setPosition(ccp(itemSize.width / 2.0 + _scrollSize.width, 0));
                    
                    _scrollSize.width += itemSize.width + SPACE;
                    _container->addChild(item, 1);
                }
                    break;
                case kDragLayerVertical:
                {
                    item->setAnchorPoint(ccp(0, 0.5));
                    CCSize itemSize = item->getContentSize();
                    item->setPosition(ccp(0,itemSize.height / 2.0 + _scrollSize.height));
                    _scrollSize.height += itemSize.height + SPACE;
                    _container->addChild(item, 1);
                }
                    break;
                default:
                    break;
            }
        };
        _container->setContentSize(_scrollSize);
        _container->ignoreAnchorPointForPosition(true);
        return true;
    }
    return false;
}

void DragItemLayer::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void DragItemLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void DragItemLayer::setFrame(const char *framePath,float widthSpace/* = 10*/, float heightSpace/* = 10*/,CCPoint pos/* = ccp(0, 0)*/) {//默认的pos == （0，0）
    bool selfDefinePos = true;
    if (pos.x == 0 && pos.y==0){
        selfDefinePos = false;
    }
//    CCSprite* bg1 = CCSprite::create(framePath);
////    bg1->setAnchorPoint(ccp(0, 0.5f));
//    bg1->setPosition(ccp(STVisibleRect::getOriginalPoint().x+10, STVisibleRect::getCenterOfScene().y-STVisibleRect::getOriginalPoint().y));
//    addChild(bg1, 10);
    CCPoint anchorPP;
    CCSprite* bg = CCSprite::create(framePath);
    _frame->ignoreAnchorPointForPosition(false);
    switch (_direction) {
        case kDragLayerHorizontal:
        {
            anchorPP = ccp(0.5f, 0);
            bg->setAnchorPoint(anchorPP);
            _frame->setAnchorPoint(anchorPP);
            _frame->setContentSize(CCSizeMake(bg->getContentSize().width - widthSpace*2, bg->getContentSize().height-heightSpace*2));
            if (selfDefinePos) {
                bg->setPosition(pos);
            }else {
                bg->setPosition(ccp(STVisibleRect::getGlvisibleSize().width/2.0, STVisibleRect::getOriginalPoint().y+50));
            }
            _frame->setPosition(bg->getPosition()+ccp(0, heightSpace));
            _scrollSize.height = _frame->getContentSize().height;
            _container->setContentSize(_scrollSize);
        }
            break;
        case kDragLayerVertical:
        {
            anchorPP = ccp(0, 0.5f);
            bg->ignoreAnchorPointForPosition(false);
            bg->setAnchorPoint(anchorPP);
            _frame->setAnchorPoint(anchorPP);
            _frame->setContentSize(CCSizeMake(bg->getContentSize().width - widthSpace*2, bg->getContentSize().height-heightSpace*2));
            if (selfDefinePos) {
                bg->setPosition(pos);
            }else {
                bg->setPosition(ccp(STVisibleRect::getOriginalPoint().x+10, STVisibleRect::getGlvisibleSize().height/2.0));
            }
            _frame->setPosition(bg->getPosition()+ccp(widthSpace, 0));
            _scrollSize.width = _frame->getContentSize().width;
            _container->setContentSize(_scrollSize);
            _contentOffset.y = _scrollSize.height-_frame->getContentSize().height;
            _container->setPositionY(-_contentOffset.y);
            CCLog("the off set is (%.2f, %.2f)", _contentOffset.x, _contentOffset.y);
        }
            break;
        default:
            break;
    }
    
    _frame->addChild(_container);
    addChild(bg, 1);
    addChild(_frame, 2);
}

//处理touch事件分发
void DragItemLayer::_dispatchTouch(CCTouch* pTouch)
{
    CCLOG("DoctorLayer::_dispatchTouch");
    //降低DoctorLayer的触摸优先级，让接下来的触摸分发，不再被DoctorLayer接收
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(100, this);
    m_bTouchDispatched = true;
    //将本次触摸再一次分发
    CCSet set;
    set.addObject(pTouch);
    //将本次触摸从DoctorLayer的handler中删除，DoctorLayer的作用就是先收了事件，然后根据情况分发出去，表明本次触摸接收和分发完成。
    CCTargetedTouchHandler* pHandler = (CCTargetedTouchHandler*)(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this));
    if(pHandler->getClaimedTouches()->containsObject(pTouch)){
        pHandler->getClaimedTouches()->removeObject(pTouch);
    }
    CCDirector::sharedDirector()->getTouchDispatcher()->touchesBegan(&set, NULL);
    //===分发结束===
    //恢复DoctorLayer的状态
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(kCCMenuHandlerPriority, this);
    m_pBeginTouch = NULL;
}

void DragItemLayer::_touchBeginSchedule(float dt)
{
    if(m_pBeginTouch && !m_bTouchDispatched)
    {
        _dispatchTouch(m_pBeginTouch);
        m_pBeginTouch = NULL;
    }
}


bool DragItemLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    beganPos = convertTouchToNodeSpace(pTouch);
    m_fTimeTouchBegin = CocosHelper::milliSecondNow();
    if (_frame->boundingBox().containsPoint(beganPos)) {
        _container->stopAllActions();
        canMove = true;
        isbDraging = true;
        m_fTimeTouchBegin = CocosHelper::milliSecondNow();
        m_bTouchDispatched = false;
        m_bTouchDecided = false;
        m_bTouchMoved = false;
        m_tTouchBeginPt = pTouch->getLocation();
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(DragItemLayer::_touchBeginSchedule), this, 0.2, 1, 0, false);
        m_pBeginTouch = pTouch;
    }
    if (CCRectMake(STVisibleRect::getOriginalPoint().x, _frame->boundingBox().origin.y, STVisibleRect::getGlvisibleSize().width, _frame->boundingBox().size.height).containsPoint(beganPos)) {
        return true;
    }
    return false;
}

void DragItemLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    if (canMove != true) {
        return;
    }
    m_bTouchMoved = true;
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(DragItemLayer::_touchBeginSchedule), this);
    if(m_bTouchDispatched){
        return;
    }
    float timeDelta = CocosHelper::milliSecondNow() - m_fTimeTouchBegin;
//    CCLog("the time delta is %f", timeDelta);
    if(timeDelta >= 100.0 && !m_bTouchDecided){
//        CCLog("_dispatchTouch");
        m_bTouchDecided = true;
        _dispatchTouch(pTouch);
    }else {//如果时间差比较短，则优先滚动
//        float lDeltaX = fabs(m_tTouchBeginPt.x - pTouch->getLocation().x);
//        float lDeltaY = (pTouch->getLocation().y - m_tTouchBeginPt.y);
//        CCLog("lDeltaX = %f, lDeltaY = %f", lDeltaX, lDeltaY);
//        if (lDeltaX < 10.0 && lDeltaY > 3.0 && !m_bTouchDecided) {
//            CCLog("_dispatchTouch");
//            m_bTouchDecided = true;
//            _dispatchTouch(pTouch);
//        }else if(lDeltaX < 10.0 && lDeltaY == 0.0 && !m_bTouchDecided) {
//            CCLog("_dispatchTouch");
//            m_bTouchDecided = true;
//            _dispatchTouch(pTouch);
//        }else{
//            CCLog("滚动");
//
            m_bTouchDecided = true;
            CCPoint delta = pTouch->getDelta();
            if (_direction == kDragLayerHorizontal) {
                _contentOffset.x -= delta.x;
                if (_contentOffset.x < -100 || _contentOffset.x > _scrollSize.width - _frame->getContentSize().width + 200) {
                    _contentOffset.x += delta.x;
                    return;
                }
                _container->setPosition(ccp(_container->getPositionX() + delta.x, _container->getPositionY()));
                
            }else {
                _contentOffset.y -= delta.y;
                if (_contentOffset.y < -100 || _contentOffset.y > _scrollSize.height - _frame->getContentSize().height + 200) {
                    _contentOffset.y += delta.y;
                    return;
                }
                _container->setPosition(ccp(_container->getPositionX(), _container->getPositionY() + delta.y));
                
            }
//        }
        CCLog("cctouchmove---->the layer content offset is (%.2f, %.2f)", _contentOffset.x, _contentOffset.y);
        
    }

}

void DragItemLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    moveEnd(pTouch, pEvent);
}

void DragItemLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    moveEnd(pTouch, pEvent);
}

void DragItemLayer::moveEnd(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    m_pBeginTouch = NULL;
    //如果本次触摸发生过移动，则需要判断工具应该停留在哪一页.
    CCLog("cctouchend----->the layer content offset is (%.2f, %.2f)", _contentOffset.x, _contentOffset.y);
    if(m_bTouchMoved)
    {
        performDistance = CCPointZero;
        canMove = false;
        isbDraging = false;
        if (_direction == kDragLayerHorizontal) {
            if (_contentOffset.x < 0) {
                _distanceSize = CCSizeMake(_contentOffset.x, 0);
                schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
            }
            if (_contentOffset.x > _scrollSize.width-_frame->getContentSize().width) {
                _distanceSize = CCSizeMake(-_scrollSize.width+_contentOffset.x+_frame->getContentSize().width, 0);
                schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
            }
        }else {
            if (_contentOffset.y < 0) {
                _distanceSize = CCSizeMake(0,_contentOffset.y);
                schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
            }
            if (_contentOffset.y > _scrollSize.height-_frame->getContentSize().height) {
                _distanceSize = CCSizeMake(0, -_scrollSize.height+_contentOffset.y+_frame->getContentSize().height);
                CCLog("the distance size is %.2f, %.2f", _distanceSize.width, _distanceSize.height);
                schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
            }
        }
    }else{  //如果本次触摸未发生过移动，则检测是否有工具被点击了，是否需要弹出选择框
        //判断是否有工具被点击,主要指那些需要点击弹出选择框的工具
        for (int i = 0; i < getChildren()->count(); ++i) {
            ItemBase* item = dynamic_cast<ItemBase*>(getChildren()->objectAtIndex(i));
            if (pTouch == NULL || item == NULL) {
                continue;
            }
            if (ptInPolygon(pTouch->getLocation(), item->getPolygon())) {
                if (pDelegate) {
                    pDelegate->onitemClicked(item);
                }
            }
        }
    }
}

void DragItemLayer::deaccelerateScrolling(float dt) {
    if (isbDraging == true) {
        unschedule(schedule_selector(DragItemLayer::deaccelerateScrolling));
    }
    CCPoint perDistance = ccpMult(_distanceSize, 1/15.0);
    performDistance = performDistance + perDistance;
    _container->setPosition(_container->getPosition() + perDistance);
    _contentOffset = _contentOffset - perDistance;
    if (fabs(_distanceSize.width - performDistance.x) <= 0.5f && fabs(_distanceSize.height - performDistance.y) <= 0.5f) {
        unschedule(schedule_selector(DragItemLayer::deaccelerateScrolling));
    }
}

CCPoint DragItemLayer::convertToWorld(cocos2d::CCPoint resPos) {
    return _container->convertToWorldSpace(resPos);
}

void DragItemLayer::addItemtoContainer(ItemBase *pitem) {
    pitem->setPosition(pitem->getStartPos());
    _container->addChild(pitem);
}

void DragItemLayer::reloadChildren(ItemBase *pItem){
    itemArray->removeObject(pItem);
    _container->removeAllChildren();
    _contentOffset = ccp(0, 0);
    _scrollSize = CCSizeMake(0, 0);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(itemArray, pObj){
        ItemBase* item = dynamic_cast<ItemBase*>(pObj);
        switch (_direction) {
            case kDragLayerHorizontal:
            {
                item->setAnchorPoint(ccp(0.5, 0));
                CCSize itemSize = item->getContentSize();
                item->setPosition(ccp(itemSize.width / 2.0 + _scrollSize.width, 0));
                
                _scrollSize.width += itemSize.width + SPACE;
                _container->addChild(item, 1);
            }
                break;
            case kDragLayerVertical:
            {
                item->setAnchorPoint(ccp(0, 0.5));
                CCSize itemSize = item->getContentSize();
                item->setPosition(ccp(0,itemSize.height / 2.0 + _scrollSize.height));
                _scrollSize.height += itemSize.height + SPACE;
                _container->addChild(item, 1);
            }
                break;
            default:
                break;
        }
    };
    if (_scrollSize.width < _frame->getContentSize().width) {
        _scrollSize.width = _frame->getContentSize().width;
    }
    if (_scrollSize.height < _frame->getContentSize().height) {
        _scrollSize.height = _frame->getContentSize().height;
    }
    _container->setPosition(CCPoint(0, 0));
    _container->setContentSize(_scrollSize);

}


void DragItemLayer::scrolltoLeft(float dt) {
    if (dt == 0) {
        _container->setPositionX(-_scrollSize.width+_frame->getContentSize().width);
        _contentOffset.x = _scrollSize.width-_frame->getContentSize().width;
    }else {
        _distanceSize = CCSizeMake(-_scrollSize.width+_frame->getContentSize().width + _contentOffset.x, 0);
        schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
    }
}

void DragItemLayer::scrolltoRight(float dt) {
    if (dt == 0) {
        _container->setPositionX(0);
        _contentOffset.x = 0;
    }else {
        _distanceSize = CCSizeMake(_contentOffset.x-0, 0);
        schedule(schedule_selector(DragItemLayer::deaccelerateScrolling), 0.02, 14, 0);
    }
}

#pragma mark 裁剪超出边框部分(clipLayer)
bool ClipLayer::init(){
    if (CCLayer::init()) {
        m_bClippingToBounds = true;
        return true;
    }
    return false;
}

CCRect ClipLayer::getViewRect()
{
    CCPoint screenPos = this->convertToWorldSpace(CCPointZero);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (CCNode *p = m_pParent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }
    
    // Support negative scaling. Not doing so causes intersectsRect calls
    // (eg: to check if the touch was within the bounds) to return false.
    // Note, CCNode::getScale will assert if X and Y scales are different.
    if(scaleX<0.f) {
        screenPos.x += this->getContentSize().width*scaleX;
        scaleX = -scaleX;
    }
    if(scaleY<0.f) {
        screenPos.y += this->getContentSize().height*scaleY;
        scaleY = -scaleY;
    }
    
    return CCRectMake(screenPos.x, screenPos.y, this->getContentSize().width*scaleX, this->getContentSize().height*scaleY);
}


void ClipLayer::beforeDraw(){
    if (m_bClippingToBounds)
    {
		m_bScissorRestored = false;
        CCRect frame = getViewRect();
        if (CCEGLView::sharedOpenGLView()->isScissorEnabled()) {
            m_bScissorRestored = true;
            m_tParentScissorRect = CCEGLView::sharedOpenGLView()->getScissorRect();
            //set the intersection of m_tParentScissorRect and frame as the new scissor rect
            if (frame.intersectsRect(m_tParentScissorRect)) {
                float x = MAX(frame.origin.x, m_tParentScissorRect.origin.x);
                float y = MAX(frame.origin.y, m_tParentScissorRect.origin.y);
                float xx = MIN(frame.origin.x+frame.size.width, m_tParentScissorRect.origin.x+m_tParentScissorRect.size.width);
                float yy = MIN(frame.origin.y+frame.size.height, m_tParentScissorRect.origin.y+m_tParentScissorRect.size.height);
                CCEGLView::sharedOpenGLView()->setScissorInPoints(x, y, xx-x, yy-y);
            }
        }
        else {
            glEnable(GL_SCISSOR_TEST);
            CCEGLView::sharedOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
        }
    }
}

void ClipLayer::afterDraw()
{
    if (m_bClippingToBounds)
    {
        if (m_bScissorRestored) {//restore the parent's scissor rect
            CCEGLView::sharedOpenGLView()->setScissorInPoints(m_tParentScissorRect.origin.x, m_tParentScissorRect.origin.y, m_tParentScissorRect.size.width, m_tParentScissorRect.size.height);
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
}

void ClipLayer::visit()
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }
    
	kmGLPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }
    
	this->transform();
    this->beforeDraw();
    
	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }
    
    this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	kmGLPopMatrix();
}
