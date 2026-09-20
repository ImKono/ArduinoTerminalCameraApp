#include <boost/asio.hpp>

namespace SerialTerminal {
    boost::asio::io_context io;
    boost::asio::serial_port port(io);

    bool openSerialPort(const std::string& device)
    {
        boost::system::error_code error;

        port.open(device, error);

        if (error) {
            std::cerr << "No se pudo abrir el puerto "
                      << device << ": "
                      << error.message()
                      << std::endl;

            return false;
        }

        //Setup
        port.set_option(boost::asio::serial_port_base::baud_rate(9600));
        port.set_option(boost::asio::serial_port_base::character_size(8));
        port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

        return true;
    }

    bool readSerialData()
    {
        char data[256];

        boost::system::error_code error;

        std::size_t length = port.read_some(
            boost::asio::buffer(data),
            error
        );

        if (error && error != boost::asio::error::eof) {
            std::cerr << "Error de lectura: "
                      << error.message()
                      << std::endl;

            return false;
        }

        std::cout << "Leídos "
                  << length
                  << " bytes."
                  << std::endl;

        std::cout.write(data, static_cast<std::streamsize>(length));
        std::cout << std::endl;

        return true;
    }
}