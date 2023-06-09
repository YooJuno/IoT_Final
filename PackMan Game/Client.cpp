// g++ -std=c++11 Client.cpp -o Client -lboost_system -pthread $(pkg-config --libs --cflags opencv4)
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include "game.h"

using namespace boost::asio;
using namespace std;
using namespace cv;

class Client {
public:
    Client(io_context& ioContext, const std::string& serverIP, short serverPort)
        : ioContext_(ioContext), socket_(ioContext_), serverIP_(serverIP), serverPort_(serverPort) {
    }

    void start() {
        try {
            ip::tcp::resolver resolver(ioContext_);
            ip::tcp::resolver::query query(serverIP_, std::to_string(serverPort_));
            ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

            connect(endpointIterator);

            std::thread t([&]() {
                ioContext_.run();
            });
            t.detach();

            handleUserInput();
        } 
        catch (const std::exception& ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
    }

private:
    void connect(ip::tcp::resolver::iterator endpointIterator) {
        boost::asio::connect(socket_, endpointIterator);
        startReading();
    }


    void startReading() {
        std::array<char, 2048> buffer;

        socket_.async_read_some(
            boost::asio::buffer(buffer),
            [this, &buffer](boost::system::error_code ec, std::size_t bytesRead) {
                if (!ec) {
                    std::string message(buffer.data(), bytesRead);
                    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
                    
                    if(message == "Play")
                        game_state = true;
                    
                    std::vector<std::string> tokens;
                    std::stringstream ss(message);
                    std::string token;

                    while (std::getline(ss, token, ':')) 
                        tokens.push_back(token);
                    
                    
                    if (tokens.size() >= 2) {
                        string temp1 = tokens[0];
                        string temp2 = tokens[1];
                        
                        int usernumber = std::stoi(temp1);
                        int direction = std::stoi(temp2);

                        if(usernumber == 0) {
                            key1 = direction;
                        } else if(usernumber == 1) {
                            key2 = direction;
                        } else if(usernumber == 2) {
                            key3 = direction;
                        } else if(usernumber == 3) {
                            key4 = direction;
                        }
                    }

                    startReading();
                } 
                else {
                    std::cerr << "Error reading from server: " << ec.message() << std::endl;
                    socket_.close();
                }
            }
        );
    }


    

    void handleUserInput() {
    	string name;
    	std::stringstream dd;
    	std::cout << "Input your Name : " ;
    	std::cin >> name;
    	
    	dd << "username:";
    	dd << name;
    	string Entername = dd.str();
    	
    	
    	boost::asio::write(socket_, boost::asio::buffer(Entername));
    	
        const int size = 500; 
        
        Background background(size);

    	Pacman pacman1(size, background, 0);
    	Pacman pacman2(size, background, 1);
        Pacman pacman3(size, background, 2);
        Pacman pacman4(size, background, 3);

    	Mat black_screen;
        black_screen = Mat(size, size, CV_8UC3, Scalar(0, 0, 0));
        
        while (true) {
            std::stringstream ss;
            std::string waitingMessage;
            
            int key = waitKey(15);
            if (key == 27) {
                break;
            }
                
	        if(key == 81 || key == 82 || key == 83 || key == 84) {
                ss << name;
                ss << ":";
                ss << key; 
                
                waitingMessage = ss.str();
                boost::asio::write(socket_, boost::asio::buffer(waitingMessage));
            }

	        if(game_state == true) {
                background.draw_background();

                pacman1.update_direction(key1);
                pacman2.update_direction(key2);
                pacman3.update_direction(key3);
                pacman4.update_direction(key4);
            
                pacman1.update_pose(size);
                pacman2.update_pose(size);
                pacman3.update_pose(size);
                pacman4.update_pose(size);

                pacman1.draw_packman();
                pacman2.draw_packman();
                pacman3.draw_packman();
                pacman4.draw_packman();
                imshow("Pacman Game", background.game_map);
            }
        }
        
	    destroyAllWindows();
        socket_.close();
    }

    io_context& ioContext_;
    ip::tcp::socket socket_;
    std::string serverIP_;
    short serverPort_;
    std::string inputBuffer_;
    std::string name;
    bool game_state = false;
    int key1 = -99;
    int key2 = -99;
    int key3 = -99;
    int key4 = -99;
};

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context ioContext;
        std::string serverIP = argv[1];  // 서버 IP를 수정해야 합니다.
        short serverPort = atoi(argv[2]);            // 서버 포트를 수정해야 합니다.

        Client client(ioContext, serverIP, serverPort);
        client.start();
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}

