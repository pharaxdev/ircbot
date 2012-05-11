DROP TABLE IF EXISTS `xrev`;
CREATE TABLE `xrev` (
  `guid` int(10) unsigned NOT NULL auto_increment,
  `emu` varchar(21) NOT NULL default '',
  `rev` tinyint(3) unsigned NOT NULL,
  `irta` varchar(21) NOT NULL default '',
  `szoveg` text NOT NULL default '',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=75 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `xrev` VALUES ('1', 'ascnhalf', '1', 'scymex', 'Welcome to new SVN!');
INSERT INTO `xrev` VALUES ('2', 'ascnhalf', '2', 'megaxx', 'delete svn_revision.h');
INSERT INTO `xrev` VALUES ('3', 'ascnhalf', '3', 'scymex', 'Boost: PART 1');
INSERT INTO `xrev` VALUES ('4', 'ascnhalf', '4', 'scymex', 'Boost: PART 2');
INSERT INTO `xrev` VALUES ('5', 'ascnhalf', '5', 'scymex', 'Boost: PART 3');
INSERT INTO `xrev` VALUES ('6', 'ascnhalf', '6', 'scymex', 'Boost: PART 4');
INSERT INTO `xrev` VALUES ('7', 'ascnhalf', '7', 'megaxx', '3.3.x');
INSERT INTO `xrev` VALUES ('8', 'ascnhalf', '8', 'Twl', '* Fix build.');
INSERT INTO `xrev` VALUES ('9', 'ascnhalf', '9', 'Twl', '* Fix build for scripts.');
INSERT INTO `xrev` VALUES ('10', 'ascnhalf', '10', 'Prometheusz', 'some SOTA fix: - WorldStates - options for second round - etc... todo: graveyard banners, spiritguids started to write IOC...');
INSERT INTO `xrev` VALUES ('11', 'ascnhalf', '11', 'Twl', '* Fix compile error in scripts related to different compiler versions.');
INSERT INTO `xrev` VALUES ('12', 'ascnhalf', '12', 'megaxx', 'test 3.3.0a');
INSERT INTO `xrev` VALUES ('13', 'ascnhalf', '13', 'megaxx', 'update UpdateFields.h');
INSERT INTO `xrev` VALUES ('14', 'ascnhalf', '14', 'Twl', '* Fix build in 3.3.0 branch.');
INSERT INTO `xrev` VALUES ('15', 'ascnhalf', '15', 'Twl', '* Fix build again. * Forgot to commit these.');
INSERT INTO `xrev` VALUES ('16', 'ascnhalf', '16', 'scymex', 'Add web shortcut ^^ SorryXD');
INSERT INTO `xrev` VALUES ('17', 'ascnhalf', '17', 'Twl', '* Didn t wanted to commit these yet :)');
INSERT INTO `xrev` VALUES ('18', 'ascnhalf', '18', 'megaxx', 'test');
INSERT INTO `xrev` VALUES ('19', 'ascnhalf', '19', 'megaxx', 'fix: pointer');
INSERT INTO `xrev` VALUES ('20', 'ascnhalf', '20', 'Twl', '* Fix build(link) for the SOTA relic script.');
INSERT INTO `xrev` VALUES ('21', 'ascnhalf', '21', 'Twl', '* Fix warnings related to the dll interface is derived from a class which is not exported.');
INSERT INTO `xrev` VALUES ('22', 'ascnhalf', '22', 'megaxx', 'fix: relic id');
INSERT INTO `xrev` VALUES ('23', 'ascnhalf', '23', 'Twl', '* Add SOTA s relic GO script.');
INSERT INTO `xrev` VALUES ('24', 'ascnhalf', '24', 'Twl', '* Add some debugging output to locate the crash.');
INSERT INTO `xrev` VALUES ('25', 'ascnhalf', '25', 'megaxx', 'fix: - creature faction');
INSERT INTO `xrev` VALUES ('26', 'ascnhalf', '26', 'scymex', '+Add plus flags');
INSERT INTO `xrev` VALUES ('27', 'ascnhalf', '27', 'Prometheusz', 'fixed ioc battlemaster script');
INSERT INTO `xrev` VALUES ('28', 'ascnhalf', '28', 'megaxx', 'fix: - Vehicle Action bar - Demolisher faction add: SpawnVehicle');
INSERT INTO `xrev` VALUES ('29', 'ascnhalf', '29', 'Prometheusz', 'Added some IOC stuff: - added gates - added teleporters - added controlpoints - added const graveyards + spirit guids - added demolishersalesmen ToDo: - fix controlpoint goids - fix vehicles Spawns - fix loser, winner spell - fix gunships!');
INSERT INTO `xrev` VALUES ('30', 'ascnhalf', '30', 'Prometheusz', 'Added some IOC gobject - fixed duplicate...');
INSERT INTO `xrev` VALUES ('31', 'ascnhalf', '31', 'scymex', '');
INSERT INTO `xrev` VALUES ('32', 'ascnhalf', '32', 'scymex', '+Add logon-server build.');
INSERT INTO `xrev` VALUES ('33', 'ascnhalf', '33', 'megaxx', 'Added some IOC stuff: - added 2 demolisherLocations - added 2 Repop - added controlpoints ToDo: - fix controlpoint goids - fix worldstate');
INSERT INTO `xrev` VALUES ('34', 'ascnhalf', '34', 'Prometheusz', 'fixed the actionbar of vehicles ToDo: - fix spellbugs - fix vehicle spellcastbugs - fix powertypes - fix change seat in vehicle (added sql stuff)');
INSERT INTO `xrev` VALUES ('35', 'ascnhalf', '35', 'megaxx', '- shared ptr fix');
INSERT INTO `xrev` VALUES ('36', 'ascnhalf', '36', 'megaxx', 'Added licence');
INSERT INTO `xrev` VALUES ('37', 'ascnhalf', '37', 'Twl', '* Add implement shared pointers in our 3.3.0 branch. * There are currently 3 errors which are need to be resolved.');