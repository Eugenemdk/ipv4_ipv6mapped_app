#include <iostream>
#include<asio.hpp>
#include<iostream>
#include<asio/placeholders.hpp>
using namespace std;

//asio::ip::udp contains neccessarry flags for udp sockets
using asio::ip::udp;
using asio::ip::address_v4;
using asio::ip::address_v6;
#define UDP_PROTOCOL 3333
//Steps to do udp socket connection:
/**
 * 1.Obtain the target servers application's
 *  IP address and a protocol port number
 * 2.Create an object of the asio::ip::udp::endpoint
 * c,ass frim the IP address and the protocol port number
 * obtained in step 1
 * 3.Create and open active socket
 * 4,Call the socket's connect() method specyfing
 *  the endpoint object created in step 2 as an argument
 * 5.If the method succeds ,the socket is considered connected
 * and can be used to send and receive data to and from
 * server
**/
void Sender(string input){
asio::error_code ec;
    //server part
    //asio::ip::address_v4 ip_address=asio::ip::address_v4::any();
    //target sever application to which we are connecting
    
    //socket part
    asio::io_context ios;
    asio::ip::udp::endpoint ep(asio::ip::make_address_v4("127.0.0.1"),3333);
    //asio::ip::udp protocol= asio::ip::udp::v4();
    asio::ip::udp::socket socket(ios);
    socket.open(asio::ip::udp::v4());
    //connect socket to a server's application
    //binding performs during connect() execution
    //socket.connect(ep);

    //accepting connections to a server
    auto sent = socket.send_to(asio::buffer(input), ep, 0, ec);
    socket.close();
    std::cout << "Sent Payload --- " << sent << "\n";
    /*    if(ec.value()!=0){
        cout<<"Failed to open socket because of "<<ec.message()<<endl;
    }else{
        cout<<"Socket is opened"<<endl;
    }*/
}
struct Client{
    asio::io_context io_executor;
    asio::ip::udp::socket socket{io_executor};
    array<char,500>recv_buffer;
    asio::ip::udp::endpoint server_endpoint;
    void handleReceive(asio::error_code ec,size_t bytesTransfered){
        if(ec.value()!=0){
            cout<<"Receive failed due to :"<<ec.message()<<endl;
        }
        cout<<"received:"<<string(recv_buffer.begin(),recv_buffer.begin()+bytesTransfered)<<endl;
    }
    

void Receiver()
    {
        socket.open(udp::v4());
        socket.bind(udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 3333));

        //wait();

        std::cout << "Receiving\n";
        io_executor.run();
        std::cout << "Receiver exit\n";
    }
};
int main(int argc, char*argv[]) {
    /*
    Client client;
    std::string input = argc>1? argv[1] : "sending bytes";
    std::cout << "Input is '" << input.c_str() << "'\nSending it to Sender Function...\n";
    Sender(input);
    client.Receiver();
   */
  //executor
  asio::io_service ios;
  //servers endpoint
  
  asio::ip::udp::endpoint remote_endpoint(asio::ip::udp::v6(),UDP_PROTOCOL);

    //ipv6 socket setup
  asio::ip::udp::socket socket_IPv6(ios);
  socket_IPv6.open(asio::ip::udp::v6());
  socket_IPv6.bind(remote_endpoint);
  //ipv4 socket setup
  asio::ip::udp::socket socket_IPv4(ios);
  /*
  asio::ip::address_v4 adr4;
  asio::ip::address_v6 adr6=address_v6::any();
  if(adr6.is_v4_mapped()||adr6.is_v4_compatible()){
    cout<<"Address v6 is compatible with IPv4"<<endl;
  }else{
    cout<<"Address adrv6 is not compatible nor mapped with ipv4"<<endl;
    cout<<adr6.to_string()<<endl;
  }
  */
  
  //socket_IPv4.open(asio::ip::udp::v4());
  //socket_IPv4.bind(remote_endpoint);

  
  ios.run();
  array<char,1024>buffer={"Send packet to an endpoint"};
  size_t sent_buffer=socket_IPv6.send_to(asio::buffer(buffer,buffer.size()),remote_endpoint);
  cout<<"Bytess sent: "<<sent_buffer<<endl;
  size_t received_buffer=socket_IPv6.receive_from(asio::buffer(buffer,buffer.size()),remote_endpoint);
  cout<<"Bytes received: "<<received_buffer<<endl;
  //checking compatibility ipv4 and ipv6
/*   
cout<<socket_IPv6.is_open()<<endl;
asio::ip::address_v4 a4;
cout<<remote_endpoint.address()<<endl;
 auto a6 = remote_endpoint.address().to_v6();
 cout<<a6<<endl;
            if (a6.is_v4_compatible() || a6.is_v4_mapped())
                a4 = a6.to_v4();
                cout<<a4<<endl;
cout << (a4.is_unspecified()? "not-mapped" : a4.to_string()) << " "  << remote_endpoint << "\n";
*/
 socket_IPv6.close();
 //asio::ip::address_v4 a4;
 //asio::ip::address_v6 a6;
   
   
    
    return 0;
    }
