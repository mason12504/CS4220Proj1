Project Report

Group Members: Mason Andersen, Zachary Donnelly 
We have neither given nor recieved unauthorized assistance on this work

These programs, client.c and server.c impliment a client and server using OpenSSL standard practice. The client establishes a secure, encrypted TLS connection with the server, recieves a message, and closes the connection when complete. 

Initially, the main issues were in setting up OpenSSL on windows, and while this seemed like a good decision for convenience, the nature of visual studio complicated some parts of the project. Overall, we were able to overcome these issues and get a working TLS connection going, with encrypted data. 
Resources:  
https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739   
https://beej.us/guide/bgnet/html/split/index.html   
https://www.binarytides.com/winsock-socket-programming-tutorial/  
https://opensource.com/article/19/6/cryptography-basics-openssl-part-1  
https://github.com/openssl/openssl/blob/master/demos/guide/tls-client-non-block.c 

