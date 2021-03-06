-- MySQL Script generated by MySQL Workbench
-- Sun Jan 19 12:06:18 2020
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema WeatherStation
-- -----------------------------------------------------
-- Estación meteorológica de la URJC

-- -----------------------------------------------------
-- Schema WeatherStation
--
-- Estación meteorológica de la URJC
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `WeatherStation` DEFAULT CHARACTER SET latin1 COLLATE latin1_spanish_ci ;
USE `WeatherStation` ;

-- -----------------------------------------------------
-- Table `WeatherStation`.`data`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `WeatherStation`.`data` (
  `id` INT(11) NOT NULL,
  `stime` TIMESTAMP NOT NULL,
  `loctime` TIMESTAMP NULL,
  `localizacion_id` VARCHAR(45) NOT NULL,
  `samplefreq` INT NULL,
  `humedad` FLOAT NULL,
  `presion` FLOAT NULL,
  `temperatura` FLOAT NULL,
  `direccion_viento` FLOAT NULL,
  `velocidad_viento` FLOAT NULL,
  `lluvia` FLOAT NULL,
  `rssi` DECIMAL NULL,
  UNIQUE INDEX `id_UNIQUE` (`id` ASC),
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
