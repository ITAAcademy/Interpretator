-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Ноя 24 2015 г., 22:05
-- Версия сервера: 5.5.46-0ubuntu0.14.04.2
-- Версия PHP: 5.5.9-1ubuntu4.14

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
-- Структура таблицы `tests_signatures`
--

CREATE TABLE IF NOT EXISTS `tests_signatures` (
  `task_id` int(11) NOT NULL,
  `lang` text NOT NULL,
  `signature` text NOT NULL,
  `etalon` text NOT NULL,
  PRIMARY KEY (`task_id`),
  UNIQUE KEY `task_id` (`task_id`),
  KEY `task_id_2` (`task_id`),
  KEY `task_id_3` (`task_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `tests_signatures`
--

INSERT INTO `tests_signatures` (`task_id`, `lang`, `signature`, `etalon`) VALUES
(408, 'c++', '{"alpha":"1","beta":"2"}\n', '...'),
(409, 'c++', '{"alpha":"1","beta":"2"}\n', '...'),
(410, 'c++', '{"return type":1,"types":[0,0,0,1,1,2,3]}\n', '...');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
