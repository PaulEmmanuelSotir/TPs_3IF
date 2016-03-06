-- Creation du lien vers la base de donnée centralisée et les autres sites

CREATE DATABASE LINK RYORI_LINK 
CONNECT TO pesotir IDENTIFIED BY mdporacle
USING 'DB1';

CREATE DATABASE LINK EUROPE_SUD_LINK 
CONNECT TO pesotir IDENTIFIED BY mdporacle
USING 'DB3';

CREATE DATABASE LINK EUROPE_NORD_LINK 
CONNECT TO pesotir IDENTIFIED BY mdporacle
USING 'DB2';

DROP DATABASE LINK EUROPE_NORD_LINK ;

-- Creation des tables d'amérique
create table PESOTIR.EMPLOYES as select * from RYORI.EMPLOYES@RYORI_LINK;

create table PESOTIR.Stock_Amerique as select * from RYORI.STOCK@RYORI_LINK
WHERE Pays IN  ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil,
              Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique,
              Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque,
              Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-
              Lucie', 'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela');
              
create table PESOTIR.Clients_Amerique as select * from RYORI.CLIENTS@RYORI_LINK
WHERE Pays IN ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil,
              Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique,
              Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque,
              Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-
              Lucie', 'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela');

create table PESOTIR.COMMANDES_AMERIQUE as select * from RYORI.COMMANDES@RYORI_LINK
WHERE CODE_CLIENT IN (SELECT CODE_CLIENT FROM PESOTIR.Clients_Amerique);

create table PESOTIR.DETAILS_COMMANDES_AMERIQUE as select * from RYORI.DETAILS_COMMANDES@RYORI_LINK
WHERE NO_COMMANDE IN (SELECT NO_COMMANDE FROM PESOTIR.COMMANDES_AMERIQUE);

-- Gestion des droits
GRANT SELECT, INSERT, UPDATE, DELETE
ON Clients_Amerique
TO GSARNETTE, FMACEROUSS;

GRANT SELECT, INSERT, UPDATE, DELETE
ON Stock_Amerique
TO GSARNETTE, FMACEROUSS;

GRANT SELECT
ON COMMANDES_AMERIQUE
TO GSARNETTE, FMACEROUSS;

GRANT SELECT
ON DETAILS_COMMANDES_AMERIQUE
TO GSARNETTE, FMACEROUSS;

GRANT SELECT
ON EMPLOYES
TO GSARNETTE, FMACEROUSS;

-- Vues
CREATE OR REPLACE VIEW Produits AS 
  SELECT *
  FROM fmacerouss.PRODUITS@EUROPE_SUD_LINK;
 
CREATE OR REPLACE  VIEW Categories AS 
   SELECT *
   FROM fmacerouss.CATEGORIES@EUROPE_SUD_LINK;

CREATE OR REPLACE VIEW FOURNISSEURS AS
   SELECT *
   FROM GSARNETTE.FOURNISSEURS@EUROPE_NORD_LINK;

CREATE OR REPLACE VIEW Clients AS 
   SELECT *
   FROM pesotir.Clients_Amerique
   WHERE Pays IN  ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil',
              'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique',
              'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque',
              'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-Lucie',
              'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela')
   UNION ALL
   select *
   FROM gsarnette.Clients_Europe_Nord@EUROPE_NORD_LINK
   WHERE Pays IN ('Norvège', 'Suède', 'Danemark', 'Islande', 'Finlande, Royaume-Uni', 'Irlande', 'Belgique', 
                  'Luxembourg', 'Pays-Bas', 'Allemagne', 'Pologne')
   UNION ALL
   select *
   FROM gsarnette.Clients_autre@EUROPE_NORD_LINK
   WHERE Pays IS NULL OR Pays NOT IN ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil',
              'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique',
              'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque',
              'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-Lucie',
              'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela', 'Espagne', 'Portugal', 'Andorre', 'France', 'Gibraltar', 'Italie', 'Saint-Marin', 'Vatican',
              'Malte', 'Albanie', 'Bosnie-Herzégovine', 'Croatie', 'Grèce', 'Macédoine', 'Monténégro', 'Serbie', 
              'Slovénie', 'Bulgarie', 'Norvège', 'Suède', 'Danemark', 'Islande', 'Finlande, Royaume-Uni', 'Irlande', 
              'Belgique', 'Luxembourg', 'Pays-Bas', 'Allemagne', 'Pologne')
   UNION ALL
   SELECT *
   FROM fmacerouss.CLIENTS_EUROPE_SUD@EUROPE_SUD_LINK
   WHERE Pays IN ('Espagne', 'Portugal', 'Andorre', 'France', 'Gibraltar', 'Italie', 'Saint-Marin', 'Vatican', 'Malte', 
                  'Albanie', 'Bosnie-Herzégovine', 'Croatie', 'Grèce', 'Macédoine',
                  'Monténégro', 'Serbie', 'Slovénie', 'Bulgarie');

CREATE VIEW Details_Commandes AS 
   SELECT *
   FROM pesotir.details_commandes_Amerique
   UNION ALL
   select *
   FROM gsarnette.details_commandes_Europe_Nord@EUROPE_NORD_LINK
   UNION ALL
   select *
   FROM gsarnette.details_commandes_autre@EUROPE_NORD_LINK
   UNION ALL
   SELECT *
   FROM fmacerouss.DETAILS_COMMANDES_EUROPE_SUD@EUROPE_SUD_LINK;

CREATE VIEW Commandes AS 
   SELECT *
   FROM pesotir.commandes_Amerique
   UNION ALL
   select *
   FROM gsarnette.commandes_Europe_Nord@EUROPE_NORD_LINK
   UNION ALL
   select *
   FROM gsarnette.commandes_autre@EUROPE_NORD_LINK
   UNION ALL 
   SELECT *
   FROM fmacerouss.COMMANDES_EUROPE_SUD@EUROPE_SUD_LINK;
   
CREATE OR REPLACE VIEW STOCK AS 
   SELECT *
   FROM pesotir.stock_Amerique
   WHERE Pays IN  ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil',
              'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique',
              'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque',
              'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-Lucie',
              'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela')
  UNION ALL 
   select *
   FROM gsarnette.stock_Europe_Nord@EUROPE_NORD_LINK
   WHERE Pays IN ('Norvège', 'Suède', 'Danemark', 'Islande', 'Finlande, Royaume-Uni', 'Irlande', 'Belgique',
                  'Luxembourg', 'Pays-Bas', 'Allemagne', 'Pologne')
   
  UNION ALL
   select *
   FROM gsarnette.Stock_autre@EUROPE_NORD_LINK
   WHERE Pays IS NULL OR Pays NOT IN ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil',
              'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique',
              'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaïque',
              'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nievès', 'Sainte-Lucie',
              'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
              'Venezuela', 'Espagne', 'Portugal', 'Andorre', 'France', 'Gibraltar', 'Italie', 'Saint-Marin', 'Vatican',
              'Malte', 'Albanie', 'Bosnie-Herzégovine', 'Croatie', 'Grèce', 'Macédoine', 'Monténégro', 'Serbie', 
              'Slovénie', 'Bulgarie', 'Norvège', 'Suède', 'Danemark', 'Islande', 'Finlande, Royaume-Uni', 'Irlande', 
              'Belgique', 'Luxembourg', 'Pays-Bas', 'Allemagne', 'Pologne')
              
  UNION ALL
   SELECT *
   FROM fmacerouss.STOCK_EUROPE_SUD@EUROPE_SUD_LINK
   WHERE Pays IN ('Espagne', 'Portugal', 'Andorre', 'France', 'Gibraltar', 'Italie', 'Saint-Marin', 'Vatican', 'Malte', 
                  'Albanie', 'Bosnie-Herzégovine', 'Croatie', 'Grèce', 'Macédoine',
                  'Monténégro', 'Serbie', 'Slovénie', 'Bulgarie');
                  
-- Contraintes
ALTER TABLE CLIENTS_AMERIQUE ADD CONSTRAINT PK_CLIENTS PRIMARY KEY (CODE_CLIENT);
ALTER TABLE COMMANDES_AMERIQUE ADD CONSTRAINT PK_COMMANDES PRIMARY KEY (NO_COMMANDE);
ALTER TABLE DETAILS_COMMANDES_AMERIQUE ADD CONSTRAINT PK_DETAILS_COMMANDES PRIMARY KEY (NO_COMMANDE, REF_PRODUIT);
ALTER TABLE EMPLOYES ADD CONSTRAINT PK_EMPLOYES PRIMARY KEY (NO_EMPLOYE);

ALTER TABLE COMMANDES_AMERIQUE ADD CONSTRAINT FK_COMMANDE_CLIENTS  
FOREIGN KEY (CODE_CLIENT) REFERENCES CLIENTS_AMERIQUE (CODE_CLIENT);

ALTER TABLE COMMANDES_AMERIQUE ADD CONSTRAINT FK_COMMANDE_EMPLOYES 
FOREIGN KEY (NO_EMPLOYE) REFERENCES EMPLOYES (NO_EMPLOYE);

ALTER TABLE DETAILS_COMMANDES_AMERIQUE ADD CONSTRAINT FK_DETAILS_COMMANDES_COMMANDES 
FOREIGN KEY (NO_COMMANDE) REFERENCES COMMANDES_AMERIQUE (NO_COMMANDE);

--ALTER TABLE DETAILS_COMMANDES_AMERIQUE ADD CONSTRAINT FK_DETAILS_COMMANDES_PRODUITS
--FOREIGN KEY (REF_PRODUIT) REFERENCES FMACEROUSS.PRODUITS@EUROPE_SUD_LINK (REF_PRODUIT);

--ALTER TABLE DETAILS_COMMANDES_AMERIQUE ADD CONSTRAINT FK_DETAILS_PRODUITS_PRODUITS 
--FOREIGN KEY (REF_PRODUIT) REFERENCES FMACEROUSS.PRODUITS@EUROPE_SUD_LINK (REF_PRODUIT);

ALTER TABLE EMPLOYES ADD CONSTRAINT FK_EMPLOYES_EMPLOYES 
FOREIGN KEY (REND_COMPTE) REFERENCES EMPLOYES (NO_EMPLOYE);

-- Tests de requettes
select * from clients;
select * from clients where pays in ('Bresil', 'Etats-Unis');
select * from clients_Amerique;

SELECT * FROM GSARNETTE.FOURNISSEURS@EUROPE_NORD_LINK;

select * from gsarnette.clients_europe_nord@europe_nord_link;

SELECT * FROM FMACEROUSS.PRODUITS@EUROPE_SUD_LINK;

-- Vues materialisées
CREATE MATERIALIZED VIEW LOG ON EMPLOYES;
GRANT SELECT ON MLOG$_EMPLOYES TO gsarnette;

CREATE MATERIALIZED VIEW Fournisseurs
REFRESH COMPLETE
NEXT sysdate + (1/24/60)
AS 
SELECT *
FROM GSARNETTE.FOURNISSEURS@EUROPE_NORD_LINK;

CREATE MATERIALIZED VIEW Categories
REFRESH COMPLETE
NEXT sysdate + (1/24/60)
AS 
SELECT *
FROM fmacerouss.CATEGORIES@EUROPE_SUD_LINK;

CREATE MATERIALIZED VIEW Produits
REFRESH FAST
NEXT sysdate + (1/24/60)
AS SELECT *
FROM fmacerouss.PRODUITS@EUROPE_SUD_LINK;
