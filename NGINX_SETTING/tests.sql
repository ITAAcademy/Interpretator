-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Ноя 27 2015 г., 14:59
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
-- Структура таблицы `tests`
--

CREATE TABLE IF NOT EXISTS `tests` (
  `task_id` int(11) NOT NULL,
  `json` text NOT NULL,
  PRIMARY KEY (`task_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `tests`
--

INSERT INTO `tests` (`task_id`, `json`) VALUES
(437, '{"args":[[1],2],"etalon":"...","lang":"c++","operation":"add_tests","return_val":[1,2],"signature":{"return type":1,"types":[0,0,0,1,1,2,3]},"task":437}\n');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
