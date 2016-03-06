CREATE OR REPLACE PROCEDURE accessGrant
        ( userTarget IN varchar2 )
is
  -- curseur pour parcourir toutes les tables
  cursor tableU is ( SELECT *
                     FROM user_tables
                   );
BEGIN
  for t in tableU 
  loop 
      EXECUTE IMMEDIATE 'GRANT SELECT ON ' || t.table_name || ' TO ' || userTarget;
  end loop;
  
  DBMS_OUTPUT.PUT_LINE('droits sur toutes les tables à l utilisateur : ' || userTarget) ;
end;



