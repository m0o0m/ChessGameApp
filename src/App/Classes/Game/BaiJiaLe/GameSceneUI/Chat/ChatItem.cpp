//
//  ChatItem.cpp
//  NiuNiu
//
//  Created by zhong on 12/17/15.
//
//

#include "ChatItem.h"
#include "HallDataMgr.h"

USING_NS_CC;
ChatItem::ChatItem():
m_clipUserName(nullptr),
m_labelChat(nullptr),
m_spBrow(nullptr)
{
    
}

ChatItem::~ChatItem()
{
    
}

//ChatItem* ChatItem::createTextItem(const std::string &str, const DWORD &senduser /*= INVALID_USERID*/)
//{
//    ChatItem *pItem = new ChatItem();
//    if (nullptr != pItem && pItem->init(senduser))
//    {
//        pItem->initTextItem(str);
//        pItem->autorelease();
//
//        return pItem;
//    }
//    CC_SAFE_DELETE(pItem);
//    return nullptr;
//}
//
//ChatItem* ChatItem::createBrowItem(const int &nIdx, const DWORD &senduser /*= INVALID_USERID*/)
//{
//    ChatItem *pItem = new ChatItem();
//    if (nullptr != pItem && pItem->init(senduser))
//    {
//        pItem->initBrowItem(nIdx);
//        pItem->autorelease();
//
//        return pItem;
//    }
//    CC_SAFE_DELETE(pItem);
//    return nullptr;
//}
//
//bool ChatItem::init(const DWORD &senduser /*= INVALID_USERID*/)
//{
//    bool bRes = false;
//    do {
//        CC_BREAK_IF(!Node::init());
//
//
//        if (INVALID_USERID != senduser)
//        {
//            std::string name = HallDataMgr::getInstance()->m_UserList.at(senduser)->m_nickname;
//            m_labelUserName = Label::createWithSystemFont(name, "Arial", 24);
//            m_labelUserName->setColor(Color3B::RED);
//            m_labelUserName->setPosition(Vec2(-200,60));
//            this->addChild(m_labelUserName);
//        }
//
//        auto sp = Sprite::create("game/xgmm_line.png");
//        sp->setRotation(90.0f);
//        this->addChild(sp);
//
//        bRes = true;
//    } while (false);
//    return bRes;
//}

bool ChatItem::init()
{
    bool bRes = false;
    do {
        CC_BREAK_IF(!Node::init());
        
        auto sp = Sprite::createWithSpriteFrameName("xgmm_line.png");
        if (nullptr != sp)
        {
            sp->setRotation(90.0f);
            this->addChild(sp);
        }
        
        bRes = true;
    } while (false);
    return bRes;
}

void ChatItem::initTextItem(const std::string &str)
{
    m_labelChat = Label::createWithSystemFont(str, "Arial", 25,Size(490,0));
    m_labelChat->setAnchorPoint(Vec2(0.5f, 0));
    m_labelChat->setPositionY(3.0f);
    Size labSize = m_labelChat->getContentSize();
    if (nullptr != m_clipUserName)
    {
        m_clipUserName->setPositionY(labSize.height + m_clipUserName->getContentSize().height * 0.5);
        m_labelChat->setColor(Color3B::BLACK);
    }
    else
    {
        m_labelChat->setColor(Color3B::WHITE);
    }
    this->setContentSize(Size(530,labSize.height + 5));
    this->addChild(m_labelChat);
}

void ChatItem::initBrowItem(const int &nIdx)
{
    char buf[24] = "";
    if (nIdx < 10)
    {
        sprintf(buf, "e0%d.png",nIdx);
    }
    else
    {
        sprintf(buf, "e%d.png",nIdx);
    }
    m_spBrow = Sprite::createWithSpriteFrameName(buf);
    if (nullptr != m_spBrow)
    {
        m_spBrow->setPosition(-180, 25);
        
        this->setContentSize(Size(500,55));
        this->addChild(m_spBrow);
    }
}

void ChatItem::refreshTextItem(const std::string &str,const DWORD &senduser /*= INVALID_USERID*/)
{
    if (nullptr != m_spBrow)
    {
        m_spBrow->setVisible(false);
    }
    
    if (nullptr == m_labelChat)
    {
        m_labelChat = Label::createWithSystemFont(str, "Arial", 25,Size(490,0));
        m_labelChat->setAnchorPoint(Vec2(0.5f, 0));
        m_labelChat->setPositionY(3.0f);
        
        this->addChild(m_labelChat);
    }
    else
    {
        m_labelChat->setString(str);
    }
    m_labelChat->setVisible(true);
    m_labelChat->setColor(Color3B::WHITE);
    
    Size labSize = m_labelChat->getContentSize();
    
    if (INVALID_USERID != senduser)
    {
        UserData *pUser = HallDataMgr::getInstance()->getUserData(senduser);
        if (nullptr != pUser)
        {
            std::string name = pUser->m_nickname;
            if (nullptr == m_clipUserName)
            {
                m_clipUserName = ClipText::createClipText(Size(200,25), name, "Arial", 25);
                m_clipUserName->setTextColor(Color4B::RED);
                m_clipUserName->setAnchorPoint(Vec2(0,0.5));
                m_clipUserName->setPosition(Vec2(-250,60));
                this->addChild(m_clipUserName);
            }
            else
            {
                m_clipUserName->setString(name);
            }
            
            m_clipUserName->setPositionY(labSize.height + m_clipUserName->getContentSize().height * 0.5 + 2);
            m_labelChat->setColor(Color3B::BLACK);
            labSize.height = labSize.height + m_clipUserName->getContentSize().height;
        }
    }
    else
    {
        if(m_clipUserName)
        {
            m_clipUserName->setVisible(false);
        }
    }
    
    this->setContentSize(Size(530,labSize.height + 15));
}

void ChatItem::refreshBrowItem(const int &nIdx,const DWORD &senduser /*= INVALID_USERID*/)
{
    char buf[24] = "";
    if (nIdx < 10)
    {
        sprintf(buf, "e0%d.png",nIdx);
    }
    else
    {
        sprintf(buf, "e%d.png",nIdx);
    }
    if (nullptr != m_labelChat)
    {
        m_labelChat->setVisible(false);
    }
    
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
    if (nullptr != frame)
    {
        if (nullptr == m_spBrow)
        {
            m_spBrow = Sprite::createWithSpriteFrame(frame);
            m_spBrow->setPosition(-180, 25);
            this->addChild(m_spBrow);
        }
        else
        {
            m_spBrow->setSpriteFrame(frame);
        }
        m_spBrow->setVisible(true);
    }
    
    float sizeHeight = 48;
    if (INVALID_USERID != senduser)
    {
        UserData *pUser = HallDataMgr::getInstance()->getUserData(senduser);
        if (nullptr != pUser)
        {
            std::string name = pUser->m_nickname;
            if (nullptr == m_clipUserName)
            {
                m_clipUserName = ClipText::createClipText(Size(200,25), name, "Arial", 25);
                m_clipUserName->setTextColor(Color4B::RED);
                m_clipUserName->setAnchorPoint(Vec2(0,0.5));
                m_clipUserName->setPosition(Vec2(-250,60));
                this->addChild(m_clipUserName);
            }
            else
            {
                m_clipUserName->setString(name);
            }
            
            m_clipUserName->setPositionY(48 + m_clipUserName->getContentSize().height * 0.5);
            sizeHeight = sizeHeight + m_clipUserName->getContentSize().height;
        }
    }
    else
    {
        if(m_clipUserName)
        {
            m_clipUserName->setVisible(false);
        }
    }
    this->setContentSize(Size(530, sizeHeight + 15));
}