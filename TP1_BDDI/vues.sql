 -- Vues

 -- Vue detail commandes
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

 -- Vue commandes
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
 
-- Vue stock
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

-- Vue Clients
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
