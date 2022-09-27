#include <iostream>
#include<asio.hpp>
#include<iostream>
#include<asio/placeholders.hpp>
#include<thread>
using namespace std;

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
  sock.close();
}
void receiver(array<char,1024>buffer){
//array<char,1024>buffer={"Send packet to an endpoint"};
asio::io_service ios_executor;
ios_executor.run();
asio::ip::udp::endpoint receiver_endpoint(asio::ip::address_v6().any(),PORT);
asio::ip::udp::socket socket_IPv6(ios_executor);

asio::ip::v6_only option(false);

socket_IPv6.open(asio::ip::udp::v6());
socket_IPv6.set_option(option);

socket_IPv6.bind(receiver_endpoint);
asio::ip::udp::endpoint ep(asio::ip::udp::v6(),3333);
size_t bytes_received=socket_IPv6.receive_from(asio::buffer(buffer,buffer.size()),ep);
cout<<"Bytes received: "<<bytes_received<<endl;
socket_IPv6.close();
}
int main(int argc, char*argv[]) {
  
  //asio::ip::udp::endpoint sender_endpoint(asio::ip::udp::v6(),PORT);
  array<char,1024>buffer={"Send packet to an endpoint"};
  thread t1(sender,buffer);
  thread t2(receiver,buffer);

  t1.join();
  t2.join();

    return 0;

    }

