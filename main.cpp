#include <iostream>
#include<asio.hpp>
#include<iostream>
#include<asio/placeholders.hpp>
#include<thread>
#include<chrono>
#include"string.h"
#include<experimental/executor>
#include<experimental/socket>
#include<experimental/internet>
#include<experimental/io_context>

using namespace std;
using namespace std::experimental;
//asio::ip::udp contains neccessarry flags for udp sockets
using asio::ip::udp;
using asio::ip::address_v4;
using asio::ip::address_v6;

#define PORT 3333

void sender(array<char,1024>buffer){
  asio::io_service ios_executor;
  ios_executor.run();
  auto sender_endpoint = asio::ip::udp::v6();
  
  asio::ip::udp::socket sock(ios_executor,sender_endpoint);
  size_t bytes_sent=sock.send_to(asio::buffer(buffer,buffer.size()),asio::ip::udp::endpoint(asio::ip::address::from_string("::1"),PORT));
  cout<<"Bytes sent: "<<bytes_sent<<endl;
  //sock.close();
}
void receiver(array<char,1024>buffer){
//array<char,1024>buffer={"Send packet to an endpoint"};
asio::io_service ios_executor;
ios_executor.run();
asio::ip::udp::endpoint receiver_endpoint(asio::ip::address_v6().any(),PORT);
asio::ip::udp::socket socket_IPv6(ios_executor);
socket_IPv6.open(asio::ip::udp::v6());
asio::ip::v6_only option;
socket_IPv6.get_option(option);
bool v6_only = option.value();
cout<<"Socket option of ipv6 only is: "<<option;
socket_IPv6.bind(receiver_endpoint);


//asio::ip::udp::endpoint ep(asio::ip::udp::v6(),3333);
asio::ip::udp::endpoint ep;
size_t bytes_received=socket_IPv6.receive_from(asio::buffer(buffer,buffer.size()),ep);
cout<<"Bytes received: "<<bytes_received<<endl;
//socket_IPv6.close();
}
void udp_server(){
  char received_msg[1024];
    const int port=3000;
    //error_code in case of unexpected behaviour
    asio::error_code ec;
    //io_service to notify operating system about our program thorught the io_service
    asio::io_service ios;
    asio::ip::udp::endpoint server_endpoint;
    //Create and bind UDP socket to server endpoint
    asio::ip::udp::socket server_socket(ios,server_endpoint);
    //auto received_bytes=
   /*

    server_socket.async_receive_from(asio::buffer(received_msg,1024),server_endpoint,[](asio::error_code ec,size_t recvd_bytes){
        if(!ec && recvd_bytes>0){
        cout<<received_msg;
        }
    }); 
  server_socket.async_receive_from()
  */ 
    
    }
void udp_sender(){
    const int port=3000;
    //error_code in case of unexpected behaviour
    asio::error_code ec;
    //io_service to notify operating system about our program thorught the io_service
    asio::io_service ios;
    //Create message to been sent to a server from a client
    string client_message="Hi server!";
    //remote_endpoint which is the server with any address and specified port of 3000
    asio::ip::udp::endpoint remote_endpoint(asio::ip::udp::v4(),port);
    //creating client_socket on base of ipv4 address family and binding socket to remote endpoint (which is server)
    asio::ip::udp::socket client_socket(ios,remote_endpoint);
    //
    client_socket.open(asio::ip::udp::v4());
    auto send=client_socket.send_to(asio::buffer(client_message,client_message.size()),remote_endpoint,0,ec);
    cout<<endl;
    cout<<"Sent Payload <---- "<<send<<endl;
    //Dont't have to close udp socket so we can reuse it in future
    //client_socket.close();
}




int main(int argc, char*argv[]) {
  
  //array<char,1024>buffer={"Send packet to an endpoint"};
  //thread t1(sender,buffer);
  //thread t2(receiver,buffer);

  //t1.join();
  //t2.join();


/*
thread server=thread([](){
  cout<<"Starting server"<<endl;
  net::io_context io_context;
  net::ip::tcp::endpoint endpoint{net::ip::tcp::v4(),3000};
  net::ip::tcp::acceptor acceptor{io_context,endpoint};
  acceptor.non_blocking(true);
  cout<<"---opened server on---"<<endpoint<<endl;
  error_code error_code;
  net::ip::tcp::socket socket(io_context);
  while(true){
    socket=acceptor.accept(error_code);
    if(!error_code){
      cout<<"Connected to a client"<<endl;
      this_thread::sleep_for(3s);
      string data="Hi client";
      net::const_buffer buffer=net::buffer(data);
      auto bytes=socket.send(buffer);
      cout<<"Data sent"<<endl;
      cout<<bytes<<endl;
    }
  }
});
*/
/*
thread client=thread([](){
 net::io_context io_context;
  net::ip::tcp::endpoint server_endpoint{net::ip::tcp::v4(),3000};
  net::ip::tcp::socket socket(io_context);
  error_code error_code;
  while(true){
    socket.connect(server_endpoint,error_code);
    if(!error_code){
      cout<<"Connected to a server"<<endl;
     std::string msg;
msg.resize(12); // prepare space for incoming data
net::mutable_buffer buf = net::buffer(msg);
socket.receive(buf);
std::cout << "I got: " << msg << std::endl;
      
      cout<<"Received data: "<<msg;
    }
  }
});
*/
//cout<<processor_count<<endl;

//server.join();


thread server_udp=thread([](){
cout<<"Starting the server"<<endl;
net::io_context io_context;
net::ip::udp::endpoint server_endpoint{net::ip::udp::v4(),4000};
error_code error_code;
net::ip::udp::socket server(io_context);
server.open(net::ip::udp::v4(),error_code);
//net::socket_base::broadcast option(true);
//server.set_option(option);

cout<<"---opened on port---"<<server_endpoint<<endl;
//server.bind(server_endpoint,error_code);
//server.connect(server_endpoint,error_code);

server.set_option(net::ip::udp::socket::reuse_address(true));
while(true){
if(!error_code){
server.connect(server_endpoint,error_code);
cout<<"Server connected to endpoint: "<<server_endpoint<<endl;
this_thread::sleep_for(3s);
string server_message="Message from server";
net::const_buffer buffer=net::buffer(server_message);
//this_thread::sleep_for(2s);
auto bytes_sent=server.send(buffer,error_code);
cout<<"Data sent "<<endl;
cout<<bytes_sent<<endl;
}
}});

thread client_udp=thread([](){
net::io_context io_context;
//net::ip::udp::endpoint server_endpoint{net::ip::udp::v4(),4000};
//this_thread::sleep_for(3s);
error_code error_code;
asio::io_context ios;
asio::ip::udp::endpoint receiver(asio::ip::udp::v4(), 4000);
asio::ip::udp::socket socket(ios, receiver);

//net::ip::udp::socket client_socket(io_context,server_endpoint);
while(true){
//client_socket.connect(server_endpoint,error_code);
cout<<"Client connected to a server"<<endl;
//char buffer[65536];
string message;
message.resize(1024);
asio::mutable_buffer buffer=asio::buffer(message);
        asio::ip::udp::endpoint sender;
        std::size_t bytes_transfered = socket.receive_from(buffer, sender);
/*
client_socket.connect(server_endpoint,error_code);

if(!error_code){

cout<<"Client connected to a server"<<endl;
string received_message;
received_message.resize(1024);
net::mutable_buffer muttable_buffer=net::buffer(received_message);
client_socket.receive(muttable_buffer,error_code);
//client_socket.receive_from(muttable_buffer,server_endpoint,error_code);
*/
cout<<"Received Data: "<<bytes_transfered<<endl;
cout<<"Received message: "<<message<<endl;
//}
}
}
);


server_udp.join();
//client_udp.join();
    return 0;
    }

