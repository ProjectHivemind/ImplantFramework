#include <string>

namespace hivemind {
	/**
	 * @brief Abstract class for transport methods. 
	 * These are what actually send and recieve data from the central server.
	*/
	class Transport {
	public:
		/**
		 * @brief Sends data to teh server and waits to recieve a response.
		 * @param  Data to send to the server.
		 * @return Data recieved from the server.
		*/
		virtual std::string SendAndRecieve(std::string) = 0;

		/**
		 * @brief Send data to the server.
		 * @param  Data to send to the server.
		*/
		virtual void Send(std::string) = 0;

		/**
		 * @brief Recieve data from the server. 
		 * @return Data recieved from the server.
		*/
		virtual std::string Recieve() = 0;
	};
}