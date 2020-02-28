import time
import socket,threading
users={}  #用户字典`
PORT=20000
max_connection=100
HOST=socket.gethostname()
LOCIP=socket.gethostbyname(HOST)
LOCIP='172.17.0.15'
LOGPATH='chat.log'

def save(text,encoding='utf-8'):
    f=open(LOGPATH,"a",)
    f.write(text)
    f.flush()
    f.close()

def readlog():
    f=open(LOGPATH,"r")
    text = f.read()
    f.close()
    return text

def handle(client,addr,encoding="utf-8"):
    BUF=10240
    END='$END$'      #断连标识符
    check=client.recv(BUF).decode(encoding)
    if check != '$TOM$':
        client.close()
        return
    username=client.recv(BUF).decode(encoding)
    if 'HTTP' in username and 'GET' in username:
        return
    if username.isspace():
        client.send("用户名为空! 登陆失败".encode(encoding))
        return
    users[username]=client
    try:
        print(time.strftime("%Y-%m-%d %H:%M:%S",time.localtime()))
        print("{} from {} Connected.".format(username,addr))
        client.send("Hello,{}! Welcome to Tom Chatroom.".format(username).encode(encoding))
        client.send(readlog().encode(encoding))
        while True:
            recv_data=client.recv(BUF)
            text=recv_data.decode(encoding,'strict')
            if text==END:                                                                  
                for u in users:
                    users[u].send("{} 退出了聊天室.".format(username).encode(encoding))
                print("{} has disconnected.".format(username))
                users[username].close()           #断开连接
                del users[username]               #删除用户
                return                             
            print("{}:\n{}\n".format(username,text))
            save("{}\n{}:\n{}\n".format(time.strftime("%Y-%m-%d %H:%M:%S",time.localtime()),username,text))
            for u in users:
                users[u].send("{}\n{}:\n{}\n".format(time.strftime("%Y-%m-%d %H:%M:%S",time.localtime()),username,text).encode(encoding))
    
    except:
        print("CONNECTION WITH {} ERROR!\n".format(username))
        users[username].close()
        del users[username]
        return

                    

if __name__ == "__main__":
    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
        s.bind((LOCIP,PORT))
        s.listen(max_connection)
        print(LOCIP,PORT)
        while True:
            cli,add=s.accept()
            new_handle = threading.Thread(target=handle,args=(cli,add))
            new_handle.setDaemon(True)
            new_handle.start()
