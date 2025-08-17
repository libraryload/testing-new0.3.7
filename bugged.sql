-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 16, 2023 at 10:08 PM
-- Server version: 10.4.24-MariaDB
-- PHP Version: 7.4.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bugged`
--

-- --------------------------------------------------------

--
-- Table structure for table `atms`
--

CREATE TABLE `atms` (
  `atmId` int(11) NOT NULL,
  `atmPosX` float NOT NULL,
  `atmPosY` float NOT NULL,
  `atmPosZ` float NOT NULL,
  `atmPosRotX` float NOT NULL,
  `atmPosRotY` float NOT NULL,
  `atmPosRotZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `atms`
--

INSERT INTO `atms` (`atmId`, `atmPosX`, `atmPosY`, `atmPosZ`, `atmPosRotX`, `atmPosRotY`, `atmPosRotZ`) VALUES
(1, 1497.75, -1749.87, 15.0882, 0, 0, 177.381),
(2, 2139.45, -1164.08, 23.6351, 0, 0, 91.3095),
(3, 2093.51, -1359.55, 23.6273, 0, 0, 0),
(4, 1795.71, -1164.84, 23.3281, 0, 0, 346.134),
(5, 1482.78, -1010.34, 26.4866, 0, 0, 0),
(6, 1460.07, -1135.88, 23.4967, 0, 0, 40.2302),
(7, 999.713, -914.554, 41.8281, 0, 0, 268.942),
(8, 691.082, -618.562, 15.9788, 0, 0, 268.691),
(9, 651.193, -520.488, 15.9788, 0, 0, 0),
(10, 565.689, -1293.93, 16.7482, 0, 0, 189.384),
(11, 387.166, -1816.05, 7.48341, 0, 0, 272.48),
(12, 1155.62, -1464.91, 15.4432, 0, 0, 290.21),
(13, 2065.44, -1897.55, 13.1967, 0, 0, 0),
(14, 2105.45, -1802.95, 13.0547, 0, 0, 275.634),
(15, 1832.76, -1835.06, 13.0781, 0, 0, 268.293),
(16, 2228.39, -1707.78, 13.25, 0, 0, 270),
(17, 1928.61, -1779.85, 13.1866, 0, 0, 88),
(18, 2324.4, -1644.94, 14.4699, 0, 0, 0),
(19, 1366.65, -1284.45, 13.0469, 0, 0, 283.959),
(20, 2316.1, -88.5226, 26.1273, 0, 0, 0),
(21, 2303.46, -13.5396, 26.1273, 0, 0, 272.435),
(22, 1260.88, 209.302, 19.1976, 0, 0, 65.5046),
(23, 1275.8, 368.315, 19.1976, 0, 0, 73.7599),
(24, 173.235, -155.076, 1.22102, 0, 0, 89.73),
(25, 45.7804, -291.809, 1.5024, 0, 0, 182.934),
(26, 2019.56, 1002.4, 10.3203, 0, 0, 99.9361),
(27, 2173.7, 1395.76, 10.5625, 0, 0, 270.491),
(28, 2631.46, 1129.53, 10.6797, 0, 0, 2.4883),
(29, 2102.31, 2261.01, 10.5234, 0, 0, 91.8659),
(30, 2001.57, 1547.05, 13.0859, 0, 0, 87.7158);

-- --------------------------------------------------------

--
-- Table structure for table `bans`
--

CREATE TABLE `bans` (
  `ID` int(11) NOT NULL,
  `PlayerName` varchar(30) NOT NULL,
  `AdminName` varchar(30) NOT NULL,
  `Reason` varchar(128) NOT NULL,
  `IP` varchar(16) NOT NULL,
  `Days` int(11) NOT NULL,
  `IPBan` int(11) NOT NULL,
  `Permanent` int(11) NOT NULL,
  `Time` int(15) NOT NULL,
  `BanTimeDate` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE current_timestamp(),
  `Active` int(11) NOT NULL,
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `bans`
--

INSERT INTO `bans` (`ID`, `PlayerName`, `AdminName`, `Reason`, `IP`, `Days`, `IPBan`, `Permanent`, `Time`, `BanTimeDate`, `Active`, `updated_at`, `created_at`) VALUES
(1, 'InViknoixX', 'DraveN', 'Reclama', '79.113.135.169', 0, 1, 1, 0, '2021-02-23 18:50:31', 1, '2021-02-23 18:50:31', '2021-02-23 18:50:31'),
(2, 'InViknoix', 'Sonikss', 'reclama de pe alte conturi', '0', 0, 0, 1, 0, '2021-02-23 18:52:21', 1, '2021-02-23 18:52:21', '2021-02-23 18:52:21'),
(3, 'Waller', 'Sonikss', 'reclama', '86.127.23.24', 0, 0, 1, 0, '2021-02-23 18:54:14', 1, '2021-02-23 18:54:14', '2021-02-23 18:54:14'),
(4, 'Waller.BanatAiurea', 'qAlbert', 'Cheats (TP-Hack)', '86.127.23.24', 0, 0, 1, 0, '2021-02-23 19:05:38', 1, '2021-02-23 19:05:38', '2021-02-23 19:05:38'),
(5, 'ClaudiuPE', 'Sonikss', 'injurii server', '46.97.168.9', 10, 0, 0, 1614973573, '2021-02-23 19:47:35', 0, '2021-02-23 19:46:47', '2021-02-23 19:46:47'),
(6, 'Mos.Craciun', 'DraveN', 'Injurii server.', '92.115.151.128', 10, 0, 0, 1614973582, '2023-09-17 18:16:43', 0, '2021-02-23 19:46:55', '2021-02-23 19:46:55'),
(7, 'Sonikss', 'AdmBot', 'invalid client data #1', '90.95.131.107', 90, 0, 0, 1621942945, '2021-02-24 11:52:02', 0, '2021-02-24 11:42:58', '2021-02-24 11:42:58');

-- --------------------------------------------------------

--
-- Table structure for table `bizz`
--

CREATE TABLE `bizz` (
  `ID` int(11) NOT NULL,
  `OwnerSQL` int(11) NOT NULL,
  `Type` int(11) NOT NULL,
  `Static` int(11) NOT NULL,
  `OwnerName` varchar(24) NOT NULL DEFAULT 'AdmBot',
  `PosX` float NOT NULL,
  `PosY` float NOT NULL,
  `PosZ` float NOT NULL,
  `Message` varchar(16) NOT NULL DEFAULT 'localhost.ro',
  `secPosX` float NOT NULL,
  `secPosY` float NOT NULL,
  `secPosZ` float NOT NULL,
  `bizMoney` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `bizz`
--

INSERT INTO `bizz` (`ID`, `OwnerSQL`, `Type`, `Static`, `OwnerName`, `PosX`, `PosY`, `PosZ`, `Message`, `secPosX`, `secPosY`, `secPosZ`, `bizMoney`) VALUES
(1, 0, 1, 0, 'AdmBot', 1462.33, -1010.18, 26.844, 'localhost.ro', 0, 0, 0, 0),
(2, 0, 2, 0, 'AdmBot', 1368.89, -1279.84, 13.547, 'localhost.ro', 0, 0, 0, 2500),
(3, 0, 3, 0, 'AdmBot', 1836.95, -1682.5, 13.327, 'localhost.ro', 0, 0, 0, 0),
(4, 0, 4, 0, 'AdmBot', 1928.58, -1776.36, 13.547, 'localhost.ro', 0, 0, 0, 0),
(5, 0, 7, 0, 'AdmBot', 2419.8, -1508.95, 24, 'localhost.ro', 0, 0, 0, 0),
(6, 0, 8, 0, 'AdmBot', 2244.35, -1665.56, 15.477, 'localhost.ro', 0, 0, 0, 0),
(7, 0, 4, 0, 'AdmBot', 1000.59, -919.89, 42.328, 'localhost.ro', 0, 0, 0, 1500),
(8, 0, 5, 0, 'AdmBot', 1199.28, -918.14, 43.123, 'localhost.ro', 0, 0, 0, 0),
(9, 0, 5, 0, 'AdmBot', 810.485, -1616.17, 13.547, 'localhost.ro', 0, 0, 0, 0),
(10, 0, 8, 0, 'AdmBot', 499.514, -1360.63, 16.369, 'localhost.ro', 0, 0, 0, 0),
(11, 0, 8, 0, 'AdmBot', 1456.48, -1137.6, 23.948, 'localhost.ro', 0, 0, 0, 0),
(12, 0, 10, 1, 'AdmBot', 485.356, -1733.82, 11.096, 'localhost.ro', 487.353, -1740.8, 11.132, 2000),
(13, 0, 10, 1, 'AdmBot', 1034.45, -1028.23, 32.102, 'localhost.ro', 1024.95, -1024.51, 32.102, 2000),
(14, 0, 10, 1, 'AdmBot', 2072.07, -1828.43, 13.555, 'localhost.ro', 2065.58, -1831.47, 13.547, 2000),
(15, 0, 10, 1, 'AdmBot', 723.278, -463.247, 16.336, 'localhost.ro', 720.213, -457.703, 16.336, 0),
(16, 0, 11, 1, 'AdmBot', 1044.9, -1026.44, 32.102, 'localhost.ro', 1041.43, -1019.07, 32.108, 0),
(17, 0, 11, 1, 'AdmBot', 2649.49, -2040.05, 13.55, 'localhost.ro', 2644.81, -2043.34, 13.62, 0),
(18, 0, 12, 1, 'AdmBot', 1004.01, -937.541, 42.328, 'localhost.ro', 0, 0, 0, 0),
(19, 0, 12, 1, 'AdmBot', 655.68, -567.399, 16.336, 'localhost.ro', 0, 0, 0, 0),
(20, 0, 12, 1, 'AdmBot', 1940.93, -1772.84, 13.641, 'localhost.ro', 0, 0, 0, 0),
(21, 0, 4, 0, 'AdmBot', 1352.38, -1759.25, 13.508, 'localhost.ro', 0, 0, 0, 0),
(22, 0, 13, 1, 'AdmBot', 1170.1, -1489.72, 22.756, 'localhost.ro', 0, 0, 0, 0),
(23, 0, 14, 1, 'AdmBot', 517.614, -1295.88, 17.242, 'localhost.ro', 559.01, -1283.88, 17.248, 0),
(24, 0, 2, 0, 'AdmBot', 1791.83, -1163.12, 23.828, 'localhost.ro', 0, 0, 0, 0),
(25, 0, 3, 0, 'AdmBot', 2310.04, -1643.49, 14.827, 'localhost.ro', 0, 0, 0, 0),
(26, 0, 1, 0, 'AdmBot', 2196.78, 1677.18, 12.367, 'localhost.ro', 0, 0, 0, 0),
(27, 0, 2, 0, 'AdmBot', 2556.92, 2065.38, 11.1, 'localhost.ro', 0, 0, 0, 0),
(28, 0, 4, 0, 'AdmBot', 2637.33, 1129.68, 11.18, 'localhost.ro', 0, 0, 0, 0),
(29, 0, 12, 1, 'AdmBot', 2116.53, 925.196, 10.961, 'localhost.ro', 0, 0, 0, 0),
(30, 0, 5, 0, 'AdmBot', 2472.87, 2034.21, 11.063, 'localhost.ro', 0, 0, 0, 0),
(31, 0, 8, 0, 'AdmBot', 2101.89, 2257.37, 11.023, 'localhost.ro', 0, 0, 0, 0),
(32, 0, 5, 0, 'AdmBot', 1872.25, 2071.85, 11.063, 'localhost.ro', 0, 0, 0, 0),
(33, 0, 5, 0, 'AdmBot', 2169.41, 2795.89, 10.82, 'localhost.ro', 0, 0, 0, 0),
(34, 0, 12, 1, 'AdmBot', 1594.52, 2204.3, 11.061, 'localhost.ro', 0, 0, 0, 0),
(35, 0, 4, 0, 'AdmBot', 1599.14, 2221.79, 11.063, 'localhost.ro', 0, 0, 0, 0),
(36, 0, 4, 0, 'AdmBot', 2546.5, 1972.67, 10.82, 'localhost.ro', 0, 0, 0, 1500),
(37, 0, 8, 0, 'AdmBot', 1657.04, 1733.33, 10.828, 'localhost.ro', 0, 0, 0, 0),
(38, 0, 14, 1, 'AdmBot', 2200.75, 1394.81, 11.063, 'localhost.ro', 2150.29, 1393.94, 10.82, 0),
(39, 0, 9, 0, 'AdmBot', 2019.32, 1007.75, 10.82, 'localhost.ro', 0, 0, 0, 0),
(40, 0, 13, 1, 'AdmBot', 2085.67, 2066.65, 11.058, 'localhost.ro', 0, 0, 0, 0),
(41, 0, 10, 1, 'AdmBot', 1967.7, 2158.27, 10.82, 'localhost.ro', 1975.43, 2162.5, 11.07, 0),
(42, 0, 12, 1, 'AdmBot', 2197.19, 2476.53, 10.995, 'localhost.ro', 0, 0, 0, 0),
(43, 0, 4, 0, 'AdmBot', 2187.71, 2469.65, 11.242, 'localhost.ro', 0, 0, 0, 0),
(44, 0, 2, 0, 'AdmBot', 776.721, 1871.43, 4.907, 'localhost.ro', 0, 0, 0, 0),
(45, 0, 12, 1, 'AdmBot', 615.105, 1693.11, 7.188, 'localhost.ro', 0, 0, 0, 0),
(46, 0, 7, 0, 'AdmBot', 172.973, 1177.19, 14.758, 'localhost.ro', 0, 0, 0, 0),
(47, 0, 10, 1, 'AdmBot', -90.965, 1118.37, 20.786, 'localhost.ro', -99.935, 1118.59, 19.742, 0),
(48, 0, 5, 0, 'AdmBot', 1157.92, 2072.21, 11.063, 'localhost.ro', 0, 0, 0, 0),
(49, 0, 11, 1, 'AdmBot', 2381.57, 1042.88, 10.82, 'localhost.ro', 2387.03, 1049.61, 10.82, 0),
(50, 0, 6, 0, 'AdmBot', 1968.77, 2295.87, 16.456, 'localhost.ro', 0, 0, 0, 0),
(51, 0, 12, 1, 'AdmBot', -2246.12, -2558.29, 32.07, 'localhost.ro', 0, 0, 0, 0),
(52, 0, 7, 0, 'AdmBot', -2155.31, -2460.16, 30.852, 'localhost.ro', 0, 0, 0, 0),
(53, 0, 4, 0, 'AdmBot', -2165.77, -2416.7, 30.828, 'localhost.ro', 0, 0, 0, 0),
(54, 0, 8, 0, 'AdmBot', -2168.79, -2351.83, 30.644, 'localhost.ro', 0, 0, 0, 0),
(55, 0, 2, 0, 'AdmBot', -2093.7, -2464.92, 30.625, 'localhost.ro', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `cars`
--

CREATE TABLE `cars` (
  `ID` int(11) NOT NULL,
  `Model` int(11) NOT NULL,
  `Locationx` float NOT NULL,
  `Locationy` float NOT NULL,
  `Locationz` float NOT NULL,
  `Angle` float NOT NULL,
  `LastLocationx` float NOT NULL,
  `LastLocationy` float NOT NULL,
  `LastLocationz` float NOT NULL,
  `LastAngle` float NOT NULL,
  `ColorOne` int(11) NOT NULL,
  `ColorTwo` int(11) NOT NULL,
  `Owner` varchar(25) NOT NULL DEFAULT 'Dealership',
  `Value` int(20) NOT NULL,
  `License` varchar(14) NOT NULL DEFAULT 'NewCar',
  `Description` varchar(50) NOT NULL,
  `Lockk` int(3) NOT NULL,
  `Inscarprice` int(11) NOT NULL DEFAULT 5000,
  `Insurancecar` int(11) NOT NULL,
  `KM` float NOT NULL,
  `Fuel` int(11) NOT NULL DEFAULT 100,
  `Owned` int(11) NOT NULL,
  `Spawned` int(11) NOT NULL,
  `Sell` int(11) NOT NULL,
  `PaintJ` int(24) NOT NULL DEFAULT 6,
  `BuyTime` int(11) NOT NULL,
  `VIP` int(11) NOT NULL,
  `VIPText` varchar(16) NOT NULL,
  `VIPColor` varchar(6) NOT NULL DEFAULT 'FFFFFF',
  `VIPPos` varchar(72) NOT NULL DEFAULT '0.0 0.0 0.0 0.0 0.0 0.0',
  `Special` int(11) NOT NULL,
  `Spoiler` int(11) NOT NULL,
  `FuelTank` int(11) NOT NULL DEFAULT 100,
  `Neon` int(11) NOT NULL,
  `Health` float NOT NULL DEFAULT 1000,
  `DamageStatus` varchar(32) NOT NULL DEFAULT '0 0 0 0',
  `Mod` varchar(72) NOT NULL DEFAULT '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cars`
--

-- --------------------------------------------------------

--
-- Table structure for table `emails`
--

CREATE TABLE `emails` (
  `ID` int(11) NOT NULL,
  `iPlayer` int(11) NOT NULL,
  `sMessage` varchar(256) NOT NULL,
  `iTimestamp` int(11) NOT NULL,
  `iReadStatus` int(11) NOT NULL,
  `DeliverStatus` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `emails`
--

INSERT INTO `emails` (`ID`, `iPlayer`, `sMessage`, `iTimestamp`, `iReadStatus`, `DeliverStatus`) VALUES
(1, 1, 'bine ai bvenit', 1637886160, 1, 1),
(2, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1658868739, 1, 1),
(3, 4, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1658868807, 1, 1),
(4, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1658870213, 1, 1),
(5, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1669488754, 1, 1),
(6, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1695153432, 1, 1),
(7, 1, 'Ai primit mute de la adminul ionchyAdv pentru 10 minute, motiv: test.', 1695153463, 1, 1),
(8, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1695313013, 1, 1),
(9, 1, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1695313677, 1, 1),
(10, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Vagos (rank 6) dupa 437 zile, fara FP. Motiv: Renuntare la functie..', 1695329196, 1, 1),
(11, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Vagos (rank 6) dupa 437 zile, fara FP. Motiv: test.', 1695329376, 1, 1),
(12, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 1) dupa 437 zile, fara FP. Motiv: Renuntare la functie..', 1695329523, 1, 1),
(13, 1, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 7) dupa 437 zile, fara FP. Motiv: test.', 1695329866, 1, 1),
(14, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 1) dupa 0 zile, cu 100 FP. Motiv: Abuz de functie..', 1695332529, 0, 1),
(15, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 1) dupa 1 zile, cu 100 FP. Motiv: Abuz de functie..', 1695332682, 0, 1),
(16, 2, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 1) dupa 1 zile, fara FP. Motiv: test.', 1695332754, 1, 1),
(17, 0, 'Nivelul tau de wanted a fost modificat (+2) pentru ca te-ai deconectat in timp ce erai urmarit de politie.', 1695377973, 0, 0),
(18, 1, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 7) dupa 439 zile, fara FP. Motiv: 0.', 1695566304, 1, 1),
(19, 1, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 1) dupa 1 zile, fara FP. Motiv: Pa.', 1695566746, 1, 1),
(20, 1, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte Los Santos Police Department (rank 7) dupa 1 zile, fara FP. Motiv: Pa.', 1695587649, 1, 0),
(21, 1, 'Ai fost demis de Admin ionchyAdv din factiunea din care faceai parte National Guard (rank 7) dupa 1 zile, fara FP. Motiv: TEst.', 1695804403, 1, 0),
(22, -1, 'Licitatii: Suma de 0.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696667579, 0, 0),
(23, -1, 'Licitatii: Suma de 0.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696667635, 0, 0),
(24, 5, 'Licitatii: Suma de 1.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696667659, 1, 0),
(25, -1, 'Licitatii: Suma de $0.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696667898, 0, 0),
(26, 5, 'Licitatii: Suma de $1.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696667903, 1, 0),
(27, -1, 'Licitatii: Suma de $0.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696668007, 0, 0),
(28, -1, 'Licitatii: Suma de $0.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696668542, 0, 0),
(29, 5, 'Licitatii: Suma de $5.000.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.', 1696670127, 1, 0);

-- --------------------------------------------------------

--
-- Table structure for table `factionlog`
--

CREATE TABLE `factionlog` (
  `ID` int(11) NOT NULL,
  `factionid` int(11) NOT NULL,
  `player` int(11) NOT NULL,
  `leader` int(11) NOT NULL,
  `action` varchar(256) NOT NULL,
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE current_timestamp(),
  `deleted` int(11) NOT NULL,
  `type` int(11) NOT NULL DEFAULT 1
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `factionlog`
--

INSERT INTO `factionlog` (`ID`, `factionid`, `player`, `leader`, `action`, `time`, `deleted`, `type`) VALUES
(1, 1, 3, 1, 'testezcodiDreamer [user:3] has joined the group Los Santos Police Department (invited by ionchyAdv[user:1]).', '0000-00-00 00:00:00', 0, 1),
(2, 1, 5, 1, 'ireplay [user:5] has joined the group Los Santos Police Department (invited by ionchyAdv[user:1]).', '0000-00-00 00:00:00', 0, 1),
(3, 1, 2, 1, 'iDreamer [user:2] has joined the group Los Santos Police Department (invited by ionchyAdv[user:1]).', '0000-00-00 00:00:00', 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `factions`
--

CREATE TABLE `factions` (
  `ID` int(11) NOT NULL,
  `Name` varchar(50) NOT NULL,
  `X` float NOT NULL,
  `Y` float NOT NULL,
  `Z` float NOT NULL,
  `eX` float NOT NULL DEFAULT 0,
  `eY` float NOT NULL DEFAULT 0,
  `eZ` float NOT NULL DEFAULT 0,
  `SafePos1` float NOT NULL DEFAULT 0,
  `SafePos2` float NOT NULL DEFAULT 0,
  `SafePos3` float NOT NULL DEFAULT 0,
  `Interior` int(5) NOT NULL DEFAULT 0,
  `Virtual` int(5) NOT NULL DEFAULT 0,
  `PickupID` int(11) NOT NULL DEFAULT 1239,
  `MapIcon` int(11) NOT NULL DEFAULT 0,
  `Locked` int(2) NOT NULL DEFAULT 0,
  `Mats` int(11) NOT NULL,
  `Drugs` int(11) NOT NULL,
  `Bank` int(11) NOT NULL,
  `Anunt` varchar(128) NOT NULL,
  `Win` int(11) NOT NULL DEFAULT 0,
  `Lost` int(11) NOT NULL DEFAULT 0,
  `MaxMembers` int(11) NOT NULL DEFAULT 10,
  `MinLevel` int(3) NOT NULL DEFAULT 5,
  `Application` int(11) NOT NULL DEFAULT 0,
  `Rank1` varchar(64) NOT NULL DEFAULT 'Rank1',
  `Rank2` varchar(64) NOT NULL DEFAULT 'Rank2',
  `Rank3` varchar(64) NOT NULL DEFAULT 'Rank3',
  `Rank4` varchar(64) NOT NULL DEFAULT 'Rank4',
  `Rank5` varchar(64) NOT NULL DEFAULT 'Rank5',
  `Rank6` varchar(64) NOT NULL DEFAULT 'Rank6',
  `Rank7` varchar(64) NOT NULL DEFAULT 'Rank7'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `factions`
--

INSERT INTO `factions` (`ID`, `Name`, `X`, `Y`, `Z`, `eX`, `eY`, `eZ`, `SafePos1`, `SafePos2`, `SafePos3`, `Interior`, `Virtual`, `PickupID`, `MapIcon`, `Locked`, `Mats`, `Drugs`, `Bank`, `Anunt`, `Win`, `Lost`, `MaxMembers`, `MinLevel`, `Application`, `Rank1`, `Rank2`, `Rank3`, `Rank4`, `Rank5`, `Rank6`, `Rank7`) VALUES
(1, 'Los Santos Police Department', 246.869, 62.8318, 1003.64, 1554.83, -1675.61, 16.1953, 256.983, 64.637, 1003.64, 6, 0, 1247, 30, 0, 708250, 237, 127600, 'muie replay', 0, 0, 5, 7, 1, 'Cadet', 'Officer', 'Sergeant', 'Inspector', 'Captain', 'Sub-Chestor LSPD', 'Master'),
(2, 'Federal Bureau of Investigations', 246.579, 107.928, 1003.22, 627.616, -571.792, 17.6242, 256.68, 120.442, 1003.22, 10, 22, 1247, 30, 1, 45501, 42, 27000, 'Liberi!', 0, 0, 5, 7, 1, 'Trial Agent', 'Special Agent', 'Special Advisor', 'Main Inspector', 'Executive Chief', 'Consultant of Leader', 'Chestor F.B.I.'),
(3, 'National Guard', 288.771, 166.975, 1007.17, 200.766, 1869.49, 13.147, 289.125, 187.97, 1007.18, 3, 1003, 1247, 30, 1, 35400, 163, 6000, 'Duminica 20:30 Sedinta obligatorie!! Raportul sa il aveti facut!', 0, 0, 5, 7, 1, 'National Guard Soldat', 'National Guard Sergent', 'National Guard Maior ', 'National Guard Locotenent', 'National Guard Comandat', 'National Guard Sub-Chestor', 'National Guard Chestor'),
(4, 'Los Aztecas', 2544.7, -1305.07, 1054.64, 1456.74, 2773.34, 10.8203, 2546.8, -1281.24, 1060.98, 2, 1, 1254, 0, 0, 384841, 1101, 7920702, 'Maine 8.03 zi de war! Toti HQ la 19:45! ', 0, 0, 10, 6, 1, 'Kaikei', 'Shatei', 'Kyodai', 'Saiko-Komon', 'Shateigashira', 'Wakagashira', 'Oyabun'),
(5, 'Crips Gang', 2544.7, -1305.07, 1054.64, 2495.33, -1690.67, 14.7656, 2546.8, -1281.11, 1060.98, 2, 2, 1254, 0, 1, 1475400, 1545, 122600, 'Vã puteti apuca de raport. Raportul este de 35k materiale, succes!', 0, 0, 10, 6, 1, 'Baby Gangsta`', 'O.G Gangsta', 'Advanced Gangsta.', 'Crip Afilliate', 'Big Boss`', 'Right Hand o` Crip', 'The Master o` Crips'),
(6, 'Los Vagos', 2544.7, -1305.07, 1054.64, 725.677, -1440.45, 13.5391, 2546.84, -1280.94, 1060.98, 2, 3, 1254, 0, 1, 1641649, 1373, 42700, 'SEDINTA SAMBATA ORA 15:00, CINE NU ARE 50,000 MATS UNINVITE!, CINE NU VINE UNINVITE!', 0, 0, 10, 6, 1, '[1] New Magnific', '[2] Advanced', '[3] Gangsta', '[4] Magnific Terror', '[5] One Of The Best', '[6] Lord Of Vagos', '[7] King Of Vagos'),
(7, 'None', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1239, 0, 1, 0, 0, 0, 'None', 0, 0, 10, 0, 0, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7'),
(8, 'Las Venturas Police Department', 246.869, 62.8318, 1003.64, 2287.1, 2431.8, 10.8203, 256.965, 64.732, 1003.64, 6, 3, 1247, 30, 0, 0, 0, 13000, 'Duminica ora 17:00 avem sedinta (Obligatorie) in cadrul factiunii pentru a discuta.', 0, 0, 5, 7, 0, 'Cadet', 'Officer', 'Sergeant', 'Inspector', 'Captain', 'Lord Of Police', 'God Of Police'),
(9, 'News Reporters', 1700.93, -1668.17, 20.2188, -329.526, 1536.78, 76.6117, 1722.83, -1673.18, 20.223, 18, 1, 1239, 0, 1, 10499, 0, 715984, 'Sedinta in fiecare weekend.', 0, 0, 10, 3, 1, 'Reporter', 'Jurnalist', 'Editor', 'Redactor', 'Manager', 'News Reporters Co-Owner', 'News Reporters Owner'),
(10, 'Ballas', 2544.7, -1305.07, 1054.64, 1455.27, 750.868, 11.0234, 2546.82, -1280.94, 1060.98, 2, 4, 1254, 0, 1, 4699682, 783, 13679330, 'Felicitari,Mafioti mei Enjoy', 0, 0, 10, 6, 1, 'Street Fish', 'City Fish', 'Small Pimp', 'Pimp', 'Small Pimp', 'Under-Pimp', 'Pimp'),
(11, 'Hitman Agency', 288.771, 166.975, 1007.17, 1081.18, -345.398, 73.9825, 289.274, 187.555, 1007.18, 3, 11, 1239, 0, 1, 39364112, 100, 81000, 'Bine ati venit in \'Hitman Agency\'', 0, 0, 10, 10, 1, 'NewsAssasin', 'Contract Killer', 'Camper', 'ProfessionalKiller', 'Ghost', 'Vice-Director', 'Director'),
(12, 'School Instructors LV', 1700.93, -1668.17, 20.2188, 2435.31, 1671.01, 10.8203, 1700.88, -1648.06, 20.219, 18, 3, 1239, 0, 1, 1300, 0, 1767191, 'Sedinta In Fiecare Duminica Ora 17:00', 0, 0, 10, 3, 1, 'LV Instructor Trainee', 'LV Instructor Member', 'LV Instructor Advanced', 'LV Instructor Skilled', 'LV Instructor Master', 'LV Assistant Boss', 'LV Boss'),
(13, 'Taxi', 1727.01, -1638.22, 20.2231, 1753.2, -1903.28, 13.5633, 1722.66, -1672.89, 20.223, 18, 2, 1239, 0, 1, 35399, 1, 5699719, 'Sedinta Duminica ora 17:00 !! :I comanda de accept e /taxi accept si id', 0, 0, 10, 3, 1, 'New Driver', 'Junior Driver', 'Expert Driver', 'Head Driver', 'Tester', 'Seful Vostru', 'Owner Taxi LS'),
(14, 'Las Venturas Paramedic Department', 288.771, 166.975, 1007.17, 1614.92, 1816.1, 10.8203, 289.11, 188.051, 1007.18, 3, 14, 1239, 22, 1, 10400, 10, 609788, 'Sedinta este pe data de 20.03.2017 la ora 20:00.Sedinta este obligatorie!', 0, 0, 10, 3, 1, 'Paramedic Stagiar', 'Paramedic Rezident', 'Paramedic Chirurg', 'Paramedic Specialist', 'Paramedic Primar', 'Deputy Chief Paramedic', 'Chief Paramedic');

-- --------------------------------------------------------

--
-- Table structure for table `faction_logs`
--

CREATE TABLE `faction_logs` (
  `id` int(11) NOT NULL,
  `player` int(11) NOT NULL,
  `leader` int(11) NOT NULL,
  `Text` text NOT NULL,
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE current_timestamp(),
  `deleted` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `faction_logs`
--

INSERT INTO `faction_logs` (`id`, `player`, `leader`, `Text`, `time`, `deleted`) VALUES
(4, 2, 1, 'iDreamer was uninvited by Admin ionchyAdv from faction Los Santos Police Department (rank 1) after 1 days, without FP. Reason: test.', '0000-00-00 00:00:00', 0),
(8, 1, 1, 'ionchyAdv was uninvited by Admin ionchyAdv from faction National Guard (rank 7) after 1 days, without FP. Reason: TEst.', '0000-00-00 00:00:00', 0);

-- --------------------------------------------------------

--
-- Table structure for table `houses`
--

CREATE TABLE `houses` (
  `ID` int(11) NOT NULL,
  `Type` int(11) NOT NULL,
  `OwnerSQL` int(11) NOT NULL,
  `OwnerName` varchar(32) NOT NULL DEFAULT 'AdmBot',
  `Description` varchar(24) NOT NULL DEFAULT 'localhost.ro',
  `Interior` int(11) NOT NULL,
  `Locked` int(11) NOT NULL,
  `Rent` int(11) NOT NULL DEFAULT 5000,
  `Rentable` int(11) NOT NULL DEFAULT 1,
  `Safe` int(11) NOT NULL,
  `Radio` int(11) NOT NULL,
  `Level` int(11) NOT NULL DEFAULT 7,
  `Special` int(11) NOT NULL,
  `ExteriorX` float NOT NULL,
  `ExteriorY` float NOT NULL,
  `ExteriorZ` float NOT NULL,
  `InteriorX` float NOT NULL,
  `InteriorY` float NOT NULL,
  `InteriorZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `houses`
--

INSERT INTO `houses` (`ID`, `Type`, `OwnerSQL`, `OwnerName`, `Description`, `Interior`, `Locked`, `Rent`, `Rentable`, `Safe`, `Radio`, `Level`, `Special`, `ExteriorX`, `ExteriorY`, `ExteriorZ`, `InteriorX`, `InteriorY`, `InteriorZ`) VALUES
(1, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 20000, 0, 7, 0, 1421.84, -885.774, 50.67, 377.15, 1417.41, 1081.33),
(2, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1298.47, -799.015, 84.141, 140.17, 1366.07, 1083.65),
(3, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 3200000, 0, 7, 0, 1496.94, -687.958, 95.563, 225.68, 1021.45, 1084.02),
(4, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 1331.95, -632.537, 109.135, 377.15, 1417.41, 1081.33),
(5, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 980.548, -677.225, 121.976, -2636.68, 1402.55, 906.46),
(6, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 827.768, -858.178, 70.331, 446.99, 1397.07, 1084.3),
(7, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 952.467, -910.147, 45.766, -2636.68, 1402.55, 906.46),
(8, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1317.59, -1183.89, 23.592, 140.17, 1366.07, 1083.65),
(9, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1286.44, -1329.26, 13.553, 140.17, 1366.07, 1083.65),
(10, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 726.023, -1276.23, 13.648, 140.17, 1366.07, 1083.65),
(11, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 487.169, -1639.93, 23.703, 140.17, 1366.07, 1083.65),
(12, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 315.79, -1770.15, 4.644, 446.99, 1397.07, 1084.3),
(13, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 192.66, -1769.72, 4.313, 387.22, 1471.7, 1080.19),
(14, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 228.188, -1405.22, 51.609, 446.99, 1397.07, 1084.3),
(15, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 189.864, -1308.32, 70.254, 225.68, 1021.45, 1084.02),
(16, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 219.515, -1250.33, 78.334, -2636.68, 1402.55, 906.46),
(17, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 251.384, -1220.26, 76.102, 140.17, 1366.07, 1083.65),
(18, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 300.193, -1154.4, 81.391, 140.17, 1366.07, 1083.65),
(19, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 850.146, -1520.05, 14.282, 446.99, 1397.07, 1084.3),
(20, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 1154.96, -1180.94, 32.819, 225.68, 1021.45, 1084.02),
(21, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 1684.8, -1343.31, 17.436, -2636.68, 1402.55, 906.46),
(22, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2232.68, -1159.7, 25.891, 387.22, 1471.7, 1080.19),
(23, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 2061.01, -1075.34, 25.679, 446.99, 1397.07, 1084.3),
(24, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2091.55, -1184.74, 27.057, 387.22, 1471.7, 1080.19),
(25, 2, 0, 'AdmBot', 'localhost.ro', 6, 0, 5000, 1, 0, 0, 7, 0, 2230.03, -1280.62, 25.367, -68.81, 1351.21, 1080.21),
(26, 2, 0, 'AdmBot', 'localhost.ro', 6, 0, 5000, 1, 0, 0, 7, 0, 2385.22, -1711.92, 14.242, -68.81, 1351.21, 1080.21),
(27, 2, 0, 'AdmBot', 'localhost.ro', 6, 0, 5000, 1, 0, 0, 7, 0, 2524.21, -1998.35, 14.113, -68.81, 1351.21, 1080.21),
(28, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 1684.72, -2098.78, 13.834, 387.22, 1471.7, 1080.19),
(29, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 1981.45, -1682.82, 17.054, 446.99, 1397.07, 1084.3),
(30, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 1726.96, -1636.41, 20.217, 225.68, 1021.45, 1084.02),
(31, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 1872.24, -1912.18, 15.257, 387.22, 1471.7, 1080.19),
(32, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 1653.8, -1655.85, 22.516, -2636.68, 1402.55, 906.46),
(33, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2260.16, -1019.9, 59.291, 377.15, 1417.41, 1081.33),
(34, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 1093.83, -806.696, 107.419, 2807.48, -1174.76, 1025.57),
(35, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 937.781, -848.236, 93.645, 446.99, 1397.07, 1084.3),
(36, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 1094.97, -647.348, 113.648, 225.68, 1021.45, 1084.02),
(37, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 795.098, -506.57, 18.013, 2807.48, -1174.76, 1025.57),
(38, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 745.263, -556.453, 18.013, 2807.48, -1174.76, 1025.57),
(39, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 818.189, -509.708, 18.013, 446.99, 1397.07, 1084.3),
(40, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 743.227, -509.649, 18.013, 446.99, 1397.07, 1084.3),
(41, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 768.197, -503.778, 18.013, 377.15, 1417.41, 1081.33),
(42, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, -1061.29, -1195.54, 129.775, 377.15, 1417.41, 1081.33),
(43, 1, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 24.048, -2646.66, 40.464, 446.99, 1397.07, 1084.3),
(44, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, -2161.16, -2535.5, 31.816, 2237.59, -1081.64, 1049.02),
(45, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 2245.49, -121.874, 28.154, 2807.48, -1174.76, 1025.57),
(46, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 2548.77, 25.015, 27.676, 2237.59, -1081.64, 1049.02),
(47, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 1846.26, 741.142, 11.461, 2807.48, -1174.76, 1025.57),
(48, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2178.03, 655.525, 11.461, 377.15, 1417.41, 1081.33),
(49, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 2186.49, 1113.68, 12.648, 225.68, 1021.45, 1084.02),
(50, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 2238.55, 1285.76, 10.82, -2636.68, 1402.55, 906.46),
(51, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 1566.53, 23.279, 24.164, 2237.59, -1081.64, 1049.02),
(52, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1319.19, 1249.83, 10.82, 140.17, 1366.07, 1083.65),
(53, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 2017.74, 1912.98, 12.326, -2636.68, 1402.55, 906.46),
(54, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 1548.86, 2125.65, 11.461, 2237.59, -1081.64, 1049.02),
(55, 0, 0, 'AdmBot', 'localhost.ro', 7, 0, 5000, 1, 0, 0, 7, 0, 1456.68, 2773.42, 10.82, 225.68, 1021.45, 1084.02),
(56, 1, 0, 'AdmBot', 'localhost.ro', 8, 0, 5000, 1, 0, 0, 7, 0, 1664.71, 2846.08, 10.827, 2807.48, -1174.76, 1025.57),
(57, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 2634.08, 1824.21, 11.023, 140.17, 1366.07, 1083.65),
(58, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 2226.74, 1838.75, 10.82, -2636.68, 1402.55, 906.46),
(59, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2012.29, 920.758, 10.82, 387.22, 1471.7, 1080.19),
(60, 0, 0, 'AdmBot', 'localhost.ro', 3, 0, 5000, 1, 0, 0, 7, 0, 2627.96, 2348.84, 10.82, -2636.68, 1402.55, 906.46),
(61, 2, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 2086.91, 2153.8, 10.82, 387.22, 1471.7, 1080.19),
(62, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1965.51, 1623.1, 12.863, 140.17, 1366.07, 1083.65),
(63, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 1952.21, 1342.92, 15.375, 140.17, 1366.07, 1083.65),
(64, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 2007.64, 1167.3, 10.82, 140.17, 1366.07, 1083.65),
(65, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 2302.13, 1283.38, 67.469, 140.17, 1366.07, 1083.65),
(66, 0, 0, 'AdmBot', 'localhost.ro', 5, 0, 5000, 1, 0, 0, 7, 0, 2561.09, 1561.81, 10.82, 140.17, 1366.07, 1083.65),
(67, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 2315.92, 1801.54, 10.82, 2237.59, -1081.64, 1049.02),
(68, 2, 0, 'AdmBot', 'localhost.ro', 2, 0, 5000, 1, 0, 0, 7, 0, 1641.16, 2044.94, 11.32, 2237.59, -1081.64, 1049.02),
(69, 1, 0, 'AdmBot', 'localhost.ro', 15, 0, 5000, 1, 0, 0, 7, 0, 1274.45, 2522.38, 10.82, 377.15, 1417.41, 1081.33);

-- --------------------------------------------------------

--
-- Table structure for table `house_mapping`
--

CREATE TABLE `house_mapping` (
  `ID` int(11) NOT NULL,
  `Model` int(11) NOT NULL,
  `House` int(11) NOT NULL,
  `Type` int(11) NOT NULL,
  `X` float NOT NULL,
  `Y` float NOT NULL,
  `Z` float NOT NULL,
  `RotX` float NOT NULL,
  `RotY` float NOT NULL,
  `RotZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `log_admin`
--

CREATE TABLE `log_admin` (
  `ID` int(11) NOT NULL,
  `playerId` int(11) NOT NULL,
  `log_text` varchar(144) NOT NULL,
  `log_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `unixtime` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `log_admin`
--

INSERT INTO `log_admin` (`ID`, `playerId`, `log_text`, `log_time`, `unixtime`) VALUES
(1, 1, '[cmd:mute-log] Admin ionchyAdv (userId: 1) muted ionchyAdv (userId: 1) for 1 minutes.', '2023-09-21 16:00:52', 0),
(2, 1, '[cmd:mute-log] Admin ionchyAdv (userId: 1) muted ionchyAdv (userId: 1) for 123 minutes.', '2023-09-21 16:04:51', 0),
(3, 1, '[cmd:mute-log] Admin ionchyAdv (userId: 1) muted ionchyAdv (userId: 1) for 123 minutes.', '2023-09-21 16:05:10', 0),
(4, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 123123.', '2023-09-21 16:08:24', 0),
(5, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ireplay (userId: 5) health to 0.', '2023-09-21 19:19:43', 1695323983),
(6, 1, '[cmd:fnc] Admin ionchyAdv (userId: 1) forced ionchyAdv (userId: 1) to change his name - reason: nume inadecvat.', '2023-09-23 17:40:49', 1695490849),
(7, 1, '[cmd:fnc] Admin ionchyAdv (userId: 1) forced ionchyAdv (userId: 1) to change his name - reason: prea prost.', '2023-09-23 17:46:31', 1695491191),
(8, 1, '[cmd:cn] Admin ionchyAdv (userId: 1) canceled ionchyAdv (userId: 1) name request.', '2023-09-23 17:47:04', 1695491224),
(9, 1, '[cmd:fnc] Admin ionchyAdv (userId: 1) forced ionchyAdv (userId: 1) to change his name - reason: Redtimes.', '2023-09-23 17:50:50', 1695491450),
(10, 1, '[cmd:fnc] Admin ionchyAdv (userId: 1) forced iDreamer (userId: 2) to change his name - reason: test.', '2023-09-23 17:52:05', 1695491525),
(11, 1, '[cmd:an] Admin ionchyAdv (userId: 1) changed iDreamer (userId: 2) nickname.', '2023-09-23 17:52:24', 1695491544),
(12, 1, '[cmd:fnc] Admin ionchyAdv (userId: 1) forced ionchyAdv (userId: 1) to change his name - reason: test.', '2023-09-24 15:00:52', 1695567652),
(13, 1, '[cmd:an] Admin ionchyAdv (userId: 1) changed ionchyAdv (userId: 1) nickname.', '2023-09-24 15:01:00', 1695567660),
(14, 1, '[cmd:fnc] Admin alx (userId: 1) forced alx (userId: 1) to change his name - reason: mgk.', '2023-09-24 15:01:23', 1695567683),
(15, 1, '[cmd:cn] Admin alx (userId: 1) canceled alx (userId: 1) name request.', '2023-09-24 15:02:57', 1695567777),
(16, 1, '[cmd:fnc] Admin alx (userId: 1) forced alx (userId: 1) to change his name - reason: test.', '2023-09-24 15:03:25', 1695567805),
(17, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 1.', '2023-09-24 17:28:43', 1695576523),
(18, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 999999999.', '2023-09-24 17:28:48', 1695576528),
(19, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 2000000000.', '2023-09-24 17:28:55', 1695576535),
(20, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 111.', '2023-10-07 16:57:51', 1696697871),
(21, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 5000.', '2023-10-07 16:57:55', 1696697875),
(22, 1, '[cmd:set-log] Admin ionchyAdv (userId: 1) updated ionchyAdv (userId: 1) money to 1012312.', '2023-10-07 17:08:12', 1696698492);

-- --------------------------------------------------------

--
-- Table structure for table `namechanges`
--

CREATE TABLE `namechanges` (
  `namechangeid` int(11) NOT NULL,
  `userid` int(11) NOT NULL,
  `oldname` varchar(30) NOT NULL,
  `newname` varchar(30) NOT NULL,
  `adminid` int(11) NOT NULL,
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `namechanges`
--

INSERT INTO `namechanges` (`namechangeid`, `userid`, `oldname`, `newname`, `adminid`, `time`) VALUES
(1, 34, 'bgood.ro', 'hai pe bgood 20:00', 2, '2021-02-13 17:17:22'),
(2, 1, 'ionchyAdv', 'ionutzAdv', 1, '2021-02-15 08:18:37'),
(3, 2, 'Sandu', '1stSandu', 2, '2021-02-15 13:23:18'),
(4, 59, 'zews@daucucod', 'zewsAdv', 1, '2021-02-15 14:24:38'),
(5, 9, 'Gabriell', 'iReplay', 2, '2021-02-15 18:35:46'),
(6, 92, 'ELSMEKERiTOrply', 'rply', 4, '2021-02-15 21:09:08'),
(7, 77, 'Nicusor7', 'PredauMagie', 1, '2021-02-16 14:16:14'),
(8, 2, '1stSandu', 'alzx', 2, '2021-02-16 14:36:10'),
(9, 2, 'alzx', 'Sandu', 2, '2021-02-16 14:36:36'),
(10, 202, 'D.N.S_YT', 'S.T.E.F.A.N_YT', 7, '2021-02-17 10:17:43'),
(11, 303, 'ZoMottan', 'ZzMotanZz', 4, '2021-02-19 18:57:54'),
(12, 46, 'Damian4ik', 'Mos.Craciun', 104, '2021-02-21 14:05:21'),
(13, 2, 'iDreamer', 'idreamerr', 1, '0000-00-00 00:00:00'),
(14, 1, 'ionchyAdv', 'alx', 1, '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `playerlogs`
--

CREATE TABLE `playerlogs` (
  `ID` int(11) NOT NULL,
  `playerid` int(11) NOT NULL,
  `giverid` int(11) NOT NULL,
  `action` varchar(128) NOT NULL,
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `playerlogs`
--

INSERT INTO `playerlogs` (`ID`, `playerid`, `giverid`, `action`, `time`) VALUES
(1, 2, 1, 'iDreamer [user: 2] changed his nickname to idreamerr - Admin ionchyAdv [admin:1]', '0000-00-00 00:00:00'),
(2, 1, 1, 'ionchyAdv [user: 1] changed his nickname to alx - Admin ionchyAdv [admin:1]', '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `punishlogs`
--

CREATE TABLE `punishlogs` (
  `id` int(11) NOT NULL,
  `playerid` int(11) NOT NULL,
  `giverid` int(11) NOT NULL,
  `playername` varchar(30) NOT NULL,
  `givername` varchar(30) NOT NULL,
  `complaintid` int(11) NOT NULL DEFAULT 0,
  `actionid` int(11) NOT NULL,
  `actiontime` int(11) NOT NULL DEFAULT 0,
  `reason` varchar(128) NOT NULL,
  `time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `unixtime` int(11) NOT NULL DEFAULT 0,
  `deleted` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) DEFAULT NULL,
  `name` varchar(24) DEFAULT NULL,
  `password` varchar(32) DEFAULT NULL,
  `Email` varchar(32) NOT NULL DEFAULT 'email@yahoo.com',
  `RegisterDate` varchar(24) NOT NULL DEFAULT '1996-01-01 00:00:00',
  `Language` int(11) DEFAULT NULL,
  `Age` int(11) DEFAULT NULL,
  `Sex` int(11) DEFAULT NULL,
  `Model` int(11) DEFAULT NULL,
  `Tutorial` int(11) DEFAULT NULL,
  `lastOn` varchar(24) NOT NULL DEFAULT '1996-01-01 00:00:00 ',
  `Status` int(11) DEFAULT NULL,
  `Level` int(11) NOT NULL DEFAULT 1,
  `Respect` int(11) DEFAULT NULL,
  `Money` int(11) NOT NULL DEFAULT 500000,
  `Bank` int(11) NOT NULL DEFAULT 1000000,
  `BankLY` int(11) DEFAULT NULL,
  `Admin` int(11) DEFAULT NULL,
  `Helper` int(11) DEFAULT NULL,
  `Member` int(11) DEFAULT NULL,
  `Rank` int(11) DEFAULT NULL,
  `FWarn` int(11) DEFAULT NULL,
  `FPunish` int(11) DEFAULT NULL,
  `FactionJoin` int(11) DEFAULT NULL,
  `FactionTime` int(11) DEFAULT NULL,
  `CarLic` int(11) DEFAULT NULL,
  `CarLicSuspend` int(11) DEFAULT NULL,
  `GunLic` int(11) DEFAULT NULL,
  `GunLicSuspend` int(11) DEFAULT NULL,
  `FlyLic` int(11) DEFAULT NULL,
  `BoatLic` int(11) DEFAULT NULL,
  `House` int(11) DEFAULT NULL,
  `Business` int(11) DEFAULT NULL,
  `SpawnChange` int(11) DEFAULT NULL,
  `HUDOptions` varchar(24) NOT NULL DEFAULT '0 0 0 0 0 0 1 0 0 0 1 1',
  `Neons` varchar(24) NOT NULL DEFAULT '0 0 0 0 0 0',
  `Quest` varchar(24) NOT NULL DEFAULT '0 0 0',
  `QuestProgress` varchar(24) NOT NULL DEFAULT '0 0 0',
  `QuestNeed` varchar(24) NOT NULL DEFAULT '0 0 0',
  `Job` int(11) DEFAULT NULL,
  `JobSkill` varchar(72) NOT NULL DEFAULT '0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1',
  `JobTimes` varchar(128) NOT NULL DEFAULT '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0',
  `JobRem` varchar(128) NOT NULL DEFAULT '0 0 50 26 26 100 26 26 26 26 100 26 26 26 75 0 100 80',
  `PaydayTime` int(11) NOT NULL DEFAULT 3600,
  `WantedLevel` int(11) DEFAULT NULL,
  `Victim` varchar(32) DEFAULT NULL,
  `Accused` varchar(32) NOT NULL DEFAULT '********',
  `Crime1` varchar(32) NOT NULL DEFAULT 'Fara',
  `Crime2` varchar(32) NOT NULL DEFAULT 'Fara',
  `Crime3` varchar(32) NOT NULL DEFAULT 'Fara',
  `Muted` int(11) DEFAULT NULL,
  `MuteTime` int(11) DEFAULT NULL,
  `Pet` int(11) DEFAULT NULL,
  `PetLevel` int(11) NOT NULL DEFAULT 1,
  `PetStatus` int(11) NOT NULL DEFAULT 1,
  `PetPoints` int(11) DEFAULT NULL,
  `PetSkin` int(11) NOT NULL DEFAULT 19079,
  `PetName` varchar(32) DEFAULT NULL,
  `PremiumPoints` int(11) DEFAULT NULL,
  `CarSlots` int(11) NOT NULL DEFAULT 2
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

--
-- Indexes for dumped tables
--

--
-- Indexes for table `atms`
--
ALTER TABLE `atms`
  ADD PRIMARY KEY (`atmId`);

--
-- Indexes for table `bans`
--
ALTER TABLE `bans`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `bizz`
--
ALTER TABLE `bizz`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `cars`
--
ALTER TABLE `cars`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `emails`
--
ALTER TABLE `emails`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `factionlog`
--
ALTER TABLE `factionlog`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `factions`
--
ALTER TABLE `factions`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `faction_logs`
--
ALTER TABLE `faction_logs`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `houses`
--
ALTER TABLE `houses`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `house_mapping`
--
ALTER TABLE `house_mapping`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `log_admin`
--
ALTER TABLE `log_admin`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `namechanges`
--
ALTER TABLE `namechanges`
  ADD PRIMARY KEY (`namechangeid`);

--
-- Indexes for table `playerlogs`
--
ALTER TABLE `playerlogs`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `punishlogs`
--
ALTER TABLE `punishlogs`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `atms`
--
ALTER TABLE `atms`
  MODIFY `atmId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT for table `bans`
--
ALTER TABLE `bans`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `bizz`
--
ALTER TABLE `bizz`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=56;

--
-- AUTO_INCREMENT for table `cars`
--
ALTER TABLE `cars`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `emails`
--
ALTER TABLE `emails`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30;

--
-- AUTO_INCREMENT for table `factionlog`
--
ALTER TABLE `factionlog`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `faction_logs`
--
ALTER TABLE `faction_logs`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `houses`
--
ALTER TABLE `houses`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=70;

--
-- AUTO_INCREMENT for table `house_mapping`
--
ALTER TABLE `house_mapping`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_admin`
--
ALTER TABLE `log_admin`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `namechanges`
--
ALTER TABLE `namechanges`
  MODIFY `namechangeid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `playerlogs`
--
ALTER TABLE `playerlogs`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `punishlogs`
--
ALTER TABLE `punishlogs`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
