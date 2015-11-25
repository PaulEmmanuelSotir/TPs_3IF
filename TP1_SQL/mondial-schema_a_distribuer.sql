
ALTER SESSION SET NLS_DATE_FORMAT = 'DD MM SYYYY';
-- SYYYY means 4-digit-year, S prefixes BC years with "-"

CREATE TABLE Country
(Name VARCHAR2(32),
 Code VARCHAR2(4) CONSTRAINT CountryKey PRIMARY KEY,
 Capital VARCHAR2(35),
 Province VARCHAR2(32),
 Area NUMBER ,
 Population NUMBER );

CREATE TABLE City
(Name VARCHAR2(35),
 Country VARCHAR2(4),
 Province VARCHAR2(32),
 Population NUMBER, 
 Longitude NUMBER, 
 Latitude NUMBER ,
 CONSTRAINT CityKey PRIMARY KEY (Name, Country, Province));

CREATE TABLE Province
(Name VARCHAR2(32) ,
 Country  VARCHAR2(4) ,
 Population NUMBER ,
 Area NUMBER ,
 Capital VARCHAR2(35),
 CapProv VARCHAR2(32),
 CONSTRAINT PrKey PRIMARY KEY (Name, Country));

CREATE TABLE Economy
(Country VARCHAR2(4) CONSTRAINT EconomyKey PRIMARY KEY,
 GDP NUMBER ,
 Agriculture NUMBER,
 Service NUMBER,
 Industry NUMBER,
 Inflation NUMBER);

CREATE TABLE Population
(Country VARCHAR2(4) CONSTRAINT PopKey PRIMARY KEY,
 Population_Growth NUMBER,
 Infant_Mortality NUMBER);

CREATE TABLE Politics
(Country VARCHAR2(4) CONSTRAINT PoliticsKey PRIMARY KEY,
 Independence DATE,
 Government VARCHAR2(120));

CREATE TABLE Language
(Country VARCHAR2(4),
 Name VARCHAR2(50),
 Percentage NUMBER ,
 CONSTRAINT LanguageKey PRIMARY KEY (Name, Country));

CREATE TABLE Religion
(Country VARCHAR2(4),
 Name VARCHAR2(50),
 Percentage NUMBER ,
 CONSTRAINT ReligionKey PRIMARY KEY (Name, Country));

CREATE TABLE Ethnic_Group
(Country VARCHAR2(4),
 Name VARCHAR2(50),
 Percentage NUMBER  ,
 CONSTRAINT EthnicKey PRIMARY KEY (Name, Country));

CREATE TABLE Continent
(Name VARCHAR2(20) CONSTRAINT ContinentKey PRIMARY KEY,
 Area NUMBER(10));

CREATE TABLE Borders
(Country1 VARCHAR2(4),
 Country2 VARCHAR2(4),
 Length NUMBER  );

CREATE TABLE encompasses
(Country VARCHAR2(4) NOT NULL,
 Continent VARCHAR2(20) NOT NULL,
 Percentage NUMBER,
  CONSTRAINT EncompassesKey PRIMARY KEY (Country,Continent));

CREATE TABLE Organization
(Abbreviation VARCHAR2(12) PRIMARY KEY,
 Name VARCHAR2(80) NOT NULL,
 City VARCHAR2(35) ,
 Country VARCHAR2(4) , 
 Province VARCHAR2(32) ,
 Established DATE,
 CONSTRAINT OrgNameUnique UNIQUE (Name));

CREATE TABLE is_member
(Country VARCHAR2(4),
 Organization VARCHAR2(12),
 Type VARCHAR2(30) DEFAULT 'member',
 CONSTRAINT MemberKey PRIMARY KEY (Country,Organization) );

CREATE OR REPLACE TYPE GeoCoord AS OBJECT
(Longitude NUMBER,
 Latitude NUMBER);
/

CREATE TABLE Mountain
(Name VARCHAR2(20) CONSTRAINT MountainKey PRIMARY KEY,
 Height NUMBER CONSTRAINT MountainHeight
     CHECK (Height >= 0),
 Coordinates GeoCoord );

CREATE TABLE Desert
(Name VARCHAR2(25) CONSTRAINT DesertKey PRIMARY KEY,
 Area NUMBER);

CREATE TABLE Island
(Name VARCHAR2(25) CONSTRAINT IslandKey PRIMARY KEY,
 Islands VARCHAR2(25),
 Area NUMBER CONSTRAINT IslandAr
  check ((Area >= 0) and (Area <= 2175600)) ,
 Coordinates GeoCoord );

CREATE TABLE Lake
(Name VARCHAR2(25) CONSTRAINT LakeKey PRIMARY KEY,
 Area NUMBER CONSTRAINT LakeAr CHECK (Area >= 0));

CREATE TABLE Sea
(Name VARCHAR2(25) CONSTRAINT SeaKey PRIMARY KEY,
 Depth NUMBER CONSTRAINT SeaDepth CHECK (Depth >= 0));

CREATE TABLE River
(Name VARCHAR2(20) CONSTRAINT RiverKey PRIMARY KEY,
 River VARCHAR2(20),
 Lake VARCHAR2(20),
 Sea VARCHAR2(25),
 Length NUMBER );

CREATE TABLE geo_Mountain
(Mountain VARCHAR2(20) ,
 Country VARCHAR2(4) ,
 Province VARCHAR2(32) ,
 CONSTRAINT GMountainKey PRIMARY KEY (Province,Country,Mountain) );

CREATE TABLE geo_Desert
(Desert VARCHAR2(25) ,
 Country VARCHAR2(4) ,
 Province VARCHAR2(32) ,
 CONSTRAINT GDesertKey PRIMARY KEY (Province, Country, Desert) );

CREATE TABLE geo_Island
(Island VARCHAR2(25) , 
 Country VARCHAR2(4) ,
 Province VARCHAR2(32) ,
 CONSTRAINT GIslandKey PRIMARY KEY (Province, Country, Island) );

CREATE TABLE geo_River
(River VARCHAR2(20) , 
 Country VARCHAR2(4) ,
 Province VARCHAR2(32) ,
 CONSTRAINT GRiverKey PRIMARY KEY (Province ,Country, River) );

CREATE TABLE geo_Sea
(Sea VARCHAR2(25) ,
 Country VARCHAR2(4)  ,
 Province VARCHAR2(32) ,
 CONSTRAINT GSeaKey PRIMARY KEY (Province, Country, Sea) );

CREATE TABLE geo_Lake
(Lake VARCHAR2(25) ,
 Country VARCHAR2(4) ,
 Province VARCHAR2(32) ,
 CONSTRAINT GLakeKey PRIMARY KEY (Province, Country, Lake) );

CREATE TABLE merges_with
(Sea1 VARCHAR2(25) ,
 Sea2 VARCHAR2(25) ,
 CONSTRAINT MergesWithKey PRIMARY KEY (Sea1,Sea2) );

CREATE TABLE located
(City VARCHAR2(35) ,
 Province VARCHAR2(32) ,
 Country VARCHAR2(4) ,
 River VARCHAR2(20),
 Lake VARCHAR2(25),
 Sea VARCHAR2(25));
