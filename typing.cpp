#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}


namespace detail_
{
    struct wait_for
    {
        explicit wait_for( unsigned int msecs ) : ms(msecs) {}
        const std::chrono::milliseconds ms ;

        template< typename C, typename T >
        friend std::basic_ostream<C,T>& operator<< ( std::basic_ostream<C,T>& stm, wait_for w )
        { if(stm) std::this_thread::sleep_for(w.ms) ; return stm ; }
    };
}

template< typename C, typename T >
std::basic_ostream<C,T>& operator<< ( std::basic_ostream<C,T>& stm, std::pair< std::string, detail_::wait_for> str_slow )
{
    for( char c : str_slow.first ) stm << str_slow.second << c << std::flush ;
    return stm ;
}

std::pair< std::string, detail_::wait_for> slowly( std::string str, unsigned int ms = 250 ) 
{ return { str, detail_::wait_for(ms) } ; }

int main(int argc, char** argv) 
{
	system("clear");
	system("export PS1=""Hello friend");
	string test = readFileIntoString(argv[1]);
    std::cout << slowly( test ) ; // with default delay of 250 ms between characters
}

