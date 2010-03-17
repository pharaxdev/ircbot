DROP TABLE IF EXISTS `sznap`;
CREATE TABLE `sznap` (
  `guid` int(10) unsigned NOT NULL auto_increment,
  `nev` varchar(21) NOT NULL default '',
  `honap` varchar(21) NOT NULL default '',
  `nap` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=75 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `sznap` VALUES ('1', 'Csaba', 'Szeptember', '6');
INSERT INTO `sznap` VALUES ('2', 'Tomi', 'Aprilis', '7');
INSERT INTO `sznap` VALUES ('3', 'Mark', 'November', '10');