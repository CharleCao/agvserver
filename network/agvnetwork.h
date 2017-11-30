﻿#ifndef AGVNETWORK_H
#define AGVNETWORK_H

#include <QObject>
#include <QMap>
#include "IOCPModel.h"

enum agv_msg_type{
    AGV_MSG_TYPE_LOGIN = 0,//登陆
    AGV_MSG_TYPE_INFO,//信息
    AGV_MSG_TYPE_WARNING,//警告
    AGV_MSG_TYPE_ERROR,//错误
    AGV_MSG_TYPE_REAL_TIME,//实时的消息，要求立即处理
};

enum client_msg_type{
    CLIENT_MSG_TYPE_LOGIN = 0,//登陆
    CLIENT_MSG_TYPE_INFO,//信息
    CLIENT_MSG_TYPE_WARNING,//警告
    CLIENT_MSG_TYPE_ERROR,//错误
    CLIENT_MSG_TYPE_REAL_TIME,//实时的消息，要求立即处理
};

class AgvNetWork : public QObject
{
    Q_OBJECT
public:
    explicit AgvNetWork(QObject *parent = nullptr);
    ~AgvNetWork();

    void sendToOne(SOCKET sock, const char *buf, int len);//发送给某个id的消息
    void sendToAll(char *buf,int len);//发送给所有的人的信息
    void sendToSome(QList<int> ones,char *buf,int len);//发送给某些id的人的消息
    //void sendToAllAgv(char *buf,int len);
    //void sendToAllClient(char *buf,int len);

    //读取的回调函数
    static void onRecvClientMsg(void *param, char *buf, int len, SOCKET sock, const QString &sIp, int port);

    //断开连接的回调函数
    static void onDisconnectClient(void *owner, SOCKET sock, const QString &sIp, int port);

    //void recvAgvMsgProcess(char *buf, int len);
    void recvClientMsgProcess(char *buf, int len, SOCKET sock, const QString &ip, int port);

    //发送消息线程
    bool initServer();
signals:

public slots:

private:
    //CIOCPModel m_agvIOCP;
    CIOCPModel m_clientIOCP;
    volatile bool isQuit;
};

#endif // AGVNETWORK_H
