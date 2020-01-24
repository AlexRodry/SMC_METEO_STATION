-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 24-01-2020 a las 22:39:22
-- Versión del servidor: 10.1.37-MariaDB-0+deb9u1
-- Versión de PHP: 7.0.33-0+deb9u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `WeatherStation`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `datos`
--

CREATE TABLE `datos` (
  `idDatos` int(11) NOT NULL,
  `station` varchar(45) COLLATE utf8_spanish2_ci NOT NULL,
  `stime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `loctime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `samplfreq` int(11) DEFAULT NULL,
  `temperatura` float DEFAULT NULL,
  `humedad` float DEFAULT NULL,
  `presion` float DEFAULT NULL,
  `lluvia` float DEFAULT NULL,
  `direccion_viento` float DEFAULT NULL,
  `velocidad_viento` float DEFAULT NULL,
  `rssi` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish2_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `endpoints`
--

CREATE TABLE `endpoints` (
  `id` int(11) NOT NULL,
  `endp_id` int(11) NOT NULL,
  `endp_address` varchar(45) COLLATE utf8_spanish2_ci NOT NULL,
  `typeCom` varchar(45) COLLATE utf8_spanish2_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish2_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `localizacion`
--

CREATE TABLE `localizacion` (
  `idLoc` int(11) NOT NULL,
  `locSt` varchar(45) COLLATE utf8_spanish2_ci NOT NULL,
  `dataId` int(11) NOT NULL,
  `longitud` double DEFAULT NULL,
  `latitud` double DEFAULT NULL,
  `altitud` double DEFAULT NULL,
  `red` varchar(45) COLLATE utf8_spanish2_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish2_ci;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `datos`
--
ALTER TABLE `datos`
  ADD PRIMARY KEY (`idDatos`);

--
-- Indices de la tabla `endpoints`
--
ALTER TABLE `endpoints`
  ADD PRIMARY KEY (`id`),
  ADD KEY `endp_id` (`endp_id`);

--
-- Indices de la tabla `localizacion`
--
ALTER TABLE `localizacion`
  ADD PRIMARY KEY (`idLoc`),
  ADD KEY `dataId` (`dataId`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `datos`
--
ALTER TABLE `datos`
  MODIFY `idDatos` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT de la tabla `endpoints`
--
ALTER TABLE `endpoints`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT de la tabla `localizacion`
--
ALTER TABLE `localizacion`
  MODIFY `idLoc` int(11) NOT NULL AUTO_INCREMENT;
--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `endpoints`
--
ALTER TABLE `endpoints`
  ADD CONSTRAINT `endpoints_ibfk_1` FOREIGN KEY (`endp_id`) REFERENCES `localizacion` (`idLoc`);

--
-- Filtros para la tabla `localizacion`
--
ALTER TABLE `localizacion`
  ADD CONSTRAINT `localizacion_ibfk_1` FOREIGN KEY (`dataId`) REFERENCES `datos` (`idDatos`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
