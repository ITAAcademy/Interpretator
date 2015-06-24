-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Июн 24 2015 г., 13:36
-- Версия сервера: 5.5.43-0ubuntu0.14.04.1
-- Версия PHP: 5.5.9-1ubuntu4.9

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
-- Структура таблицы `Assignment`
--

CREATE TABLE IF NOT EXISTS `Assignment` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `Assignment`
--

INSERT INTO `Assignment` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(1, 'hello world', '#include <iostream> \r\n int main()\r\n {', 'std::cout << "Hello World!" << std::endl;', 'return 0;}'),
(2, 'pcount(): reports th', '#include <strstream>\r\n#include <iostream>\r\nusing namespace std;\r\nint main()\r\n{', ' char str[80];ostrstream outs(str, sizeof(str));\r\n  outs << "abcdefg ";\r\n  outs << 27 << " "  << 890.23;\r\n  outs << ends;  // null terminate\r\n  cout << "chars in outs: "<< outs.pcount(); // \r\n  cout << " " << str;', ' return 0;}'),
(3, 'cout: output hex', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', ' cout << hex << 100 << endl;  cout << setfill(''?'') << setw(10) << 2343.0;', 'return 0;}'),
(4, 'Set cout: hex and ba', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', 'cout.setf(ios::hex, ios::basefield);\r\n  cout << 100 << endl;                  // cout 100 in hex\r\n  cout.fill(''?'');\r\n  cout.width(10);\r\n  cout << 2343.0;', 'return 0;}'),
(5, 'cout: uppercase,show', '#include <iostream>\r\nusing namespace std;\r\nint main() {', 'cout.unsetf(ios::dec);\r\n  cout.setf(ios::uppercase | ios::showbase | ios::hex);\r\n  cout << 88 << ''\n'';\r\n  cout.unsetf(ios::uppercase);\r\n  cout << 88 << ''\n'';', 'return 0;}'),
(6, 'Defines your own ter', '#include <iostream>\r\n#include <cstdlib>\r\n#include <exception>\r\nusing namespace std;\r\nvoid myTerminator() {\r\n  cout << "Your own terminate handler\n";\r\n  abort();\r\n}\r\nint main() {', 'set_terminate(myTerminator);   \r\n  try {\r\n    cout << "Inside try block.";\r\n    throw 100; \r\n  }\r\n  catch (double i) { }', 'return 0;}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}');

-- --------------------------------------------------------

--
-- Структура таблицы `History`
--

CREATE TABLE IF NOT EXISTS `History` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(20) DEFAULT NULL,
  `code` varchar(512) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=247 ;

--
-- Дамп данных таблицы `History`
--

INSERT INTO `History` (`ID`, `ip`, `code`, `date_time`) VALUES
(1, '123', '123', '2015-06-02 00:00:00'),
(242, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-23 21:22:22'),
(243, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-23 21:26:37'),
(244, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:28:13'),
(245, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:57:14'),
(246, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:57:35');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
