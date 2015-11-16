-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Ноя 17 2015 г., 00:15
-- Версия сервера: 5.5.44-0ubuntu0.14.04.1
-- Версия PHP: 5.5.9-1ubuntu4.13

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `ITA-codeforce`
--

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_cpp`
--

CREATE TABLE IF NOT EXISTS `assignment_cpp` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` text,
  `etalon` text,
  `footer` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=18232 ;

--
-- Дамп данных таблицы `assignment_cpp`
--

INSERT INTO `assignment_cpp` (`id`, `name`, `header`, `etalon`, `footer`) VALUES
(1, 'hello world', '#include <iostream> \r\n int main()\r\n {', 'std::cout << "Hello World!" << std::endl;', 'return 0;}'),
(2, 'pcount(): reports th', '#include <strstream>\r\n#include <iostream>\r\nusing namespace std;\r\nint main()\r\n{', ' char str[80];ostrstream outs(str, sizeof(str));\r\n  outs << "abcdefg ";\r\n  outs << 27 << " "  << 890.23;\r\n  outs << ends;  // null terminate\r\n  cout << "chars in outs: "<< outs.pcount(); // \r\n  cout << " " << str;', ' return 0;}'),
(3, 'cout: output hex', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', ' cout << hex << 100 << endl;  cout << setfill(''?'') << setw(10) << 2343.0;', 'return 0;}'),
(4, 'Set cout: hex and ba', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', 'cout.setf(ios::hex, ios::basefield);\r\n  cout << 100 << endl;                  // cout 100 in hex\r\n  cout.fill(''?'');\r\n  cout.width(10);\r\n  cout << 2343.0;', 'return 0;}'),
(5, 'cout: uppercase,show', '#include <iostream>\r\nusing namespace std;\r\nint main() {', 'cout.unsetf(ios::dec);\r\n  cout.setf(ios::uppercase | ios::showbase | ios::hex);\r\n  cout << 88 << ''\n'';\r\n  cout.unsetf(ios::uppercase);\r\n  cout << 88 << ''\n'';', 'return 0;}'),
(6, 'Defines your own ter', '#include <iostream>\r\n#include <cstdlib>\r\n#include <exception>\r\nusing namespace std;\r\nvoid myTerminator() {\r\n  cout << "Your own terminate handler\n";\r\n  abort();\r\n}\r\nint main() {', 'set_terminate(myTerminator);   \r\n  try {\r\n    cout << "Inside try block.";\r\n    throw 100; \r\n  }\r\n  catch (double i) { }', 'return 0;}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}'),
(8, 'memory usage', '#include <unistd.h>\r\n#include <ios>\r\n#include <iostream>\r\n#include <fstream>\r\n#include <string>\r\n\r\n//////////////////////////////////////////////////////////////////////////////\r\n//\r\n// process_mem_usage(double &, double &) - takes two doubles by reference,\r\n// attempts to read the system-dependent data for a process'' virtual memory\r\n// size and resident set size, and return the results in KB.\r\n//\r\n// On failure, returns 0.0, 0.0\r\n\r\nvoid process_mem_usage(double& vm_usage, double& resident_set)\r\n{\r\n   using std::ios_base;\r\n   using std::ifstream;\r\n   using std::string;\r\n\r\n   vm_usage     = 0.0;\r\n   resident_set = 0.0;\r\n\r\n   // ''file'' stat seems to give the most reliable results\r\n   //\r\n   ifstream stat_stream("/proc/self/stat",ios_base::in);\r\n\r\n   // dummy vars for leading entries in stat that we don''t care about\r\n   //\r\n   string pid, comm, state, ppid, pgrp, session, tty_nr;\r\n   string tpgid, flags, minflt, cminflt, majflt, cmajflt;\r\n   string utime, stime, cutime, cstime, priority, nice;\r\n   string O, itrealvalue, starttime;\r\n\r\n   // the two fields we want\r\n   //\r\n   unsigned long vsize;\r\n   long rss;\r\n\r\n   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr\r\n               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt\r\n               >> utime >> stime >> cutime >> cstime >> priority >> nice\r\n               >> O >> itrealvalue >> starttime >> vsize >> rss; // don''t care about the rest\r\n\r\n   stat_stream.close();\r\n\r\n   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages\r\n   vm_usage     = vsize / 1024.0;\r\n   resident_set = rss * page_size_kb;\r\n}\r\nusing std::cout;\r\n   using std::endl;\r\n\r\n int main()\r\n {', 'std::cout << "Hello World!" << std::endl;', '   double vm, rss;\r\n   process_mem_usage(vm, rss);\r\n   cout << "VM: " << vm << "; RSS: " << rss << endl;\r\nreturn 0;}'),
(10, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i;  cout << "Please see an integer value: ";  cout << i; cout << "The value you entered is " << i;  cout << " and its double is " << i*2 << ".\n";', 'return 0;}'),
(11, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i;  cout << "Please see an integer value: ";  cout << i; cout << "The value you entered is " << i;  cout << " and its double is " << i*2 << ".\n";', 'return 0;}'),
(12, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i;  cout << "Please see an integer value: ";  cout << i; cout << "The value you entered is " << i;  cout << " and its double is " << i*2 << ".\n";', 'return 0;}'),
(13, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i;  cout << "Please see an integer value: ";  cout << i; cout << "The value you entered is " << i;  cout << " and its double is " << i*2 << ".\n";', 'return 0;}'),
(14, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i;  cout << "Please see an integer value: ";  cout << i; cout << "The value you entered is " << i;  cout << " and its double is " << i*2 << ".\n";', 'return 0;}'),
(20, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i; cout Â« "Please see an integer value: "; cout Â« i; cout Â« "The value you entered is " Â« i; cout Â« " and its double is " Â« i*2 Â« ".\n";', 'return 0;}'),
(22, 'test example', 'function(int false){\n', 'hff', '}\n'),
(24, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i; cout Â« "Please see an integer value: "; cout Â« i; cout Â« "The value you entered is " Â« i; cout Â« " and its double is " Â« i*2 Â« ".\n";', 'return 0;}'),
(25, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i; cout Â« "Please see an integer value: "; cout Â« i; cout Â« "The value you entered is " Â« i; cout Â« " and its double is " Â« i*2 Â« ".\n";', 'return 0;}'),
(28, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-3 22:42:22', NULL),
(29, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-3 22:45:5', NULL),
(30, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-4 10:23:48', NULL),
(31, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-4 10:24:33', NULL),
(32, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-4 10:27:52', NULL),
(200, 'some code2', ' #include <iostream> \n using namespace std;\nint main () {', 'int i; cout Â« "Please see an integer value: "; cout Â« i; cout Â« "The value you entered is " Â« i; cout Â« " and its double is " Â« i*2 Â« ".\n";', 'return 0;}'),
(201, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(int false){\n', 'hff', '}\nint main(){\n(falsefalse);}'),
(202, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(int ){\n', 'hff', '}\nint main(){\n();}'),
(204, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(float x){\n', 'hff', '}\nint main(){\n(2);}'),
(205, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(float x){\n', 'hff', '}\nint main(){\nfunction(2);}');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
