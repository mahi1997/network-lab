# chat_client.py

import sys
import socket
import select
import time
 
def chat_client():
    if(len(sys.argv) < 4) :
        print 'Usage : python chat_clientone.py hostname port group'
        sys.exit()

    host = sys.argv[1]
    port = int(sys.argv[2])
    group = sys.argv[3]
    cname = sys.argv[4]
     
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
     
    # connect to remote host
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()

    s.send('$' + group)
     
    print 'Connected to remote host. You can start sending messages to group : ', group
    sys.stdout.write(cname+'>>'); sys.stdout.flush()
    try:
        while 1:
            socket_list = [sys.stdin, s]
             
            # Get the list sockets which are readable
            ready_to_read,ready_to_write,in_error = select.select(socket_list , [], [])
             
            for sock in ready_to_read:             
                if sock == s:
                    # incoming message from remote server, s
                    data = sock.recv(4096)

                    if not data :
                        print '\nDisconnected from chat server'
                        sys.exit()
                    else :
                        #print data
                        array = data.split(' ')
                        msg = ""
                        if(array[0] == "Error:"):
                            sys.stdout.write("Group Max limit reached\n")
                            sys.stdout.flush()
                            time.sleep(3)
                            s.send('$' + group)

                            


                        elif(array[2] == group):
                            for i in range(len(array)):
                                if(i > 2):
                                    msg += array[i] + ' '
                            sys.stdout.write('\n'+msg[:len(msg) - 1]+'\n'+cname+'>>')
                            sys.stdout.flush()    
                
                else :
                    # user entered a message
                    msg = sys.stdin.readline()
                    msg = group + ' ' +cname+">> "+ msg
                    s.send(msg) 
                    sys.stdout.write(cname+'>>'); sys.stdout.flush()
    
    except KeyboardInterrupt:
        s.send('#' + group)
        pass

if __name__ == "__main__":

    sys.exit(chat_client())
